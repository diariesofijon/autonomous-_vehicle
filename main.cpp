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
    
        void toRide () {
            bool WillBeInThePoint = true;
            setVectorOfMoving();
            startMoving();
            while (WillBeInThePoint and !isArrived) {
                WillBeInThePoint = checkWillBeInThePoint();
            }
            toRide();
        }

        void setUpPins() {
            pinMode(VectorLeftPIN, INPUT);
            pinMode(VectorRightPIN, INPUT);
            pinMode(TurnPIN, INPUT);
            pinMode(StopPIN, INPUT);
        }
    
    private:
    
        unsigned int lastResolution = 0;
    
        void stopVehicle() {
            digitalWrite(TurnPIN, LOW);
            digitalWrite(StopPIN, HIGH);
        }
    
        void stopMoving() {
            digitalWrite(TurnPIN, LOW);
        }
    
        void powerVehicle () {
            digitalWrite(StopPIN, LOW);
        }
    
        void startMoving() {
            if (digitalRead(StopPIN) == HIGH) {
                powerVehicle();
            }
            digitalWrite(TurnPIN, HIGH);
            digitalWrite(VectorLeftPIN, LOW);
            digitalWrite(VectorRightPIN, LOW);
        }

        void toTurn(int left, int right) {
            /*
                ВАЖНО!
                при команде поворота контроллер перестает отзываться на другие команды, но ждет граду на который нужно повернуть
            */
            digitalWrite(VectorLeftPIN, left);
            digitalWrite(VectorRightPIN, right);
            bool isTurning = true;
            unsigned int currentDegree = 0;
            while (isTurning) {
                while (!HCBluetooth.available()) {
                    // waiting ...
                }
                unsigned int streamDegree = 0;
                while (streamDegree <= 5) {
                    streamDegree = readBluetoothStream();
                    currentDegree = streamDegree - 5;
                    HCBluetooth.println();
                    HCBluetooth.print("Нужно повернуть на ");
                    HCBluetooth.print(currentDegree);
                    HCBluetooth.println();
                }
                isTurning = !!currentDegree;
            }
        }

        void setVectorOfMoving () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            if (HCBluetooth.available() > 0) {
                lastResolution = readBluetoothStream();
                switch (lastResolution) {
                case 5:
                    startMoving();
                    break;
                case 4:
                    toTurn(HIGH, LOW);
                    break;
                case 3:
                    stopVehicle();
                    break;
                case 2:
                    stopMoving();
                    break;
                case 1:
                    toTurn(LOW, HIGH);
                    break;
                default:
                    setVectorOfMoving();
                    break;
                }
            }
        }
    
        bool checkWillBeInThePoint () {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            int currentResolution = HCBluetooth.read();
            return lastResolution == currentResolution;
        }
    
        unsigned int readBluetoothStream() {
            while (!HCBluetooth.available()) {
                // waiting ...
            }
            unsigned int result = 0;
            while (!result) {
                result = HCBluetooth.read();
            }
            return result;
        }
};

// setup initializes serial and the button pin
void setup() {
  Controller vehicle = Controller();
  Serial.begin(9600);
  HCBluetooth.begin(9600);
  vehicle.setUpPins();
}

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop() {
  Controller vehicle = Controller();
  delay(1000);
  vehicle.toRide();
}
