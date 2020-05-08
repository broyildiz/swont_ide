/*
 * FL.h
 *
 *  Created on: Apr 22, 2020
 *      Author: Ömer
 */

#ifndef INC_FL_H_
#define INC_FL_H_
#include "main.h"


int FL_uart_decode(void);
int FL_find_decode_nr();
int FL_find_args(int function_number, int num_args,  int len_function_name);
int FL_convert_args(char arg_array[], int argcounter);
uint8_t FL_find_color(char color[]);
int FL_find_font_style(char arg_array[]);

void FL_error_handler(int error);
void FL_global_debug_check();
void FL_debug_int(int num);
void FL_debug_tx( char *pDebugMessage);
void FL_error_tx(char  *pErrorMessage);
void FL_global_error_handler(int error);

#define MAX_LEN_TEKST_STRING 128
#define MAX_LEN_FONTNAME 30

#define LETTERA 'a'
#define LETTERB 'b'
#define LETTERC 'c'
#define LETTERE 'e'
#define LETTERF 'f'
#define LETTERG 'g'
#define LETTERH 'h'
#define LETTERI 'i'
#define LETTERL 'l'
#define LETTERN 'm'
#define LETTERM 'n'
#define LETTERR 'r'
#define LETTERT 't'
#define LETTERV 'v'
#define LETTERW 'w'
#define LETTERZ 'z'

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
#define MONDRIAAN_FUNCTION_NO 	10
#define WACHT_FUNCTION_NO 		11
#define TETRIS_FUNCTION_NO		12

#define MAX_NUM_RGS				10
#define MAX_ARG_LEN				128
#define BITMAP_ARGS				3
#define CIRKEL_ARGS 			4
#define CLEARSCHERM_ARGS 		1
#define EXECUTE_ARGS 			0
#define FIGUUR_ARGS  			9
#define HERHAAL_ARGS 			2
#define LIJN_ARGS 				6
#define RECHTHOEK_ARGS 			6
#define TEKST_ARGS 				6
#define MONDRIAAN_ARGS			0
#define WACHT_ARGS 				1
#define TETRIS_ARGS				0

#define BITMAP_FUNCTION_NAME_LEN 		6
#define CIRKEL_FUNCTION_NAME_LEN 		6
#define CLEARSCHERM_FUNCTION_NAME_LEN 	11
#define EXECUTE_FUNCTION_NAME_LEN 		7
#define FIGUUR_FUNCTION_NAME_LEN 		6
#define HERHAAL_FUNCTION_NAME_LEN 		7
#define LIJN_FUNCTION_NAME_LEN 			4
#define RECHTHOEK_FUNCTION_NAME_LEN 	9
#define TEKST_FUNCTION_NAME_LEN 		5
#define MONDRIAAN_FUNCTION_NAME_LEN 	9
#define WACHT_FUNCTION_NAME_LEN 		5

#define	VGA_COL_BROWN 0x68
#define	VGA_COL_GREY 0x92
#define	VGA_COL_LITE_BLUE 0x17
#define	VGA_COL_LITE_CYAN 0x15
#define	VGA_COL_LITE_GREEN 0x9F
#define	VGA_COL_LITE_MAGENTA 0xF7
#define	VGA_COL_LITE_RED 0x4F


typedef struct
{
	int nr;
	uint16_t xlup;
	uint16_t ylup;
}bitmap_func;

typedef struct
{
	uint16_t x;
	uint16_t y;
	int radius;
	int kleur;
}cirkel_func;

typedef struct
{
	int kleur;
}clearscherm_func;

typedef struct
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	uint16_t x3;
	uint16_t y3;
	uint16_t x4;
	uint16_t y4;
	uint16_t x5;
	uint16_t y5;
	int kleur;
}figuur_func;

typedef struct
{
	int aantal;
	int hoevaak;

}herhaal_func;

typedef struct
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	int kleur;
	int dikte;

}lijn_func;

typedef struct
{
	uint16_t xlup;
	uint16_t ylup;
	int breedte;
	int hoogte;
	int kleur;
	int gevuld;

}rechthoek_func;

typedef struct
{
	uint16_t xlup;
	uint16_t ylup;
	int kleur;
	char tekst[MAX_LEN_TEKST_STRING];
	char fontnaam[MAX_LEN_FONTNAME];
	int fontgrootte;
	int fontstijl;

}tekst_func;


typedef struct
{
	int msecs;

}wacht_func;

struct collection
{
	int function_number;
	bitmap_func bitmap;
	cirkel_func cirkel;
	clearscherm_func clearscherm;
	figuur_func figuur;
	herhaal_func herhaal;
	lijn_func lijn;
	rechthoek_func rechthoek;
	tekst_func tekst;
	wacht_func wacht;
}command;



#endif /* INC_FL_H_ */
