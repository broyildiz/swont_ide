/*
 * bitmaps.h
 *
 *  Created on: 29 apr. 2020
 *      Author: Rutger
 */

#ifndef INC_BITMAPS_H_
#define INC_BITMAPS_H_

#include "main.h"


#define MEGAMAN_WIDTH  21
#define MEGAMAN_HEIGHT  24

#define SMILEY_WIDTH  40
#define SMILEY_HEIGHT  40

#define ARROW_UP_WIDTH  27
#define ARROW_UP_HEIGHT  41

#define ARROW_DOWN_WIDTH  27
#define ARROW_DOWN_HEIGHT  41

#define ARROW_LEFT_WIDTH  41
#define ARROW_LEFT_HEIGHT  27

#define ARROW_RIGHT_WIDTH  41
#define ARROW_RIGHT_HEIGHT  27


extern const uint8_t megaman[];
extern const uint8_t megaman_2[MEGAMAN_WIDTH * MEGAMAN_HEIGHT];
extern const uint8_t smiley_happy[SMILEY_WIDTH * SMILEY_HEIGHT];
extern const uint8_t smiley_sad[SMILEY_WIDTH * SMILEY_HEIGHT];
extern const uint8_t arrow_up[ARROW_UP_WIDTH * ARROW_UP_HEIGHT];
extern const uint8_t arrow_down[ARROW_DOWN_WIDTH * ARROW_DOWN_HEIGHT];
extern const uint8_t arrow_left[ARROW_LEFT_WIDTH * ARROW_LEFT_HEIGHT];
extern const uint8_t arrow_right[ARROW_RIGHT_WIDTH * ARROW_RIGHT_HEIGHT];



/**
 * Made with Marlin Bitmap Converter
 * https://marlinfw.org/tools/u8glib/converter.html
 *
 * This bitmap from the file 'megaman-sprite.bmp'
 */

#pragma once








#endif /* INC_BITMAPS_H_ */
