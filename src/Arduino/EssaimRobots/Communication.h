#ifndef Communication_h
#define Communication_h

#include "Arduino.h"

#define TOTAL_DEBUGGING false
#define HH_REQUEST_PATH_CODE_DEBUGGING false

//////RX packet of hedgehog coordinates (stream from Hedgehog)//////
#define HH_STREAM_POSITION_DEST_ADDRESS 0xff // 0xff = 255
#define HH_STREAM_POSITION_TYPE  0x47       
#define HH_STREAM_POSITION_CODE 0x0001 // cm 
#define HH_STREAM_POSITION_DATASIZE 0x10

#define HH_BUF_SIZE 32

#define HH_RX_POSITION_HIGHRES_CODE 0x0011 // mm
#define HH_RX_POSITION_HIGHRES_DATASIZE 0x16

//////TX confirmation packet of hedgehog coordinates//////
#define HH_ACK_TYPE 0x48
#define HH_ACK_CODE 0x0100
#define HH_ACK_DATASIZE 0x04
// #define HH_ACK_NOTready 0x00
// #define HH_ACK_RXready 0x01
// #define HH_ACK_TXready 0x02

//////RX confirmation packet of hedgehog coordinates//////
#define HH_REQUEST_PATH_TYPE 0x4a     //0x4a = 74
#define HH_REQUEST_PATH_CODE 0x0201
#define HH_REQUEST_PATH_DATASIZE 0x0c //0x0c = 12

extern  long  hh_actual_X, hh_actual_Y;  // coordinates of hedgehog (X,Y), mm
extern  long  hh_actual_Z;        // height of hedgehog, mm

extern  long  hh_target_X, hh_target_Y;

extern  bool  hh_position_update_flag; // flag of new data from hedgehog received
extern  bool  hh_commande_update_flag;
extern  bool  high_resolution_mode;    // by default set to false in Dashboard

extern  byte  hh_buffer[HH_BUF_SIZE];
/* 
 * hh_buffer[0]     - Destination Address   - 1 byte
 * hh_buffer[1]     - Type                  - 1 byte
 * hh_buffer[2:3]   - ID                    - 2 bytes
 * hh_buffer[4]     - Size = N              - 1 byte
 * hh_buffer[5:5+N] - Payload               - N bytes
 * hh_buffer[6+N:7+N]- CRC-16               - 2 bytes
*/
extern  byte  hh_buffer_index;
extern  byte  hh_flags;
extern  byte  hh_address;

extern  unsigned int hh_packet_type;
extern  unsigned int hh_packet_id;
extern  unsigned int paired_heading;

typedef union {byte b[2];unsigned int w;int wi;} uni_8x2_16;
typedef union {byte b[4];float f;unsigned long v32;long vi32;} uni_8x4_32;

extern void hh_set_crc16(byte *buf, byte size);

extern void setup_hedgehog(); 

extern void loop_hedgehog();

extern void HH_process_stream_position_packet();

extern void HH_process_write_packet();

extern void HH_send_write_answer_success();

extern void HH_send_packet(byte address, byte packet_type, unsigned int id, byte data_size);

extern void HH_send_ack_ready(byte status);

#endif
