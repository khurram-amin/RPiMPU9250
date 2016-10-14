#include "MPU9250.h"
#include <wiringPi.h>
#include <iostream>

using namespace std;
int main()
{
	short *data = new short[3];
	MPU9250 mpu9250;
	cout<<"config mpu2950 ";
	mpu9250.initMPU9250();
	cout<<"done!"<<endl;
	while(1)
	{
//		cout<<"reading data ..."<<endl;
		mpu9250.readAccelData(data);
		cout<<"T: "<<mpu9250.readTempInC()<<endl;
		for(int i=0; i<3; i++)
		{
			cout<<i<<": "<<1.0f*data[i]*mpu9250.getAres()<<endl;
		}
		cout<<endl<<endl<<endl;
		delay(1);
	}
}