#ifndef __PULSE_OX__
#define __PULSE_OX__ 1

#include<math.h>
#include "pulse_ox_definitions.h"

//SYSTEM_MODE(MANUAL);

void setup() {
  Serial.begin(9600);
#ifdef PULSE_OXIMETER
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDIR, OUTPUT);
  pinMode(pulseOxInputPin, INPUT);
  red_state = false;
  ir_state  = true;
  state_diag  = true; // Init state
  change_led_timer.start();
#endif // PULSE_OXIMETER
#ifdef ACCELEROMETER_ON
  pinMode(accelXInput, INPUT);
  pinMode(accelYInput, INPUT);
  pinMode(accelZInput, INPUT);
  sample_accel_values.start();
#endif // ACCELEROMETER_ON
#ifdef PULSE_OXIMETER
  #ifndef OLD_CODE_PULSE_OX
  sample_pulse_values.start();
  #endif
#endif // PULSE_OXIMETER
} // setup

void loop() {
    // red_led_on and start red_timer
#ifdef ACCELEROMETER_ON
  //read_accel_input();
#endif // ACCELEROMETER_ON
#ifdef PULSE_OXIMETER
    if(red_state)
    {
      #ifndef OLD_CODE_PULSE_OX
       red_led_on();
       #else
       read_red();
       #endif
       red_state  =  false;
       ir_state   =  false;
    }

    if(ir_state)
    {
      #ifndef OLD_CODE_PULSE_OX
      ir_led_on();
      #else
      read_ir();
      #endif
      red_state = false;
      ir_state  = false;
    }
#endif // PULSE_OXIMETER

} // loop
#endif
