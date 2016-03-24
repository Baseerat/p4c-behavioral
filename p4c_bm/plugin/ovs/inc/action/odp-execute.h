/*
 * Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * File:   odp-execute.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_ODP_EXECUTE_H
#define	OVS_ACTION_ODP_EXECUTE_H 1

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_FUNCS \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ACTIONS_CASES \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_REQUIRES_DATAPATH_ASSISTANCE_CASES \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_CALC_FIELDS_SRCS_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case OVS_CALC_FIELD_ATTR_${field_name.upper()}: \
        /*memcpy(buf, &packet->_${header_name}.${field_name}, sizeof packet->_${header_name}.${field_name});*/ \
        /*buf += sizeof packet->_${header_name}.${field_name};*/ \
		{ \
			struct _${header_name}_header *_${header_name} = dp_packet_${header_name}(packet); \
			memcpy(buf, &_${header_name}->${field_name}, sizeof _${header_name}->${field_name}); \
			buf += sizeof _${header_name}->${field_name}; \
		} \
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_CALC_FIELDS_VERIFY_DST_FIELD_16BIT_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 16:
    case OVS_CALC_FIELD_ATTR_${field_name.upper()}: \
//::        # @Shahbaz: revert this ... temporarily commented because of some issue in pkt reception.
        /*return true; /*(packet->_${header_name}.${field_name} == res16);*/ \
		{ \
			struct _${header_name}_header *_${header_name} = dp_packet_${header_name}(packet); \
			return true; /*(_${header_name}->${field_name} == res16);*/ \
		} \
//::      else:
//::        pass  # TODO: handle other cases (for different bit sizes).
//::      #endif
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_CALC_FIELDS_UPDATE_DST_FIELD_16BIT_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 16:
    case OVS_CALC_FIELD_ATTR_${field_name.upper()}: \
        /*packet->_${header_name}.${field_name} = res16;*/ \
		{ \
			struct _${header_name}_header *_${header_name} = dp_packet_${header_name}(packet); \
			_${header_name}->${field_name} = res16; \
		} \
        break; \
//::      else:
//::        pass  # TODO: handle other cases (for different bit sizes).
//::      #endif
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ADD_TO_FIELD_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//    case OVS_KEY_ATTR_${field_name.upper()}: { \
//::      if bit_width == 8:
//        const uint8_t *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = \
//                packet->_${header_name}.${field_name} + *value; \
//::      elif bit_width == 16:
//        const ovs_be16 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htons( \
//                ntohs(packet->_${header_name}.${field_name}) + ntohs(*value)); \
//::      elif bit_width == 32:
//        const ovs_be32 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htonl( \
//                ntohl(packet->_${header_name}.${field_name}) + ntohl(*value)); \
//::      elif bit_width == 64:
//        const ovs_be64 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htonll( \
//                ntohll(packet->_${header_name}.${field_name}) + ntohll(*value)); \
//::      else:
//::        pass  # TODO: handle this case.
//::      #endif
//        break; \
//    } \
//::    #endfor
//::  #endfor
//    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_SUB_FROM_FIELD_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//    case OVS_KEY_ATTR_${field_name.upper()}: { \
//::      if bit_width == 8:
//        const uint8_t *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = \
//                packet->_${header_name}.${field_name} - *value; \
//::      elif bit_width == 16:
//        const ovs_be16 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htons( \
//                ntohs(packet->_${header_name}.${field_name}) - ntohs(*value)); \
//::      elif bit_width == 32:
//        const ovs_be32 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htonl( \
//                ntohl(packet->_${header_name}.${field_name}) - ntohl(*value)); \
//::      elif bit_width == 64:
//        const ovs_be64 *value = nl_attr_get(a); \
//        packet->_${header_name}.${field_name} = htonll( \
//                ntohll(packet->_${header_name}.${field_name}) - ntohll(*value)); \
//::      else:
//::        pass  # TODO: handle this case.
//::      #endif
//        break; \
//    } \
//::    #endfor
//::  #endfor
//    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ADD_HEADER_GET_OFS \
//::  for header_name in ordered_header_instances_regular:
	if (OVS_KEY_ATTR__${header_name.upper()} == key) { \
		header_size = sizeof(struct _${header_name}_header); \
		packet->_${header_name}_valid = 1; \
		goto push; \
	} \
	else if (packet->_${header_name}_valid) { \
		header_ofs += sizeof(struct _${header_name}_header); \
	} \
	\
//::  #endfor
	\

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_REMOVE_HEADER_GET_OFS \
//::  for header_name in ordered_header_instances_regular:
	if (OVS_KEY_ATTR__${header_name.upper()} == key) { \
		header_size = sizeof(struct _${header_name}_header); \
		packet->_${header_name}_valid = 0; \
		goto pop; \
	} \
	else if (packet->_${header_name}_valid) { \
		header_ofs += sizeof(struct _${header_name}_header); \
	} \
	\
//::  #endfor
	\

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ADD_REMOVE_HEADER_SET_OFS \
//::  for header_name in ordered_header_instances_regular:
	if (packet->_${header_name}_valid) { \
		packet->_${header_name}_ofs = header_ofs; \
		header_ofs += sizeof(struct _${header_name}_header); \
	} \
	\
//::  #endfor
	\


#endif	/* OVS_ACTION_ODP_EXECUTE_H */