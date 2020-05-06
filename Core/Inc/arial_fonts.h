/*
 * arial_fonts.h
 *
 *  Created on: 3 mei 2020
 *      Author: Rutger
 */

#ifndef INC_ARIAL_FONTS_H_
#define INC_ARIAL_FONTS_H_

#include "main.h"

// Font data for Arial 11pt
//extern const uint8_t arial_11ptBitmaps[];

//extern const uint16_t arial_11ptDescriptors[95][2];

#define NR_OF_ELEMENTS 2
#define NR_OF_SYMBOLS 95

/* Small arial fonts */

#define ARIAL_SMALL_HEIGHT		  10
#define ARIAL_SMALL_ITALIC_HEIGHT 12
#define ARIAL_SMALL_BOLD_HEIGHT   11

extern const uint8_t arial_8ptBitmaps[];
extern const uint8_t arial_italic_8ptBitmaps[];
extern const uint8_t arial_bold_8ptBitmaps[];

extern const uint16_t arial_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t arial_italic_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t arial_bold_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];

/* Large arial fonts */

#define ARIAL_LARGE_HEIGHT			15
#define ARIAL_LARGE_ITALIC_HEIGHT 	15
#define ARIAL_LARGE_BOLD_HEIGHT 	16

extern const uint8_t arial_11ptBitmaps[];
extern const uint8_t arial_italic_11ptBitmaps[];
extern const uint8_t arial_bold_11ptBitmaps[];

extern const uint16_t arial_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t arial_italic_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t arial_bold_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];






#endif /* INC_ARIAL_FONTS_H_ */
