#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;

char buff[85];


void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
}

void loop() {
  // put your main code here, to run repeatedly:
}
