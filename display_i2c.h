/*
 * display_i2c.h
 *
 *  Created on: Nov 17, 2024
 *      Author: Matheus
 */

#ifndef INC_DISPLAY_I2C_H_
#define INC_DISPLAY_I2C_H_

void Lcd_Init(); // initialize  LCD

void Send_Cmd(char cmd); // send command to LCD

void Lcd_Put_Cur(int line, int col); // put the cursor at the position line (0 or 1) and column (0 to 15)

void Lcd_Clear (); // clear the LCD scream

void Lcd_Send_Data (char data);  // send data to the lcd

void Lcd_Send_String (char *str);  // send string to the lcd



#endif /* INC_DISPLAY_I2C_H_ */
