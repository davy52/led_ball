

#include <Wire.h>

#define gyro_range  2 // while "testing" found out that 1000*//s is about max for normal handling 
#define acc_range  0
/* choose desired range by changing var range to coresponding number:
  0 - gyro 250*\/s accel 2g
  1 - gyro 500*\/s accel 4g
  2 - gyro 1000*\/s accel 8g
  3 - gyro 2000*\/s accel 16g
*/

//                                                                      is it possible to define arrays?
float gyro_sens[4] = {131, 65.5, 32.8, 16.4}; 
float acc_sens[4] = {16384, 8192, 4096, 2048};


const int MPU_ADDR = 0x68;

float acc_x, acc_y, acc_z;
float gyro_x, gyro_y, gyro_z;

float gyro_angle_x, gyro_angle_y, gyro_angle_z;

float time_current, time_previous, time_elapsed;

float errors[6] = {0};           
float* acc_x_error = &(errors[0]);
float* acc_y_error = &(errors[1]);
float* acc_z_error = &(errors[2]);
float* gyro_x_error = &(errors[3]);
float* gyro_y_error = &(errors[4]);
float* gyro_z_error = &(errors[5]);





void setup() {
  Serial.begin(19200);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(B10000000); //mpu reset
  Wire.endTransmission(true);
  delay(20);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(B00001000); //disable temp_sens
  Wire.endTransmission(true);

  // ranges:
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1B);
  Wire.write(0x00 | (gyro_range << 3));
  Wire.endTransmission(false);
  Wire.write(0x1C);
  Wire.write(0x00 | (acc_range << 3));
  Wire.endTransmission(true);
  

  calculate_sensor_errors(errors);
  delay(20);
}


void loop() {
  time_current = millis();

  //reading accel values - not used now
  // Wire.beginTransmission(MPU_ADDR);
  // Wire.write(0x3B);
  // Wire.endTransmission(false);
  // Wire.requestFrom(MPU_ADDR, 6, true); //acc - x,y,z
  
  // acc_x = (Wire.read() << 8 | Wire.read()) / acc_sens[acc_range]; 
  // acc_y = (Wire.read() << 8 | Wire.read()) / acc_sens[acc_range];
  // acc_z = (Wire.read() << 8 | Wire.read()) / acc_sens[acc_range];

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  gyro_x = (Wire.read() << 8 | Wire.read()) / gyro_sens[gyro_range];
  gyro_y = (Wire.read() << 8 | Wire.read()) / gyro_sens[gyro_range];
  gyro_z = (Wire.read() << 8 | Wire.read()) / gyro_sens[gyro_range];

  Serial.println(gyro_z);
}


void calculate_sensor_errors(float* errors){ 
  /*
    calculating sensor errors for calibration
    errors = {acc_x_error, acc_y_error, acc_z_error, gyro_x_error, gyro_y_error, gyro_z_error} - floats
  */


}
