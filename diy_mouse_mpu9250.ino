#include <BleMouse.h>
#include <Wire.h>
#include <MPU9250_asukiaaa.h>

#define LEFTBUTTON 19
#define RIGHTBUTTON 18
#define SPEED 10

MPU9250_asukiaaa mySensor;

BleMouse bleMouse;

void setup() {
  Serial.begin(115200);

  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);

  bleMouse.begin();
  Wire.begin();

  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag(); // optional

  delay(1000);

  Serial.println("MPU9250 initialized without DMP");
}

void loop() {
  if (!bleMouse.isConnected()) return;

  mySensor.accelUpdate();
  mySensor.gyroUpdate();

  float gx = mySensor.gyroX();
  float gy = mySensor.gyroY();
  float gz = mySensor.gyroZ();

  // Debug
  Serial.print("Gx: "); Serial.print(gx);
  Serial.print(" Gy: "); Serial.print(gy);
  Serial.print(" Gz: "); Serial.println(gz);

  // Control mouse with gyro data
  int dx = (abs(gz) > 0.5) ? (int)(gz * -0.2) : 0;
int dy = (abs(gx) > 0.5) ? (int)(gx * -0.2) : 0;
bleMouse.move(dx, dy);


  if (!digitalRead(LEFTBUTTON)) {
    Serial.println("Left click");
    bleMouse.click(MOUSE_LEFT);
    delay(500);
  }

  if (!digitalRead(RIGHTBUTTON)) {
    Serial.println("Right click");
    bleMouse.click(MOUSE_RIGHT);
    delay(500);
  }
}