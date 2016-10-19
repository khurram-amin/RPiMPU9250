/*************************************************************************
 * 
 * CONICS LABS™ PROPRIETARY AND CONFIDENTIAL
 * __________________
 * 
 * Copyrights © [2016] - [2017]
 * Conics Labs Incorporated 
 * All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Conics Labs Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Conics Labs Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material via any medium
 * is strictly forbidden unless prior written permission is obtained
 * from Conics Labs Incorporated. If you have received this file in error, 
 * please notify copyright holder and destroy this and any other copies as instructed.
 *
*************************************************************************/


#ifndef MPU9250REGMAP_H
#define MPU9250REGMAP_H



// All Register Addresses and their purposes are taken from follwoing file
// https://www.invensense.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Magnetometer Registers
#define AK8963_ADDRESS   0x0C  //Self-Test Control: If '1' is written on D6 (7th LSB) of this register then magnetic field for self test is generated. DO NOT WRITE ANYOTHER BIT.  (Read/Write Only)
							   //Possible values 0x00 for normal operations, 0x40 to generate magnetic field for self testing.

#define WHO_AM_I_AK8963  0x00  //Device ID of AK8963. It is described in one byte and fixed value  (Read Only)
							   //Should always return 0x48

#define INFO             0x01  //Device information for AKM (Read Only)

#define AK8963_ST1       0x02  // Data Ready Register (Read Only)
							   // If VALUE = 0x01; then data is ready in single measurement mode or self-test mode. It returns to “0” when any one of ST2 register or measurement data register (HXL to HZH) is read.
							   // If VALUE = 0x10; data has been skipped in continuous measurement mode or external trigger measurement mode

// AKM Data Register: Measurement data is stored in two’s complement and Little Endian format. Measurement range of each axis is from [-32760 to +32760] decimal in 16-bit output.
// +32760 = 4912(maximum value of sensor) Micro Tesla 
// -32760 = 4912(minimum value of sensor) Micro Tesla 
#define AK8963_XOUT_L    0x03  // X-axis measurement data lower 8bit (Read Only)
#define AK8963_XOUT_H    0x04  // X-axis measurement data higher 8bit (Read Only)
#define AK8963_YOUT_L    0x05  // Y-axis measurement data lower 8bit (Read Only)
#define AK8963_YOUT_H    0x06  // Y-axis measurement data higher 8bit (Read Only)
#define AK8963_ZOUT_L    0x07  // Z-axis measurement data lower 8bit (Read Only)
#define AK8963_ZOUT_H    0x08  // Z-axis measurement data higher 8bit (Read Only)


#define AK8963_ST2       0x09  // Data overflow bit D3 (4th LSB) When next measurement stars, it returns to “0”. (Read Only)
							   // D4 (5th LSB) Has two roles:
							   //		1. If 0 it shows that 14-bit output mode is selected. IF 1 then 16-bit output mode is selected.
							   // 		2. When any of measurement data register is read in continuous measurement mode or external trigger measurement mode, it means data reading start and taken as data reading until ST2 register is read. 
							   // 	 	   Therefore, when any of measurement data is read, be sure to read ST2 register at the end.


#define AK8963_CNTL      0x0A  // Operation mode setting (Read Only)
							   // Power down (0x00) D0 Low
							   // Single-measurement (0x01) D0 High
							   // Continuous measurement mode 1 (0x02) D1 High
							   // Continuous measurement mode 2 (0x06) D2 & D1 both High
							   // External trigger measurement mode (0x04) D2 Only High
							   // Self-test (0x08) D3 High
							   // Fuse ROM (0x0F) D1-D3 All High
							   // Output bit setting (D5)
							   //		If 0 then 14-bit mode
							   //		If 1 then 16-bit mode


#define AK8963_CNTL2     0x0B  // Control Register 2 (Read Only)
					    	   // Soft Reset (D0): If High then all registers are re-initialized to default settings. If Low then normal operation.


#define AK8963_ASTC      0x0C  // Self test control (Read/Write Only)
							   // D6: If High then Generate Magentic Field for Self Test. If Low normal operation.


#define AK8963_I2CDIS    0x0F  // I2C disable. This register disables I2C bus interface. I2C bus interface is enabled in default.
							   // To disable I2C Write 0x1B
							   // To enable I2C bus interface, reset AK8963


// ASAX, ASAY, ASAZ: Sensitivity Adjustment values
// Sensitivity adjustment data for each axis is stored to fuse ROM on shipment
// Hadj = H x ( (ASA-128)/256 + 1 ); Do this calculation with RAW data
// 		H = measurement data read out from the measurement data register
//	  ASA = sensitivity adjustment value
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value (Read Only)
#define AK8963_ASAY      0x11  // Fuse ROM y-axis sensitivity adjustment value (Read Only)
#define AK8963_ASAZ      0x12  // Fuse ROM z-axis sensitivity adjustment value (Read Only)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Gyroscope Registers

// Self Testing Gyroscope (Read/Write Only)
// The value in this register indicates the self test output generated during manufacturing tests. This value is to be used to check against subsequent self test outputs performed by the end user.
#define SELF_TEST_X_GYRO 0x00                  
#define SELF_TEST_Y_GYRO 0x01                                                                          
#define SELF_TEST_Z_GYRO 0x02

// Gyro Offset Registers (Read/Write Only)
// These registers are used to remove DC bias from the gyro sensor data output for X, Y and Z axes. The values in these registers are subtracted from the gyro sensor values before going into the sensor registers.
// OffsetLSB = OFFS_USR * 4 / 2^FS_SEL
// OffsetDPS = OFFS_USR * 4 / 2^FS_SEL / Gyro_Sensitivity
// Refer to page 11 of Registermap v1.6
// User-defined trim values for gyroscope
#define XG_OFFSET_H      0x13  // X-Axis High Byte
#define XG_OFFSET_L      0x14  // X-Axis Low Byte
#define YG_OFFSET_H      0x15  // Y-Axis High Byte
#define YG_OFFSET_L      0x16  // Y-Axis Low Byte
#define ZG_OFFSET_H      0x17  // Z-Axis High Byte
#define ZG_OFFSET_L      0x18  // Z-Axis Low Byte

// Gyroscope Configuration (Read/Write Only)
#define GYRO_CONFIG      0x1B  // D7, If High, X-Axis-Gyro-Self-Testing will be turned ON
  							   // D6, If High, Y-Axis-Gyro-Self-Testing will be turned ON
  							   // D5, If High, Z-Axis-Gyro-Self-Testing will be turned ON
							   // D4:D3 = Gyro Full Scale Select
							   //  0x00 = + 250 DPS
							   //  0x01 = + 500 DPS
							   //  0x02 = +1000 DPS
							   //  0x03 = +2000 DPS
							   // D1:D0 = Used to bypass DLPF, Please refer to page 14 of Register Map v1.6 for further detail.

// Gyroscope Measurements (Read Only)
#define GYRO_XOUT_H      0x43 // High Byte of the X-Axis gyroscope output
#define GYRO_XOUT_L      0x44 // Low  Byte of the X-Axis gyroscope output
#define GYRO_YOUT_H      0x45 // High Byte of the Y-Axis gyroscope output
#define GYRO_YOUT_L      0x46 // Low  Byte of the Y-Axis gyroscope output
#define GYRO_ZOUT_H      0x47 // High Byte of the Z-Axis gyroscope output
#define GYRO_ZOUT_L      0x48 // Low  Byte of the Z-Axis gyroscope output


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Accelerometer Registers

// Self Testing Accelerometer (Read/Write Only)
// The value in these registers indicates the self test output generated during manufacturing tests. This value is to be used to check against subsequent self test outputs performed by the end user.
#define SELF_TEST_X_ACCEL 0x0D 
#define SELF_TEST_Y_ACCEL 0x0E    
#define SELF_TEST_Z_ACCEL 0x0F

// Accelerometer Offset Register
#define XA_OFFSET_H      0x77 // D7-D0 = Upper 8-bits of the X accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps
#define XA_OFFSET_L      0x78 // D7-D1 = Lower 7-bits of the X accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps
#define YA_OFFSET_H      0x7A // D7-D0 = Upper 8-bits of the Y accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps
#define YA_OFFSET_L      0x7B // D7-D1 = Lower 7-bits of the Y accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps
#define ZA_OFFSET_H      0x7D // D7-D0 = Upper 8-bits of the Z accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps
#define ZA_OFFSET_L      0x7E // D7-D1 = Lower 7-bits of the Z accelerometer offset cancellation. +/- 16g Offset cancellation in all Full Scale modes, 15 bit 0.98-mg steps


// Accelerometer Configuration Registers (Read/Write Only)
#define ACCEL_CONFIG     0x1C  // D7, If High, X-Axis-Accel-Self-Testing will be turned ON
  							   // D6, If High, Y-Axis-Accel-Self-Testing will be turned ON
  							   // D5, If High, Z-Axis-Accel-Self-Testing will be turned ON
							   // D4:D3 = Accel Full Scale Select
							   //  0x00 = +- 2 G
							   //  0x01 = +- 4 G
							   //  0x02 = +- 8 DPS
							   //  0x03 = +- 16

#define ACCEL_CONFIG2    0x1D  // D3    = Used to bypass DLPF, Please refer to page 15 of Register Map v1.6 for further detail.
							   // D2:D0 = Accelero Low Pass Filter Settings, Please refer to page 15 of Register Map v1.6 for further detail.


// Accelerometer Measurements (Read Only)
#define ACCEL_XOUT_H     0x3B  // High byte of Accelerometer X-Axis data
#define ACCEL_XOUT_L     0x3C  // Low  byte of Accelerometer X-Axis data
#define ACCEL_YOUT_H     0x3D  // High byte of Accelerometer Y-Axis data
#define ACCEL_YOUT_L     0x3E  // Low  byte of Accelerometer Y-Axis data
#define ACCEL_ZOUT_H     0x3F  // High byte of Accelerometer Z-Axis data
#define ACCEL_ZOUT_L     0x40  // Low  byte of Accelerometer Z-Axis data



#define LP_ACCEL_ODR     0x1E  // Low Power Accelerometer ODR Control (Read/Write Only)
							   // D3:D0 = Sets the frequency of waking up the chip to take a sample of accel data – the low power accel Output Data Rate.
							   // Please refer to page 17 of Register Map v1.6 for further detail.

#define WOM_THR          0x1F  // Wake-on Motion Threshold
							   // This register holds the threshold value for the Wake on Motion Interrupt for accel x/y/z axes. LSB = 4mg. Range is 0mg to 1020mg.
							   // For more details on how to configure the Wake-on-Motion interrupt, please refer to section 5 in the MPU-9250 Product Specification document.

// Accelerometer Interrupt Control
#define MOT_DETECT_CTRL  0x69  // D7 = ACCEL_INTEL_EN = This bit enables the Wake-on-Motion detection logic.
							   // D6 = ACCEL_INTEL_MODE = If set, compares the current sample with the previous one.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Temperature Sensor Registers (Registers that effect Temperature Sensor)


// Temperature Measurements Data
#define TEMP_OUT_H       0x41 // High Byte of the Temperature Sensor Output
#define TEMP_OUT_L       0x42 // Low  Byte of the Temperature Sensor Output

// To convert Temperrature Sensor Output into Celsius, use the following equation
// TEMP_degC = ((TEMP_OUT – RoomTemp_Offset)/Temp_Sensitivity) + 21degC
// Temp_degC = Temperature in Celsius
// Temp_Out  = actual output of the sensor



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// General Registers (Registers that effect both Accelerometer and Gyroscope)


// Divides the internal sample rate (see register CONFIG) to generate the sample rate that controls sensor data output rate, FIFO sample rate. (Read/Write Only)
// NOTE: This register is only effective when Fchoice = 2’b11 (fchoice_b register bits are 2’b00), and (0 < dlpf_cfg < 7), such that the average filter’s output is selected (see chart below).
// This is the update rate of sensor register.
// SAMPLE_RATE= Internal_Sample_Rate / (1 + SMPLRT_DIV)
// Data should be sampled at or above sample rate; SMPLRT_DIV is only used for1kHz internal sampling.
#define SMPLRT_DIV       0x19

// Configuration Register
#define CONFIG           0x1A  // D6    = Low, When FIFO is full additional data will be written to the FIFO, replacing the oldest data
							   //       = High, When FIFO is full additional data will be not be written to the FIFO
							   // D5:D3 = Enables the FSYNC pin data to be sampled
							   //  0x00 = Function Disabled
							   //  0x01 = TEMP_OUT_L[0]
							   //  0x02 = GYRO_XOUT_L[0]
							   //  0x03 = GYRO_YOUT_L[0]
							   //  0x04 = GYRO_ZOUT_L[0]
							   //  0x05 = ACCEL_XOUT_L[0]
							   //  0x06 = ACCEL_YOUT_L[0]
							   //  0x07 = ACCEL_ZOUT_L[0]
							   //
							   // D2:D0 = DLPF_CFG, For details please refer to the page 13 of Register map v1.6

#define FIFO_EN          0x23  // FIFO Enable (Read/Write Only)
							   // D7 = TEMP_OUT = if HIGH, Write TEMP_OUT_H and TEMP_OUT_L to the FIFO at the sample rate;
							   // D6 = GYRO_XOUT = if HIGH, Write GYRO_XOUT_H and GYRO_XOUT_L to the FIFO at the sample rate;
							   // D5 = GYRO_YOUT = if HIGH, Write GYRO_YOUT_H and GYRO_YOUT_L to the FIFO at the sample rate;
							   // D4 = GYRO_ZOUT = if HIGH, Write GYRO_ZOUT_H and GYRO_ZOUT_L to the FIFO at the sample rate;
							   // D3 = ACCEL_OUT = if HIGH, write ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H, ACCEL_YOUT_L, ACCEL_ZOUT_H, and ACCEL_ZOUT_L to the FIFO at the sample rate;
							   // D2 = SLV_2 = if HIGH, write EXT_SENS_DATA registers associated to SLV_2 (as determined by I2C_SLV0_CTRL, I2C_SLV1_CTRL, and I2C_SL20_CTRL) to the FIFO at the sample rate;
							   // D1 = SLV_1 = if HIGH, write EXT_SENS_DATA registers associated to SLV_1 (as determined by I2C_SLV0_CTRL and I2C_SLV1_CTRL) to the FIFO at the sample rate;
							   // D0 = SLV_0 = if HIGH, rite EXT_SENS_DATA registers associated to SLV_0 (as determined by I2C_SLV0_CTRL) to the FIFO at the sample rate;

// Interrupt Registers

#define INT_PIN_CFG      0x37 // INT Pin/Bypass Enable configurations (Read/Write Only)
							  // D7 = ACTL = if High, the logic level of INT pin is active-low else the logic level of INT pin will be active-high.
							  // D6 = OPEN = If High, INT pin is configured as open drain else INT pin is configured as push-pull.
							  // D5 = LATCH_INT_EN = If High, INT pin level is held high until interrupt status is cleared
							  //				   = If Low,  INT pin indicates interrupt pulse’s is width 50us.
							  // D4 = INT_ANYRD_2CLEAR = if High, Interrupt status is cleared if any read operation is performed.
							  //                       = if Low , Interrupt status is cleared only by reading INT_STATUS register.
							  // D3 = ACTL_FSYNC = If High, The logic level for the FSYNC pin as an interrupt is active low.
							  // 				 = If Low , The logic level for the FSYNC pin as an interrupt is active high.
							  // D2 = FSYNC_INT_MODE_EN = If High, this enables the FSYNC pin to be used as an interrupt. For further details please refere to the page 29 of Register map v1.6
							  // D1 = BYPASS_EN = If High, I2C_MASTER interface pin will fo into bypass.

#define INT_ENABLE       0x38 // Interrupt Enable Register (Read/Write Only)
							  // D6 = WOM_EN = If High, enable interrupt for wake on motion to propagate to the interrupt pin else the function is disabled.
							  // D4 = FIFO_OVERFLOW_EN = If High, Enable interrupt for FIFO overflow to propagate to interrupt pin else this function is disabled.
							  // D3 = FSYNC_INT_EN = If High, enable FSYNC interrupt to propogate to the interrupt pin else this funciton is disabled.
							  // D0 = RAW_RDY_EN = Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin. The timing of the interrupt can vary depending on the setting in register 36 I2C_MST_CTRL, bit [6] WAIT_FOR_ES.
							  //	  For further details please refer to the page 30 of Register map v1.6

#define INT_STATUS       0x3A // Interrupt Status Register (Read/Clear Only)
							  // D6 = WOM_INT = If High, WAKE ON MOTION interrupt occured.
							  // D4 = FIFO_OVERFLOW_INT = IF High, FIFO Overflow interrupt occured. Note that in this case oldest data has been DROPPED-OFF from FIFO.
							  // D3 = FSYNC_INT = If High, FSYNC interrupt occured.
							  // D0 = RAW_DATA_RDY_INT = Sensor Register Raw Data sensors are updated and Ready to be read. The timing of the interrupt can vary depending on the setting in register 36 I2C_MST_CTRL, bit [6] WAIT_FOR_ES.
							  //	  For further details please refer to the page 30 of Register map v1.6								

// Signal Path Reset
#define SIGNAL_PATH_RESET  0x68 // D2 = GYRO_RESET  = Reset gyro digital signal path. Note: Sensor registers are not cleared. Use SIG_COND_RST to clear sensor registers.
								// D1 = ACCEL_RESET = Reset accel digital signal path. Note: Sensor registers are not cleared. Use SIG_COND_RST to clear sensor registers.
								// D0 = TEMP_RESET  = Reset temp digital signal path. Note: Sensor registers are not cleared. Use SIG_COND_RST to clear sensor registers.

// User Control Register (Read/Write Only)
#define USER_CTRL        0x6A // D6 = FIFO_EN = If High then enabels the FIFO operation mode. If low then Disable FIFO access from serial interface. To disable FIFO writes by dma, use FIFO_EN register. To disable possible FIFO writes from DMP, disable the DMP.
							  // D5 = I2C_MST_EN = If High then Enable the I2C Master I/F module; pins ES_DA and ES_SCL are isolated from pins SDA/SDI and SCL/ SCLK. 
							  //				   If Low then Disable I2C Master I/F module; pins ES_DA and ES_SCL are logically driven by pins SDA/SDI and SCL/ SCLK.
							  // NOTE: DMP will run when enabled, even if all internal sensors are disabled, except when the sample rate is set to 8Khz.
							  // D4 = I2C_IF_DIS = If High, Disable I2C Slave module and put the serial interface in SPI mode only.
							  // D2 = FIFO_RESET = IF High, Reset FIFO module. Reset is asynchronous. This bit auto clears after one clock cycle.
							  // D1 = I2C_MST_RESET = If High, Reset I2C Master module. Reset is asynchronous. This bit auto clears after one clock cycle.
							  //      NOTE: This bit should only be set when the I2C master has hung. If this bit is set during an active I2C master transaction, the I2C slave will hang, which will require the host to reset the slave.
							  // D0 = SIG_COND_RESET = If High, Reset all gyro digital signal path, accel digital signal path, and temp digital signal path. This bit also clears all the sensor registers. SIG_COND_RST is a pulse of one clk8M wide.

// Power Management 1 (Read/Write Only)
#define PWR_MGMT_1       0x6B // D7 = H_RESET = If High then Reset the internal registers and restores the default settings. Write a 1 to set the reset, the bit will auto clear.
							  // D6 = SLEEP = If High then the chip is set to sleep mode (After OTP loads, the PU_SLEEP_MODE bit will be written here)
							  // D5 = CYCLE = IF High then and SLEEP and STANDBY are not set, the chip will cycle between sleep and taking a single sample at a rate determined by LP_ACCEL_ODR register
							  // 	NOTE: When all accelerometer axis are disabled via PWR_MGMT_2 register bits and cycle is enabled, the chip will wake up at the rate determined by the respective registers above, but will not take any samples.
							  // D4 = GYRO_STANDBY = If High, the gyro drive and pll circuitry are enabled, but the sense paths are disabled. This is a low power mode that allows quick enabling of the gyros.
							  // D3 = PD_PTAT = If High then Power down internal PTAT voltage generator and PTAT ADC
							  // D2:D0 = CLKSEL; 
							  //	0x00 - Internal 20MHz Oscillator
							  //	0x01 - Auto selects the best available clock source – PLL if ready, else use the Internal oscillator
							  //	0x02 - Auto selects the best available clock source – PLL if ready, else use the Internal oscillator
							  //	0x03 - Auto selects the best available clock source – PLL if ready, else use the Internal oscillator
							  //	0x04 - Auto selects the best available clock source – PLL if ready, else use the Internal oscillator
							  //	0x05 - Auto selects the best available clock source – PLL if ready, else use the Internal oscillator
							  //	0x06 - Internal 20MHz Oscillator
							  //	0x07 - Stops the clock and keeps timing generator in reset
							  //	Note: (After OTP loads, the inverse of PU_SLEEP_MODE bit will be written to CLKSEL[0])

// Power Management 2 (Read/Write Only)
#define PWR_MGMT_2       0x6C // D5 = DISABLE_X_ACCEL = If High, X accelerometer is disabled else X accelerometer is ON.
							  // D4 = DISABLE_Y_ACCEL = If High, Y accelerometer is disabled else Y accelerometer is ON.
							  // D3 = DISABLE_Z_ACCEL = If High, Z accelerometer is disabled else Z accelerometer is ON.
							  // D2 = DISABLE_X_GYRO = If High, X gyroscope is disabled else X gyroscope is ON.
							  // D1 = DISABLE_Y_GYRO = If High, Y gyroscope is disabled else Y gyroscope is ON.
							  // D0 = DISABLE_Z_GYRO = If High, Z gyroscope is disabled else Z gyroscope is ON.

/* LOW POWER MODE USING ONLY ACCELEROMETER
The MPU-9250 can be put into Accelerometer Only Low Power Mode using the following steps:
(i) Set CYCLE bit to 1
(ii) Set SLEEP bit to 0
(iii) Set TEMP_DIS bit to 1
(iv) Set DIS_XG, DIS_YG, DIS_ZG bits to 1
The bits mentioned in the steps (i) to (iii) can be found in Power Management 1 register (Register 107).
In this mode, the device will power off all devices except for the primary I2C interface, waking only the accelerometer at fixed intervals to take a single measurement.
*/

// FIFO COUNTH (Read Only)
#define FIFO_COUNTH      0x72 // D4:D0 = FIFO_COUNT[12:8] = High Bits, count indicates the number of written bytes in the FIFO.
							  // 		 Reading this byte latches the data for both FIFO_COUNTH, and FIFO_COUNTL.
#define FIFO_COUNTL      0x73 // D7:D0 = FIFO_COUNT[ 7:0] = Low Bits, count indicates the number of written bytes in the FIFO. 
							  //		 NOTE: Must read FIFO_COUNTH to latch new data for both FIFO_COUNTH and FIFO_COUNTL.

// FIFO Read Write (Read/Write Only)
#define FIFO_R_W         0x74 // Read/Write command provides Read or Write operation for the FIFO.
							  // For further detail of the process please refer to page 43 of Register Map v1.6

// WHO AM I? (Read Only)
#define WHO_AM_I_MPU9250 0x75 // Register to indicate to user which device is being accessed.
							  // Should return 0x71


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// I2C Registers

#define I2C_MST_CTRL     0x24  // I2C Master Control (Read/Write Only)
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36

#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66

#define I2C_MST_DELAY_CTRL 0x67


// External Slaves on I2C 

#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// These register addresses are not in the specifications

// #define SELF_TEST_A      0x10
// #define MOT_DUR          0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
// #define ZMOT_THR         0x21  // Zero-motion detection threshold bits [7:0]
// #define ZRMOT_DUR        0x22  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
// #define DMP_INT_STATUS   0x39  // Check DMP interrupt
// #define MOT_DETECT_STATUS 0x61
// #define DMP_BANK         0x6D  // Activates a specific bank in the DMP
// #define DMP_RW_PNT       0x6E  // Set read/write pointer to a specific start address in specified DMP bank
// #define DMP_REG          0x6F  // Register in DMP from which to read or to which to write
// #define DMP_REG_1        0x70
// #define DMP_REG_2        0x71 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Using the MSENSR-9250 breakout board, ADO is set to 0 
// Seven-bit device address is 110100 for ADO = 0 and 110101 for ADO = 1
// mbed uses the eight-bit device address, so shift seven-bit addresses left by one!
#define ADO 0
#if ADO
	#define MPU9250_ADDRESS 0x69  // Device address when ADO = 1
#else
	#define MPU9250_ADDRESS 0x68  // Device address when ADO = 0
#endif  

#endif 
//IFNDEF MPU9250RegMap