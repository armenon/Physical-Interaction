// these constants won't change:
const int flexSensor = A0;
const int vibratorModule = 12;


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int vibrateState = LOW;         // variable used to store the last LED status, to toggle the light
int clampedValue = 0;
int counter = 1;

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  pinMode(vibratorModule, OUTPUT);
  Serial.begin(9600);       // use the serial port
}

void loop() {
  // read the sensor and store it in the variable sensorReading:

 if(counter % 20 == 0){
   if(vibrateState == LOW)
    vibrateState = HIGH;
   vibrate(vibrateState);
 }
 
 if(vibrateState == HIGH){
  sensorReading = analogRead(flexSensor);
  clampedValue = map(sensorReading, 500, 900, 0, 255);
  Serial.println(clampedValue);
  if (clampedValue > 100){
   vibrateState = LOW; 
   vibrate(vibrateState);
   } 
 }
 
 Serial.println(counter);
 counter++;
 if(counter == 3600)
   counter = 0;
 delay(500);  // delay to avoid overloading the serial port buffer
}

void vibrate(int vibrate){
  digitalWrite(vibratorModule, vibrate);
//  delay(100);
//  digitalWrite(vibratorModule, LOW);
}
