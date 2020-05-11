/**
  ******************************************************************************
  * @file           : IO.h
  * @brief          : This file contains the IO layer code
  * @author			: Groep 8
  * @date			: 08-05-2020
  ******************************************************************************
  */

/** @addtogroup SWONT
  * @{
  */

/** @addtogroup IO_Layer
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define sgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a
                                         number */
#define NORMAL			  0
#define ITALIC   		  1
#define BOLD 			  2

#define ARIAL         	  0
#define ARIAL_NORMAL	  0
#define ARIAL_ITALIC	  1
#define ARIAL_BOLD		  2

#define CONSOLAS  		  1
#define CONSOLAS_NORMAL   0
#define CONSOLAS_ITALIC   1
#define CONSOLAS_BOLD  	  2

#define LARGE_FONT		  2
#define SMALL_FONT  	  1
#define ASCII_OFFSET 	  32

#define BYTE_SIZE 		  8
#define BITMASK			  128
#define ARRAY_DIMENSION   2
#define CHAR_START_OFFSET 1

#define CASE_OFFSET	      32
#define ASCII_DEL		  127

/* Enum's --------------------------------------------------------------------*/
enum BITMAPS
{
	SMILEY_HAPPY = 0,
	SMILEY_SAD,
	ARROW_UP,
	ARROW_RIGHT,
	ARROW_DOWN,
	ARROW_LEFT,
	MEGAMAN
};

/* Typedefs ------------------------------------------------------------------*/
typedef unsigned char  byte;
typedef unsigned short word;

/* Prototypes ----------------------------------------------------------------*/
int drawCircle(int xc, int yc, int x, int y, byte color);
int FillScreen(uint8_t color);
int IO_draw_rectangle(uint16_t x_lup, uint16_t y_lup, int width, int height, int color, int filled);
int IO_clearscreen(int color);
int IO_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, byte color, int thickness);
int IO_draw_circle(int xc, int yc, int radius, byte color);
int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color);
int IO_draw_bitmap(int xlup, int ylup, int bmpnr);
int IO_draw_text(uint16_t x, uint16_t y, int color, char* text, char *font, int font_size, int font_style);
int IO_draw_mondriaan();

void IO_tetris(void);
void screen(void);

#endif /* INC_SCREEN_H_ */

/**
  * @}
  */

/**
  * @}
  */
