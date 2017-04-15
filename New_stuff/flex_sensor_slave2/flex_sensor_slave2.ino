// RIGHT FLEX SENSOR -> SLAVE 2

#include <Wire.h>

#define NODE_ADDRESS 3
#define PAYLOAD_SIZE 2

byte nodePayload[PAYLOAD_SIZE];

// FLEX SENSOR VARIABLES 
const int FLEX_PIN = A0; // Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(NODE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(FLEX_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  nodePayload[0] = NODE_ADDRESS;
  float angle = calculateAngle();
  nodePayload[1] = angle/4.0;
}

void requestEvent()
{
  Wire.write(nodePayload, PAYLOAD_SIZE);
}

float calculateAngle()
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  //sSerial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  //delay(100);
  //Serial.println("Bend: " + String(angle) + " degrees");
  //Serial.println();

  delay(500);

  return angle;
}

