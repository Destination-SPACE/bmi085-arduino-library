#include <Wire.h> 
#define BMI085_accel 0x18
#define BMI085_gyro 0x68

void setup() { 
  Wire.begin();
  Serial.begin(9600);
  // ACC_SOFTRESET
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x00);
  Wire.endTransmission();
  
  // ACC_PWR_CTRL ENABLE
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x7D);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(50);
} 

void loop() {
  delay(0);
  // Set start byte as ACC_X_LSB
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x12);
  Wire.endTransmission();

  // Request 6 bytes from ACC
  Wire.beginTransmission(BMI085_accel);
  Wire.requestFrom(BMI085_accel,6); 
  byte ACC_X_LSB = Wire.read();
  byte ACC_X_MSB = Wire.read();
  byte ACC_Y_LSB = Wire.read();
  byte ACC_Y_MSB = Wire.read();
  byte ACC_Z_LSB = Wire.read();
  byte ACC_Z_MSB = Wire.read();
  Wire.endTransmission();
  delay(0);

  // Set start byte as RATE_X_LSB
  Wire.beginTransmission(BMI085_gyro);
  Wire.write(0x02);
  Wire.endTransmission();

  // Request 6 bytes from GYRO
  Wire.beginTransmission(BMI085_gyro);
  Wire.requestFrom(BMI085_gyro,6);
  byte GYRO_X_LSB = Wire.read();
  byte GYRO_X_MSB = Wire.read();
  byte GYRO_Y_LSB = Wire.read();
  byte GYRO_Y_MSB = Wire.read();
  byte GYRO_Z_LSB = Wire.read();
  byte GYRO_Z_MSB = Wire.read();
  Wire.endTransmission();

  float accelX = (int16_t)(ACC_X_MSB << 8 | ACC_X_LSB) * 0.00120971; 
  float accelY = (int16_t)(ACC_Y_MSB << 8 | ACC_Y_LSB) * 0.00120971; 
  float accelZ = (int16_t)(ACC_Z_MSB << 8 | ACC_Z_LSB) * 0.00120971;

  float gyroX = (int16_t)(GYRO_X_MSB << 8 | GYRO_X_LSB) * 0.03051757812;
  float gyroY = (int16_t)(GYRO_Y_MSB << 8 | GYRO_Y_LSB) * 0.03051757812;
  float gyroZ = (int16_t)(GYRO_Z_MSB << 8 | GYRO_Z_LSB) * 0.03051757812;

  Serial.print(accelX, 3); Serial.print(",");
  Serial.print(accelY, 3); Serial.print(",");
  Serial.print(accelZ, 3); Serial.print(",");
  Serial.print(gyroX, 3); Serial.print(",");
  Serial.print(gyroY, 3); Serial.print(",");
  Serial.println(gyroZ, 3);
}
