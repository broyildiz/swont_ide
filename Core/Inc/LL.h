/**
  ******************************************************************************
  * @file           : LL.h
  * @brief          : This file contains the logic layer code
  * @author			: Groep 8
  * @date			: 08-05-2020
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_LL_H_
#define INC_LL_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Prototypes ----------------------------------------------------------------*/
struct collection;
int  LL_exec(struct collection * commands);
void LL_tetris_check();


#endif /* INC_LL_H_ */
