// ECHO Locator Sensor is MASTER
#include <Wire.h>

#define PAYLOAD_SIZE 2   // how many bytes we are sending over the wire
#define NODE_MAX 5       // number of ardunios
#define START_NODE 2     // starting I2C address for the slave nodes
#define DELAY 1000       // delay between reads, between I2C nodes

int nodeInfo[PAYLOAD_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("HERE");
  for(int a=START_NODE; a<NODE_MAX; a++)
  {
     Wire.requestFrom(a, PAYLOAD_SIZE);   
     if(Wire.available() ==  PAYLOAD_SIZE)
     {
        for(int i=0; i<PAYLOAD_SIZE; i++)
          nodeInfo[i] = Wire.read();

        for(int j=0; j<PAYLOAD_SIZE; j++)
          Serial.println("** payload: " + String(nodeInfo[j]) + " **");
     }
  }
  delay(DELAY);
}
