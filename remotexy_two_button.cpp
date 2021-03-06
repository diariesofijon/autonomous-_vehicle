// https://remotexy.com/en/editor/c7090379d49a7892149ecba7d7b44e7f/

/*
   -- viktors pult with double button by nikita --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.7 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.9.02 or later version;
     - for iOS 1.6.2 or later version;
    
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
  { 255,11,0,11,0,135,0,14,13,0,
  2,0,38,4,22,11,2,26,31,31,
  79,78,0,79,70,70,0,1,0,4,
  5,12,12,2,31,88,0,129,0,3,
  19,13,6,17,115,116,97,114,116,0,
  1,0,9,43,12,12,2,31,88,0,
  1,0,82,42,12,12,2,31,88,0,
  1,0,82,4,12,12,2,31,88,0,
  129,0,81,18,13,6,17,115,116,111,
  112,0,8,0,20,23,17,17,24,5,
  0,47,17,30,30,2,26,31,129,0,
  5,56,18,6,17,108,101,102,116,0,
  129,0,78,56,18,6,17,114,105,103,
  104,116,0,67,4,51,50,20,5,2,
  26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t turn_on_engine; // =1 if switch ON and =0 if OFF 
  uint8_t button_start; // =1 if button pressed, else =0 
  uint8_t button_change_vector_left; // =1 if button pressed, else =0 
  uint8_t button_change_vector_right; // =1 if button pressed, else =0 
  uint8_t button_stop; // =1 if button pressed, else =0 
  float compass_vector; // 0 .. 359.999 
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position 

    // output variables
  char text_1[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

SoftwareSerial HCBluetooth(REMOTEXY_SERIAL_RX, REMOTEXY_SERIAL_TX); // RX, TX

void writeBluetoothStream (int data) {
    while (!HCBluetooth.available()) {
        // waiting ...
    }
    HCBluetooth.write(data);
}

unsigned int getDegreeToTurn() {
   if (!RemoteXY.joystick_1_y) {
      return 90;
   }
   if (!RemoteXY.joystick_1_x) {
      return 0;
   }
   int result = floor(RemoteXY.compass_vector - 180);
   result -= atan(RemoteXY.joystick_1_y/RemoteXY.joystick_1_x);
   unsigned int uresult = floor(result);
   dtostrf(uresult, 0, 2, RemoteXY.text_1);
   return uresult;
}

int changeVector(int left, int right) {
   if (left) {
      writeBluetoothStream(4);
   } else if (right) {
      writeBluetoothStream(1);
   } else {
      return -1;
   }
   unsigned int degree = getDegreeToTurn();
   while (degree) {
      writeBluetoothStream(degree);
      degree = getDegreeToTurn();
   }
   return 0;
}

void setup() 
{
  RemoteXY_Init (); 
  
  // TODO you setup code
  
}

/*
    5 is 101 go to ahead
    4 is 100 have to vector to 0
    3 is 011 stop vehicle
    2 is 010 stop movement
    1 is 001 have to vector to 1
*/

void loop() 
{ 
  RemoteXY_Handler ();
   
  changeVector(RemoteXY.button_change_vector_left, RemoteXY.button_change_vector_right);

  
  writeBluetoothStream((RemoteXY.turn_on_engine==0)?5:3);
  writeBluetoothStream((RemoteXY.button_start==0)?2:5);
  writeBluetoothStream((RemoteXY.button_stop==0)?2:0);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
