/*
 * spi_drive_master.c
 *
 *  Created on: Apr 7, 2021
 *      Author: Administrator
 */


/*
 * spi_drive.c
 *
 *  Created on: 27 окт. 2020 г.
 *      Author: admin
 */

#include <spi_drive_master.h>
//#include "crc.h"

void delay_us(int value)
{
	int tmp = 0;
	while(tmp < 72*value){tmp++;}
}

void spi_read(uint8_t adr, uint8_t numbers)
{

}

void SET_CS()
{
//	GPIOA->BSRR = 0x0010 << 16u;
	GPIOA->BSRR = 0x0010;

//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

void CLR_CS()
{
	GPIOA->BSRR = 0x0010 << 16u;
}

void spi_write(uint8_t adr_reg, uint16_t val)
{
//	uint8_t data[3];
//	msg_write.start.all = adr_reg;
//	msg_write.start.bits.bit0 = 1;
//	data[1] = msg_write.dataHi.all = val >> 8;
//	data[2] = msg_write.dataLow.all = val & 0xff;
//
//	data[0] = msg_write.start.all;
//
//	int crc = crc_calc(data, 3);
//
//	msg_write.crcHi.all = crc >> 8;
//	msg_write.crcLow.all = crc & 0xff;
//
//	SET_CS();
//
//	SPI_SEND_8_BIT(msg_write.start.all);
//	delay_us(20);
//
//	SPI_SEND_8_BIT(msg_write.dataHi.all);
//	delay_us(20);
//
//	SPI_SEND_8_BIT(msg_write.dataLow.all);
//	delay_us(20);
//
//	SPI_SEND_8_BIT(msg_write.crcHi.all);
//	delay_us(20);
//
//	SPI_SEND_8_BIT(msg_write.crcLow.all);
//	delay_us(20);
//
//	SPI_RECEIVE_8_BIT;
//
//	CLR_CS();
//
//	int test;
//
//	if(spiRecBuf == 0b10011011)
//	{
//		test = 10;
//	}
//	else
//		test = 5;

	SET_CS();
	SPI_SEND_8_BIT(adr_reg);
	delay_us(20);
	CLR_CS();
}
