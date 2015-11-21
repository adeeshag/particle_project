float InputPin = A0; // Analog input pin from output of op amp
float sensorVoltage = 0;
float sensorCurrent = 0;
float LEDCurrentRed = 0;
float AbsorbanceRed = 0;
float LEDCurrentIR = 0;
float AbsorbanceIR = 0;
float CalculatedRatio;
float bloodOx = 0;
int LEDRed=D0;
int LEDIR=D1;
bool red_state;
bool ir_state;
bool state_diag;

#include<math.h>

//#define DEBUG_ON 1
#define MULT_CONSTANT (3.3/(15000000*4095))*1000000 //150000000 is resistance
#define LED_CURRENT 4.8/1000 // 4.8V by 1k Ohms

//SYSTEM_MODE(MANUAL);

Timer change_led_timer(3000, change_led_type);
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
//ir_timer.start();
change_led_timer.start();
//change_ir_timer.start();
//call_connect_timer.start();
}

void loop() {
    // red_led_on and start red_timer
    if(red_state)
    {
       read_red_and_calc();
       red_state  =  false;
       ir_state   =  false;
    }

    if(ir_state)
    {
      read_ir_and_calc();
      red_state = false;
      ir_state  = false;
    }
    //else
    //{
      // do nothing
    //}
} // loop

void red_led_on()
{
  digitalWrite(LEDIR, LOW); digitalWrite(LEDRed, HIGH);
}

void ir_led_on()
{
  digitalWrite(LEDRed, LOW); digitalWrite(LEDIR, HIGH);
}

void read_red_and_calc()
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

void read_ir_and_calc()
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

void call_connect()
{
  Particle.connect();
}
