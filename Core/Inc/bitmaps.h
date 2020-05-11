/**
  ******************************************************************************
  * @file           : bitmaps.h
  * @brief          : This file contains various stored bitmaps
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
#ifndef INC_BITMAPS_H_
#define INC_BITMAPS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define MEGAMAN_WIDTH  		21	/* bitmap width in pixels 	*/
#define MEGAMAN_HEIGHT  	24	/* bitmap height in pixels */

#define SMILEY_WIDTH  		40	/* bitmap width in pixels 	*/
#define SMILEY_HEIGHT 		40	/* bitmap height in pixels */

#define ARROW_UP_WIDTH  	27	/* bitmap width in pixels 	*/
#define ARROW_UP_HEIGHT     41	/* bitmap height in pixels */

#define ARROW_DOWN_WIDTH    27	/* bitmap width in pixels 	*/
#define ARROW_DOWN_HEIGHT   41	/* bitmap height in pixels */

#define ARROW_LEFT_WIDTH    41	/* bitmap width in pixels 	*/
#define ARROW_LEFT_HEIGHT   27	/* bitmap height in pixels */

#define ARROW_RIGHT_WIDTH   41  /* bitmap width in pixels 	*/
#define ARROW_RIGHT_HEIGHT  27	/* bitmap height in pixels */

/* Constants -----------------------------------------------------------------*/
extern const uint8_t megaman[];
extern const uint8_t megaman_2[MEGAMAN_WIDTH * MEGAMAN_HEIGHT];
extern const uint8_t smiley_happy[SMILEY_WIDTH * SMILEY_HEIGHT];
extern const uint8_t smiley_sad[SMILEY_WIDTH * SMILEY_HEIGHT];
extern const uint8_t arrow_up[ARROW_UP_WIDTH * ARROW_UP_HEIGHT];
extern const uint8_t arrow_down[ARROW_DOWN_WIDTH * ARROW_DOWN_HEIGHT];
extern const uint8_t arrow_left[ARROW_LEFT_WIDTH * ARROW_LEFT_HEIGHT];
extern const uint8_t arrow_right[ARROW_RIGHT_WIDTH * ARROW_RIGHT_HEIGHT];


#endif /* INC_BITMAPS_H_ */

/**
  * @}
  */

/**
  * @}
  */
