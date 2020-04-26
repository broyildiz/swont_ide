/*
 * FL.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Ömer
 */

#include "FL.h"
#include "string.h"

/**
  * @brief  Sets the priority grouping field (preemption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bits for preemption priority
  *                                    4 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bits for preemption priority
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for preemption priority
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for preemption priority
  *                                    1 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_4: 4 bits for preemption priority
  *                                    0 bits for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ preemption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void FL_uart_decode()
{
	int function_number = FL_find_decode_nr();
	if(function_number == FUNCTION_NO_RESET)
		FL_error_handler("Did not recognise function number, line 34");

//	struct collection command;

	command.function_number = function_number;


	switch(function_number)
	{
	/*
	 * struct aanmaken voor functies
	 * afhankelijk van de functie het adres vand e struct meegeven
	 */
		case BITMAP_FUNCTION_NO: FL_find_args(function_number, BITMAP_ARGS, BITMAP_FUNCTION_NAME_LEN);
		break;

		case CLEARSCHERM_FUNCTION_NO: FL_find_args(function_number, CLEARSCHERM_ARGS, CLEARSCHERM_FUNCTION_NAME_LEN);
		break;

		case CIRKEL_FUNCTION_NO: FL_find_args(function_number, CIRKEL_ARGS, CIRKEL_FUNCTION_NAME_LEN);
		break;

		case EXECUTE_FUNCTION_NO: //special case: no args, so directly execute
		break;

		case FIGUUR_FUNCTION_NO: FL_find_args(function_number, FIGUUR_ARGS, FIGUUR_FUNCTION_NAME_LEN);
		break;

		case HERHAAL_FUNCTION_NO: FL_find_args(function_number, HERHAAL_ARGS, HERHAAL_FUNCTION_NAME_LEN);
		break;

		case LIJN_FUNCTION_NO: FL_find_args(function_number, LIJN_ARGS, LIJN_FUNCTION_NAME_LEN);
		break;

		case RECHTHOEK_FUNCTION_NO: FL_find_args(function_number, RECHTHOEK_ARGS, RECHTHOEK_FUNCTION_NAME_LEN);
		break;

		case TEKST_FUNCTION_NO: FL_find_args(function_number, TEKST_ARGS, TEKST_FUNCTION_NAME_LEN);
		break;

		case WACHT_FUNCTION_NO: FL_find_args(function_number, WACHT_ARGS, WACHT_FUNCTION_NAME_LEN);
		break;

		default : FL_error_handler("Did not recognise function number, line 77");
	}

	LL_exec(&command);

}

int FL_find_decode_nr()
{
	if(input.line_rx_buffer[0] == LETTERB) return BITMAP_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERC)
	{
		if(input.line_rx_buffer[1] == LETTERL) return CLEARSCHERM_FUNCTION_NO;
		else return CIRKEL_FUNCTION_NO;
	}

	if(input.line_rx_buffer[0] == LETTERE) return EXECUTE_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERF) return FIGUUR_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERH) return HERHAAL_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERL) return LIJN_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERR) return RECHTHOEK_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERT)
	{
		if(input.line_rx_buffer[1] == LETTERE) return TEKST_FUNCTION_NO;
		else return TOREN_FUNCTION_NO;
	}

	if(input.line_rx_buffer[0] == LETTERW) return WACHT_FUNCTION_NO;

	return FUNCTION_NO_RESET;

}

void FL_find_args(int function_number, int num_args, int len_function_name)
{
	if(function_number != TEKST_FUNCTION_NO)
	{
		char string_container[MAX_ARG_LEN]; //ook resetten
		int k;
		for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
		int arg_character_counter = 0;
		char stored_args = 0; // Counts how many arguments are stored. is incremented after successfully storing an arg
		//als er een spatie voor de erste komma zit werkt dit niet
		//Begin een loop die breekt bijd e eerste komma, de plaats waar die breekt stop je in i
		int i = len_function_name; // Start at the first comma
		int argcounter = 0;

		while(i <= input.msglen)
		{
			if(input.line_rx_buffer[i] == ',')
			{

				if(stored_args != 0) // Dit is niet de eerste komma dus
				{
					// convert the stored string()
					FL_convert_args(string_container, arg_character_counter, num_args, stored_args, ++argcounter);
//					FL_convert_args(string_container, arg_character_counter, num_args, arg_num++);
					// reset string container
					for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
					arg_character_counter = 0;
					stored_args++;
				}
				else stored_args++;

				i++;
			}
			if(input.line_rx_buffer[i] == ' ')
				i++;
			else
			{
				if(input.line_rx_buffer[i] == ',')
					FL_error_handler("Argument not filled, line 150");
				else
				{
					string_container[arg_character_counter++] = input.line_rx_buffer[i++];
				}
			}


		}
		FL_convert_args(string_container, --arg_character_counter, num_args, stored_args, ++argcounter);
//		FL_convert_args(string_container, --arg_character_counter, function_number, num_args, stored_args); // Op het einde van de while wordt arg_counter opgehoogd.
																	//je krijgt, als je dat aan de functie meegeeft, een \0 te zien.
																	//om die ertui te halen doe je --

/*
		sscanf()

//hmm
		while(stored_args != num_args)
		{
			if(input.line_rx_buffer[i] == ',')
			{
				stored_args++;
				i++;
				if(input.line_rx_buffer[i] == ' ')
					i++;
				else
				{
					if(input.line_rx_buffer[i] == ',')
						FL_error_handler();
					else

				}
			}
		}

*/
	}
	else
	{

	}
}

void FL_convert_args(char arg_array[], int num_chars, int num_args, int stored_args, int argcounter)
{
	switch(command.function_number)
	{
		case BITMAP_FUNCTION_NO:
		{
			switch(argcounter)
			{
				case 1:	command.bitmap.nr = atoi(arg_array); break;

				case 2: command.bitmap.xlup = atoi(arg_array); break;

				case 3: command.bitmap.ylup = atoi(arg_array); break;

//				default: FL_error_handler("Illegal stored_args value, line 209");//Error_Handler();
			}
		}break;

		case CIRKEL_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.cirkel.x = atoi(arg_array); break;
			case 2: command.cirkel.y = atoi(arg_array); break;
			case 3: command.cirkel.radius = atoi(arg_array); break;
			case 4: command.cirkel.kleur = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 221");//Error_Handler();
			}
		}break;

		case CLEARSCHERM_FUNCTION_NO: command.clearscherm.kleur = FL_find_color(arg_array); break;

//		case EXECUTE_FUNCTION_NO: // Hoort er misschien niet in
//		{
//
//		}break;
		case FIGUUR_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.figuur.x1 = atoi(arg_array); break;
			case 2: command.figuur.y1 = atoi(arg_array); break;
			case 3: command.figuur.x2 = atoi(arg_array); break;
			case 4: command.figuur.y2 = atoi(arg_array); break;
			case 5: command.figuur.x3 = atoi(arg_array); break;
			case 6: command.figuur.y3 = atoi(arg_array); break;
			case 7: command.figuur.x4 = atoi(arg_array); break;
			case 8: command.figuur.y4 = atoi(arg_array); break;
			case 9: command.figuur.x5 = atoi(arg_array); break;
			case 10: command.figuur.y5 = atoi(arg_array); break;
			case 11: command.figuur.kleur = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 247");
			}
		}break;

		case HERHAAL_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.herhaal.aantal = atoi(arg_array); break;
			case 2: command.herhaal.hoevaak = atoi(arg_array); break;
//			default: Error_Handler();//FL_error_handler("Illegal stored_args value, line 257");
			}
		}break;

		case LIJN_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.lijn.x1 = atoi(arg_array); break;
			case 2: command.lijn.y1 = atoi(arg_array); break;
			case 3: command.lijn.x2 = atoi(arg_array); break;
			case 4: command.lijn.y2 = atoi(arg_array); break;
			case 5: command.lijn.kleur = FL_find_color(arg_array); break;
			case 6: command.lijn.dikte = atoi(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 271");
			}
		}break;
		case RECHTHOEK_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.rechthoek.xlup = atoi(arg_array); break;
			case 2: command.rechthoek.ylup = atoi(arg_array); break;
			case 3: command.rechthoek.breedte = atoi(arg_array); break;
			case 4: command.rechthoek.hoogte = atoi(arg_array); break;
			case 5: command.rechthoek.kleur = FL_find_color(arg_array); break;
			case 6: command.rechthoek.gevuld = atoi(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 284");
			}
		}break;

//		case TEKST_FUNCTION_NO:	//Moet ik op terukomen. Je kan niet zomaar arg array meegeven aan de tekst functie want die is
//		{	 					//kleiner dan de max aantal karakters in 1 zin
//			switch(stored_args)
//			{
//			case 1: command.tekst.xlup = atoi(arg_array); break;
//			case 2: command.tekst.ylup = atoi(arg_array); break;
//			case 3: strcpy(command.tekst.tekst, arg_array); break;
//			}
//		}break;
		case TOREN_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.toren.x1 = atoi(arg_array); break;
			case 2: command.toren.y1 = atoi(arg_array); break;
			case 3: command.toren.grootte = atoi(arg_array); break;
			case 4: command.toren.kleur1 = FL_find_color(arg_array); break;
			case 5: command.toren.kleur2 = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 306");
			}
		}break;

		case WACHT_FUNCTION_NO: command.wacht.msecs = atoi(arg_array); break;

		default : FL_error_handler("Did not recognise function number, line 312");
	}



/*
	switch(command.function_number)
	{
		case BITMAP_FUNCTION_NO:
		{
			switch(stored_args)
			{
				case 1:	command.bitmap.nr = atoi(arg_array); break;

				case 2: command.bitmap.xlup = atoi(arg_array); break;

				case 3: command.bitmap.ylup = atoi(arg_array); break;

//				default: FL_error_handler("Illegal stored_args value, line 209");//Error_Handler();
			}
		}break;

		case CIRKEL_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.cirkel.x = atoi(arg_array); break;
			case 2: command.cirkel.y = atoi(arg_array); break;
			case 3: command.cirkel.radius = atoi(arg_array); break;
			case 4: command.cirkel.kleur = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 221");//Error_Handler();
			}
		}break;

		case CLEARSCHERM_FUNCTION_NO: command.clearscherm.kleur = FL_find_color(arg_array); break;

//		case EXECUTE_FUNCTION_NO: // Hoort er misschien niet in
//		{
//
//		}break;
		case FIGUUR_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.figuur.x1 = atoi(arg_array); break;
			case 2: command.figuur.y1 = atoi(arg_array); break;
			case 3: command.figuur.x2 = atoi(arg_array); break;
			case 4: command.figuur.y2 = atoi(arg_array); break;
			case 5: command.figuur.x3 = atoi(arg_array); break;
			case 6: command.figuur.y3 = atoi(arg_array); break;
			case 7: command.figuur.x4 = atoi(arg_array); break;
			case 8: command.figuur.y4 = atoi(arg_array); break;
			case 9: command.figuur.y4 = atoi(arg_array); break;
			case 10: command.figuur.x5 = atoi(arg_array); break;
			case 11: command.figuur.y5 = atoi(arg_array); break;
			case 12: command.figuur.kleur = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 247");
			}
		}break;

		case HERHAAL_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.herhaal.aantal = atoi(arg_array); break;
			case 2: command.herhaal.hoevaak = atoi(arg_array); break;
//			default: Error_Handler();//FL_error_handler("Illegal stored_args value, line 257");
			}
		}break;

		case LIJN_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.lijn.x1 = atoi(arg_array); break;
			case 2: command.lijn.y1 = atoi(arg_array); break;
			case 3: command.lijn.x2 = atoi(arg_array); break;
			case 4: command.lijn.y2 = atoi(arg_array); break;
			case 5: command.lijn.kleur = FL_find_color(arg_array); break;
			case 6: command.lijn.dikte = atoi(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 271");
			}
		}break;
		case RECHTHOEK_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.rechthoek.xlup = atoi(arg_array); break;
			case 2: command.rechthoek.ylup = atoi(arg_array); break;
			case 3: command.rechthoek.breedte = atoi(arg_array); break;
			case 4: command.rechthoek.hoogte = atoi(arg_array); break;
			case 5: command.rechthoek.kleur = FL_find_color(arg_array); break;
			case 6: command.rechthoek.gevuld = atoi(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 284");
			}
		}break;

//		case TEKST_FUNCTION_NO:	//Moet ik op terukomen. Je kan niet zomaar arg array meegeven aan de tekst functie want die is
//		{	 					//kleiner dan de max aantal karakters in 1 zin
//			switch(stored_args)
//			{
//			case 1: command.tekst.xlup = atoi(arg_array); break;
//			case 2: command.tekst.ylup = atoi(arg_array); break;
//			case 3: strcpy(command.tekst.tekst, arg_array); break;
//			}
//		}break;
		case TOREN_FUNCTION_NO:
		{
			switch(stored_args)
			{
			case 1: command.toren.x1 = atoi(arg_array); break;
			case 2: command.toren.y1 = atoi(arg_array); break;
			case 3: command.toren.grootte = atoi(arg_array); break;
			case 4: command.toren.kleur1 = FL_find_color(arg_array); break;
			case 5: command.toren.kleur2 = FL_find_color(arg_array); break;
//			default: FL_error_handler("Illegal stored_args value, line 306");
			}
		}break;

		case WACHT_FUNCTION_NO: command.wacht.msecs = atoi(arg_array); break;

		default : FL_error_handler("Did not recognise function number, line 312");
	}


*/

//	int i;
//	for(i = 0; i < num_chars; i++)
//	{
//		container[temp++] = arg_array[i];
//	}

//*/
}

uint8_t FL_find_color(char color[])
{
	/*
	 * hmm
	 */
	int ret_val;
	switch(color[0])
	{
	case LETTERB:{
		if(color[1] == LETTERL) ret_val = VGA_COL_BLUE;
		else ret_val = VGA_COL_BROWN;
	}break;

	case LETTERC: ret_val = VGA_COL_CYAN; break;

	case LETTERG:
	{
		if(color[1] == LETTERE) ret_val = VGA_COL_YELLOW;
		else {
			if(color[2] == LETTERI) ret_val = VGA_COL_GREY;
			else ret_val = VGA_COL_GREEN;
		}
	}break;

	case LETTERL:
	{
		switch(color[5])
		{
		case LETTERB: ret_val = VGA_COL_LITE_BLUE; break;
		case LETTERC: ret_val = VGA_COL_LITE_CYAN; break;
		case LETTERG: ret_val = VGA_COL_LITE_GREEN; break;
		case LETTERM: ret_val = VGA_COL_LITE_MAGENTA; break;
		case LETTERR: ret_val = VGA_COL_LITE_RED; break;
		default: ret_val = VGA_COL_BLACK;
		}
	}break;

	case LETTERM: ret_val = VGA_COL_MAGENTA; break;
	case LETTERR: ret_val = VGA_COL_RED; break;
	case LETTERW: ret_val = VGA_COL_WHITE; break;
	case LETTERZ: ret_val = VGA_COL_BLACK; break;

	default: ret_val = VGA_COL_BLACK;
	}

return ret_val;
}


void FL_error_handler(char *pErrorString)
{
	while(1);
}
