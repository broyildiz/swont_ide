#include "LL.h"
#include "string.h"



/**
  * @brief  Determines which API function should be called based on input.
  * 		Calls error handler in case of error.
  *
  * @param  Command : Contains parsed data from UART for every API command.
  *
  * @retval None
  */
int LL_exec(struct collection *commands)
{

	Debug_Tx("Enterred the LL\n");
	int error = NO_ERROR;

	Debug_Tx("Entering LL_exec command switch\n");

	switch(commands->function_number)
	{
	case BITMAP_FUNCTION_NO:
	{
		Debug_Tx("case bitmap\n");
		error = IO_draw_bitmap(commands->bitmap.xlup,
							   commands->bitmap.ylup,
							   commands->bitmap.nr);
	}break;

	case CIRKEL_FUNCTION_NO:
	{
		Debug_Tx("case circle\n");
		error = IO_draw_circle(commands->cirkel.x,
							   commands->cirkel.y,
							   commands->cirkel.radius,
							   commands->cirkel.kleur);
	}break;

	case CLEARSCHERM_FUNCTION_NO:
	{
		Debug_Tx("case clearscreen\n");
		error = IO_clearscreen(commands->clearscherm.kleur);
	}break;

	case FIGUUR_FUNCTION_NO:
	{
		Debug_Tx("case figure\n");
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
		

	case HERHAAL_FUNCTION_NO :
	{
//		Debug_Tx("Going to execute HERHAAL_FUNCTION_NO\n");
//		error = IO_repeat_commands(commands->herhaal.aantal,
//								   commands->herhaal.hoevaak);
	}break;

	case LIJN_FUNCTION_NO :
	{
		Debug_Tx("case line\n");
		error = IO_draw_line(commands->lijn.x1,
							 commands->lijn.y1,
							 commands->lijn.x2,
							 commands->lijn.y2,
							 commands->lijn.kleur,
							 commands->lijn.dikte);
	}break;

	case RECHTHOEK_FUNCTION_NO :
	{
		Debug_Tx("case rectangle\n");
		error = IO_draw_rectangle(commands->rechthoek.xlup,
								  commands->rechthoek.ylup,
								  commands->rechthoek.breedte,
								  commands->rechthoek.hoogte,
								  commands->rechthoek.kleur,
								  commands->rechthoek.gevuld);
	}break;

	case TEKST_FUNCTION_NO :
	{
		Debug_Tx("case text\n");
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
//
	case WACHT_FUNCTION_NO:
	{
//		Debug_Tx("Going to execute WACHT_FUNCTION_NO\n");
//		waitCheck = True;
////		HAL_Delay(command->wacht.msecs);
//		error = IO_wait(command->wacht.msecs);
	}break;

	default:
	{
		Debug_Tx("LL Switch Not a supported function\n");
		error = LL_NOT_A_SUPPORTED_FUNCTION;
		return error;

	}break;
	}

	if(error)
	{
		Debug_Tx("Some IO function threw an Error!\n");
		return error;
	}
	Debug_Tx("back in LL.c\n");
	Debug_Tx("Going back to FL.c\n");
	return error;

}


