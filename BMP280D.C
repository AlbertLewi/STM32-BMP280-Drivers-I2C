/*
 * BMP280D.c
 *
 *  Created on: Oct 1, 2025
 *      Author: Albert A Lewis
 */

#include "stm32f3xx_hal.h"
#include "BMP280D.h"
#include <math.h>

//Low Level Functions

//Function to read a single register
BMP280STATUS bmp280_Read_Reg(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data) {
	return HAL_I2C_Mem_Read(bmp280->i2c, I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

//Function to read more than one register at once, notice the length variable in the size parameter
BMP280STATUS bmp280_Read_Regs(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data, uint8_t length) {
	return HAL_I2C_Mem_Read(bmp280->i2c, I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

//Function to write registers
BMP280STATUS bmp280_Write_Reg(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data) {
	return HAL_I2C_Mem_Write(bmp280->i2c, I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}


//INITIALIZE FUNCTION

BMP280STATUS bmp280_INIT(BMP280HANDLE *bmp280, I2C_HandleTypeDef *i2c, uint16_t i2c_addr){
	//Set parameters and set data to 0
	bmp280->i2c = i2c;

	bmp280->temp = 0.0f;
	bmp280->press = 0.0f;

	/*store number of transaction errors
	 *
	 */
	uint8_t errNum = 0;
	BMP280STATUS status;

	/*Check device ID
	 *
	 * Set Data parameter as regData
	 * Set Register to read, check if register is correct
	 *
	 */

	uint8_t regData;
	status = bmp280_Read_Reg(bmp280, DEV_ID, &regData);
	errNum += (status != BMP280_Ok);

	if (regData != DEV_ID) {
		return 255;
	}

	/*
	 * Set modes for sensor
	 * Set regData to do this according to the data sheet: Chapter 4
	 */

	//Put in measurement mode, 00100000, in hex
	regData = 0x20;
	status = bmp280_Write_Reg(bmp280, STATUS, &regData);


	//Mess with unused things later
	//Control measurement over-sampling, Not needed for this driver for simplicity

	//Can control a filter, Not needed yet as data is probably going to be relatively static in a room

	/*Crtl mode will be used for controlling power mode, Using Normal mode
	 * Use register 0xF4
	 *
	 * [1:0], final 2 bits
	 * 11
	 * 00000011
	 *
	 */
	regData = 0x03;
	status = bmp280_Write_Reg(bmp280, CRTL, &regData);

	//If errNum > 0, we got a problem
	return errNum;
}

/*
 * Data Acquisition Functions ///////////////////////
 */

BMP280STATUS bmp280_Read_Temp(BMP280HANDLE *bmp280){

}

BMP280STATUS bmp280_Read_Press(BMP280HANDLE *bmp280){

}

