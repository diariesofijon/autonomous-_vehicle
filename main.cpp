int VectorPIN = 7;
int TurnPIN = 8;
int StopPIN = 9;

struct Locatoin {
    int x;
    int y;
};

class Controller {
    
    // работает после сетапа
    
    public:
    
        bool isGoToLeft = true;
    
        Location currentLocation = {0, 0};
        Location arrivingLocation = {0, 0}
    
        GeoConnection connection;
    
        Controller() {
            setUpsPins();
            connection = connectGeoLocation();
        }
    
        toRide () {
            WillBeInThePoint = true;
            DidntArrive = false;
            startVehicle()
            while (WillBeInThePoint and !DidntArrive) {
                WillBeInThePoint = checkWillBeInThePoint();
            } else {
                while
            }
        }
    
    private:
    
        setUpPins() {
            pinMode(VectorPIN, INPUT);
            pinMode(TurnPIN, INPUT);
            pinMode(StopPIN, INPUT);
            
            digitalWrite(VectorPIN, isGoToLeft);
            digitalWrite(TurnPIN, false);
            digitalWrite(StopPIN, false);
        }
    
        handleGeoData () {
            if (connection.location.x == -1 and connection.location.y = -1 ) {
                stopVehicle();
            }
        }
    
        stopVehicle() {
            digitlaWrite(TurnPIN, false);
            digitalWrite(StopPIN, true);
        }
    
        powerVehicle () {
            digitalWrite(StopPIN, false);
        }
    
        startMoving() {
            if (digitalRead(StopPin)) {
                powerVehicle();
            }
            digitlaWrite(TurnPIN, true);
        }
    
        connectGeoLocation () {
            // library that produce connection to the server of geolocation
            return connection;
        }
    
        checkWillBeInThePoint () {
            
        }
};


// setup initializes serial and the button pin
void setup() {
  Serial.begin(9600);
}

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop() {

  delay(1000);
}
