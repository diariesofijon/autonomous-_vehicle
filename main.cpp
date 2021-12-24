int VectorPIN = 7;
int TurnPIN = 8;
int StopPIN = 9;

struct Location {
    int x;
    int y;
};

class Controller {
    
    // работает после сетапа
    
    public:
    
        bool isGoToLeft = false;
        bool isGoToRight = false;

        bool DidntArrived

 
        Location currentLocation = {0, 0};
        Location arrivingLocation = {0, 0}
    
        GeoConnection connection;
    
        Controller() {
            setUpsPins();
            connection = connectGeoLocation();
        }
    
        toRide () {
            WillBeInThePoint = true;
            setVectorOfMoving();
            startVehicle();
            while (WillBeInThePoint and !DidntArrived) {
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

        setVectorOfMoving () {
            if (currentLocation.x - arrivingLocation.x > 0) {
                isGoToLeft = true;
                isGoToRight = false;
            }
            if (currentLocation.x - arrivingLocation.x < 0) {
                isGoToLeft = false;
                isGoToRight = true;
            }
            if (currentLocation.x - arrivingLocation.x == 0) {
                isGoToLeft = false;
                isGoToRight = false;
            }
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

Controller vehicle = Controller ();

// loop checks the button pin each time,
// and will send serial if it is pressed
void loop() {
  delay(1000);
  vehicle.toRide()
}
