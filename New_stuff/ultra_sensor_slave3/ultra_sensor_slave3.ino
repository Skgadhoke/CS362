// Ultra sonic sensor -> SLAVE 3

#include <Wire.h>

#define NODE_ADDRESS 4
#define PAYLOAD_SIZE 2

#define COMMON_ANODE

int redPin = 11;
int greenPin = 10;
int bluePin = 9;


byte nodePayload[PAYLOAD_SIZE];

const int trigPin = 10;
const int echoPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(NODE_ADDRESS);
  Wire.onRequest(requestEvent);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  nodePayload[0] = NODE_ADDRESS;
  float distance = getDistance();
  nodePayload[1] = distance/4.0;

  LED_CODE();
}

float getDistance()
{
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  //delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  return distance;
}


void LED_CODE()
{
  setColor(255, 0, 0);  // red
  delay(100);
  setColor(0, 255, 0);  // green
  delay(100);
  setColor(0, 0, 255);  // blue
  delay(100);
  setColor(255, 255, 0);  // yellow
  delay(100);  
  setColor(80, 0, 80);  // purple
  delay(100);
  setColor(0, 255, 255);  // aqua
  delay(100);
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void requestEvent()
{
  Wire.write(nodePayload, PAYLOAD_SIZE);
}

