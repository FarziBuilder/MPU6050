

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_


#define WHO_AM_I_REG 0x75
#define MPU6050_ADDR (0b1101000 << 1) + 0
#define PWR_MGMT_1_REG 0x6B
#define REG_CONFIG_GYRO 27
#define GYRO_SCALE 0b00010000
#define REG_CONFIG_ACCEL 28
#define ACCEL_SCALE 0b00010000
#define REG_CONFIG_PWR 107

#define AccelRange 8192.0f
#define GValue 9.81f

#define ACCEL_X 0x3B
#define ACCEL_Y 0x3D
#define ACCEL_Z 0x3F

#define GYROCONVERTOR 0.00762962736f

#define GYRO_X 0x43
#define GYRO_Y 0x45
#define GYRO_Z 0x47
#define TIMERFREQUENCY 64000.0f


void mpu6050_Init();
void mpu6050_ReadGyro();
void mpu6050_ReadAccel();
void TimerCheck();
void mpu6050GyroPrint();
void FinalAngle();



#endif /* INC_MPU6050_H_ */
