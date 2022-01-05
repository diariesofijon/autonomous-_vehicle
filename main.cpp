#include <SoftwareSerial.h> 

int BluetoothRX = 2;
int BluetoothTX = 3;
int VectorLeftPIN = 7;
int VectorRightPIN = 7;
int TurnPIN = 8;
int StopPIN = 9;

SoftwareSerial HCBluetooth(BluetoothRX, BluetoothTX); // RX, TX
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
    
        Controller() {
            setUpPins();
        }
    
        toRide () {
            bool WillBeInThePoint = true;
            setVectorOfMoving();
            startMoving();
            while (WillBeInThePoint and !isArrived) {
                WillBeInThePoint = checkWillBeInThePoint();
            }
            HCBluetooth.print(HCBluetooth.read());
            HCBluetooth.println();
            toRide();
        }

        setUpPins() {
            pinMode(VectorLeftPIN, INPUT);
            pinMode(VectorRightPIN, INPUT);
            pinMode(TurnPIN, INPUT);
            pinMode(StopPIN, INPUT);
        }
    
    private:
    
        int lastResolution = 0;
    
        stopVehicle() {
            digitalWrite(TurnPIN, LOW);
            digitalWrite(StopPIN, HIGH);
        }
    
        stopMoving() {
            digitalWrite(TurnPIN, LOW);
        }
    
        powerVehicle () {
            digitalWrite(StopPIN, LOW);
        }
    
        startMoving() {
            if (digitalRead(StopPIN) == HIGH) {
                powerVehicle();
            }
            digitalWrite(TurnPIN, LOW);
            digitalWrite(VectorLeftPIN, LOW);
            digitalWrite(VectorRightPIN, LOW);
        }

        setVectorOfMoving () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            if (HCBluetooth.available() > 0) {
                lastResolution = HCBluetooth.read();
                switch (lastResolution) {
                case 5:
                    startMoving();
                    break;
                case 4:
                    digitalWrite(VectorLeftPIN, HIGH);
                    digitalWrite(VectorRightPIN, LOW);
                    break;
                case 3:
                    stopVehicle();
                    break;
                case 2:
                    stopMoving();
                    break;
                case 1:
                    digitalWrite(VectorLeftPIN, LOW);
                    digitalWrite(VectorRightPIN, HIGH);
                    break;
                default:
                    setVectorOfMoving();
                    break;
                }
            }
        }
    
        checkWillBeInThePoint () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            int currentResolution = HCBluetooth.read();
            return lastResolution == currentResolution;
        }
};

Controller vehicle = Controller();

// setup initializes serial and the button pin
void setup() {
  Serial.begin(9600);
  HCBluetooth.begin(9600);
  vehicle.setUpPins();
}

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop() {
  delay(1000);
  vehicle.toRide();
}
