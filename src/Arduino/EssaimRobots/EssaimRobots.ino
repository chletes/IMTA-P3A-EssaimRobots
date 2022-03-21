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
// PololuBuzzer buzzer; // Comment when using Arduino MEGA

DW_uncouping_controller_T uncoupling_controller_T;

void setup_debug(){
  //ledYellow(0); // Comment when using Arduino MEGA
  //ledRed(0); // Comment when using Arduino MEGA
  //ledGreen(0); // Comment when using Arduino MEGA

  //Serial.begin(115200); // Comment when using Pololu Zumo 32U4
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
    
    //printPosition();
    //playBuzzer();
    //lightLEDS();
    // appels a PID
    //calculate commandes for robot
    //update_theta_v(Vd_t, Vg_t, delta_t_position_update); //update theta and v_centre
  ledYellow(1);
    if(uncoupling_ready)
    {
      uncoupling_controller(&hh_target_X, &hh_target_Y, &hh_actual_X, &hh_actual_Y, theta, &v_center, 0.083, &Vd, &Vg, &uncoupling_controller_T);
      velocity_PID();
//      if(hh_target_X==hh_actual_X+0.5 && hh_target_Y== hh_actual_Y+0.5){
//        uncoupling_ready=false;
//        }
      }
  }

  if (hh_commande_update_flag){
    hh_commande_update_flag = false;
    // Variables hh_target_X, hh_target_Y disponibles.

    // appels a PID
    //calculate commandes for robot
    uncoupling_ready = true;
//    uncoupling_controller(&hh_target_X, &hh_target_Y, &hh_actual_X, &hh_actual_Y, theta, &v_center, 0.5, &Vd, &Vg, &uncoupling_controller_T);
//    velocity_PID();
    ledRed(1);
    // robots control
  }
}

/*void printPosition(){ //Only for Arduino MEGA, several Serial needs to be implemented
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
}*/

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
