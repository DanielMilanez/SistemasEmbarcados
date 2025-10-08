/*
 * display16x2.h
 *
 *  Created on: Aug 16, 2025
 *      Author: ALUNO OC
 */

#include "main.h"

#define LCD_INSTRUCT 0
#define LCD_DATA  	 1

/*----------------------------------------*/

typedef struct{
	unsigned P0: 1;
	unsigned P1: 1;
	unsigned P2: 1;
	unsigned P3: 1;
	unsigned P4: 1;
	unsigned P5: 1;
	unsigned P6: 1;
	unsigned P7: 1;
}bit;

/*----------------------------------------*/

void LcdStart(void);
uint8_t WordSize(char *message);
void ControlLcd(uint8_t data, uint8_t state);
void SendMessage(uint8_t x, uint8_t y, char *message);

