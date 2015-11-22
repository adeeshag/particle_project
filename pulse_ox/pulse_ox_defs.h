#ifndef __PULSE_OX_DEFS__
#define __PULSE_OX_DEFS__

#include "pulse_ox_decl.h"

/*** Global variables ***/
float InputPin = A0; // Analog input pin from output of op amp
float sensorVoltage = 0;
float sensorCurrent = 0;
float AbsorbanceRed = 0;
float AbsorbanceIR = 0;
float CalculatedRatio;
float bloodOx = 0;
int LEDRed=D0;
int LEDIR=D1;
bool red_state;
bool ir_state;
bool state_diag;
int red_arr[10]; // array to store red_values
int ir_arr[10]; // array to store red_values

/*** Software Timers ***/
Timer change_led_timer(1500, change_led_type);
//Timer change_ir_timer(6000, change_ir_type);
//Timer ir_timer(6000, read_ir_and_calc);
//Timer call_connect_timer(20000, call_connect);

/*** Function definitions ***/

// Turns on Red LED
void red_led_on()
{
  digitalWrite(LEDIR, LOW); digitalWrite(LEDRed, HIGH);
}

// Turns on IR LED
void ir_led_on()
{
  digitalWrite(LEDRed, LOW); digitalWrite(LEDIR, HIGH);
}

// Reads analog data of Red LED values
void read_red()
{
  ir_led_on();
  sensorVoltage = analogRead(InputPin);
  sensorCurrent = (sensorVoltage*MULT_CONSTANT);
  AbsorbanceRed = log10(sensorCurrent/LED_CURRENT);
#ifdef DEBUG_ON
  Serial.print("Voltage Red = ");
  Serial.println(sensorVoltage);
  Serial.print("Current Red = ");
  Serial.println(sensorCurrent);
#endif
}

// Reads analog data of IR LED values
void read_ir()
{
  red_led_on();
  sensorVoltage = analogRead(InputPin);
  sensorCurrent = (sensorVoltage*MULT_CONSTANT);
  AbsorbanceIR = log10(sensorCurrent/LED_CURRENT);
#ifdef DEBUG_ON
  Serial.print("Voltage IR = ");
  Serial.println(sensorVoltage);
  Serial.print("Current IR = ");
  Serial.println(sensorCurrent);
#endif
  CalculatedRatio =  AbsorbanceRed/(AbsorbanceIR + AbsorbanceRed);
  bloodOx = -30.667*CalculatedRatio*CalculatedRatio + 10*CalculatedRatio  + 102.67;
  Serial.print("Blood Ox % = " );
  Serial.println(bloodOx);
}

// Changes which LED to shine
void change_led_type()
{
  if(state_diag)
  {
    red_state = true;
    ir_state  = false;
  }
  else
  {
    red_state = false;
    ir_state  = true;
  }
  state_diag  = !state_diag;
}

#endif
