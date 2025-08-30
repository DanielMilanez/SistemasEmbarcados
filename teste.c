#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef enum{
    DEVICE_NOT_EXIST = 1,
    CANT_ACESS_REG_GYRO = 2,
    CANT_ACESS_REG_ACC = 3,
    CANT_ACESS_REG_PWR = 4
}MPU180_STATUS;


MPU180_STATUS MPU180_StartUp(int verify);

int main(void){

}

MPU180_STATUS MPU180_StartUp(int verify){

    if(verify == 0) return DEVICE_NOT_EXIST;
}