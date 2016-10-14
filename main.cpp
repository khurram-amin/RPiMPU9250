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
    printf("%d", myIMU.SelfTest[0]); printf("perc of factory value\n");
    printf("y-axis self test: acceleration trim within : ");
	printf("%d", myIMU.SelfTest[1]); printf("perc of factory value\n");
	printf("z-axis self test: acceleration trim within : ");
	printf("%d", myIMU.SelfTest[2]); printf("perc of factory value\n");
	printf("x-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[3]); printf("perc of factory value\n");
	printf("y-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[4]); printf("perc of factory value\n");
	printf("z-axis self test: gyration trim within : ");
	printf("%d", myIMU.SelfTest[5]); printf("perc of factory value\n");	

	//Calibrate gyro and accelerometers, load biases in bias registers
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

    myIMU.initMPU9250();
    // Initialize device for active mode read of acclerometer, gyroscope, and
    // temperature
    printf("MPU9250 initialized for active data mode....\n");

    // Read the WHO_AM_I register of the magnetometer, this is a good test of
    // communication
    byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    printf("AK8963 "); printf("I AM "); printf("%X", d);
    printf(" I should be "); printf("0x48");

}