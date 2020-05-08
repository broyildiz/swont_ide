/**
  ******************************************************************************
  * @file           : FL.c
  * @brief          : This file contains the front layer
  * @author			: Groep 8
  * @date			: 08-05-2020
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FL.h"
#include "string.h"

/********************************************************************************************************
  * @brief  Decodes the received USART2 buffer.
  *
  * @param  None
  * @retval None
  *******************************************************************************************************/
int FL_uart_decode()
{
	int error = NO_ERROR;
	int function_number = FL_find_decode_nr(); /* Get the function number	   */
	if(function_number == FUNCTION_NO_RESET)   /* If no function is recognized */
	{
		FL_error_tx("Did not recognize function number, line 22\n");
		error = FL_INVALID_FUNCTION_NO;
//		Debug_INT(error);
//		printf("Error code:\t%d\n",error);
		return error;
	}

	command.function_number = function_number; /* Store the function number in the struct */


	/* This switch passes the right arguments to the FL_find_args function based on the function number */
	printf("function = %d\n",function_number);
	switch(function_number)
	{
		case BITMAP_FUNCTION_NO: error = FL_find_args(function_number, BITMAP_ARGS, BITMAP_FUNCTION_NAME_LEN);
		break;

		case CLEARSCHERM_FUNCTION_NO: error = FL_find_args(function_number, CLEARSCHERM_ARGS, CLEARSCHERM_FUNCTION_NAME_LEN);
		break;

		case CIRKEL_FUNCTION_NO: error = FL_find_args(function_number, CIRKEL_ARGS, CIRKEL_FUNCTION_NAME_LEN);
		break;

		case EXECUTE_FUNCTION_NO: /* special case: no args, so directly execute */
		break;

		case FIGUUR_FUNCTION_NO: error = FL_find_args(function_number, FIGUUR_ARGS, FIGUUR_FUNCTION_NAME_LEN);
		break;

		case HERHAAL_FUNCTION_NO: error = FL_find_args(function_number, HERHAAL_ARGS, HERHAAL_FUNCTION_NAME_LEN);
		break;

		case LIJN_FUNCTION_NO: error = FL_find_args(function_number, LIJN_ARGS, LIJN_FUNCTION_NAME_LEN);
		break;

		case RECHTHOEK_FUNCTION_NO: error = FL_find_args(function_number, RECHTHOEK_ARGS, RECHTHOEK_FUNCTION_NAME_LEN);
		break;

		case TEKST_FUNCTION_NO: error = FL_find_args(function_number, TEKST_ARGS, TEKST_FUNCTION_NAME_LEN);
		break;

		case WACHT_FUNCTION_NO: error = FL_find_args(function_number, WACHT_ARGS, WACHT_FUNCTION_NAME_LEN);
		break;

		case MONDRIAAN_FUNCTION_NO: break; /* No arguments */

		default : {
			FL_error_tx("Did not recognise function number, line 67\n");
			error = FL_SWITCH_INVALID_FUNCTION_NO;
			return error;
		}
	}
	if(error)
	{
		FL_error_tx("A FL_find_args function returned an error\n");
		return error;
	}

	/*
	 * Let the Logic Layer know that it can start to execute the command
	 * It should not be called if there was an error in the previous switch case
	 */

	error = LL_exec(&command);
	return error;
}

/********************************************************************************************************
  * @brief  Finds the function number based on the name of the function
  *
  * @param  None
  * @retval Function number
  *******************************************************************************************************/
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

	if(input.line_rx_buffer[0] == LETTERT) return TEKST_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERW) return WACHT_FUNCTION_NO;

	if(input.line_rx_buffer[0] == LETTERM) return MONDRIAAN_FUNCTION_NO;

	return FUNCTION_NO_RESET;

}

/********************************************************************************************************
  * @brief  Finds the arguments of the function by looping through the buffer and storing and converting
  * 		the characters
  *
  * @param  Function number	  : The function numbers are defined/enumerated in FL.h
  * @param	num_args	      : Number of funcion arguments
  * @param 	len_function_name : Number of characters in the function name
  * 							(This determines the starting point of the parser)
  * @retval None
  *******************************************************************************************************/
int FL_find_args(int function_number, int num_args, int len_function_name)
{
	char string_container[MAX_ARG_LEN]; /* Container for the raw string characters */
	int  error = NO_ERROR;
	int  arg_character_counter = 0;
	int  argcounter = 0; /* Counts how many arguments are stored. Is incremented after successfully storing an arg */
	int  skip_first_comma = FALSE;
	int  k;
	int  i = len_function_name; /* Start at the first comma */

	for(k = 0; k < MAX_ARG_LEN; k++)
		string_container[k] = 0; /* Reset the container */

	/* The Text function needs to be decoded differently */
	if(function_number != TEKST_FUNCTION_NO)
	{
		while(i <= input.msglen)
		{
			if(input.line_rx_buffer[i] == ',')
			{
				if(skip_first_comma) /* When it is not the first argument */
				{
					/* convert the stored string() */
					error = FL_convert_args(string_container, ++argcounter);

					if(error) break;
					/* reset string container */
					for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
					arg_character_counter = 0;
				}
				else skip_first_comma = TRUE;	/* This else is only reached after the while loop */

				i++; /* Go to the next character in the rx_buffer */
			}
			if(input.line_rx_buffer[i] == ' ')
				i++;	/* Ignore the spaces */
			else
			{
				if(input.line_rx_buffer[i] == ','){
					/* If there is a comma after a comma, then there is no argument given. */
					FL_error_tx("Argument not filled, line 191");
					error = FL_EMPTY_ARGUMENT;
					return error;
				}
				else
				{
					/* Save the character into the string container */
					string_container[arg_character_counter++] = input.line_rx_buffer[i++];
				}
			}
		}
		/* If there was a break just now */
		if(error)
		{
			FL_error_tx("There was an error during conversion\n");
			return error;
		}

		/* In case there was no break */
		error = FL_convert_args(string_container, ++argcounter);

		if(error)
		{
			FL_error_tx("There was an error during conversion\n");
			return error;
		}
//		if(stored_args != (num_args - 1)) {
//			error = FL_TOO_MANY_ARGS;
//			return error;
//		}

		return NO_ERROR;


	}

	/* It is the Text function */
	else
	{
		while(i <= input.msglen)
		{
			if(input.line_rx_buffer[i] == ',')
			{

				if(skip_first_comma) /* This else is only reached after the while loop */
				{
					/* convert the stored string() */
					error = FL_convert_args(string_container, ++argcounter);
					if(error) break;
					/* reset string container */
					for(k = 0; k < MAX_ARG_LEN; k++) string_container[k] = 0;
					arg_character_counter = 0;
				}
				else skip_first_comma = TRUE; /* This else is only reached after the while loop */

				i++; /* Go to the next character in the rx_buffer */
			}

			if(argcounter == 3)
			{
				/*
				 * The fourth argument of the text function is the text to be displayed on the screen
				 * This text contains spaces and they must not be ignored.
				 */
				if(input.line_rx_buffer[i] == ','){
					/* If there is a comma after a comma, then there is no argument given. */
					FL_error_tx("Argument not filled, line 191");
					error = FL_EMPTY_ARGUMENT;
					return error;
				}
				else {
					/* Save the character into the string container */
					string_container[arg_character_counter++] = input.line_rx_buffer[i++];
				}

			}
			else
			{
				if(input.line_rx_buffer[i] == ' ') i++; /* Ignore the spaces */
				else
				{
					if(input.line_rx_buffer[i] == ','){
						/* If there is a comma after a comma, then there is no argument given. */
						FL_error_tx("Argument not filled, line 191");
						error = FL_EMPTY_ARGUMENT;
						return error;
					}
					else {
						/* Save the character into the string container */
						string_container[arg_character_counter++] = input.line_rx_buffer[i++];
					}
				}
			}

		}

		/* If there was a break just now */
		if(error)
		{
			FL_error_tx("There was an error during conversion\n");
			return error;
		}

		/* In case there was no break */
		error = FL_convert_args(string_container, ++argcounter);

		if(error)
		{
			FL_error_tx("There was an error during conversion\n");
			return error;
		}

		return NO_ERROR;
	}
}

/********************************************************************************************************
  * @brief  Converts the arguments to the right types and stores them in the command struct
  *
  * @param  arg_array  : Array with the to be processed string
  * @param	argcounter : Counter that keeps track of which argument of the function is to be processed
  * @retval None
  *******************************************************************************************************/
int FL_convert_args(char arg_array[], int argcounter)
{
	int error = NO_ERROR;
	switch(command.function_number)
	{
		case BITMAP_FUNCTION_NO:
		{
			switch(argcounter)
			{
			case 1:	command.bitmap.nr = atoi(arg_array); break;
			case 2: command.bitmap.xlup = atoi(arg_array); break;
			case 3: command.bitmap.ylup = atoi(arg_array); break;
//			default: FL_error_tx("Illegal stored_args value, line 209");//Error_Handler();
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
//			default: FL_error_tx("Illegal stored_args value, line 221");//Error_Handler();
			}
		}break;

		case CLEARSCHERM_FUNCTION_NO:
			command.clearscherm.kleur = FL_find_color(arg_array);
			break;

		case FIGUUR_FUNCTION_NO:
		{
			switch(argcounter)
			{
				case 1:  command.figuur.x1 = atoi(arg_array); break;
				case 2:  command.figuur.y1 = atoi(arg_array); break;
				case 3:  command.figuur.x2 = atoi(arg_array); break;
				case 4:  command.figuur.y2 = atoi(arg_array); break;
				case 5:  command.figuur.x3 = atoi(arg_array); break;
				case 6:  command.figuur.y3 = atoi(arg_array); break;
				case 7:  command.figuur.x4 = atoi(arg_array); break;
				case 8:  command.figuur.y4 = atoi(arg_array); break;
				case 9:  command.figuur.x5 = atoi(arg_array); break;
				case 10: command.figuur.y5 = atoi(arg_array); break;
				case 11: command.figuur.kleur = FL_find_color(arg_array); break;
//			default: FL_error_tx("Illegal stored_args value, line 247");
			}
		}break;

		case HERHAAL_FUNCTION_NO:
		{
			switch(argcounter)
			{
				case 1: command.herhaal.aantal = atoi(arg_array); break;
				case 2: command.herhaal.hoevaak = atoi(arg_array); break;
//			default: Error_Handler();//FL_error_tx("Illegal stored_args value, line 257");
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
//			default: FL_error_tx("Illegal stored_args value, line 271");
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
//			default: FL_error_tx("Illegal stored_args value, line 284");
			}
		}break;

		case TEKST_FUNCTION_NO:
		{
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

		case WACHT_FUNCTION_NO: command.wacht.msecs = atoi(arg_array); break;

//		case MONDRIAAN_FUNCTION_NO: //No Arguments

		default : {
			FL_error_tx("Did not recognise function number in the convert args function");
			error = FL_CONVERT_ARGS_INVALID_FUNCTION_NO;
			return error;
		}
	}
	return error;
}

/********************************************************************************************************
  * @brief  Determines the color from a string passed to it
  * 		If the string is "white" this returns 0xFF
  *
  * @param  color: Array with the string containing the color
  * @retval 8 bit color value
  *******************************************************************************************************/
uint8_t FL_find_color(char color[])
{
	int ret_val;

	switch(color[0])
	{
	case LETTERB:
	{
		if(color[1] == LETTERL) ret_val = VGA_COL_BLUE;
		else ret_val = VGA_COL_BROWN;
	}break;

	case LETTERC: ret_val = VGA_COL_CYAN; break;

	case LETTERG:
	{
		if(color[1] == LETTERE) ret_val = VGA_COL_YELLOW;
		else
		{
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

/********************************************************************************************************
  * @brief  Determines the font style of the text function
  *
  * @param  arg_array: Array with the string containing the font style
  * @retval predefined integer value of the font style
  *******************************************************************************************************/
int FL_find_font_style(char arg_array[])
{
	int retval;
	if(arg_array[0] == LETTERN) retval = NORMAL;
	if(arg_array[1] == LETTERC) retval = ITALIC;
	if(arg_array[2] == LETTERV) retval = BOLD;
	return retval;
}

/********************************************************************************************************
  * @brief  When an error has occured, this function informs the user via USARt2 debugging
  *
  * @param  error: The error code
  * @retval none
  *******************************************************************************************************/
void FL_global_error_handler(int error)
{
	printf("\n\nENCOUNTERRED AN ERROR!\n");
	printf("Error code:\t%d\n",error);
	switch(error)
	{
	case FL_INIT_ERROR: 					printf("\nERROR:\tFL_INIT_ERROR\n"); break;
	case FL_INVALID_FUNCTION_NO: 			printf("\nERROR:\tFL_INVALID_FUNCTION_NO\n");  break;
	case FL_SWITCH_INVALID_FUNCTION_NO: 	printf("\nERROR:\tFL_SWITCH_INVALID_FUNCTION_NO\n");  break;
	case FL_INVALID_ARGUMENTS: 				printf("\nERROR:\tFL_INVALID_ARGUMENTS\n");  break;
	case FL_TOO_MANY_ARGS: 					printf("\nERROR:\tFL_TOO_MANY_ARGS\n");  break;
	case FL_EMPTY_ARGUMENT: 				printf("\nERROR:\tFL_EMPTY_ARGUMENT\n");  break;
	case LL_NOT_A_SUPPORTED_FUNCTION: 		printf("\nERROR:\tLL_NOT_A_SUPPORTED_FUNCTION\n");  break;
	case IOL_LINE_INVALID_ARG_VALUE: 		printf("\nERROR:\tIOL_LINE_INVALID_ARG_VALUE\n");  break;
	case IOL_BITMAP_NON_EXISTENT: 			printf("\nERROR:\tIOL_BITMAP_NON_EXISTENT\n");  break;
	case IOL_ERROR_FONTNAME: 				printf("\nERROR:\tIOL_ERROR_FONTNAME\n");  break;
	case IOL_ERROR_FONTNAME_UNKNOWN: 		printf("\nERROR:\tIOL_ERROR_FONTNAME_UNKNOWN\n");  break;
	case IOL_ARIAL_FONT_ERROR: 				printf("\nERROR:\tIOL_ARIAL_FONT_ERROR\n");  break;
	case IOL_CONSOLAS_FONT_ERROR: 			printf("\nERROR:\tIOL_CONSOLAS_FONT_ERROR\n");  break;
	case IOL_FONT_ERROR: 					printf("\nERROR:\tIOL_FONT_ERROR\n");  break;
	default: 								printf("\nERROR:\tNo Error\n"); break;
	}
}

/********************************************************************************************************
  * @brief  When an error message needs to be sent, this function does it. It is not dependent on if debug
  * 		is enabled
  *
  * @param  pDebugmessage: The error message string
  * @retval None
  *******************************************************************************************************/
void FL_error_tx(char  *pErrorMessage)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)pErrorMessage, strlen(pErrorMessage), HAL_MAX_DELAY);
}

/********************************************************************************************************
  * @brief  When a debug message needs to be sent, this function does it. It is dependent on if debug
  * 		 is enabled
  *
  * @param  pDebugmessage: The debug message string
  * @retval None
  *******************************************************************************************************/
void FL_debug_tx( char *pDebugMessage)
{
	if(global_debug)
		HAL_UART_Transmit(&huart2, (uint8_t*)pDebugMessage, strlen(pDebugMessage), HAL_MAX_DELAY);
}

/********************************************************************************************************
  * @brief  When an integer needs to be sent to the UART, this function is used
  *
  * @param  num: The integer number to be sent
  * @retval None
  *******************************************************************************************************/
void FL_debug_int(int num)
{
	if(global_debug)
		printf("%d\n",num);
}

/********************************************************************************************************
  * @brief  This function checks if the debugging needs to be toggled
  *
  * @param  None
  * @retval None
  *******************************************************************************************************/
void FL_global_debug_check()
{
	FL_debug_tx("Toggling Debugging\n");
	if(	(input.line_rx_buffer[0] == 'd') &&
		(input.line_rx_buffer[1] == 'e') &&
		(input.line_rx_buffer[2] == 'b'))
	{
//		global_debug = True;
		global_debug = !global_debug;
	}
}


