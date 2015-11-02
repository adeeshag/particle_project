#include "application.h"


int mic=A4;
int value;
int max_val;
int min_val;

/* This function is called once at start up ----------------------------------*/
void setup()
{
	//Setup the Tinker application here
	pinMode(mic, INPUT);
	Serial.begin(9600);
	min_val = 10000;
	max_val = 0;

}

/* This function loops forever --------------------------------------------*/
void loop()
{
	//This will run in a loop
	value = analogRead(mic);
	if(value > max_val)
		max_val = value;
	if(value < min_val)
		min_val = value;
	Serial.printlnf("Min :%d   Max:%d  Value: %d\n", min_val, max_val, value);
	Serial.println(value, DEC);
	delay(1000);
}
