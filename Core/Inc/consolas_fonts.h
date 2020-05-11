/**
  ******************************************************************************
  * @file           : consolas_fonts.h
  * @brief          : This file contains multiple variants of the consolas font
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
#ifndef INC_CONSOLAS_FONTS_H_
#define INC_CONSOLAS_FONTS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define NR_OF_ELEMENTS 2
#define NR_OF_SYMBOLS 95

/* Small consolas fonts */

#define CONSOLAS_SMALL_HEIGHT 11
#define CONSOLAS_SMALL_ITALIC_HEIGHT 11
#define CONSOLAS_SMALL_BOLD_HEIGHT 11

/* Large consolas fonts */

#define CONSOLAS_LARGE_HEIGHT 15
#define CONSOLAS_LARGE_ITALIC_HEIGHT 15
#define CONSOLAS_LARGE_BOLD_HEIGHT 15


/* Prototypes ----------------------------------------------------------------*/
/* Small consolas fonts */

extern const uint8_t  consolas_8ptBitmaps[];
extern const uint8_t  consolas_italic_8ptBitmaps[];
extern const uint8_t  consolas_bold_8ptBitmaps[];

extern const uint16_t consolas_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_italic_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_bold_8ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];

extern const uint8_t  consolas_11ptBitmaps[];
extern const uint8_t  consolas_italic_11ptBitmaps[];
extern const uint8_t  consolas_bold_11ptBitmaps[];

extern const uint16_t consolas_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_italic_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];
extern const uint16_t consolas_bold_11ptDescriptors[NR_OF_SYMBOLS][NR_OF_ELEMENTS];

#endif /* INC_CONSOLAS_FONTS_H_ */

/**
  * @}
  */

/**
  * @}
  */
