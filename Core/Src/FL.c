/*
 * FL.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Ömer
 */

#include "FL.h"
#include "string.h"

/**
  * @brief  Resets all the variables
  * @param  None
  * @retval None
  */
void FL_Init()
{
	input.char_counter = 0;
	input.command_execute_flag = False;
	waitCheck = False;

	rb_vars.write_counter = 0;
	rb_vars.read_counter = 0;
	rb_vars.buffer_lengt = 0;

//	int i;
//	for(i = 0; i < LINE_BUFLEN; i++) input.line_rx_buffer[i] = 0;
	memset(rb, 0, sizeof(rb)); // Set all the bits to 0, reset the whole array
	memset(command.tekst.tekst, 0, sizeof(command.tekst.tekst));
	Debug_Tx("Done with FL Init\n");
}


/**
  * @brief  Decodes the received buffer.
  * @param  The buffer containing the message
  * @param 	The ammounf of characters in the buffer
  * @retval Error value
  */
int FL_uart_decode(uint8_t line_rx_buffer[], int msglen)
{
	Debug_Tx("Entering FL_uart_decode\n");
	strcpy(container, line_rx_buffer);
	Debug_Tx(container); Debug_Tx("\n");

	int error = NO_ERROR;

	int function_number = FL_decode_func_no(line_rx_buffer); // Get the function number
	if(function_number == FUNCTION_NO_RESET) // If no function is recognized
	{
		error = FL_INVALID_FUNCTION_NO;
		Debug_Tx("Did not recognize function number, line 52\n");
		return error;

	}

	Debug_Tx("Found and storing function number\n");
	command.function_number = function_number; // Store the function number in the struct

	Debug_Tx("Entering the function number switch case\n");

	//This switch passes the right arguments to the FL_find_args function based on the function number
	printf("function = %d\n",function_number);
	switch(function_number)
	{
		case BITMAP_FUNCTION_NO: error = FL_find_args(function_number, BITMAP_ARGS, BITMAP_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case CLEARSCHERM_FUNCTION_NO: error = FL_find_args(function_number, CLEARSCHERM_ARGS, CLEARSCHERM_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case CIRKEL_FUNCTION_NO: error = FL_find_args(function_number, CIRKEL_ARGS, CIRKEL_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case EXECUTE_FUNCTION_NO: //special case: no args, so directly execute
		break;

		case FIGUUR_FUNCTION_NO: error = FL_find_args(function_number, FIGUUR_ARGS, FIGUUR_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case HERHAAL_FUNCTION_NO: error = FL_find_args(function_number, HERHAAL_ARGS, HERHAAL_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case LIJN_FUNCTION_NO: error = FL_find_args(function_number, LIJN_ARGS, LIJN_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case RECHTHOEK_FUNCTION_NO: error = FL_find_args(function_number, RECHTHOEK_ARGS, RECHTHOEK_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case TEKST_FUNCTION_NO: error = FL_find_args(function_number, TEKST_ARGS, TEKST_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		case WACHT_FUNCTION_NO: error = FL_find_args(function_number, WACHT_ARGS, WACHT_FUNCTION_NAME_LEN,
												line_rx_buffer, msglen);
		break;

		default : {
			error = FL_SWITCH_INVALID_FUNCTION_NO;
			Debug_Tx("Did not recognize function number, line 107\n");
			return error;
		}
	}

	if(error) {
		Debug_Tx("One of the FL_find_args functions threw an error, line 113!\n");
		return error;
	}

	Debug_Tx("Back in the FL_uart_decode function\n");
	Debug_Tx("Going into Logic layer\n");
	/*
	 * Let the Logic Layer know that it can start to execute the command
	 * It should not be called if there was an error in the previous switch case
	 */
	error = LL_exec(&command);

	Debug_Tx("Back in the FL_uart_decode function\n");
	Debug_Tx("Exiting FL_uart_decode\n");
	return error;
}

/**
  * @brief  Finds the function number based on the name of the function
  * @param  The array containing the function name in text
  * @retval Function number
  */
int FL_decode_func_no(uint8_t buffer[])
{
	if(buffer[0] == LETTERB) {
		Debug_Tx("\n\t BITMAP_FUNCTION\n\n");
		return BITMAP_FUNCTION_NO;}

	if(buffer[0] == LETTERC)
	{
		if(buffer[1] == LETTERL) {
			Debug_Tx("\n\t CLEARSCHERM_FUNCTION\n\n");
			return CLEARSCHERM_FUNCTION_NO;
		}
		else {
			Debug_Tx("\n\t CIRKEL_FUNCTION\n\n");
			return CIRKEL_FUNCTION_NO;
		}
	}

	if(buffer[0] == LETTERE) {
		Debug_Tx("\n\t EXECUTE_FUNCTION\n\n");
		return EXECUTE_FUNCTION_NO;
	}

	if(buffer[0] == LETTERF) {
		Debug_Tx("\n\t FIGUUR_FUNCTION\n\n");
		return FIGUUR_FUNCTION_NO;
	}

	if(buffer[0] == LETTERH) {
		Debug_Tx("\n\t HERHAAL_FUNCTION\n\n");
		return HERHAAL_FUNCTION_NO;
	}

	if(buffer[0] == LETTERL) {
		Debug_Tx("\n\t LIJN_FUNCTION\n\n");
		return LIJN_FUNCTION_NO;
	}

	if(buffer[0] == LETTERR) {
		Debug_Tx("\n\t RECHTHOEK_FUNCTION\n\n");
		return RECHTHOEK_FUNCTION_NO;
	}

	if(buffer[0] == LETTERT)
	{
		if(buffer[1] == LETTERE) {
			Debug_Tx("\n\t TEKST_FUNCTION\n\n");
			return TEKST_FUNCTION_NO;
		}
		else {
			Debug_Tx("\n\t TOREN_FUNCTION\n\n");
			return TOREN_FUNCTION_NO;
		}
	}

	if(buffer[0] == LETTERW) {
		Debug_Tx("\n\t WACHT_FUNCTION\n\n");
		return WACHT_FUNCTION_NO;
	}

	return FUNCTION_NO_RESET;

}

/**
  * @brief  Finds the arguments of the function by looping through the buffer and storing and converting the characters
  * @param  The function numbers are defined/enumerated in FL.h
  *
  * @param	Number of funcion arguments
  * @param 	Number of characters in the function name. This determines the starting point of the parser
  * @retval None
  */
int FL_find_args(int function_number, int num_args, int len_function_name, uint8_t line_rx_buffer[], int msglen)
{
	Debug_Tx("Entered the FL_find_args function\n");
	int error = NO_ERROR;
	/*
	 * Keep track of how many arguments are found.
	 * If num_args_counter exceeds num_args throw an error
	 */
	char num_args_counter = 0;

	char string_container[MAX_ARG_LEN]; // Container for the raw string characters

	int k;
	for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0; // Reset the container

	int arg_character_counter = 0;
	char stored_args = 0; // Counts how many arguments are stored. is incremented after successfully storing an arg
	int argcounter = 0;
	int i = len_function_name; // Start at the first comma

	//The Text function needs to be decoded differently
	if(function_number != TEKST_FUNCTION_NO)
	{
		Debug_Tx("It is not the text function\n");
		while(i <= msglen)
		{

			if(line_rx_buffer[i] == ',')
			{

				if(stored_args != 0) // Dit is niet de eerste komma dus
				{
					// convert the stored string()
					Debug_Tx("Found an argument that should be decoded\n");
					Debug_Tx("The argument:\t");
					Debug_Tx(string_container);
					Debug_Tx("\n");
					error = FL_convert_args(string_container, ++argcounter);
					if(error){
						Error_Tx("There was a problem while converting the arguments\n");
						return error;
					}
					num_args_counter++;
					Debug_Tx("Done with the converting, back in the FL_find_args function\n");
					// reset string container
					for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
					arg_character_counter = 0;
					stored_args++;
				}
				else stored_args++;

				i++;
			}
			if(line_rx_buffer[i] == ' ')
				i++;
			else
			{
				if(line_rx_buffer[i] == ',')
				{
					Debug_Tx("Argument not filled, line 150");
					Error_Tx("The argument is not filled");
					error = FL_EMPTY_ARGUMENT;
					return error;
				}

				else
				{
					string_container[arg_character_counter++] = line_rx_buffer[i++];
				}
			}
		}
		Debug_Tx("The last argument to be processed:\t");
		Debug_Tx(string_container);Debug_Tx("\n");

		error = FL_convert_args(string_container, ++argcounter);
		if(error){
			Error_Tx("There was a problem while converting the arguments\n");
			return error;
		}

		num_args_counter++;
		if(num_args_counter > num_args) {
			Error_Tx("Too many arguments");
			error = FL_TOO_MANY_ARGS;
			return error;
		}
		Debug_Tx("Done with converting, exiting FL_find_args\n");
		return error;

	}

	// It is the Text function
	else
	{
		Debug_Tx("It is the text function\n");
		while(i <= msglen)
		{
			if(line_rx_buffer[i] == ',')
			{

				if(stored_args != 0) // Dit is niet de eerste komma dus
				{
					// convert the stored string()
					Debug_Tx("Found an argument that should be decoded\n");
					Debug_Tx("The argument:\t");
					Debug_Tx(string_container);
					Debug_Tx("\n");
					error = FL_convert_args(string_container, ++argcounter);
					if(error)
					{
						Error_Tx("There was a problem while converting the arguments\n");
						return error;
					}

					// reset string container
					for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
					arg_character_counter = 0;
					stored_args++;
				}
				else stored_args++;

				i++;
			}

			if(stored_args == 4)
			{
				if(line_rx_buffer[i] == ',')
				{
					Debug_Tx("Argument not filled, line 335");
					Error_Tx("The argument is not filled");
					error = FL_EMPTY_ARGUMENT;
					return error;
				}
				else string_container[arg_character_counter++] = line_rx_buffer[i++];

			}
			else
			{
				if(line_rx_buffer[i] == ' ') i++;
				else
				{
					if(line_rx_buffer[i] == ',')
					{
						Debug_Tx("Argument not filled, line 150");
						Error_Tx("The argument is not filled");
						error = FL_EMPTY_ARGUMENT;
						return error;
					}
					else string_container[arg_character_counter++] = line_rx_buffer[i++];
				}
			}

		}
		Debug_Tx("The last argument to be processed:\t");
		Debug_Tx(string_container);Debug_Tx("\n");
		error = FL_convert_args(string_container, ++argcounter);
		if(error){
			Error_Tx("There was a problem while converting the arguments\n");
			return error;
		}
		Debug_Tx("Done with converting, exiting FL_find_args\n");
		num_args_counter++;
		if(num_args_counter > num_args) {
			Error_Tx("Too many arguments");
			error = FL_TOO_MANY_ARGS;
			return error;
		}
		Debug_Tx("Done with converting, exiting FL_find_args\n");
		return error;

	}
}

/**
  * @brief  Converts the arguments to the right types and stores them in the command struct
  * @param  Array with the to be processed string
  * @param	Counter that keeps track of which argument of the function is to be processed
  * @retval None
  */
int FL_convert_args(char arg_array[], int argcounter)
{
	int error = NO_ERROR;
	Debug_Tx("Entered the FL_convert_args function\n");
	switch(command.function_number)
	{
		case BITMAP_FUNCTION_NO:
		{
			switch(argcounter)
			{
				case 1:	command.bitmap.nr = atoi(arg_array); break;

				case 2: command.bitmap.xlup = atoi(arg_array); break;

				case 3: command.bitmap.ylup = atoi(arg_array); break;

//				default: Error_Tx("Illegal stored_args value, line 209");//Error_Handler();
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
//			default: Error_Tx("Illegal stored_args value, line 221");//Error_Handler();
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
//			default: Error_Tx("Illegal stored_args value, line 247");
			}
		}break;

		case HERHAAL_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.herhaal.aantal = atoi(arg_array); break;
			case 2: command.herhaal.hoevaak = atoi(arg_array); break;
//			default: Error_Handler();//Error_Tx("Illegal stored_args value, line 257");
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
//			default: Error_Tx("Illegal stored_args value, line 271");
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
//			default: Error_Tx("Illegal stored_args value, line 284");
			}
		}break;

		case TEKST_FUNCTION_NO:	//Moet ik op terukomen. Je kan niet zomaar arg array meegeven aan de tekst functie want die is
		{	 					//kleiner dan de max aantal karakters in 1 zin
			switch(argcounter)
			{
			case 1: command.tekst.xlup = atoi(arg_array); break;
			case 2: command.tekst.ylup = atoi(arg_array); break;
			case 3: command.tekst.kleur = FL_find_color(arg_array); break;
			case 4: strcpy(command.tekst.tekst, arg_array); break;
			case 5: strcpy(command.tekst.fontnaam, arg_array); break;
			case 6: command.tekst.fontgrootte = atoi(arg_array); break;
			case 7: command.tekst.fontstijl = FL_find_font_style(arg_array); break;
			}
		}break;
		case TOREN_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1: command.toren.x1 = atoi(arg_array); break;
			case 2: command.toren.y1 = atoi(arg_array); break;
			case 3: command.toren.grootte = atoi(arg_array); break;
			case 4: command.toren.kleur1 = FL_find_color(arg_array); break;
			case 5: command.toren.kleur2 = FL_find_color(arg_array); break;
//			default: Error_Tx("Illegal stored_args value, line 306");
			}
		}break;

		case WACHT_FUNCTION_NO: command.wacht.msecs = atoi(arg_array); break;

		default : {
			Error_Tx("Did not recognize function number, line 312");
			error = FL_CONVERT_ARGS_INVALID_FUNCTION_NO;
			return error;
		}
	}

	Debug_Tx("Exiting the FL_convert_args function\n");
	return error;
}

/**
  * @brief  Determines the color from a string passed to it
  * 		If the string is "white" this returns 0xFF
  * @param  Array with the string containing the color
  * @retval 8 bit color value
  */
uint8_t FL_find_color(char color[])
{
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

int FL_find_font_style(char arg_array[])
{
	if(arg_array[0] == LETTERN) return NORMAL;
	if(arg_array[1] == LETTERC) return NORMAL;
	if(arg_array[2] == LETTERV) return NORMAL;
}


