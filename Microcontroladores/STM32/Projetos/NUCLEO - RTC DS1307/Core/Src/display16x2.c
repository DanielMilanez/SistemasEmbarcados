/*
 * display16x2.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Eletronica
 */

#include "main.h"
#include "display16x2.h"

extern BIT port;
extern INFO_LCD info_lcd;

void ControlLcd(uint8_t data, uint8_t state){
	port.P0 = (data >> 0) & 1;
	port.P1 = (data >> 1) & 1;
	port.P2 = (data >> 2) & 1;
	port.P3 = (data >> 3) & 1;
	port.P4 = (data >> 4) & 1;
	port.P5 = (data >> 5) & 1;
	port.P6 = (data >> 6) & 1;
	port.P7 = (data >> 7) & 1;

	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, state);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, port.P4);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, port.P5);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, port.P6);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, port.P7);

	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, port.P0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, port.P1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, port.P2);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, port.P3);

	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);

}

void SendMessage(uint8_t x_pos, uint8_t y_pos, char *message){
	if(!y_pos){
		switch(x_pos){
			case 0: ControlLcd(0x80, LCD_INSTRUCTION); break;
			case 1: ControlLcd(0x81, LCD_INSTRUCTION); break;
			case 2: ControlLcd(0x82, LCD_INSTRUCTION); break;
			case 3: ControlLcd(0x83, LCD_INSTRUCTION); break;
			case 4: ControlLcd(0x84, LCD_INSTRUCTION); break;
			case 5: ControlLcd(0x85, LCD_INSTRUCTION); break;
			case 6: ControlLcd(0x86, LCD_INSTRUCTION); break;
			case 7: ControlLcd(0x87, LCD_INSTRUCTION); break;
			case 8: ControlLcd(0x88, LCD_INSTRUCTION); break;
			case 9: ControlLcd(0x89, LCD_INSTRUCTION); break;
			case 10: ControlLcd(0x8A, LCD_INSTRUCTION); break;
			case 11: ControlLcd(0x8B, LCD_INSTRUCTION); break;
			case 12: ControlLcd(0x8C, LCD_INSTRUCTION); break;
			case 13: ControlLcd(0x8D, LCD_INSTRUCTION); break;
			case 14: ControlLcd(0x8E, LCD_INSTRUCTION); break;
			case 15: ControlLcd(0x8F, LCD_INSTRUCTION); break;
		}
	} else{
		switch(x_pos){
			case 0: ControlLcd(0xC0, LCD_INSTRUCTION); break;
			case 1: ControlLcd(0xC1, LCD_INSTRUCTION); break;
			case 2: ControlLcd(0xC2, LCD_INSTRUCTION); break;
			case 3: ControlLcd(0xC3, LCD_INSTRUCTION); break;
			case 4: ControlLcd(0xC4, LCD_INSTRUCTION); break;
			case 5: ControlLcd(0xC5, LCD_INSTRUCTION); break;
			case 6: ControlLcd(0xC6, LCD_INSTRUCTION); break;
			case 7: ControlLcd(0xC7, LCD_INSTRUCTION); break;
			case 8: ControlLcd(0xC8, LCD_INSTRUCTION); break;
			case 9: ControlLcd(0xC9, LCD_INSTRUCTION); break;
			case 10: ControlLcd(0xCA, LCD_INSTRUCTION); break;
			case 11: ControlLcd(0xCB, LCD_INSTRUCTION); break;
			case 12: ControlLcd(0xCC, LCD_INSTRUCTION); break;
			case 13: ControlLcd(0xCD, LCD_INSTRUCTION); break;
			case 14: ControlLcd(0xCE, LCD_INSTRUCTION); break;
			case 15: ControlLcd(0xCF, LCD_INSTRUCTION); break;
		}
	}

	for(int i = 0; message[i] != '\0'; ++i) {
		ControlLcd(message[i], LCD_DATA);
	}
}

void StartLcd(void){
	ControlLcd(0x33, LCD_INSTRUCTION);
	ControlLcd(0x32, LCD_INSTRUCTION);
	ControlLcd(0x28, LCD_INSTRUCTION);
	ControlLcd(0x0C, LCD_INSTRUCTION);
	ControlLcd(0x06, LCD_INSTRUCTION);
	ControlLcd(0x01, LCD_INSTRUCTION);
}

int WordSize(char * word){
	int i;
	for(i = 0; word[i] != '\0'; ++i);
	return i + 1; // Considerando também o indice 0
}

