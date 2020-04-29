

#ifndef INC_LL_H_
#define INC_LL_H_

#include "main.h"


void LL_exec(struct collection *commands);


// dit kan weg als alle layers er zijn
int API_draw_bitmap(uint16_t, uint16_t, int);
int API_draw_circle(uint16_t, uint16_t, int, int);
int API_clearscreen(int);
int API_execute(int);
int	API_draw_figure(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t,
					uint16_t, uint16_t, uint16_t, uint16_t, uint16_t,
					int);
int	API_repeat_commands(int, int);
int API_draw_line(uint16_t, uint16_t, uint16_t, uint16_t, int, int);
int API_draw_rectangle(uint16_t, uint16_t, int, int, int, int);
int API_draw_text(uint16_t, uint16_t, int, char*, int, int, int);
int API_draw_tower(uint16_t, uint16_t, int, int, int);
int API_wait(int);
/************************************************************************/


// de namen zijn lang
//enum FUNCTIONS
//{
//	FUNCTION_NO_RESET = 0,
//	BITMAP_FUNCTION_NO,
//	CIRKEL_FUNCTION_NO,
//	CLEARSCHERM_FUNCTION_NO,
//	EXECUTE_FUNCTION_NO,
//	FIGUUR_FUNCTION_NO,
//	HERHAAL_FUNCTION_NO,
//	LIJN_FUNCTION_NO,
//	RECHTHOEK_FUNCTION_NO,
//	TEKST_FUNCTION_NO,
//	TOREN_FUNCTION_NO,
//	WACHT_FUNCTION_NO
//};


#endif /* INC_LL_H_ */
