/*  Projet 3A : Pilotage essaim robots
 *  Encadrant : Fabien Claveau
 *  Élèves    : Carlos SANTOS SEISDEDOS, Fatima-Zahra LAFTISSI, Wentao GONG
 *  Date      : 02/12/21
 *  Ce code permet de vérifier la communication entre un Pololu Zumo 32U4 et une balise mobile (hedgehog) Marvelmind
 */
// https://marvelmind.com/pics/marvelmind_beacon_interfaces.pdf
// https://marvelmind.com/pics/marvelmind_navigation_system_manual.pdf
/*
 * Les connections pour le robot Pololu Zumo 32U4:
 * * USB connection to computer (Serial)
 * (Pin 14)   Zumo 32U4 TX     <=> Hedgehog RX     (Pin 11)
 * (Pin 15)   Zumo 32U4 RX     <=> Hedgehog TX     (Pin 10)
 * (Pin GND)  Zumo 32U4 Ground  <=> Hedgehog Ground (Pin 12)
 * 
 *  Les connections pour l'Arduino Mega:
 *  * USB connection to computer (Serial)
 * (Pin 14)   Arduino TX3     <=> Hedgehog RX     (Pin 11)
 * (Pin 15)   Arduino RX3     <=> Hedgehog TX     (Pin 10)
 * (Pin GND)  Arduino Ground  <=> Hedgehog Ground (Pin 12)
 * 
 * (Pin 14 + Pin 15) = Serial3 pour l'Arduino MEGA
 */

 /* Nous avons programmé sur le Dashboard un baudrate de 115200 bps pour le hedgehog.
  */

#include <stdlib.h>
//#include <Zumo32U4.h> // Comment when using Arduino MEGA
//#include <PololuBuzzer.h> // Comment when using Arduino MEGA
#include "Hedgehog_communication.h"

// PololuBuzzer buzzer; // Comment when using Arduino MEGA

#define CM 1      //Centimeter
#define INC 0     //Inch
#define TP 2      //Trig_pin
#define EP 3      //Echo_pin

void setup_debug(){
  //ledYellow(0); // Comment when using Arduino MEGA
  //ledRed(0); // Comment when using Arduino MEGA
  //ledGreen(0); // Comment when using Arduino MEGA

  Serial.begin(115200); // Comment when using Pololu Zumo 32U4
}

void setup(){
  //pinMode(TP,OUTPUT);       // set TP output for trigger  
  //pinMode(EP,INPUT);        // set EP input for echo
    
  setup_hedgehog(); // Marvelmind hedgehog support initialize
  setup_debug();    // Serial connection to PC.
}
void PID(){
  // Variables hh_actual_X, hh_actual_Y disponibles.
}
void loop(){
  #ifdef DISTANCE_SENSOR_ENABLED
  long microseconds = TP_init();
  long distance_cm = Distance(microseconds, CM);
  #endif

  loop_hedgehog();          // Marvelmind hedgehog service loop
  
  if (hh_position_update_flag){// new data from hedgehog available
    hh_position_update_flag = false;// clear new data flag 
    // Variables hh_actual_X, hh_actual_Y disponibles.
    PID();
    //printPosition();
    //playBuzzer();
    //lightLEDS();
  }

  if (hh_commande_update_flag){
    hh_commande_update_flag = false;
    // Variables hh_target_X, hh_target_Y disponibles.
    //Serial.print("Target X: "); 
    //Serial.print((int) hh_target_X); 
    
    //Serial.print("\tTarget Y: "); 
    //Serial.print((int) hh_target_Y); 
    
    // appel a PID
  }
}

void printPosition(){ //Only for Arduino MEGA, several Serial needs to be implemented
    byte coord_precision;
    char buf[12];

    if (high_resolution_mode){
      coord_precision= 3;
    }else{
      coord_precision= 2; 
    }
    
    Serial.print("X="); 
    dtostrf(((float) hh_actual_X)/1000.0f, 4, coord_precision, buf);
    Serial.print(buf); 
    
    Serial.print("\tY="); 
    dtostrf(((float) hh_actual_Y)/1000.0f, 4, coord_precision, buf);
    Serial.print(buf); 
    
    Serial.print("\tZ="); 
    dtostrf(((float) hh_actual_Z)/1000.0f, 4, coord_precision, buf);
    Serial.println(buf); 
}

/*void playBuzzer(){ // Comment when using Arduino MEGA
  byte coord_precision;
  char buf[12];
    
  if (high_resolution_mode){
    coord_precision= 3;
  } else{
    coord_precision= 2; 
  }
  
  dtostrf(((float) hh_actual_X)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    buzzer.playFrequency(300, 200, 15);
    delay(300);
    buzzer.stopPlaying();
  }
  
  dtostrf(((float) hh_actual_Y)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    buzzer.playFrequency(400, 200, 15);
    delay(300);
    buzzer.stopPlaying();
  }
  
  dtostrf(((float) hh_actual_Z)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    buzzer.playFrequency(500, 200, 15);
    delay(300);
    buzzer.stopPlaying();
  }
}*/

/*void lightLEDS(){ // Comment when using Arduino MEGA
  byte coord_precision;
  char buf[12];
    
  if (high_resolution_mode){
    coord_precision= 3;
  } else{
    coord_precision= 2; 
  }
  
  dtostrf(((float) hh_actual_X)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    ledYellow(1);
  }
  
  dtostrf(((float) hh_actual_Y)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    ledRed(1);
  }
  
  dtostrf(((float) hh_actual_Z)/1000.0f, 4, coord_precision, buf);
  if (buf != 0){
    ledGreen(1);
  }

  ledYellow(0);
  ledRed(0);
  ledGreen(0);
}*/

long Distance(long time, int flag){
  long distance;
  if(flag)
    distance = time /29 / 2  ;     // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
                                   //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
                                   //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2
  else
    distance = time / 74 / 2;      // INC
  return distance;
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
