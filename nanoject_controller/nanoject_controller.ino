/* 
the nanoject ii has a 3.5 mm input pulled up to 5V, rising edge after closing ground triggers injection
hence the time between injections is hightime+lowtime  
*/

#include "math.h"

//USER CONSTANTS 

const int switch_pin = 13;

//DYNAMIC VARIABLES

int hightime = 9000; // time in milliseconds
int lowtime = 1000; //time in milliseconds

unsigned long starttime = 0; //initialize for clock checks

void setup() {

  pinMode(switch_pin,OUTPUT);
  digitalWrite(switch_pin,LOW);

}

void loop() {

  starttime=millis();
  digitalWrite(switch_pin,HIGH);
  while (millis()-starttime<hightime);
  
  digitalWrite(switch_pin,LOW);
  starttime=millis();
  while(millis()-starttime<lowtime);
  
}




