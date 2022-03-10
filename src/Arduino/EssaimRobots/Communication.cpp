#include <Arduino.h>
#include "Communication.h"
//////////////////////////////////////////////////////////////////////////////
////////////////////MARVELMIND HEDGEHOG RELATED PART//////////////////////////

float  hh_actual_X, hh_actual_Y;  // coordinates of hedgehog (X,Y), mm
float hh_actual_Z;        // height of hedgehog, mm

float hh_target_X, hh_target_Y;

bool  hh_position_update_flag; // flag of new data from hedgehog received
bool  hh_commande_update_flag;
bool  uncoupling_ready;
bool  high_resolution_mode;    // by default set to false in Dashboard

byte  hh_buffer[HH_BUF_SIZE];
byte  hh_buffer_index;
byte  hh_flags;
byte  hh_address;

unsigned int hh_packet_type;
unsigned int hh_packet_id;
unsigned int paired_heading;

//    Marvelmind hedgehog setup initialize
void setup_hedgehog(){
  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
    Serial1.begin(115200); 
  #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
    Serial3.begin(115200); 
  #endif

  hh_position_update_flag = false;
  hh_commande_update_flag = false;
  hh_buffer_index = 0;
  hh_flags = 0;
  hh_address = 0;
}

// Marvelmind hedgehog service loop
void loop_hedgehog(){
  int incoming_byte;
  int bytes_received_in_loop = 0;
  bool packet_received = false;
  bool good_byte = false;
  byte hh_packet_size;
  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
    while(Serial1.available() > 0){ 
  #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
    while(Serial3.available() > 0){
  #endif
    if (hh_buffer_index >= HH_BUF_SIZE){
      hh_buffer_index= 0; // restart buffer fill
      break;              // buffer overflow
    }
    bytes_received_in_loop++;
    if (bytes_received_in_loop>100) break;// too much data without required header
    
    #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
      incoming_byte = Serial1.read();
    #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560s
      incoming_byte = Serial3.read();
    #endif
    
    good_byte = false;
    switch(hh_buffer_index){
      case 0: // Check destination adress
      { 
        good_byte = (incoming_byte = HH_STREAM_POSITION_DEST_ADDRESS);
        break;
      }
      case 1: // Check packet type
      { 
        //good_byte = (incoming_byte = HH_STREAM_POSITION_TYPE);
        good_byte = ( (incoming_byte == HH_STREAM_POSITION_TYPE) ||
                      (incoming_byte == HH_ACK_TYPE) ||
                      (incoming_byte == HH_REQUEST_PATH_TYPE) );
        hh_packet_type = incoming_byte;
        #if TOTAL_DEBUGGING && defined(__AVR_ATmega2560__) // Arduino Mega 2560
        Serial.println("1. Checking packet type");
        #endif
        break;
      }
      case 2:
      {
        good_byte= true;
        break;
      }
      case 3: // Check packet ID 
      {
        hh_packet_id = (((unsigned int) incoming_byte)<<8) + hh_buffer[2];
        //hh_packet_id = hh_buffer[2] + incoming_byte * 256;
        good_byte=   (hh_packet_id == HH_STREAM_POSITION_CODE) ||
                     (hh_packet_id == HH_RX_POSITION_HIGHRES_CODE) ||
                     (hh_packet_id == HH_REQUEST_PATH_CODE);
        #if TOTAL_DEBUGGING && defined(__AVR_ATmega2560__) // Arduino Mega 2560
        Serial.println("2. Checking packet id");
        #endif
        break;
      }
      case 4: // Check 'data size' field
      { 
        switch(hh_packet_id){ 
          case HH_STREAM_POSITION_CODE: // 0x0001
          {
            good_byte= (incoming_byte == HH_STREAM_POSITION_DATASIZE);
            break;
          }
          case HH_RX_POSITION_HIGHRES_CODE: //0x0011
          {
            good_byte= (incoming_byte == HH_RX_POSITION_HIGHRES_DATASIZE);
            break;
          }
          case HH_REQUEST_PATH_CODE:
          {
            #if TOTAL_DEBUGGING && defined(__AVR_ATmega2560__) // Arduino Mega 2560
            Serial.print("4. Checking request packet data size: ");
            Serial.println(7+incoming_byte);
            #endif
            good_byte= (incoming_byte == HH_REQUEST_PATH_DATASIZE);
            break;
          }
        }
        // Save required packet size:
        hh_packet_size =  7 + incoming_byte; // 7 bytes = ADDR (1) + TYPE (1) + CODE (2) + DATA_SIZE (1) + CRC (2)
        
        break;
      }
      default:
      {
        good_byte = true;
        break;
      }
    }
      
    if (!good_byte){
      hh_buffer_index = 0;// restart bufer fill
      hh_packet_id = 0;
      hh_packet_type = 0;
      continue;
    }
    hh_buffer[hh_buffer_index++] = incoming_byte; 
    if (hh_buffer_index>5){
      if (hh_buffer_index == hh_packet_size){// received packet with required header
        packet_received = true;
        hh_buffer_index = 0;// restart bufer fill
        break; 
      }
    }
  }

  if (packet_received){
    hh_set_crc16(&hh_buffer[0], hh_packet_size);// calculate CRC checksum of packet
    if ((hh_buffer[hh_packet_size] == 0) && (hh_buffer[hh_packet_size+1] == 0)){// checksum success
      switch (hh_packet_type){
        case HH_STREAM_POSITION_TYPE:
          HH_process_stream_position_packet();
          break;
        case HH_REQUEST_PATH_TYPE:
          #if TOTAL_DEBUGGING && defined(__AVR_ATmega2560__) // Arduino Mega 2560
          Serial.println("5. Request packet received");
          #endif
          HH_process_write_packet();
          break;
        
        default:
          break;
      }
    }
  }
}

void HH_process_stream_position_packet(){
  uni_8x2_16 un16;
  uni_8x4_32 un32;
  
  switch(hh_packet_id){
    case HH_STREAM_POSITION_CODE: // 0x0001
    { // coordinates of hedgehog (X,Y), cm ==> mm
      un16.b[0] = hh_buffer[9];
      un16.b[1] = hh_buffer[10];
      hh_actual_X = 10*long(un16.wi);

      un16.b[0] = hh_buffer[11];
      un16.b[1] = hh_buffer[12];
      hh_actual_Y = 10*long(un16.wi);
      
      // height of hedgehog, cm==>mm (FW V3.97+)
      un16.b[0] = hh_buffer[13];
      un16.b[1] = hh_buffer[14];
      hh_actual_Z = 10*long(un16.wi);

      hh_flags = hh_buffer[15];

      hh_address = hh_buffer[16];
      un16.b[0] = hh_buffer[17];
      un16.b[1] = hh_buffer[18]&0x0f;
      paired_heading = un16.w;
      
      hh_position_update_flag = true;// flag of new data from hedgehog received
      high_resolution_mode = false;

      #if TOTAL_DEBUGGING
      //Serial.println("3. Sending ACK ready");
      #endif
      if (hh_flags & 0x08) HH_send_ack_ready((byte) 0x01); // request for writing data

      break;
    }
    case HH_RX_POSITION_HIGHRES_CODE: // 0x0011
    {
      // coordinates of hedgehog (X,Y), mm
      un32.b[0] = hh_buffer[9];
      un32.b[1] = hh_buffer[10];
      un32.b[2] = hh_buffer[11];
      un32.b[3] = hh_buffer[12];
      hh_actual_X = un32.vi32;

      un32.b[0] = hh_buffer[13];
      un32.b[1] = hh_buffer[14];
      un32.b[2] = hh_buffer[15];
      un32.b[3] = hh_buffer[16];
      hh_actual_Y = un32.vi32;
      
      // height of hedgehog, mm 
      un32.b[0] = hh_buffer[17];
      un32.b[1] = hh_buffer[18];
      un32.b[2] = hh_buffer[19];
      un32.b[3] = hh_buffer[20];
      hh_actual_Z = un32.vi32;

      hh_flags = hh_buffer[21];

      hh_address = hh_buffer[22];
      un16.b[0] = hh_buffer[23];
      un16.b[1] = hh_buffer[24]&0x0f;
      paired_heading = un16.w;
      
      hh_position_update_flag = true;// flag of new data from hedgehog received
      high_resolution_mode= true;
      
      if (hh_flags & 0x08) HH_send_ack_ready((byte) 0x01); // request for writing data

      break;
    }
  }
}

void HH_process_write_packet(){
  int incoming_byte;
  byte type_of_mouvement, index, total_mouvements;
  uni_8x2_16 parameter_0;
  uni_8x2_16 parameter_1;
  uni_8x2_16 parameter_2;
  long param_movement_0, param_movement_1, param_movement_2;
  
  if (hh_packet_id == HH_REQUEST_PATH_CODE){ // Set Mouvement Path packet
    #if TOTAL_DEBUGGING && defined(__AVR_ATmega2560__) // Arduino Mega 2560
    Serial.println("6. Processing write packet");
    #endif

    type_of_mouvement = hh_buffer[5];
    index             = hh_buffer[6] + 1;
    total_mouvements  = hh_buffer[7];
    parameter_0.b[0] = hh_buffer[8];
    parameter_0.b[1] = hh_buffer[9];
    param_movement_0 = 10*long(parameter_0.wi);
    hh_target_X = param_movement_0/10;
    parameter_1.b[0] = hh_buffer[10];
    parameter_1.b[1] = hh_buffer[11];
    param_movement_1 = 10*long(parameter_1.wi);
    hh_target_Y = param_movement_1/10;
    parameter_2.b[0] = hh_buffer[12];
    parameter_2.b[1] = hh_buffer[13];
    param_movement_2 = 10*long(parameter_2.wi);
    
    
    //bytes from 14:16 are reserved
    hh_commande_update_flag = true;
    #if defined(__AVR_ATmega2560__) // Arduino Mega 2560
    Serial.print("Packet 0x201 received (");
    Serial.print(">> Index of this elementary movement : ");
    Serial.print(index);
    Serial.print(">> Total number of elementary movements : ");
    Serial.print("/");
    Serial.print(total_mouvements);
    Serial.println(").");
    Serial.print(">> Type of mouvement: ");
    switch(type_of_mouvement){
      case 0:{ 
        Serial.println("Move forward.");
        break;
      }
      case 1:{
        Serial.println("Move backward.");
        break;
      }
      case 2:{ 
        Serial.println("Rotate right (clockwise).");
        break;
      }
      case 3:{ 
        Serial.println("Rotate left (counterclockwise).");
        break;
      }
      case 4:{ 
        Serial.println("Pause.");
        break;
      }
      case 5:{
        Serial.println("Repeat program from start.");
        break;
      }
      case 6:{ 
        Serial.println("Move to specified point.");
        break;
      }
      case 7:{
        Serial.println("Setup speed.");
        break;
      }
      default:{
        break;
      }
    }
    
    switch(type_of_mouvement){
      case 0:
      case 1:{
        Serial.print(">> Distance of mouvement (cm): ");
        Serial.println(param_movement_0);
        break;
      }
      case 2:
      case 3:{
        Serial.print(">> Angle of rotation (degrees): ");
        Serial.println(param_movement_0);
        break;
      }
      case 4:{ 
        Serial.print(">> Time of pause (ms): ");
        Serial.println(param_movement_0);
        break;
      }
      case 5: break;
      case 6:{ 
        Serial.print(">> Target X: ");
        Serial.print((int) param_movement_0/10);
        Serial.print("\tTarget Y: ");
        Serial.print((int) param_movement_1/10);
        Serial.print("\tTarget Z: ");
        Serial.println((int) param_movement_2/10);
        break;
      }
      case 7:{ 
        Serial.print(">> Speed (%): ");
        Serial.println(param_movement_0);
        break;
      }
      default:{
        break;
      }
    }
    #endif
    
    HH_send_write_answer_success(); // send answer packet
  }
}

void HH_send_write_answer_success(){
  HH_send_packet(hh_address, hh_packet_type, hh_packet_id, 0);
}

void HH_send_packet(byte address, byte packet_type, unsigned int id, byte data_size){
  byte frameSizeBeforeCRC;

  hh_buffer[0] = address;
  hh_buffer[1] = packet_type;
  hh_buffer[2] = id & 0xff;
  hh_buffer[3] = (id >> 8) & 0xff;

  if (data_size != 0){
    hh_buffer[4] = data_size;
    frameSizeBeforeCRC = data_size + 5;
  }else{
    frameSizeBeforeCRC = 4;
  }
  hh_set_crc16(&hh_buffer[0], frameSizeBeforeCRC);

  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
  Serial.write(hh_buffer, frameSizeBeforeCRC + 2);
  #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
  Serial3.write(hh_buffer, frameSizeBeforeCRC + 2);
  #endif
}

void HH_send_ack_ready(byte status){
  int data_ofs = 5;

  /*
  if (digitalRead(READY_RECEIVE_PATH_PIN) == LOW)
    status |= (1 << 0); // ready to receive data
  */
  hh_buffer[data_ofs + 0] = status;
  hh_buffer[data_ofs + 1] = 0;
  hh_buffer[data_ofs + 2] = 0;
  hh_buffer[data_ofs + 3] = 0;

  HH_send_packet(hh_address, HH_ACK_TYPE, HH_ACK_CODE, HH_ACK_DATASIZE);
}

// CRC-16 of hedgehog packet calculation
void hh_set_crc16(byte *buf, byte size){
  uni_8x2_16 sum;
  byte shift_cnt;
  byte byte_cnt;

  sum.w=0xffffU;

  for(byte_cnt=size; byte_cnt>0; byte_cnt--){
   sum.w=(unsigned int) ((sum.w/256U)*256U + ((sum.w%256U)^(buf[size-byte_cnt])));

     for(shift_cnt=0; shift_cnt<8; shift_cnt++){
         if((sum.w&0x1)==1) sum.w=(unsigned int)((sum.w>>1)^0xa001U);
                       else sum.w>>=1;
       }
   }

  buf[size]=sum.b[0];
  buf[size+1]=sum.b[1];// little endian
}// hh_set_crc16

//////////////////MARVELMIND HEDGEHOG RELATED PART END////////////////////////
//////////////////////////////////////////////////////////////////////////////
