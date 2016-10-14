#include <stdio>

#include "MPU9250.h"


int main()
{
	MPU9250 myGPU;

	uint8_t c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);

	printf("%u", c);
}