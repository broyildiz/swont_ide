#include "LL.h"

/**
  * @brief  Determines which API function should be called based on input.
  * 		Calls error handler in case of error.
  *
  * @param  Command : Contains parsed data from UART for every API command.
  *
  * @retval None
  */
void LL_exec(struct collection *commands)
{
	int error;
	switch(commands->function_number)
	{

		case FUNCTION_NO_RESET:
			 break; //nieuwe functie?

		case BITMAP_FUNCTION_NO:
			error = API_draw_bitmap(commands->bitmap.xlup,
			 						commands->bitmap.ylup,
									commands->bitmap.nr);
			break;

		case CIRKEL_FUNCTION_NO:
			error = API_draw_circle(commands->cirkel.x,
									commands->cirkel.y,
									commands->cirkel.radius,
									commands->cirkel.kleur);
			break;

		case CLEARSCHERM_FUNCTION_NO:
			error = API_clearscreen(commands->clearscherm.kleur);
			break;

		case EXECUTE_FUNCTION_NO:
			error = API_execute(commands->execute.null);
			break;

		case FIGUUR_FUNCTION_NO:
			error = API_draw_figure(commands->figuur.x1,
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
			break;

		case HERHAAL_FUNCTION_NO :
			error = API_repeat_commands(commands->herhaal.aantal,
										commands->herhaal.hoevaak);
			break;

		case LIJN_FUNCTION_NO :
			error = API_draw_line(commands->lijn.x1,
								  commands->lijn.y1,
								  commands->lijn.x2,
								  commands->lijn.y2,
								  commands->lijn.kleur,
								  commands->lijn.dikte);
			break;

		case RECHTHOEK_FUNCTION_NO :
			error = API_draw_rectangle(commands->rechthoek.xlup,
									   commands->rechthoek.ylup,
									   commands->rechthoek.breedte,
									   commands->rechthoek.hoogte,
									   commands->rechthoek.kleur,
									   commands->rechthoek.gevuld);
			break;

		case TEKST_FUNCTION_NO :
			error = API_draw_text(commands->tekst.xlup,
								  commands->tekst.ylup,
								  commands->tekst.kleur,
								  commands->tekst.tekst,
								  commands->tekst.fontnaam,
								  commands->tekst.fontgrootte,
								  commands->tekst.fontstijl);
			break;

		case TOREN_FUNCTION_NO:
			error = API_draw_tower(commands->toren.x1,
								   commands->toren.y1,
								   commands->toren.grootte,
								   commands->toren.kleur1,
								   commands->toren.kleur2);
			break; //nieuw functie

		case WACHT_FUNCTION_NO:
			error = API_wait(commands->wacht.msecs);
			break;

		default: break;
	}
	// if met error handling
	if(error==1)
	{

	}

}


