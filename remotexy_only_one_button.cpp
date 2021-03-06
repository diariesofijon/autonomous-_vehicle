/*
   -- viktors pult --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.6 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.8.01 or later version;
     - for iOS 1.5.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,3,0,0,0,100,0,13,13,0,
  2,0,39,7,22,11,2,26,31,31,
  79,78,0,79,70,70,0,1,0,7,
  5,12,12,2,31,88,0,1,0,82,
  5,12,12,2,31,88,0,129,0,5,
  18,13,6,17,115,116,97,114,116,0,
  129,0,64,20,34,3,17,208,184,208,
  183,208,188,208,181,208,189,208,184,209,
  130,209,140,32,208,189,208,176,208,191,
  209,128,208,176,208,178,208,187,208,181,
  208,189,208,184,208,181,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t turn_on_engine; // =1 if switch ON and =0 if OFF 
  uint8_t button_start; // =1 if button pressed, else =0 
  uint8_t button_change_vector; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_TURN_ON_ENGINE 0
#define PIN_BUTTON_START 0
#define PIN_BUTTON_CHANGE_VECTOR 0

/*
    5 is 101 go to ahead
    4 is 100 have to vector to 0
    3 is 011 stop vehicle
    2 is 010 stop movement
    1 is 001 have to vector to 1
*/

void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_TURN_ON_ENGINE, OUTPUT);
  pinMode (PIN_BUTTON_START, OUTPUT);
  pinMode (PIN_BUTTON_CHANGE_VECTOR, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  analogWrite(PIN_TURN_ON_ENGINE, (RemoteXY.turn_on_engine==0)?5:3);
  analogWrite(PIN_BUTTON_START, (RemoteXY.button_start==0)?2:5);
  analogWrite(PIN_BUTTON_CHANGE_VECTOR, (RemoteXY.button_change_vector==0)?1:4);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
