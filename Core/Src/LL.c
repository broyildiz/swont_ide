


#include "LL.h"
#include "string.h"

/**
  * @brief  Determines which API function should be called based on input.
  * 		Calls error handler in case of error.
  *
  * @param  Commands : Contains parsed data from UART for every API command.
  *
  * @retval Error:	returns errors from called IO functions
  */
int LL_exec(struct collection *commands)
{

	FL_debug_tx("Enterred the LL\n");
	int error = NO_ERROR;

	FL_debug_tx("Entering LL_exec command switch\n");

	switch(commands->function_number)
	{
	case BITMAP_FUNCTION_NO:
	{
		FL_debug_tx("case bitmap\n");
		error = IO_draw_bitmap(commands->bitmap.xlup,
							   commands->bitmap.ylup,
							   commands->bitmap.nr);
	}break;

	case CIRKEL_FUNCTION_NO:
	{
		FL_debug_tx("case circle\n");
		error = IO_draw_circle(commands->cirkel.x,
							   commands->cirkel.y,
							   commands->cirkel.radius,
							   commands->cirkel.kleur);
	}break;

	case CLEARSCHERM_FUNCTION_NO:
	{
		FL_debug_tx("case clearscreen\n");
		error = IO_clearscreen(commands->clearscherm.kleur);
	}break;

	case FIGUUR_FUNCTION_NO:
	{
		FL_debug_tx("case figure\n");
		error = IO_draw_figure(commands->figuur.x1,
							   commands->figuur.y1,
							   commands->figuur.x2,
							   commands->figuur.y2,
							   commands->figuur.x3,
							   commands->figuur.y3,
							   commands->figuur.x4,
							   commands->figuur.y4,
							   commands->figuur.x5,
							   commands->figuur.y5,
							   commands->figuur.kleur);
	}break;
		
	case LIJN_FUNCTION_NO :
	{
		FL_debug_tx("case line\n");
		error = IO_draw_line(commands->lijn.x1,
							 commands->lijn.y1,
							 commands->lijn.x2,
							 commands->lijn.y2,
							 commands->lijn.kleur,
							 commands->lijn.dikte);
	}break;

	case RECHTHOEK_FUNCTION_NO :
	{
		FL_debug_tx("case rectangle\n");
		error = IO_draw_rectangle(commands->rechthoek.xlup,
								  commands->rechthoek.ylup,
								  commands->rechthoek.breedte,
								  commands->rechthoek.hoogte,
								  commands->rechthoek.kleur,
								  commands->rechthoek.gevuld);
	}break;

	case TEKST_FUNCTION_NO :
	{
		FL_debug_tx("case text\n");
		error = IO_draw_text(commands->tekst.xlup,
							 commands->tekst.ylup,
							 commands->tekst.kleur,
							 commands->tekst.tekst,
							 commands->tekst.fontnaam,
							 commands->tekst.fontgrootte,
							 commands->tekst.fontstijl);
	}break;
    
    case MONDRIAAN_FUNCTION_NO:
    {
	    error = IO_draw_mondriaan();
    }break;

	default:
	{
		FL_debug_tx("LL Switch Not a supported function\n");
		error = LL_NOT_A_SUPPORTED_FUNCTION;
		return error;

	}break;
	}

	if(error)
	{
		FL_debug_tx("Some IO function threw an Error!\n");
		return error;
	}
	FL_debug_tx("back in LL.c\n");
	FL_debug_tx("Going back to FL.c\n");
	return error;

}

/*
 * @brief Tetris function checking the string
 *
 * @retval None
 *
 */

void LL_tetris_check()
{
	if(	(input.line_rx_buffer[0] == 't') &&
		(input.line_rx_buffer[1] == 'e') &&
		(input.line_rx_buffer[2] == 't') &&
		(input.line_rx_buffer[3] == 'r') &&
		(input.line_rx_buffer[4] == 'i') &&
		(input.line_rx_buffer[5] == 's'))
	{
		IO_tetris();
	}
}
