/*
 * imu.c
 *
 *  Created on: Nov 26, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

#define XL_ADDRESS	0xd6

void IMU_init(void)
{
	I2C_init(I2C1, 100000); // 100KHz

	// CTRL_REG5_XL = 0011 1000 = 0x38
	I2C_write_register(I2C1, XL_ADDRESS, 0x1f, 0x38);

	// CTRL_REG6_XL = 101 1 1 0 00 = 0xb8
	I2C_write_register(I2C1, XL_ADDRESS, 0x20, 0xb8);
}

void IMU_read(float * ax, float * ay, float * az)
{
	int16_t accel_data[3];
	I2C_read_buffer(I2C1, XL_ADDRESS, 0x28, (unsigned char *)accel_data, 6);

	*ax = (accel_data[0] * 0.244) / 1000.0;
	*ay = (accel_data[1] * 0.244) / 1000.0;
	*az = (accel_data[2] * 0.244) / 1000.0;
}

int main(void)
{
	CONSOLE_init();
	printf("Premi un tasto per iniziare:\n");
	readchar();
	IMU_init();
	for (;;) {
		float x, y, z;
		IMU_read(&x, &y, &z);
		printf("AX=%9.6f       AY=%9.6f       AZ=%9.6f\n", x, y, z);
		delay_ms(100);
	}
}
