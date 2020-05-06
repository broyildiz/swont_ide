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

	switch(command->function_number)
	{
	case BITMAP_FUNCTION_NO:
	{
		Debug_Tx("case bitmap\n");
		error = IO_draw_bitmap(command->bitmap.xlup,
							   command->bitmap.ylup,
							   command->bitmap.nr);
	}break;

	case CIRKEL_FUNCTION_NO:
	{
		Debug_Tx("case circle\n");
		error = IO_draw_circle(command->cirkel.x,
							   command->cirkel.y,
							   command->cirkel.radius,
							   command->cirkel.kleur);
	}break;

	case CLEARSCHERM_FUNCTION_NO:
	{
		Debug_Tx("case clearscreen\n");
		error = IO_clearscreen(command->clearscherm.kleur);
	}break;

	case FIGUUR_FUNCTION_NO:
	{
		Debug_Tx("case figure\n");
		error = IO_draw_figure(command->figuur.x1,
							   command->figuur.y1,
							   command->figuur.x2,
							   command->figuur.y2,
							   command->figuur.x3,
							   command->figuur.y3,
							   command->figuur.x4,
							   command->figuur.y4,
							   command->figuur.x5,
							   command->figuur.y5,
							   command->figuur.kleur);
	}break;

	case HERHAAL_FUNCTION_NO :
	{
		Debug_Tx("Going to execute HERHAAL_FUNCTION_NO\n");
		error = IO_repeat_commands(command->herhaal.aantal,
								command->herhaal.hoevaak);
	}break;

	case LIJN_FUNCTION_NO :
	{
		Debug_Tx("case line\n");
		error = IO_draw_line(command->lijn.x1,
							 command->lijn.y1,
							 command->lijn.x2,
							 command->lijn.y2,
							 command->lijn.kleur,
							 command->lijn.dikte);
	}break;

	case RECHTHOEK_FUNCTION_NO :
	{
		Debug_Tx("case rectangle\n");
		error = IO_draw_rectangle(command->rechthoek.xlup,
								  command->rechthoek.ylup,
								  command->rechthoek.breedte,
								  command->rechthoek.hoogte,
								  command->rechthoek.kleur,
								  command->rechthoek.gevuld);
	}break;

	case TEKST_FUNCTION_NO :
	{
		Debug_Tx("case text\n");
		error = IO_draw_text(command->tekst.xlup,
							 command->tekst.ylup,
							 command->tekst.kleur,
							 command->tekst.tekst,
							 command->tekst.fontnaam,
							 command->tekst.fontgrootte,
							 command->tekst.fontstijl);
	}break;
//
//		case TOREN_FUNCTION_NO:
//			error = IO_draw_tower(command->toren.x1,
//								   command->toren.y1,
//								   command->toren.grootte,
//								   command->toren.kleur1,
//								   command->toren.kleur2);
//			break; //nieuw functie
//
	case WACHT_FUNCTION_NO:
	{
		Debug_Tx("Going to execute WACHT_FUNCTION_NO\n");
		waitCheck = True;
//		HAL_Delay(command->wacht.msecs);
		error = IO_wait(command->wacht.msecs);
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


