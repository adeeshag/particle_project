#ifndef __PULSE_OX_DECL__
#define __PULSE_OX_DECL__

/*** Debugging options ***/
//#define DEBUG_ON 1
#define DEBUG2_ON 2
//#define OLD_CODE 1

/*** Defines ***/
#define MULT_CONSTANT (3.3/(15000000*4095))*1000000 //150000000 is resistance
#define LED_CURRENT 4.8/1000 // 4.8V by 1k Ohms
#define INVALID_ABSORBANCE_VAL 2147483645 // just an arbitrary value based on observationL
#define LED_ON_TIME 2000 // in ms
#define SAMPLE_WINDOW_SIZE 1
#define SAMPLE_INTERVAL LED_ON_TIME/SAMPLE_WINDOW_SIZE // in ms

/*** Function Declarations ***/
void read_red();
void read_ir();
void red_led_on();
void ir_led_on();
void change_led_type();
float  calc_average(float *arr);
void read_val_to_arr_pos(float *arr, int pos);
bool read_and_store(float *arr);
void sample_and_store();
#endif
