#include <SoftwareSerial.h>

//transmitter & rreceiver pins
#define PIN_TRANS_RX 10
#define PIN_TRANS_TX 11

//joystick pins
#define PIN_JOY1_X_PITCH 0
#define PIN_JOY1_Y_ROLL  1

//throttle
#define PIN_JOY2_X_THR 2

//data pos.
#define DATA_POSITION_THR 0
#define DATA_POSITION_ROLL 1
#define DATA_POSITION_PITCH 2
#define DATA_COUNT 3

//array of bytes for reading the potentiometer
int data[DATA_COUNT];

//creating serial object to talk to transmitter
SoftwareSerial mySerial(PIN_TRANS_RX, PIN_TRANS_TX);


void setup() {
  // initiatialisation of debuging connection
  Serial.begin(9600);

  //waiting for serial to finish
  while (!Serial) {
  }
  //printing stuff
  Serial.println("cool, ok and radical");

  //setting speed for that bit(transimiter)
  mySerial.begin(57600);
}

void loop() {
  //lets read data from joystick values
  data[DATA_POSITION_THR] = analogRead(PIN_JOY2_X_THR);
  data[DATA_POSITION_ROLL] = analogRead(PIN_JOY1_Y_ROLL);
  data[DATA_POSITION_PITCH] = analogRead(PIN_JOY1_X_PITCH);

  //printing debug info
  Serial.print(" Throttle: ");
  Serial.print(data[DATA_POSITION_THR]);
  Serial.print(" Roll: ");
  Serial.println(data[DATA_POSITION_ROLL]);
  Serial.print(" Pitch: ");
  Serial.println(data[DATA_POSITION_PITCH]);

  //still gonna send it(sending data)
  byte *dataPtr = (byte*)data;
  
  for (int i=0; i <= sizeof(data); i++){
    mySerial.write(dataPtr[i]);
    
  }

}
