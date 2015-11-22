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
float red_arr[SAMPLE_WINDOW_SIZE]; // array to store red_values
float ir_arr[SAMPLE_WINDOW_SIZE]; // array to store ir_values

/*** Software Timers ***/
Timer change_led_timer(LED_ON_TIME, change_led_type);
Timer sample_pulse_values(SAMPLE_INTERVAL, sample_and_store);
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
#ifdef DEBUG2_ON
    Serial.print("AbsorbanceRed = ");
    Serial.println(AbsorbanceRed);
    Serial.print("AbsorbanceIR = ");
    Serial.println(AbsorbanceIR);
#endif
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

// Calculates the average of the given array elements
float calc_average(float *arr)
{
  int iter, avg_count = 0;
  float temp_sum  = 0;

  for(iter=0; iter<SAMPLE_WINDOW_SIZE; ++iter)
  {
    if(abs(arr[iter]) < INVALID_ABSORBANCE_VAL)
    {
      temp_sum  += arr[iter];
      ++avg_count;
    }
  }
  return !avg_count ? INVALID_ABSORBANCE_VAL : (temp_sum/avg_count) ;
}

// Reads the value from analog InputPin.
// Computes Absorbance and stores in position
// of the array
void read_val_to_arr_pos(float *arr, int pos)
{
  float temp_voltage, temp_current, temp_absorbance;
  temp_voltage  = analogRead(InputPin);
#ifdef DEBUG2_ON
  Serial.print("Analog read = ");
  Serial.println(temp_voltage);
#endif
  temp_current = (temp_voltage*MULT_CONSTANT);
  temp_absorbance = log10(temp_current/LED_CURRENT);
#ifdef DEBUG2_ON
  Serial.print("temp_absorbance value = ");
  Serial.println(temp_absorbance);
#endif
  if(abs(temp_absorbance) < INVALID_ABSORBANCE_VAL)
    arr[pos] = temp_absorbance;
  else
    arr[pos]  = INVALID_ABSORBANCE_VAL;
#ifdef DEBUG2_ON
  Serial.print("Arr[pos] contents = ");
  Serial.println(arr[pos]);
#endif
}

// Reads the analog value into Red or IR array
// Returns true if it fills up the array
// else false
bool read_and_store(float *arr)
{
  static int cur_pos;
  if(cur_pos < SAMPLE_WINDOW_SIZE)
  {
    read_val_to_arr_pos(arr, cur_pos++);
    if(SAMPLE_WINDOW_SIZE == 1)
    {
      cur_pos = 0;
      return true;
    }
    else
      return false;
  }
  else
  {
    cur_pos = 0;
    return true;
  }
}

// Function called at each sample interval
void sample_and_store()
{
  float avgAbsorbanceRed, avgAbsorbanceIR;

  if(state_diag)
  {
#ifdef DEBUG2_ON
  Serial.print("Red LED  \n" );
  //Serial.println(avgAbsorbanceRed);
#endif
    read_and_store(red_arr);
  }
  else
  {
#ifdef DEBUG2_ON
      Serial.print("IR LED  \n" );
      //Serial.println(avgAbsorbanceRed);
#endif
    if(read_and_store(ir_arr))
    {
      avgAbsorbanceIR   = calc_average(ir_arr);
      avgAbsorbanceRed  = calc_average(red_arr);
      if(avgAbsorbanceIR != INVALID_ABSORBANCE_VAL)
      {
        AbsorbanceIR = avgAbsorbanceIR;
      }
      if(avgAbsorbanceRed != INVALID_ABSORBANCE_VAL)
      {
        AbsorbanceRed = avgAbsorbanceRed;
      }
#ifdef DEBUG2_ON
      Serial.print("avgAbsorbanceRed = " );
      Serial.println(avgAbsorbanceRed);
      Serial.print("avgAbsorbanceIR = " );
      Serial.println(avgAbsorbanceIR);
#endif
      CalculatedRatio =  AbsorbanceRed/(AbsorbanceIR + AbsorbanceRed);
      bloodOx = -30.667*CalculatedRatio*CalculatedRatio + 10*CalculatedRatio  + 102.67;
      Serial.print("Blood Ox % = " );
      Serial.println(bloodOx);
    }
  }
}

#endif
