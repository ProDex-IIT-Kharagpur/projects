#include <Servo.h>

Servo horizontalServo;
Servo verticalServo;

int top_left = A0;
int top_right = A1;
int bottom_left = A2;
int bottom_right = A3;

int horizontalPosition = 90;
int verticalPosition = 90;

int lightTolerance = 30;

int stepSize = 2;     

int horizontalDirection = 1;
int verticalDirection = 1;

int minPosition = 10;
int maxPosition = 170;

int readAverage(int pin) {
  long sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 8;
}

void setup() {
  Serial.begin(9600);

  horizontalServo.attach(10);
  verticalServo.attach(9);

  horizontalServo.write(horizontalPosition);
  verticalServo.write(verticalPosition);
  delay(500);
}

void loop() {

  int topLeft = readAverage(top_left);
  int topRight = readAverage(top_right);
  int bottomLeft = readAverage(bottom_left);
  int bottomRight = readAverage(bottom_right);

  int topLight = (topLeft + topRight) / 2;
  int bottomLight = (bottomLeft + bottomRight) / 2;

  int leftLight = (topLeft + bottomLeft) / 2;
  int rightLight = (topRight + bottomRight) / 2;

  if (abs(topLight - bottomLight) > lightTolerance) {
    if (topLight > bottomLight) {
      verticalPosition += stepSize * verticalDirection;
    } else {
      verticalPosition -= stepSize * verticalDirection;
    }

    verticalPosition = constrain(verticalPosition, minPosition, maxPosition);
    verticalServo.write(verticalPosition);
  }

  if (abs(leftLight - rightLight) > lightTolerance) {
    if (leftLight > rightLight) {
      horizontalPosition -= stepSize * horizontalDirection;
    } else {
      horizontalPosition += stepSize * horizontalDirection;
    }

    horizontalPosition = constrain(horizontalPosition, minPosition, maxPosition);
    horizontalServo.write(horizontalPosition);
  }

  Serial.print("TL:"); Serial.print(topLeft);
  Serial.print(" TR:"); Serial.print(topRight);
  Serial.print(" BL:"); Serial.print(bottomLeft);
  Serial.print(" BR:"); Serial.print(bottomRight);
  Serial.print(" | H:"); Serial.print(horizontalPosition);
  Serial.print(" V:"); Serial.println(verticalPosition);

  delay(50);
}