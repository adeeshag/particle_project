#ifndef __PULSE_OX_DECL__
#define __PULSE_OX_DECL__

/*** Defines ***/
//#define DEBUG_ON 1
#define MULT_CONSTANT (3.3/(15000000*4095))*1000000 //150000000 is resistance
#define LED_CURRENT 4.8/1000 // 4.8V by 1k Ohms


/*** Function Declarations ***/
void read_red();
void read_ir();
void red_led_on();
void ir_led_on();
void change_led_type();
#endif
