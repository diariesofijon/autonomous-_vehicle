#include <SoftwareSerial.h> 

int BluetoothInPut = 2;
int BluetoothOutPut = 3;
int VectorPIN = 7;
int TurnPIN = 8;
int StopPIN = 9;

SoftwareSerial HCBluetooth(BluetoothInPut, BluetoothOutPut);

/*

    5 is 101 go to ahead
    4 is 100 have to vector to 0
    3 is 011 stop vehicle
    2 is 010 stop movement
    1 is 001 have to vector to 1

*/

class Controller {
    
    // работает после сетапа
    
    public:

        bool isArrived = false;
    
        int analogBase = 10;
    
        int lastResolution = 0;
    
        Controller() {
            setUpPins();
        }
    
        toRide () {
            bool WillBeInThePoint = true;
            setVectorOfMoving();
            startMoving();
            while (WillBeInThePoint and !isArrived) {
                WillBeInThePoint = checkWillBeInThePoint();
            } else {
                toRide();
            }
        }
    
    private:
    
        setUpPins() {
            pinMode(VectorPIN, INPUT);
            pinMode(TurnPIN, INPUT);
            pinMode(StopPIN, INPUT);
        }
    
        stopVehicle() {
            digitlaWrite(TurnPIN, LAW);
            digitalWrite(StopPIN, HIGH);
        }
    
        stopMoving() {
            digitlaWrite(TurnPIN, LAW);
        }
    
        powerVehicle () {
            digitalWrite(StopPIN, LAW);
        }
    
        startMoving() {
            if (digitalRead(StopPin) == HIGH) {
                powerVehicle();
            }
            digitalWrite(TurnPIN, HOW);
        }

        setVectorOfMoving () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            if (HCBluetooth.available() > 0) {
                lastResolution = HCBLuetooth.read();
                switch (lastResolution) {
                case 5:
                    startMoving();
                    break;
                case 4:
                    digitlaWrite(VectorPIN, LAW);
                    break;
                case 3:
                    stopVehicle();
                    break;
                case 2:
                    stopMoving();
                    break;
                case 1:
                    digitlaWrite(VectorPIN, HIGH);
                    break;
                default:
                    setVectorOfMoving()
                    break;
                }
            }
        }
    
        checkWillBeInThePoint () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            return lastResolution == HCBLuetooth.read();
        }
};


// setup initializes serial and the button pin
void setup() {
  Serial.begin(9600);
  HCBluetooth.begin(9600);
}

Controller vehicle = Controller ();

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop() {
  delay(1000);
  vehicle.toRide();
}
