/////////Header File for Driver////////////

/*
 * BMP280D.h
 *
 *  Created on: Oct 1, 2025
 *      Author: Albert A Lewis
 */

#ifndef BMP280D_H_
#define BMP280D_H_

//#include "stm32f_xx_hal.h"

//Define i2c Addresses
#define I2C_ADDR (0x77<<1) //Shift to left
#define I2C_ALT_ADDR (0x76<<1)

//Define Device ID for device verification
#define DEV_ID 0xD0

//Define Other device Registers
#define CONFIG 0xF5 // -> Configure the device: Stand by mode, Filter, SPI Enabled
#define CRTL_MEAS 0xF4 //-> sets over-sampling and mode
#define STATUS 0xF3 // -> Tells status of device - Measuring at bit 3 or Im_Update at bit 0
#define RESET 0xE0 //-> Resets Device
//Define data registers
#define TEMP_XLSB 0xFC // -> Bits [7:4] + Least significant 4 bits
#define TEMP_LSB 0xFB // -> Bits [7:0]
#define TEMP_MSB 0xFA // -> Bits [7:0]

#define PRESS_XLSB 0xF9 //-> Bits [7:4] + Least significant 4 bits
#define PRESS_LSB 0xF8 //->  Bits [7:0]
#define PRESS_MSB 0xF7 //->  Bits [7:0]

//Define structure to hold calibration data
typedef struct {
	unsigned short T1;
	short T2;
	short T3;
	unsigned short P1;
	short P2;
	short P3;
	short P4;
	short P5;
	short P6;
	short P7;
	short P8;
	short P9;

} BMP280CALIB;

//Define structure to handle sensor
typedef struct {
		I2C_HandleTypeDef *i2c;
	    uint16_t i2c_addr;
	    BMP280CALIB calibration_data;

	    //Temperature and pressure variables, processed 
	    float temp;
	    float press;
} BMP280HANDLE;


//States of sensor connection
typedef enum {
    BMP280_Ok,
    BMP280_Err
} BMP280_result_t;


//Functions, INIT, DATA ACQUISITION, LOW LEVEL FUNCTIONS
BMP280_result_t bmp280_INIT(BMP280HANDLE *bmp280, I2C_HandleTypeDef *i2c, uint16_t i2c_addr);

//Read functions
BMP280_result_t bmp280_Read_Temp(BMP280HANDLE *bmp280);
BMP280_result_t bmp280_Read_Press(BMP280HANDLE *bmp280);

//LOW Level Functions
BMP280_result_t bmp280_Read_Reg(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data); //-> Reads single register
BMP280_result_t bmp280_Read_Regs(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data, uint8_t length); //-> Reads multiple
BMP280_result_t bmp280_Write_Reg(BMP280HANDLE *bmp280, uint8_t reg, uint8_t *data); //Writes to a register

#endif /* BMP280D_H_ */
