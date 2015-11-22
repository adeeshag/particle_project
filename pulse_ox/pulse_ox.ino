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
#ifndef OLD_CODE
  sample_pulse_values.start();
#endif
} // setup

void loop() {
    // red_led_on and start red_timer
    if(red_state)
    {
#ifndef OLD_CODE
       red_led_on();
#else
       read_red();
#endif
       red_state  =  false;
       ir_state   =  false;
    }

    if(ir_state)
    {
#ifndef OLD_CODE
      ir_led_on();
#else
      read_ir();
#endif
      red_state = false;
      ir_state  = false;
    }

} // loop
#endif
