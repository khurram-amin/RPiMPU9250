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
	uint8_t d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
	printf("AK8963 "); printf("I AM "); printf("%X", d);
	printf(" I should be "); printf("0x48");

	myIMU.initAK8963(myIMU.magCalibration);

	while(1)
	{
  // If intPin goes high, all data registers have new data
  // On interrupt, check if data ready interrupt
		if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
		{  
    		myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
    		myIMU.getAres();

		    // Now we'll calculate the accleration value into actual g's
		    // This depends on scale being set
		    myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; // - accelBias[0];
		    myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; // - accelBias[1];
		    myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; // - accelBias[2];

		    myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
		    myIMU.getGres();

		    // Calculate the gyro value into actual degrees per second
		    // This depends on scale being set
		    myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
		    myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
		    myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;

		    myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
		    myIMU.getMres();
		    // User environmental x-axis correction in milliGauss, should be
		    // automatically calculated
		    myIMU.magbias[0] = +470.;
		    // User environmental x-axis correction in milliGauss TODO axis??
		    myIMU.magbias[1] = +120.;
		    // User environmental x-axis correction in milliGauss
		    myIMU.magbias[2] = +125.;

		    // Calculate the magnetometer values in milliGauss
		    // Include factory calibration per data sheet and user environmental
		    // corrections
		    // Get actual magnetometer value, this depends on scale being set
		    myIMU.mx = (float)myIMU.magCount[0]*myIMU.mRes*myIMU.magCalibration[0] -
		    myIMU.magbias[0];
		    myIMU.my = (float)myIMU.magCount[1]*myIMU.mRes*myIMU.magCalibration[1] -
		    myIMU.magbias[1];
		    myIMU.mz = (float)myIMU.magCount[2]*myIMU.mRes*myIMU.magCalibration[2] -
		    myIMU.magbias[2];
  		} // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

  	// Must be called before updating quaternions!
  	myIMU.updateTime();

	  // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
	  // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
	  // (+ up) of accelerometer and gyro! We have to make some allowance for this
	  // orientationmismatch in feeding the output to the quaternion filter. For the
	  // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
	  // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
	  // modified to allow any convenient orientation convention. This is ok by
	  // aircraft orientation standards! Pass gyro rate as rad/s
	  //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
	  	// MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx*DEG_TO_RAD,
	  	// myIMU.gy*DEG_TO_RAD, myIMU.gz*DEG_TO_RAD, myIMU.my,
	  	// myIMU.mx, myIMU.mz, myIMU.deltat);

		if (1)
		{
		  	myIMU.delt_t = myIMU.millis() - myIMU.count;
		  	if (myIMU.delt_t > 500)
		  	{
		  		if(1)
		  		{
		        // Print acceleration values in milligs!
		  			printf("X-acceleration: "); printf("%d", 1000*myIMU.ax);
		  			printf(" mg ");
		  			printf("Y-acceleration: "); printf("%d", 1000*myIMU.ay);
		  			printf(" mg ");
		  			printf("Z-acceleration: "); printf("%d", 1000*myIMU.az);
		  			printf(" mg \n");

		        // Print gyro values in degree/sec
		  			printf("X-gyro rate: "); printf("%d",myIMU.gx);
		  			printf(" degrees/sec ");
		  			printf("Y-gyro rate: "); printf("%d",myIMU.gy);
		  			printf(" degrees/sec ");
		  			printf("Z-gyro rate: "); printf("%d",myIMU.gz);
		  			printf(" degrees/sec\n");

		        // Print mag values in degree/sec
		  			printf("X-mag field: "); printf("%d", myIMU.mx);
		  			printf(" mG ");
		  			printf("Y-mag field: "); printf("%d", myIMU.my);
		  			printf(" mG ");
		  			printf("Z-mag field: "); printf("%d", myIMU.mz);
		  			printf(" mG\n");

			        myIMU.tempCount = myIMU.readTempData();  // Read the adc values
			        // Temperature in degrees Centigrade
			        myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;
			        // Print temperature in degrees Centigrade
			        printf("Temperature is ");  printf("%d", myIMU.temperature);
			        printf(" degrees C\n");
		    	}
				myIMU.count = myIMU.millis();
	        } // if (myIMU.delt_t > 500)
	  	} // if (!AHRS)
	  }
	}
}