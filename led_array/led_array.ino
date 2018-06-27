/* test code for fet/transistor switch */

#include "math.h"

//USER CONSTANTS 

int led_pins[] = {
  2, 3, 4, 5, 6, 7, 13
};
int pin_count = 7;
//DYNAMIC VARIABLES

int hightime = 1000; // time in milliseconds
int lowtime = 1000; //time in milliseconds

unsigned long starttime = 0; //initialize for clock checks

void setup() {

  for (int cnt = 0; cnt < pin_count; cnt++) {   
    pinMode(led_pins[cnt], OUTPUT);
    digitalWrite(led_pins[cnt],HIGH);
  }
  
}

void loop() {

  for (int cnt = 0; cnt < pin_count; cnt++) {   
    digitalWrite(led_pins[cnt],HIGH);
  }
  
  starttime=millis();
  while (millis()-starttime<hightime);
  
  for (int cnt = 0; cnt < pin_count; cnt++) {   
      digitalWrite(led_pins[cnt],LOW);
  };
  
  starttime=millis();
  while(millis()-starttime<lowtime);
  
}




