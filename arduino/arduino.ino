

#include <Wire.h>

/* choose desired range by changing var range to coresponding number:
  0 - ,
  1 - ,
  2 - ,
  3 - 
*/
short int range = 0; 


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
  Wire.write(0x00);
  

  calculate_sensor_errors(errors);
  delay(20);
}


void loop() {
  time_current = millis();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); //acc - x,y,z
  
  acc_x = (Wire.read() << 8 | Wire.read()) / 16384.0; //16380.0 from datasheet works only on default ranges
  acc_y = (Wire.read() << 8 | Wire.read()) / 16384.0;
  acc_z = (Wire.read() << 8 | Wire.read()) / 16384.0;


  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  gyro_x = (Wire.read() << 8 | Wire.read()) / 131.0; //131.0 from datasheet for default range
  gyro_y = (Wire.read() << 8 | Wire.read()) / 131.0;
  gyro_z = (Wire.read() << 8 | Wire.read()) / 131.0;

}


void calculate_sensor_errors(float* errors){ 
  /*
    calculating sensor errors for calibration
    errors = {acc_x_error, acc_y_error, acc_z_error, gyro_x_error, gyro_y_error, gyro_z_error} - floats
  */


}
