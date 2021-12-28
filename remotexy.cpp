/*
   -- New project --
   
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

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,14,0,0,0,50,0,13,13,0,
  2,0,39,7,22,11,2,26,31,31,
  79,78,0,79,70,70,0,1,0,7,
  5,12,12,2,31,88,0,1,0,82,
  5,12,12,2,31,88,0,7,36,32,
  29,20,5,2,26,2,11 };

/*
    5 is 101 go to ahead
    4 is 100 have to vector to 0
    3 is 011 stop vehicle
    2 is 010 stop movement
    1 is 001 have to vector to 1
*/
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t turn_on_engine; // =1 если переключатель включен и =0 если отключен 
  uint8_t button_start; // =1 если кнопка нажата, иначе =0 
  uint8_t button_change_vector; // =1 если кнопка нажата, иначе =0 
  char edit_coordiantes[11];  // =строка UTF8 оканчивающаяся нулем  

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
  
  digitalWrite(PIN_TURN_ON_ENGINE, (RemoteXY.turn_on_engine==0)?5:3);
  digitalWrite(PIN_BUTTON_START, (RemoteXY.button_start==0)?2:5);
  digitalWrite(PIN_BUTTON_CHANGE_VECTOR, (RemoteXY.button_change_vector==0)?1:4);
  
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 


}
