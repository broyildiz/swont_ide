/*
 * consolas_fonts.h
 *
 *  Created on: 5 mei 2020
 *      Author: Rutger
 */

#ifndef INC_CONSOLAS_FONTS_H_
#define INC_CONSOLAS_FONTS_H_
#include "main.h"

/* Small consolas fonts */

#define CONSOLAS_SMALL_HEIGHT 11
#define CONSOLAS_SMALL_ITALIC_HEIGHT 11
#define CONSOLAS_SMALL_BOLD_HEIGHT 11

extern const uint8_t consolas_8ptBitmaps[];
extern const uint8_t consolas_italic_8ptBitmaps[];
extern const uint8_t consolas_bold_8ptBitmaps[];

extern const uint16_t consolas_8ptDescriptors[];
extern const uint16_t consolas_italic_8ptDescriptors[];
extern const uint16_t consolas_bold_8ptDescriptors[];


/* Large consolas fonts */

#define CONSOLAS_LARGE_HEIGHT 15
#define CONSOLAS_LARGE_ITALIC_HEIGHT 15
#define CONSOLAS_LARGE_BOLD_HEIGHT 15

extern const uint8_t consolas_11ptBitmaps[];
extern const uint8_t consolas_italic_11ptBitmaps[];
extern const uint8_t consolas_bold_11ptBitmaps[];

extern const uint16_t consolas_11ptDescriptors[];
extern const uint16_t consolas_italic_11ptDescriptors[];
extern const uint16_t consolas_bold_11ptDescriptors[];



#endif /* INC_CONSOLAS_FONTS_H_ */
