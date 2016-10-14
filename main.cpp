#include <stdio.h>

#include "MPU9250.h"


int main()
{
	MPU9250 myIMU;

	uint8_t c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);

	printf("%u", c);
}