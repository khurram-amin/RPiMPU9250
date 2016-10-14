#include <stdio.h>

#include "MPU9250.h"


int main()
{
	MPU9250 myIMU;

	uint8_t c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);

	printf("%u\n", c);

	printf("MPU9250 is online...");

    // Start by performing self test and reporting values
    myIMU.MPU9250SelfTest(myIMU.SelfTest);
    printf("x-axis self test: acceleration trim within : ");
    printf("%d", myIMU.SelfTest[0]); printf("% of factory value\n");
    printf("y-axis self test: acceleration trim within : ");
	printf("%d", myIMU.SelfTest[1]); print("% of factory value\n");
	printf("z-axis self test: acceleration trim within : ");
	printf("%d", myIMU.SelfTest[2]); printf("% of factory value\n");
	printf("x-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[3]); printf("% of factory value\n");
	printf("y-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[4]); printf("% of factory value\n");
	printf("z-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[5]); printf("% of factory value\n");	

	//Calibrate gyro and accelerometers, load biases in bias registers
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
}