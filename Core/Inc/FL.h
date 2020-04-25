/*
 * FL.h
 *
 *  Created on: Apr 22, 2020
 *      Author: Ömer
 */

#ifndef INC_FL_H_
#define INC_FL_H_
#include "main.h"


void FL_uart_decode(void);
int FL_find_decode_nr();
void FL_find_args(int function_number, int num_args,  int len_function_name);
void FL_convert_args(char arg_array[], int num_chars, int function_number, int num_args, int stored_args);
uint8_t FL_find_color(char color);
void FL_error_handler();

#define LETTERB 'b'
#define LETTERC 'c'
#define LETTERE 'e'
#define LETTERF 'f'
#define LETTERH 'h'
#define LETTERL 'l'
#define LETTERR 'r'
#define LETTERT 't'
#define LETTERW 'w'

#define FUNCTION_NO_RESET		0
#define BITMAP_FUNCTION_NO 		1
#define CIRKEL_FUNCTION_NO 		2
#define CLEARSCHERM_FUNCTION_NO 3
#define EXECUTE_FUNCTION_NO 	4
#define FIGUUR_FUNCTION_NO 		5
#define HERHAAL_FUNCTION_NO 	6
#define LIJN_FUNCTION_NO 		7
#define RECHTHOEK_FUNCTION_NO 	8
#define TEKST_FUNCTION_NO 		9
#define TOREN_FUNCTION_NO 		10
#define WACHT_FUNCTION_NO 		11

#define MAX_NUM_RGS				10
#define MAX_ARG_LEN				10
#define BITMAP_ARGS				3
#define CIRKEL_ARGS 			4
#define CLEARSCHERM_ARGS 		1
#define EXECUTE_ARGS 			0
#define FIGUUR_ARGS  			9
#define HERHAAL_ARGS 			2
#define LIJN_ARGS 				6
#define RECHTHOEK_ARGS 			6
#define TEKST_ARGS 				6
#define TOREN_ARGS 				5
#define WACHT_ARGS 				1

#define BITMAP_FUNCTION_NAME_LEN 		6
#define CIRKEL_FUNCTION_NAME_LEN 		6
#define CLEARSCHERM_FUNCTION_NAME_LEN 	11
#define EXECUTE_FUNCTION_NAME_LEN 		7
#define FIGUUR_FUNCTION_NAME_LEN 		6
#define HERHAAL_FUNCTION_NAME_LEN 		7
#define LIJN_FUNCTION_NAME_LEN 			4
#define RECHTHOEK_FUNCTION_NAME_LEN 	9
#define TEKST_FUNCTION_NAME_LEN 		5
#define TOREN_FUNCTION_NAME_LEN 		5
#define WACHT_FUNCTION_NAME_LEN 		5


#define	VGA_COL_BROWN 0x01
#define	VGA_COL_GREY 0x02
#define	VGA_COL_LITE_BLUE 0x03
#define	VGA_COL_LITE_BLUE 0x04
#define	VGA_COL_LITE_GREEN 0x05
#define	VGA_COL_LITE_MAGENTA 0x06
#define	VGA_COL_LITE_RED 0x07

//#define	VGA_COL_GREEN
//#define	VGA_COL_CYAAN
//#define	VGA_COL_YELLOW
//#define	VGA_COL_BLUE
//#define	VGA_COL_MAGENTA 0xE3
//#define	VGA_COL_RED 0xE0
//#define	VGA_COL_WHITE 0xFF
//#define	VGA_COL_BLACK 0x00


typedef struct
{
	int function_number;

}bitmap;

typedef struct
{
	int function_number;

}cirkel;
typedef struct
{
	int function_number;

}clearscherm;
typedef struct
{
	int function_number;

}execute;
typedef struct
{
	int function_number;

}figuur;
typedef struct
{
	int function_number;

}herhaal;
typedef struct
{
	int function_number;

}lijn;
typedef struct
{
	int function_number;

}rechthoek;
typedef struct
{
	int function_number;

}tekst;
typedef struct
{
	int function_number;

}toren;
typedef struct
{
	int function_number;

}wacht;

#endif /* INC_FL_H_ */
