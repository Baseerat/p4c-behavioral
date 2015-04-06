#include <assert.h>
#include <pthread.h>

#include "pkt_manager.h"
#include "pipeline.h"
#include "parser.h"
#include "deparser.h"
#include "queuing.h"
#include "mirroring_internal.h"
#include "rmt_internal.h"
#include "enums.h"
#include "lf.h"

#include <p4utils/circular_buffer.h>

#define TRANSMIT_CB_SIZE 1024

circular_buffer_t *rmt_transmit_cb; /* only 1 */

pthread_t pkt_out_thread;

uint64_t packet_id;

typedef struct transmit_pkt_s {
  buffered_pkt_t pkt;
  int egress;
  int ingress;
} transmit_pkt_t;

int pkt_manager_receive(int ingress, void *pkt, int len) {
  void *pkt_data = malloc(len);
  memcpy(pkt_data, pkt, len);
  ++packet_id;
  ingress_pipeline_receive(ingress, NULL, NULL,
			   pkt_data, len, packet_id,
			   PKT_INSTANCE_TYPE_NORMAL);
  return 0;
}

int pkt_manager_transmit(int egress, void *pkt, int len, uint64_t packet_id, int ingress) {
  transmit_pkt_t *t_pkt = malloc(sizeof(transmit_pkt_t));
  buffered_pkt_t *b_pkt = &t_pkt->pkt;
  t_pkt->egress = egress;
  t_pkt->ingress = ingress;
  b_pkt->pkt_data = pkt;
  b_pkt->pkt_len = len;
  cb_write(rmt_transmit_cb, t_pkt);
  return 0;
}

static void *pkt_out_loop(void *arg) {
  while(1) {
    transmit_pkt_t *t_pkt = (transmit_pkt_t *) cb_read(rmt_transmit_cb);
    buffered_pkt_t *b_pkt = &t_pkt->pkt;
    RMT_LOG(P4_LOG_LEVEL_TRACE, "outgoing thread: packet dequeued\n");
    if(rmt_instance->tx_fn) {
      RMT_LOG(P4_LOG_LEVEL_VERBOSE,
	      "outgoing thread: sending pkt out of port %d\n",
	      t_pkt->egress);
      rmt_instance->tx_fn(t_pkt->egress, b_pkt->pkt_data, b_pkt->pkt_len, t_pkt->ingress);
    }
    free(b_pkt->pkt_data);
    free(t_pkt);
  }
  return NULL;
}

void pkt_manager_init(void) {
  rmt_transmit_cb = cb_init(TRANSMIT_CB_SIZE, CB_WRITE_BLOCK, CB_READ_BLOCK);

  packet_id = 0;

  lf_init();

  ingress_pipeline_init();

  queuing_init();

  mirroring_init();

  egress_pipeline_init();

  pthread_create(&pkt_out_thread, NULL,
		 pkt_out_loop, NULL); 
}
