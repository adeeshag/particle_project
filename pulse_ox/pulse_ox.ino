#ifndef __PULSE_OX__
#define __PULSE_OX__ 1

#include<math.h>
#include "pulse_ox_defs.h"

//SYSTEM_MODE(MANUAL);

void setup() {
  Serial.begin(9600);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDIR, OUTPUT);
  pinMode(InputPin, INPUT);
  red_state = false;
  ir_state  = true;
  state_diag  = true; // Init state
  change_led_timer.start();
} // setup

void loop() {
    // red_led_on and start red_timer
    if(red_state)
    {
       read_red();
       red_state  =  false;
       ir_state   =  false;
    }

    if(ir_state)
    {
      read_ir();
      red_state = false;
      ir_state  = false;
    }

} // loop
#endif
