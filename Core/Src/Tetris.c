/*
 * Tetris.c
 *
 *  Created on: May 7, 2020
 *      Author: Ömer
 */
#include "main.h"
#include "IOL.h"
#include "stm32_ub_vga_screen.h"
#include "string.h"

void move_piece(char  , unsigned char *);
void line_clear();
void move_row_down(unsigned char);
unsigned char initialize_piece(unsigned char *);
unsigned char collision_check(unsigned char, unsigned char);
unsigned char rotate_piece(unsigned char, unsigned char, unsigned char *, char);
unsigned char random_shape(void);
unsigned char gravity(unsigned char, unsigned char*);

void Display();

//#define DEBUG
#define DFTSIZE 100
//#define TRUE 1

//#define MOVE_LEFT   			  1
//#define MOVE_RIGHT 	  			  3
//#define ROTATE_COUNTERCLOCKWISE   5
//#define ROTATE_CLOCKWISE  		  2
#define ROWS					  22
#define COLUMNS                   10

#define I_SHAPE 1
#define J_SHAPE 2
#define L_SHAPE 3
#define O_SHAPE 4
#define S_SHAPE 5
#define T_SHAPE 6
#define Z_SHAPE 7

//globals
unsigned char field[ROWS][COLUMNS];//playing field

//static
unsigned char starting_points[7][8] =  {{3, 20, 4, 20, 5, 20, 6, 20}, //starting point I
										{4, 21, 5, 20, 4, 20, 6, 20}, //starting point J
										{4, 20, 5, 20, 6, 20, 6, 21}, //starting point L
										{4, 21, 4, 20, 5, 21, 5, 20}, //starting point O
										{4, 20, 5, 20, 6, 21, 7, 21}, //starting point S
										{4, 20, 5, 20, 5, 21, 6, 20}, //starting point T
										{4, 20, 5, 20, 5, 21, 6, 20}}; //starting point Z

/*****************************************************************************
 main: tetris game
 arguments (inputs):
	magnitudes of the following frequencies:
 return value (output):
	RS232 protocol message
*****************************************************************************/
void IO_tetris(void)
{
	tetris_toggle = TRUE;
/***initialization*******************************************************/
	unsigned char playpos[8];//position of the playing piece
	unsigned char shape = 0; //0 t/m 6 corresponds with the shape of the tetromino
	unsigned char orientation=0; // 0 t/m 3  there are 4 rotation orientations needed for wallkicks and I tetromino
	//unsigned char *pplaypos = &playpos[0];
    //	uint32_t gravity = 0;
//	srand(time(NULL));   	 // Initialization, should only be called once.
	unsigned char i,j,k=0;

/***********************************************************************/
	for (i = 0; i < ROWS; i++) // misschien dit in een functie zetten
  		for ( j = 0; j < COLUMNS; j++)
    		field[i][j] = 0;

	while(1)
	{

		#ifdef DEBUG
				printf("start van main \n "); // toont de posities van het huidige speel stuk/blok

		#endif
		if (shape == 0)//checks if there is a piece in play
		{
			shape = initialize_piece(playpos); //initializes the position of the piece

			orientation = 0;// resets piece orientation
		}
		for (k=0; k<1;k++)
		{
//			scanf("%d", &key);// leest 1,2,3 of 5 uit
			HAL_Delay(1000);

	 		switch (key)
	 		{
	 			case MOVE_LEFT:
	 				move_piece((char)MOVE_LEFT, playpos);//moves piece to the left
	 				break;
	 			case MOVE_RIGHT:
	 				move_piece((char)MOVE_RIGHT , playpos);//moves piece to the right
	 				break;
	 			case ROTATE_COUNTERCLOCKWISE:
	 				orientation = rotate_piece(shape, orientation, playpos, -1); // rotate piece counter clockwise
	 				break;
	 			case ROTATE_CLOCKWISE:
	 				orientation = rotate_piece(shape, orientation, playpos, 1); // rotate piece clockwise
	 				break;
	 			default:
	 				break;
	 		}

 		}
		key = 6; //zodat die niet dezelfde waarde blijft behoudden. wordt maar 1 keer gedaan dus

		for(i=0; i<7; i+=2)
			field[playpos[i+1]][playpos[i]] = shape;	// plaatst de shape in het veld

		for(i = ROWS; i >= 1; i--)
		{
			for(j = 0; j < COLUMNS; j++)
				printf("%d ", field[i-1][j]);
			printf("\n");
		}
		Display();

 		printf("voor gravity \n ");
		shape = gravity(shape, playpos)	;
 		line_clear();

	}
}


void Display()
{
	//clearscherm blauw
	//Teken rechthoek speelveld
	//Teken blokken
		//Convert
	//Teken raster
	int r = 0;
	int c = 0;
	int i = 0;

	int y = 0;
	int x = 0;
	int z = 10;

	uint8_t color = VGA_COL_BLACK;

	for(z = 230; z > 10; z -= 10)
	{
		for(y = z-10; y < z; y++)
		{
		i = 0;
		for(x = 10; x < 110; x++)
		{
			if(i > 9)
			{
				i = 0;

				c++;
			}
			if(field[r][c]) color = VGA_COL_BLUE;
			else color = VGA_COL_BLACK;
			UB_VGA_SetPixel(x, y, (color));
			i++;
		}

			c = 0;
		}
		r++;
	}


}



//update rate or gravity through interrupt

unsigned char random_shape(void) // determines the shape of the tetromino  moet anders voor op de ARM
{
	unsigned char shape = rand() % 7;      // Returns a pseudo-random integer between 0 and 7.
	#ifdef DEBUG

	printf("random_shape function : %d \n", shape+1);
	#endif
	return shape;
}

unsigned char initialize_piece(unsigned char *pplaypos) // initializes the piece to determine the shape and starting point values
{
	unsigned char shape = random_shape(); // chooses a random shape
	#ifdef DEBUG

	printf("initialize_piece function : %d \n", shape+1);
	#endif
	unsigned char i;
		for (i = 0; i < 8; i++) // misschien dit in een functie zetten
		*(pplaypos+i) = starting_points[shape][i];
	return shape+1;
}

void move_piece(char direction, unsigned char *pplaypos)// function to move the play piece if possible
{
	unsigned char i,j;
	if(direction==MOVE_LEFT) //checks if the direction of the movement is to the left
		direction = -1;

	else if(direction==MOVE_RIGHT) //checks if the direction of the movement is to the right
		direction =  1;

	for (i=0; i<7; i+=2)
		{
			if(collision_check(*(pplaypos+i)+direction,*(pplaypos+i+1))) // checks if the new positions are available
				continue;
			else
				break;
		}

	if (i>6) //4 checks total check for each block is OK
	{
		for(j=0; j<7; j+=2)
		{
			*(pplaypos+j) = *(pplaypos+j)+direction;// moving x_pos to the left
		}
	}
}

unsigned char rotate_piece(unsigned char shape, unsigned char orientation, unsigned char *pplaypos, char rotation) //rotates the play piece if possible
{
	unsigned char tempplaypos[8];// temporary array to check for collision before writing the new values
	unsigned i, j,k=0;
   /*for (unsigned char i; i < 8;i++)
		tempplaypos[i]= *(pplaypos+i);
	*/
	/*if (shape == I_SHAPE)
		if (orientation%2==1)
	 hier moet nog code omdat het draaipunt van de I anders te bepalen is wisselingen tussen 0 & 1 en 2 & 3 moet als draaipunt x3 en y3 nemen ofwel array plek 4 en 5 de rest werkt met alleen x2 en y2
	*/

	/*
	tempplaypos[2]	*(pplaypos+2)
	tempplaypos[3]	*(pplaypos+3)
	*/
	#ifdef DEBUG

	printf("rotate piece : %d \n", shape);
	#endif
	#ifdef DEBUG
			for(i=0; i<7; i+=2)
				field[*(pplaypos+i+1)][*(pplaypos+i)] = 0;	// verwijdert de oude positie van het veld


			for(i = ROWS-1; i > 0; i--)
			{
	    		for(j = 0; j < COLUMNS; j++)
					printf("%d ", field[i][j]);
			    printf("\n");
			}
			for(i = 0; i < 8; i++)
			{

					printf("%d ", *(pplaypos+i)); // toont de posities van het huidige speel stuk/blok

			}
			printf("\n");

	#endif

	if(rotation==-1) //counterclockwise
	{
		tempplaypos[0] = (*(pplaypos+1) - *(pplaypos+3))  + *(pplaypos+2); //x1 (y1-y2) + x2 = new x1
		tempplaypos[1] = (*(pplaypos+2) - *pplaypos) 	  + *(pplaypos+3); //y1 (x2-x1) + y2 = new y1

		tempplaypos[4] = (*(pplaypos+5) - *(pplaypos+3))  + *(pplaypos+2); //x3 (y3-y2) + x2 = new x3
		tempplaypos[5] = (*(pplaypos+2) - *(pplaypos+4))  + *(pplaypos+3); //y3 (x2-x3) + y2 = new y3

		tempplaypos[6] = (*(pplaypos+7) - *(pplaypos+3))  + *(pplaypos+2); //x4 (y4-y2) + x2 = new x4
		tempplaypos[7] = (*(pplaypos+2) - *(pplaypos+6))  + *(pplaypos+3); //y4 (x2-x4) + y2 = new y4
	}

	else//clockwise
	{
		tempplaypos[0] = (*(pplaypos+3) - *(pplaypos+1))  + *(pplaypos+2); //x1 (y2-y1) + x2 = new x1
		tempplaypos[1] = (*pplaypos     - *(pplaypos+2))  + *(pplaypos+3); //y1 (x1-x2) + y2 = new y1

		tempplaypos[4] = (*(pplaypos+3) - *(pplaypos+5))  + *(pplaypos+2); //x3 (y2-y3) + x2 = new x3
		tempplaypos[5] = (*(pplaypos+4) - *(pplaypos+2))  + *(pplaypos+3); //y3 (x3-x2) + y2 = new y3

		tempplaypos[6] = (*(pplaypos+3) - *(pplaypos+7))  + *(pplaypos+2); //x4 (y2-y4) + x2 = new x4
		tempplaypos[7] = (*(pplaypos+6) - *(pplaypos+2))  + *(pplaypos+3); //y4 (x4-x2) + y2 = new y4
	}
		#ifdef DEBUG

			for(i = 0; i < 8; i++)
			{

					printf("%d ", tempplaypos[i]); // toont de posities van het huidige speel stuk/blok

			}
			printf("\n");

		#endif
	for (j=0; j<7; j+=2)//checks new translated values for collision
			{
	#ifdef DEBUG

	printf("teller : %d \n", j);
	#endif
				if(j!=2)// x2 en y2 values stay the same
				{
					if(collision_check(tempplaypos[j],tempplaypos[j+1])) // checks if the new positions are available
					{
						k++;
						#ifdef DEBUG

						printf("teller : %d \n", j);
						#endif
						continue;
					}
					else
						break;
				}

			}
	#ifdef DEBUG

	printf("4 checks : %d \n", k);
	#endif
	if (k==3) //4 checks total check for each block is OK
	{
	#ifdef DEBUG

	printf("4 checks : %d \n", shape);
	#endif
		for(k=0; k<7; k+=2)
		{	if(k!=2) // x2 en y2 values stay the same
			{
				*(pplaypos+k)   = tempplaypos[k]; //place x and y values in play pos array
				*(pplaypos+k+1) = tempplaypos[k+1];
			}
		}
	}
	if((char)orientation + rotation == -1) // kan mooier gemaakt worden denkt ik
		orientation = 3;
	else if ((char)orientation + rotation == 4)
		orientation = 0;
	return orientation;
}

unsigned char collision_check(unsigned char pos_x, unsigned char pos_y) //checks for collission return 0 or 1
{
	if (pos_x >9) // checks if the piece is out of bounds horizontally
		return 0;
	else if (pos_y >21) // checks if the piece is out of bounds vertically
		return 0;
	else
		{
			if (field[pos_y][pos_x] == 0) // checks if the space in the field is free
				return 1;
			else
				return 0;
		}
}



void line_clear() // clears a line when filled with ones
{
	unsigned char i,j;
	for (j = 0; j < ROWS; ++j)// keeps track of the rows
	{
    	for( i= 0; i < COLUMNS && field[j][i] == TRUE; ++i) // checks every column
	    	if (i == COLUMNS) // if every column was true
				{
				for(i = 0; i < COLUMNS ; i++)
					field[i][j] = 0; // clears every element on a row
				move_row_down(j); //move the rows above it down
				}
	}
}

void move_row_down(unsigned char row)// deze functie kan beter want nu wordt elke regel gekopieerd als deze omlaag gehaald wordt in plaats van dynamisch te schalen van hoeveel regels erboven gekopieerd worden.
{
	unsigned char i,j;
	for (i = row; j < ROWS; i++)
	{
	  for (j = 0; j < COLUMNS; j++)
	  {
	    field[i][j] = field[i-1][j];
	  }
	}
}


unsigned char gravity(unsigned char shape, unsigned char *pplaypos) //moves playing piece down if possible
{
	unsigned char i,j=0;
	#ifdef DEBUG
			for(i=0; i<7; i+=2)
				field[*(pplaypos+i+1)][*(pplaypos+i)] = 0;	// verwijdert de oude positie van het veld
	#endif
	#ifdef DEBUG

			for(i = 0; i < 8; i++)
			{

					printf("%d ", *(pplaypos+i)); // toont de posities van het huidige speel stuk/blok

			}
			printf("\n");
			printf("gravity nummers \n");

	#endif
	for (i=0; i<7; i+=2)
		{
			if(collision_check(*(pplaypos+i),*(pplaypos+i+1)-1)) // checks if the new positions are available
			{
				j++;
				continue;
			}
			else
				break;
		}
	#ifdef DEBUG

	printf("gravity : %d \n", j);
	#endif
	#ifdef DEBUG

			for(i = 0; i < 8; i++)
			{

					printf("%d ", *(pplaypos+i)); // toont de posities van het huidige speel stuk/blok

			}
			printf("\n");

	#endif
	if (j==4) //4 checks total check for each block is OK
	{
		for( j=0; j<7; j+=2)
		{
			*(pplaypos+j+1) = *(pplaypos+j+1)-1;// moving x_pos to the left
		}
		return shape;
	}
	else
	{
		for( i=0; i<7; i+=2)
			field[*(pplaypos+i+1)][*(pplaypos+i)] = shape;	// vult de shape of kleurwaarde in bij het veld
		return shape=0;

	}

}
