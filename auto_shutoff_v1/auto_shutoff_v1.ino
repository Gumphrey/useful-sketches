/* test code for fet/transistor switch */

#include "math.h"

//USER CONSTANTS 

const int limit = 3000;
const int input_pin = A0;
const int switch_pin = 10;

//DYNAMIC VARIABLES

int count = 0;
float input_val=0;
float input_chk=0;
int input_threshold=500;

void setup() {
  pinMode(switch_pin,OUTPUT);
  
  //OPEN SWITCH
  
  digitalWrite(switch_pin,LOW);
  pinMode(input_pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  if (count > limit) {
    
    //SHUTOFF AND STAY SHUT OFF!
    
    digitalWrite(switch_pin,HIGH);
    while (count > limit) {}
       
   } 
   else 
   {
     
     input_val=analogRead(input_pin); 
     input_chk=pow(input_val,2);
     //Serial.println(input_chk);
     
     // SQUARE INPUT, EXCEED THRESHOLD

     if (input_chk > input_threshold) {
       count+=1;
       Serial.println(count);
       } 
   }
}

