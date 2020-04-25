/*
 * FL.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Ömer
 */

#include "FL.h"

void FL_uart_decode()
{
	int function_number = FL_find_decode_nr();
	if(function_number == FUNCTION_NO_RESET)
		FL_error_handler();

	switch(function_number)
	{
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

		default : FL_error_handler();
	}

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
		int i = len_function_name; // Start at the first comma

		while(i <= input.msglen)
		{
			if(input.line_rx_buffer[i] == ',')
			{

				if(stored_args != 0) // Dit is niet de eerste komma dus
				{
					// convert the stored string()
					FL_convert_args(string_container, arg_character_counter, function_number, num_args, stored_args);
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
					FL_error_handler();
				else
				{
					string_container[arg_character_counter++] = input.line_rx_buffer[i++];
				}
			}


		}
		FL_convert_args(string_container, --arg_character_counter, function_number, num_args, stored_args); // Op het einde van de while wordt arg_counter opgehoogd.
																	//je krijgt, als je dat aan de functie meegeeft, een \0 te zien.
																	//om die ertui te halen doe je --

/*
		sscanf()


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

void FL_convert_args(char arg_array[], int num_chars, int function_number, int num_args, int stored_args)
{
	switch(function_number)
	{
		case BITMAP_FUNCTION_NO:
		{

		}break;
		case CIRKEL_FUNCTION_NO:
		{

		}break;
		case CLEARSCHERM_FUNCTION_NO:
		{

		}break;
		case EXECUTE_FUNCTION_NO:
		{

		}break;
		case FIGUUR_FUNCTION_NO:
		{

		}break;
		case HERHAAL_FUNCTION_NO:
		{

		}break;
		case LIJN_FUNCTION_NO:
		{

		}break;
		case RECHTHOEK_FUNCTION_NO:
		{

		}break;
		case TEKST_FUNCTION_NO:
		{

		}break;
		case TOREN_FUNCTION_NO:
		{

		}break;
		case WACHT_FUNCTION_NO:
		{

		}break;

	}




//	int i;
//	for(i = 0; i < num_chars; i++)
//	{
//		container[temp++] = arg_array[i];
//	}
}

uint8_t FL_find_color(int color)
{

}


void FL_error_handler()
{
	while(1);
}
