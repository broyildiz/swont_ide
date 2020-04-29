/*
 * IOL.h
 *
 *  Created on: 26 apr. 2020
 *      Author: kelly
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

void screen(void);

#include "stdlib.h"
#include "main.h"
//#include "screen.c"
//#include "images.h"

//#include "stm32f4xx.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_gpio.h"
//GPIO_InitTypeDef  GPIO_InitStruct;


#define sgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a
                                         number */
typedef unsigned char  byte;
typedef unsigned short word;

void IO_draw_rectangle(int x_lup, int y_lup, int width, int height, int color, int filled);
void IO_clearscreen(int color);
void IO_draw_line(int x1, int y1, int x2, int y2, byte color, int thickness);
void IO_draw_circle(int xc, int yc, int radius, byte color);
void drawCircle(int xc, int yc, int x, int y, byte color);
void IO_draw_figure(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5, byte color);

void FillScreen(uint8_t color);
void SetPixel(uint8_t xp, uint8_t yp, uint8_t color);

//void initButton(void);
//unsigned char buttonPressed(void);


#endif /* INC_SCREEN_H_ */
