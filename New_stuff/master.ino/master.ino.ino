// ECHO Locator Sensor is MASTER
#include <Wire.h>

#define PAYLOAD_SIZE 2   // how many bytes we are sending over the wire
#define NODE_MAX 6       // number of ardunios
#define START_NODE 2     // starting I2C address for the slave nodes
#define DELAY 100        // delay between reads, between I2C nodes

float nodeInfo[PAYLOAD_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int addr = 2; addr <= NODE_MAX; addr++)
  {
     Wire.requestFrom(addr, PAYLOAD_SIZE);   
     //Serial.println("ADDRESS: " + String(addr));
     if(Wire.available() ==  PAYLOAD_SIZE)
     {
        for(int i=0; i<PAYLOAD_SIZE; i++){
          nodeInfo[i] = Wire.read();
          if(i % 2 != 0)
            nodeInfo[i] = nodeInfo[i] * 4.0;
          else
            nodeInfo[i] = nodeInfo[i];

        }
        for(int j=0; j<PAYLOAD_SIZE; j++){
          if(j % 2 != 0){
            Serial.println("Slave:" + String(addr) + " Data: " + String(nodeInfo[j]));
          }
        }
        
     }
  }
  delay(DELAY);
}
