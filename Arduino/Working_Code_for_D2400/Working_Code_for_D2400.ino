#include <MAX3100Serial.h>

//#include <SoftwareSerial.h>  

// Digital Pins
const int bluetooth1Tx = 2;           // TX-O pin of bluetooth mate, Arduino D2
const int bluetooth1Rx = 4;           // RX-I pin of bluetooth mate, Arduino 
const int switchModule = 6;           // Use D6 as the switch input
const int ledPin1 = 3;                // Use PWM3 (D3) as Blue led control pin
const int ledPin2 = 5;                // Use PWM5 (D5) as Yellow led control pin 
const int vibratorModule = 12;        // Use D12 as the vibrator ouput 
const int fadeTime      = 15;         // Adjust value to speed up or slow down fade

int batteryValue = -1;
int vibrateState = LOW;      
int ledState = LOW; 
int counter = 1;
int switchReading;
int ledWhiteValue = 1;
bool isBlueLed  = true;
bool isBluetoothConnected = false;            
bool fadeup = true;
unsigned long lastFadeTime = 0;        // will store last time LED was updated

//SoftwareSerial bluetooth1(bluetooth1Tx, bluetooth1Rx); // Initialise Bluetooth serial lines

void setup() {
  pinMode(switchModule, INPUT);       // Initialise switchModule as an input module to take in readings of the switch
  pinMode(vibratorModule, OUTPUT);    // Initilise vibratorModule as an output to send data to vibrator
  pinMode(ledPin1, OUTPUT);         // Initilise ledModule as an output to send data to the LED
  pinMode(ledPin2, OUTPUT);         // Initilise ledModule as an output to send data to the LED
//  Serial.begin(9600);                 // Serial port for debug 
  switchReading = LOW;
  // Initialise Bluetooth communications
 /* bluetooth1.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth1.print("$");  // Print three times individually
  bluetooth1.print("$");
  bluetooth1.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth1.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth1.begin(9600);  // Start bluetooth serial at 9600*/

}

void loop() {
  switchReading = digitalRead(switchModule);
Serial.println(switchReading);
  batteryValue= analogRead(ADC_BATTERY);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 4.3V):
  float voltage = batteryValue * (4.3 / 1023.0);
  // print out the value you read:
  Serial.print(voltage);
  Serial.println("V");
 
  vibrateState = switchReading; 
  vibrate(vibrateState);

  if(counter % 200 == 0){
    if(!ledState)
      ledState = !ledState;
  }

  if(ledState){
    if(isBlueLed){
      ledFade(ledPin1);
      if(!isBluetoothConnected){
//        connectToSlave(1);
      }
    }
    else
      ledFade(ledPin2);
  }

//Serial.println(counter);
 /*if(isBluetoothConnected){
  if(bluetooth1.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
   // Serial.print((char)bluetooth1.read());  
  }
 }*/
 counter++;
 if(counter == 3600)
   counter = 0;
 delay(50);  // delay to avoid overloading the serial port buffer
}

/*
 * Vibrate Function
 * Use this function to write data to the vibratorModule
 * 
 * vibrate - Set HIGH to vibrate, set LOW to stop vibration
 */
void vibrate(int vibrate){
  digitalWrite(vibratorModule, vibrate);
}


/*
 * LED Fade Function
 * Use this function to make the selected LED Pin fade
 * 
 * ledPin - Pass which ledPin needs to be lit up
 */
void ledFade(int ledPin){
 if((millis() - lastFadeTime) > fadeTime){
//   Serial.println(ledWhiteValue);
    if(fadeup) {
      analogWrite(ledPin, ledWhiteValue);
      if(ledWhiteValue >= 254) {
        ledWhiteValue = 254;
        fadeup = false;
      }
      ledWhiteValue++;
    } 
    else {
      analogWrite(ledPin, ledWhiteValue);
      if(ledWhiteValue <= 1) {
        ledWhiteValue = 0;  
        fadeup = true;
        isBlueLed = !isBlueLed;
      }
      ledWhiteValue--;
    }
    lastFadeTime = millis();
  }
}

/*void connectToSlave(int slaveNumber){
  bluetooth1.print("$");  // Print three times individually
  bluetooth1.print("$");
  bluetooth1.print("$");  // Enter command mode
  delay(100); 
  switch(slaveNumber){
    case 1: {
            bluetooth1.println("C,201412081158");
            readBluetooth();
    }
    break;
   default:
    break;
  }
}

String readBluetooth(){
  char string[48];
  char byteRead;
  int availableBytes = bluetooth1.available();
  for(int i=0; i<availableBytes; i++){
    string[i] = bluetooth1.read();
  }
  String readData(string); 
  Serial.print(readData);
  return readData;
}*/
