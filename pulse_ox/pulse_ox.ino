#ifndef __PULSE_OX__
#define __PULSE_OX__ 1

#include<math.h>
#include "pulse_ox.h"

//SYSTEM_MODE(MANUAL);

Timer change_led_timer(1500, change_led_type);
//Timer change_ir_timer(6000, change_ir_type);
//Timer ir_timer(6000, read_ir_and_calc);
//Timer call_connect_timer(20000, call_connect);

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
