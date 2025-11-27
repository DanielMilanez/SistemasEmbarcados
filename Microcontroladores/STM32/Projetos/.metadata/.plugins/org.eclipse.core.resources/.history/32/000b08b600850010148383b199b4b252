#ifndef INC_MCU6050_H_
#define INC_MCU6050_H_

#include "main.h"
#define MPU6050_ADDR (0x68 << 1)

// Registers
#define REG_CONFIG			0x1A

#define REG_CONFIG_GYRO 	0x1B
#define REG_CONFIG_ACC  	0x1C

#define REG_PWR_CTRL		0x6B

#define REG_ACC_DATA		0x3D
#define REG_GYRO_DATA 		0x43
#define REG_TEMP_DATA 		0x41

typedef enum{
	STATUS_OK,
    DEVICE_NOT_EXIST,
    CANT_ACESS_REG_GYRO,
    CANT_ACESS_REG_ACC,
    CANT_ACESS_REG_PWR
}MPU6050_STATUS;

typedef struct{
	int16_t AccXValue,
			AccYValue,
			AccZValue;

	int16_t GyroXValue,
			GyroYValue,
			GyroZValue;

	float Temperature;

}MPU6050_VALUES;

MPU6050_STATUS MPU6050_StartUp(void);
MPU6050_STATUS MPU6050_TestMode(void);
MPU6050_VALUES MPU6050_ReadValues(void);

#endif /* INC_MCU6050_H_ */
