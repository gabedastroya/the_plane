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
#define DATA_POSITION_SYNC 0
#define DATA_POSITION_THR 1
#define DATA_POSITION_ROLL 2
#define DATA_POSITION_PITCH 3
#define DATA_COUNT 4
#define DATA_BYTE_COUNT (DATA_COUNT * sizeof(int))

//array of bytes for reading the potentiometer
int data[DATA_COUNT];

int rx_index;

byte *rx_ptr;

//creating serial object to talk to transmitter
SoftwareSerial mySerial(PIN_TRANS_RX, PIN_TRANS_TX);


void setup() {
  //initiaising the receiver index to 0
  rx_index = 0;
  rx_ptr = (char*)data;
  
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

void update_servos ()
{
   //printing debug info
  Serial.print(" Throttle: ");
  Serial.print(data[DATA_POSITION_THR]);
  Serial.print(" Roll: ");
  Serial.print(data[DATA_POSITION_ROLL]);
  Serial.print(" Pitch: ");
  Serial.println(data[DATA_POSITION_PITCH]);

}

void loop() {
  if (!mySerial.available()) //check if data is available 
  {
   return; 
  }
  byte this_byte = mySerial.read();
  //check for sync integer
  if (rx_index == 1 || rx_index == 0) 
  {
    //if it's sync byte then advance th rx_index
    if (this_byte == 0xAA)  
    {
      rx_index ++; 
    }
    else  //otherwise reset the rx_index 
    {
      rx_index = 0;
    }
  }
  else
  {
    //write receive byte into data array @ rx_index
    rx_ptr[rx_index] =  this_byte;
    rx_index ++;
    //check if we ehave entire packet
    if(rx_index == DATA_BYTE_COUNT)
    {
      update_servos();
      rx_index = 0;
    }
  }

}
