
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
const long SERIAL_REFRESH_TIME = 100;
#define ArrayLength 20
int valOfZero, valOf90, valOf180;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.println("Yeu cau hieu chinh");
  delay(1000);
  Serial.println("ve 0 do");
  delay(1000);
  valOfZero = calculateOriginalAngleValue();
  Serial.println("ve 90 do");
  delay(1000);
  valOf90 = calculateOriginalAngleValue();
  Serial.println("ve 180 do");
  delay(1000);
  valOf180 = calculateOriginalAngleValue();
  Serial.println("Done....");
  Serial.println(valOfZero);
  Serial.println(valOf90);
  Serial.println(valOf180);
  delay(1000);
}

void loop() {
  int real_value = analogRead(A0);
  
  // put your main code here, to run repeatedly:
  int estimated_value = simpleKalmanFilter.updateEstimate(real_value);
  Serial.println(estimated_value);
  Serial.print(",");
  Serial.println(real_value);
  if (abs(estimated_value - valOfZero) < 30) {
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  } else if (abs(estimated_value - valOf90) < 30) {
    digitalWrite(13, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(12, LOW);
  } else if (abs(estimated_value - valOf180) < 30) {
    digitalWrite(12, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(10, LOW);
    digitalWrite(13, LOW);
  }
  delay(SERIAL_REFRESH_TIME);
}

int calculateOriginalAngleValue() {
  int tong;
  for (int i = 0; i < ArrayLength; i++) {
    tong += simpleKalmanFilter.updateEstimate(analogRead(A0));
    delay(100);
  }
  return tong / ArrayLength;
}

void resetToZero(int* arr, int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = 0;
  }
}