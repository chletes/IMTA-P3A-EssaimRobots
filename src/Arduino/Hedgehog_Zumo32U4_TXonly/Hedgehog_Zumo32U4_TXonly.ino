/*  Projet 3A : Pilotage essaim robots
 *  Encadrant : Fabien Claveau
 *  Élèves    : Carlos SANTOS SEISDEDOS, Fatima-Zahra LAFTISSI, Wentao GONG
 *  Date      : 02/12/21
 *  Ce code permet de vérifier la communication entre un Pololu Zumo 32U4 et une balise mobile (hedgehog) Marvelmind
 */

/*
 * Les connections :
 * USB connection to computer (Serial)
 * (Pin 14)   Zumo 32U4 TX     <=> Hedgehog RX     (Pin 11)
 * (Pin 15)   Zumo 32U4 RX     <=> Hedgehog TX     (Pin 10)
 * (Pin GND)  Zumo 32U4 Ground  <=> Hedgehog Ground (Pin 12)
 * 
 */

 /* Nous avons programmé sur le Dashboard un baudrate de 115200 bps pour le hedgehog.
  */

#include <stdlib.h>

#include <Zumo32U4.h>
#include <PololuBuzzer.h>

PololuBuzzer buzzer;

//////////////////////////////////////////////////////////////////////////////
////////////////////MARVELMIND HEDGEHOG RELATED PART//////////////////////////
#define HEDGEHOG_BUF_SIZE 40 
#define HEDGEHOG_CM_DATA_SIZE 0x10
#define HEDGEHOG_MM_DATA_SIZE 0x16
#define POSITION_DATAGRAM_ID 0x0001
#define POSITION_DATAGRAM_HIGHRES_ID 0x0011

long hedgehog_x, hedgehog_y;  // coordinates of hedgehog (X,Y), mm
long hedgehog_z;              // height of hedgehog, mm
int hedgehog_pos_updated;     // flag of new data from hedgehog received

bool high_resolution_mode;    // by default set to false in Dashboard

byte hedgehog_serial_buf[HEDGEHOG_BUF_SIZE];
byte hedgehog_serial_buf_ofs;

unsigned int hedgehog_data_id;

byte hedgehog_address;
unsigned int paired_heading;

typedef union {byte b[2]; unsigned int w;int wi;} uni_8x2_16;
typedef union {byte b[4];float f;unsigned long v32;long vi32;} uni_8x4_32;

//    Marvelmind hedgehog setup initialize
void setup_hedgehog(){
  Serial1.begin(115200); // hedgehog transmits data on 115200 bps  

  hedgehog_serial_buf_ofs= 0;
  hedgehog_pos_updated= 0;
}

// Marvelmind hedgehog service loop
void loop_hedgehog(){
  int incoming_byte;
  int total_received_in_loop;
  int packet_received;
  bool good_byte;
  byte packet_size;
  uni_8x2_16 un16;
  uni_8x4_32 un32;

  total_received_in_loop= 0;
  packet_received= 0;
  
  while(Serial1.available() > 0){
    if (hedgehog_serial_buf_ofs>=HEDGEHOG_BUF_SIZE){
      hedgehog_serial_buf_ofs= 0; // restart bufer fill
      break;                      // buf overflow
    }
    total_received_in_loop++;
    if (total_received_in_loop>100) break;// too much data without required header
      
    incoming_byte= Serial1.read();
    good_byte= false;
    switch(hedgehog_serial_buf_ofs){
      case 0:
      {
        good_byte= (incoming_byte = 0xff);
        break;
      }
      case 1:
      {
        good_byte= (incoming_byte = 0x47);
        break;
      }
      case 2:
      {
        good_byte= true;
        break;
      }
      case 3:
      {
        hedgehog_data_id= (((unsigned int) incoming_byte)<<8) + hedgehog_serial_buf[2];
        good_byte=   (hedgehog_data_id == POSITION_DATAGRAM_ID) ||
                     (hedgehog_data_id == POSITION_DATAGRAM_HIGHRES_ID);
        break;
      }
      case 4:
      {
        switch(hedgehog_data_id){
          case POSITION_DATAGRAM_ID:
          {
            good_byte= (incoming_byte == HEDGEHOG_CM_DATA_SIZE);
            break;
          }
          case POSITION_DATAGRAM_HIGHRES_ID:
          {
            good_byte= (incoming_byte == HEDGEHOG_MM_DATA_SIZE);
            break;
          }
        }
        break;
      }
      default:
      {
        good_byte= true;
        break;
      }
    }
      
    if (!good_byte){
      hedgehog_serial_buf_ofs= 0;// restart bufer fill         
      continue;
    }     
    hedgehog_serial_buf[hedgehog_serial_buf_ofs++]= incoming_byte; 
    if (hedgehog_serial_buf_ofs>5){
      packet_size=  7 + hedgehog_serial_buf[4];
      if (hedgehog_serial_buf_ofs == packet_size){// received packet with required header
        packet_received= 1;
        hedgehog_serial_buf_ofs= 0;// restart bufer fill
        break; 
      }
    }
  }

  if (packet_received){
    hedgehog_set_crc16(&hedgehog_serial_buf[0], packet_size);// calculate CRC checksum of packet
    if ((hedgehog_serial_buf[packet_size] == 0)&&(hedgehog_serial_buf[packet_size+1] == 0)){// checksum success
        switch(hedgehog_data_id){
          case POSITION_DATAGRAM_ID:
          {
            // coordinates of hedgehog (X,Y), cm ==> mm
            un16.b[0]= hedgehog_serial_buf[9];
            un16.b[1]= hedgehog_serial_buf[10];
            hedgehog_x= 10*long(un16.wi);

            un16.b[0]= hedgehog_serial_buf[11];
            un16.b[1]= hedgehog_serial_buf[12];
            hedgehog_y= 10*long(un16.wi);
            
            // height of hedgehog, cm==>mm (FW V3.97+)
            un16.b[0]= hedgehog_serial_buf[13];
            un16.b[1]= hedgehog_serial_buf[14];
            hedgehog_z= 10*long(un16.wi);

            hedgehog_address= hedgehog_serial_buf[16];
            un16.b[0]= hedgehog_serial_buf[17];
            un16.b[1]= hedgehog_serial_buf[18]&0x0f;
            paired_heading= un16.w;
            
            hedgehog_pos_updated= 1;// flag of new data from hedgehog received
            high_resolution_mode= false;
            break;
          }

          case POSITION_DATAGRAM_HIGHRES_ID:
          {
            // coordinates of hedgehog (X,Y), mm
            un32.b[0]= hedgehog_serial_buf[9];
            un32.b[1]= hedgehog_serial_buf[10];
            un32.b[2]= hedgehog_serial_buf[11];
            un32.b[3]= hedgehog_serial_buf[12];
            hedgehog_x= un32.vi32;

            un32.b[0]= hedgehog_serial_buf[13];
            un32.b[1]= hedgehog_serial_buf[14];
            un32.b[2]= hedgehog_serial_buf[15];
            un32.b[3]= hedgehog_serial_buf[16];
            hedgehog_y= un32.vi32;
            
            // height of hedgehog, mm 
            un32.b[0]= hedgehog_serial_buf[17];
            un32.b[1]= hedgehog_serial_buf[18];
            un32.b[2]= hedgehog_serial_buf[19];
            un32.b[3]= hedgehog_serial_buf[20];
            hedgehog_z= un32.vi32;

            hedgehog_address= hedgehog_serial_buf[22];
            un16.b[0]= hedgehog_serial_buf[23];
            un16.b[1]= hedgehog_serial_buf[24]&0x0f;
            paired_heading= un16.w;
            
            hedgehog_pos_updated= 1;// flag of new data from hedgehog received
            high_resolution_mode= true;
            break;
          }
        }
      } 
  }
}

// CRC-16 of hedgehog packet calculation
void hedgehog_set_crc16(byte *buf, byte size){
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
}// hedgehog_set_crc16

////////////////////MARVELMIND HEDGEHOG RELATED PART//////////////////////////
//////////////////////////////////////////////////////////////////////////////

void setup_debug(){
  ledYellow(0);
  ledRed(0);
  ledGreen(0);
}

#define CM 1      //Centimeter
#define INC 0     //Inch
#define TP 2      //Trig_pin
#define EP 3      //Echo_pin

void setup(){
  //pinMode(TP,OUTPUT);       // set TP output for trigger  
  //pinMode(EP,INPUT);        // set EP input for echo
    
  setup_hedgehog(); //    Marvelmind hedgehog support initialize
  setup_debug();    // Serial connection to PC.
}

void loop(){  
  byte coord_precision;
  char buf[12];

  #ifdef DISTANCE_SENSOR_ENABLED
  long microseconds = TP_init();
  long distacne_cm = Distance(microseconds, CM);
  #endif

  loop_hedgehog();          // Marvelmind hedgehog service loop

  if (hedgehog_pos_updated){// new data from hedgehog available
    hedgehog_pos_updated= 0;// clear new data flag 
    
    if (high_resolution_mode){
      coord_precision= 3;
    }
    else{
      coord_precision= 2; 
    }
    
    //Serial.print("X=");
    dtostrf(((float) hedgehog_x)/1000.0f, 4, coord_precision, buf);
    if (buf != 0){
      ledYellow(1);
//      buzzer.playFrequency(440, 200, 15);
//      delay(300);
//      buzzer.stopPlaying();
    }
    //Serial.print(buf);
    
    //Serial.print("\tY=");
    dtostrf(((float) hedgehog_y)/1000.0f, 4, coord_precision, buf);
    if (buf != 0){
      ledRed(1);
    }
    //Serial.print(buf);  
    
    //Serial.print("\tZ=");  
    dtostrf(((float) hedgehog_z)/1000.0f, 4, coord_precision, buf);
    if (buf != 0){
      ledGreen(1);
    }
    //Serial.println(buf);
    ledYellow(0);
    ledRed(0);
    ledGreen(0);
 }
}

long Distance(long time, int flag){
  long distacne;
  if(flag)
    distacne = time /29 / 2  ;     // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
                                   //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
                                   //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2
  else
    distacne = time / 74 / 2;      // INC
  return distacne;
}

long TP_init(){                     
  digitalWrite(TP, LOW);                    
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);                 // pull the Trig pin to high level for more than 10us impulse 
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  long microseconds = pulseIn(EP,HIGH);   // waits for the pin to go HIGH, and returns the length of the pulse in microseconds
  return microseconds;                    // return microseconds
}
