/*  Projet 3A : Pilotage essaim robots
 *  Encadrant : Fabien Claveau
 *  Élèves    : Carlos SANTOS SEISDEDOS, Fatima-Zahra LAFTISSI, Wentao GONG
 *  Date      : 28/02/22
 */

/* Les connections pour le robot Pololu Zumo 32U4:
 * + USB connection to computer (Serial)
 * (Pin 14)   Zumo 32U4 TX     <=> Hedgehog RX     (Pin 11)
 * (Pin 15)   Zumo 32U4 RX     <=> Hedgehog TX     (Pin 10)
 * (Pin GND)  Zumo 32U4 Ground  <=> Hedgehog Ground (Pin 12)
 * 
 * Les connections pour l'Arduino Mega:
 * + USB connection to computer (Serial)
 * (Pin 14)   Arduino TX3     <=> Hedgehog RX     (Pin 11)
 * (Pin 15)   Arduino RX3     <=> Hedgehog TX     (Pin 10)
 * (Pin GND)  Arduino Ground  <=> Hedgehog Ground (Pin 12)
 * 
 * (Pin 14 + Pin 15) = Serial3 pour l'Arduino MEGA
 */

 /* Modem location update frequency   : 2       Hz
  * Modem location update time        : 0.5 sec
  * UART Hedgehog sampling frequency  : 115200  Hz
  */

#include "Globals.h"
#include "Communication.h"
#include "Controllers.h"

#if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
  #include <Zumo32U4.h>
  #include <PololuBuzzer.h>
  PololuBuzzer buzzer;
#elif defined(__AVR_ATmega2560__)// Arduino Mega 2560

#else
  #error “Unsupported board selected!”
#endif


DW_uncouping_controller_T uncoupling_controller_T;

void setup_debug(){
  #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
    ledYellow(0); 
    ledRed(0); 
    ledGreen(0); 
  #elif defined(__AVR_ATmega2560__)// Arduino Mega 2560
    Serial.begin(115200); 
  #endif
}

void setup(){
  setup_hedgehog(); // Marvelmind hedgehog support initialize
  setup_debug();    // Serial connection to PC.
  setup_Velocity_PID();
  uncoupling_controller_init(&uncoupling_controller_T);
}

void loop(){
  loop_hedgehog();          // Marvelmind hedgehog service loop
  
  /* Modem location update time : 0.5 sec*/

  if (hh_position_update_flag){       // new data from hedgehog available
    hh_position_update_flag = false;  // clear new data flag 
    // Variables hh_actual_X, hh_actual_Y disponibles.
    
    #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
      ledYellow(1);
      //playBuzzer();
      //lightLEDS();
    #elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
      printPosition();
    #endif
  }

  if (hh_commande_update_flag){
    hh_commande_update_flag = false;
    // Variables hh_target_X, hh_target_Y disponibles.

    // appels a PID
    //calculate commandes for robot
    uncoupling_controller(hh_target_X, hh_target_Y, hh_actual_X, hh_actual_Y, theta, v_center, 0.5, &Vd, &Vg, &uncoupling_controller_T);
    velocity_PID();
    // robots control
    #if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
      ledRed(1);
    #endif
  }
}

#if defined (__AVR_ATmega32U4__) // Pololu Zumo 32U4
void playBuzzer(){
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
}

void lightLEDS(){
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
}
#elif defined(__AVR_ATmega2560__) // Arduino Mega 2560
void printPosition(){
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
#endif
