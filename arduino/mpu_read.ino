#include <Wire.h>

const int MPU_ADDR = 0x68;
#define sda 4
#define scl 3


int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z; 
char buff[85];

void setup() {
  Wire.begin(); // without param join as master
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(B00001000);
  Wire.endTransmission(false);
  Wire.write(0x6C);
  Wire.write(0x00); 
  Wire.endTransmission(false);
  Wire.write(0x23);
  Wire.write(B01111000); //temp/XG/YG/ZG/ACC/slv2/slv1/slv0
  Wire.endTransmission(false);
  Wire.write(0x18);
  Wire.write(0x00); // gyro fs_range 250 deg/s
  Wire.endTransmission(false);
  Wire.write(0x1C);
  Wire.write(B00001000); // accel fs_range +-4g
  Wire.endTransmission(false);
  Wire.write(0x6A);
  Wire.write(B01000000);
  Wire.endTransmission(false);
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, false);    // request 6 bytes from slave device #2


  acc_x = Wire.read() << 8 | Wire.read();
  acc_y = Wire.read() << 8 | Wire.read();
  acc_z = Wire.read() << 8 | Wire.read();
  
  Wire.write(0x43);
  Wire.requestFrom(MPU_ADDR, 6, true);

  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
  
  
  //sprintf(buff, "gx = %d\tgy = %d\tgz = %d\taccx = %d\taccy = %d\taccz = %d", gyro_x, gyro_y, gyro_z,acc_x, acc_y, acc_z);
  //acc_z = map(acc_z, -32767, 32768, -20, 20); 

//  acc_x = 0;
//  acc_y = 0;
//  acc_z = 0;
  
  sprintf(buff, "%d%d%d%d%d%d" ,gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
  //Serial.println(buff);
  Serial.print("X: "); Serial.print(acc_x); Serial.print("\t");
//  Serial.print("Y: "); Serial.print(gyro_y); Serial.print("\t");
//  Serial.print("Z: "); Serial.print(gyro_z); Serial.print("\t");
  Serial.println("uT");
  delay(20);
}