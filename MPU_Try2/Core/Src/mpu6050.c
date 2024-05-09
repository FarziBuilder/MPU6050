#include <mpu6050.h>
#include <main.h>
#include <stdio.h>
#include <math.h>



extern I2C_HandleTypeDef hi2c1;
float calib_gyroX = 0.0f;
float calib_gyroY = 0.0f;
float calib_gyroZ = 0.0f;
uint32_t previousTime = 0;
extern TIM_HandleTypeDef htim1;
//extern angX,angY,angZ;
float angX1 = 0;
float angY1 = 0;
float angZ1 = 0;
float final_gyro_X, final_gyro_Y,final_gyro_Z;
float gyro_X, gyro_Y,gyro_Z;
float final_accel_X, final_accel_Y, final_accel_Z;
double AngleRoll, AngleYaw, AnglePitch;


void mpu6050_Init(){
	  HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, MPU6050_ADDR, 1, 100);

	  if (ret == HAL_OK){
		  printf("I AM READYY!");
	  }
	  else{
		  printf("NOOOO!!!");
	  }

	  uint8_t temp_data = GYRO_SCALE;

	  ret = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_CONFIG_GYRO, 1, &temp_data, 1, 100);

	  if (ret == HAL_OK)
	  {
		  printf("Written gyro! \n");
	  }
	  else
	  {
		  printf("NOT WRITTEN IN GYRO!!! \n");
	  }

	  temp_data = ACCEL_SCALE;

	  ret = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_CONFIG_ACCEL, 1, &temp_data, 1, 100);

	  if (ret == HAL_OK)
	  	  {
	  		  printf("Written accel! \n");
	  	  }
	  	  else
	  	  {
	  		  printf("NOT WRITTEN IN ACCEL!!! \n");
	  	  }

	  temp_data = 0;

	  ret = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_CONFIG_PWR, 1, &temp_data, 1, 100);

	  if (ret == HAL_OK)
		  {
			  printf("Power Mode ON! \n");
		  }
		  else
		  {
			  printf("Power Mode OFF!!! \n");
		  }
}

void mpu6050_ReadAccel()
{
	uint8_t dataX[2];
	HAL_StatusTypeDef retX = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_X, 1, dataX, 1, 100);

	uint16_t combinedX = (dataX[0] << 8) | dataX[1];
	int16_t accelX = (int16_t)combinedX;
	final_accel_X = (accelX/AccelRange) * GValue;

//	if (retX == HAL_OK)
//	  {
//		printf("AccelX is %f \n",final_accel_X);
//	  }
//	  else
//	  {
//		  printf("OFF!!! \n");
//	  }

	uint8_t dataY[2];
	HAL_StatusTypeDef retY = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_Y, 1, dataY, 1, 100);

	uint16_t combinedY = (dataY[0] << 8) | dataY[1];
	int16_t accelY = (int16_t)combinedY;
	final_accel_Y = (accelY/AccelRange) * GValue;

//	if (retY == HAL_OK)
//	  {
//		printf("AccelY is %f \n",final_accel_Y);
//	  }
//	  else
//	  {
//		  printf("OFF!!! \n");
//	  }

	uint8_t dataZ[2];
	HAL_StatusTypeDef retZ = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_Z, 1, dataZ, 1, 100);

	uint16_t combinedZ = (dataZ[0] << 8) | dataZ[1];
	int16_t accelZ = (int16_t)combinedZ;
	final_accel_Z = (accelZ/AccelRange) * GValue;

//	if (retZ == HAL_OK)
//	  {
//		printf("AccelZ is %f \n",final_accel_Z);
//	  }
//	  else
//	  {
//		  printf("OFF!!! \n");
//	  }

	double AngleRoll = atan(final_accel_Y/sqrt(final_accel_X * final_accel_X + final_accel_Z*final_accel_Z)) * 1/(3.142/180) + 3.578485f;
	double AnglePitch = -atan(final_accel_X/sqrt(final_accel_Y*final_accel_Y + final_accel_Z*final_accel_Z))*1/(3.142/180);
	double AngleYaw = atan(final_accel_Z/sqrt(final_accel_X*final_accel_X + final_accel_Y*final_accel_Y)* 1/(3.142/180)) + 1.569705f;

//	printf("Roll Angle is %f\n", AngleRoll);
//	printf("Pitch Angle is %f\n", AnglePitch);
//	printf("Yaw Angle is %f\n", AngleYaw);

	printf("\n \n \n \n");
}

void mpu6050_ReadGyro()
{
	uint8_t dataX[2];
	HAL_StatusTypeDef retX = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, GYRO_X, 1, dataX, 1, 100);

	uint16_t combinedX = (dataX[0] << 8) | dataX[1];
	int16_t accelX = (int16_t)combinedX;
	final_gyro_X = (accelX * GYROCONVERTOR) + 1.953141f;

	if (retX == HAL_OK)
	  {
		//printf("GyroX is %f \n",final_gyro_X);
	  }
	  else
	  {
		  printf("OFFX!!! \n");
	  }

	uint8_t dataY[2];
	HAL_StatusTypeDef retY = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, GYRO_Y, 1, dataY, 1, 100);

	uint16_t combinedY = (dataY[0] << 8) | dataY[1];
	int16_t accelY = (int16_t)combinedY;
	final_gyro_Y = (accelY * GYROCONVERTOR) - 0.022888f;

	if (retY == HAL_OK)
	  {
		//printf("GyroY is %f \n",final_gyro_Y);
	  }
	  else
	  {
		  printf("OFFY!!! \n");
	  }

	uint8_t dataZ[2];
	HAL_StatusTypeDef retZ = HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, GYRO_Z, 1, dataZ, 1, 100);

	uint16_t combinedZ = (dataZ[0] << 8) | dataZ[1];
	int16_t accelZ = (int16_t)combinedZ;
	final_gyro_Z = (accelZ * GYROCONVERTOR);

	if (retZ == HAL_OK)
	  {
		//printf("GyroZ is %f \n",final_gyro_Z);
	  }
	  else
	  {
		  printf("OFFZ!!! \n");
	  }

	uint32_t currentTime = __HAL_TIM_GET_COUNTER(&htim1);
	float TickSpan, TimeSpan;
	if(currentTime < previousTime){
		TickSpan = (65535.0f - previousTime) + currentTime;
		//printf("OverFlow\n");
		//TickSpan = (float) TickSpan;
	}else{
		TickSpan = currentTime - previousTime;
		//printf("Chill calc\n");
	}


	TimeSpan = TickSpan / 64000.0f;

	gyro_X = 0.7f * gyro_X + 0.3f * final_gyro_X;
	gyro_Y = 0.7f * gyro_Y + 0.3f * final_gyro_Y;
	gyro_Z = 0.7f * gyro_Z + 0.3f * final_gyro_Z;

	//printf("\nThe TimeValues  is %f %f, %f\n",TimeSpan, TickSpan, TIMERFREQUENCY);
//	float angX,angY,angZ;
	angX1 += gyro_X * TimeSpan;
	angY1 += gyro_Y * TimeSpan;
	angZ1 += gyro_Z * TimeSpan;

	//printf("\n\n 1GyroX is %f \n GyroY is %f \n GyroZ is %f \n\n", gyro_X, gyro_Y, gyro_Z);

	if(__HAL_TIM_GET_COUNTER(&htim1) >= 60000)
	{
		//printf("2GyroX is %f \n GyroY is %f \n GyroZ is %f \n\n",angX1 , angY1, angZ1);
	}


	previousTime = currentTime;


//	for(int i=0;i<2000;i++)
//	{
//		calib_gyroX += final_gyro_X;
//		calib_gyroY += final_gyro_Y;
//		calib_gyroZ += final_gyro_Z;
//	}
//
//	printf("\n Calib values of X is %f\nCalib values of Y is %f\nCalib values of Z is %f\n",calib_gyroX/2000.0f,calib_gyroY/2000.0f,calib_gyroZ/2000.0f);

	//printf("\n");
}



void mpu6050GyroPrint()
{
	//write the code which takes gyro and accelerometer readings, to get accurate orientations.
	mpu6050_ReadGyro();
	//printf("GyroX is %f \n GyroY is %f \n GyroZ is %f \n\n",angX , angY, angZ);

}


//void FinalAngle()
//{
//	Mpu6050_ReadGyro(); //final_gyro values updated
//	mpu6050_ReadAccel();
//
//	float angle_pitch = 0.996f * angX1 + 0.004f * AnglePitch;
//	float angle_roll = 0.996f * angY1 + 0.004f * AngleRoll;
//	float angle_yaw = 0.996f * angZ1 + 0.004f * AngleYaw;
//
//	angle_pitch -= angle_roll * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the roll angle to the pitch angel.
//	angle_roll += angle_pitch * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the pitch angle to the roll angel.
//
//	printf("\nPitch Angle is %f Roll Angle is %f\n\n",angle_pitch, angle_roll);
//
//}

void TimerCheck()
{
//	uint32_t currentTime = __HAL_TIM_GET_COUNTER(&htim1);
//
//	printf("\n %u", currentTime);
//
//	uint32_t ticksElapsed = currentTime - previousTime;
//	uint32_t timeElapsed = ticksElapsed / TIMERFREQUENCY;
//	__HAL_TIM_SET_COUNTER(&htim1, 0);  // Reset the counter to 0

//
//
//
//	previousTime = currentTime;
}








