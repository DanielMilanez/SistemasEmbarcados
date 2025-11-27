/*
 * display16x2.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Eletronica
 */

typedef struct{
	unsigned P0: 1;
	unsigned P1: 1;
	unsigned P2: 1;
	unsigned P3: 1;
	unsigned P4: 1;
	unsigned P5: 1;
	unsigned P6: 1;
	unsigned P7: 1;
}BIT;

typedef struct{
	uint8_t word_size;
}INFO_LCD;

/*--------------------------------------------------*/
#define LCD_DATA 1
#define LCD_INSTRUCTION 0
#define CLEAR_ALL 0x01

#define MAX_COLUMNS 16
#define MAX_ROWS 	2
/*--------------------------------------------------*/
void StartLcd(void);
int WordSize(char * word);
void ControlLcd(uint8_t data, uint8_t state);
void SendMessage(uint8_t x_pos, uint8_t y_pos, char *message);
