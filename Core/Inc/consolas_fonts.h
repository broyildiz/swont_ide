/*
 * consolas_fonts.h
 *
 *  Created on: 5 mei 2020
 *      Author: Rutger
 */

#ifndef INC_CONSOLAS_FONTS_H_
#define INC_CONSOLAS_FONTS_H_
#include "main.h"

#define NR_OF_ELEMENTS 2
#define NR_OF_SYMBOLS 95

/* Small consolas fonts */

#define CONSOLAS_SMALL_HEIGHT 11
#define CONSOLAS_SMALL_ITALIC_HEIGHT 11
#define CONSOLAS_SMALL_BOLD_HEIGHT 11

extern const uint8_t consolas_8ptBitmaps[];
extern const uint8_t consolas_italic_8ptBitmaps[];
extern const uint8_t consolas_bold_8ptBitmaps[];

extern const uint16_t consolas_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_italic_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_bold_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];


/* Large consolas fonts */

#define CONSOLAS_LARGE_HEIGHT 15
#define CONSOLAS_LARGE_ITALIC_HEIGHT 15
#define CONSOLAS_LARGE_BOLD_HEIGHT 15

extern const uint8_t consolas_11ptBitmaps[];
extern const uint8_t consolas_italic_11ptBitmaps[];
extern const uint8_t consolas_bold_11ptBitmaps[];

extern const uint16_t consolas_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_italic_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_bold_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];



#endif /* INC_CONSOLAS_FONTS_H_ */
