/*
 * display_i2c.c
 *
 *  Created on: Nov 17, 2024
 *      Author: Matheus
 */
#include "main.h"
#include "display_i2c.h"
#include "i2c.h"

#define SLAVE_ADDRESS_LCD 0x4E

void Send_Cmd(char cmd){

	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0 -> bxxxx1100
	data_t[1] = data_u|0x08;  //en=0, rs=0 -> bxxxx1000
	data_t[2] = data_l|0x0C;  //en=1, rs=0 -> bxxxx1100
	data_t[3] = data_l|0x08;  //en=0, rs=0 -> bxxxx1000
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);

}

void Lcd_Send_Data (char data){
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0 -> bxxxx1101
	data_t[1] = data_u|0x09;  //en=0, rs=0 -> bxxxx1001
	data_t[2] = data_l|0x0D;  //en=1, rs=0 -> bxxxx1101
	data_t[3] = data_l|0x09;  //en=0, rs=0 -> bxxxx1001
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void Lcd_Clear (){

	Send_Cmd(0x80);

	for (int i=0; i<70; i++){
		Lcd_Send_Data (' ');
	}
}

void Lcd_Put_Cur(int line, int col){
    switch (line)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    Send_Cmd (col);
}

void Lcd_Init(){

	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	Send_Cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	Send_Cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	Send_Cmd (0x30);
	HAL_Delay(10);
	Send_Cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	Send_Cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	Send_Cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	Send_Cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	Send_Cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	Send_Cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

}

void Lcd_Send_String(char *str)
{
	while (*str) Lcd_Send_Data (*str++);
}

