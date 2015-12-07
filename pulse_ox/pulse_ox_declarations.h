#ifndef __PULSE_OX_DECL__
#define __PULSE_OX_DECL__

/*** Debugging options ***/
//#define DEBUG_ON 1
//#define DEBUG2_ON 2
//#define OLD_CODE_PULSE_OX 1
#define PULSE_OXIMETER 1
#define ACCELEROMETER_ON 1
#define MICROPHONE_ON 1

/*** Defines ***/
#define MULT_CONSTANT (4.8/(15000000*4095))*115000 //150000000 is resistance and 115000 is the gain
#define LED_CURRENT 3.3/1000 // 4.8V by 1k Ohms
#define INVALID_ABSORBANCE_VAL 2147483645 // just an arbitrary value based on observationL
#define LED_ON_TIME 3000 // in ms
#define SAMPLE_WINDOW_SIZE 1
#define SAMPLE_INTERVAL LED_ON_TIME/SAMPLE_WINDOW_SIZE // in ms
#define X_Y_Z_REFERNCE_VAL 1.6 // normalization values for each of them
#define MULT_CONSTANT_ACCEL 3.3/4095
#define RADIANS_TO_DEG_MULT_CONSTANT 57.2957795
#define VAL_180 180 //180 degrees used for conversion
#define ACCELEROMETER_SAMPLE_INTERVAL 2000
#define MAX_ANALOG_INPUT_VAL 4095
#define MIC_SAMPLE_INTERVAL 500
#define MAX_MIC_VAL 180

/*** Function Declarations ***/
/* ACCELEROMETER_ON */
void read_accel_input();
/* PULSE_OXIMETER */
void read_red();
void read_ir();
void red_led_on();
void ir_led_on();
void change_led_type();
float  calc_average(float *arr);
void read_val_to_arr_pos(float *arr, int pos);
bool read_and_store(float *arr);
void sample_and_store();
void mic_check_val();
#endif
