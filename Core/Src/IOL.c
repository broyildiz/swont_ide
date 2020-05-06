/*
 * IOL.c
 *
 *  Created on: 26 apr. 2020
 *      Author: kelly
 */
/**
  ******************************************************************************
  * @file           : IOL.c
  * @brief          : I/O Layer
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Private includes ----------------------------------------------------
 */
#include "IOL.h"

const unsigned char megaman[] = {
    0B11111111, 0B11000111, 0B11111111, // ##########...###########
    0B11111111, 0B00000011, 0B11111111, // ########......##########
	0B11111110, 0B00001001, 0B11111111, // #######.....#..#########
	0B11111100, 0B00000000, 0B11111111, // ######..........########
	0B11111100, 0B00000000, 0B01111111, // ######...........#######
	0B11111000, 0B00000000, 0B01111111, // #####............#######
	0B11111000, 0B01111001, 0B01111111, // #####....####..#.#######
	0B11111000, 0B11100101, 0B01111111, // #####...###..#.#.#######
	0B11111100, 0B11100101, 0B01111111, // ######..###..#.#.#######
	0B11111000, 0B11111111, 0B01111111, // #####...########.#######
	0B11100010, 0B01000010, 0B00111111, // ###...#..#....#...######
	0B11001111, 0B01111101, 0B10011111, // ##..####.#####.##..#####
	0B11000101, 0B10000001, 0B00011111, // ##...#.##......#...#####
	0B10000000, 0B11111000, 0B00001111, // #.......#####.......####
	0B10000000, 0B11111100, 0B00001111, // #.......######......####
	0B10000000, 0B11111000, 0B00001111, // #.......#####.......####
	0B10000000, 0B00000000, 0B00001111, // #...................####
	0B11000100, 0B00000001, 0B00011111, // ##...#.........#...#####
	0B11111001, 0B00001100, 0B11111111, // #####..#....##..########
	0B11110001, 0B10001110, 0B01111111, // ####...##...###..#######
	0B11100000, 0B00100000, 0B00111111, // ###.......#.......######
	0B10000000, 0B01110000, 0B00001111, // #........###........####
	0B00000000, 0B01110000, 0B00000111, // .........###.........###
	0B00000000, 0B01110000, 0B00000111  // .........###.........###
};

void IOL()
{

	HAL_Delay(1000);

	while(1)
	{


	}
}

/**
  * @brief  Function for drawing a figure
  * @param  x1...x5, x-coordinate of the line
  * @param	y1...y5, y-coordinate of the line
  * @param 	color is the color of the figure
  * @retval None
  */
int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color)
{
	int thickness = 1;
	//Drawing all lines seperate
	IO_draw_line(x1, y1, x2, y2, color, thickness);
	IO_draw_line(x2, y2, x3, y3, color, thickness);
	IO_draw_line(x3, y3, x4, y4, color, thickness);
	IO_draw_line(x4, y4, x5, y5, color, thickness);
	IO_draw_line(x5, y5, x1, y1, color, thickness);
}

/**
  * @brief  Function for drawing a line
  * @param  x1 & x2, x-coordinate of the line
  * @param	y1 & y2, y-coordinate of the line
  * @param 	color is the color of the figure
  * @param  thickness is the thickness of the line
  * @retval None
  */
int IO_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, byte color, int thickness)
{
	/*
	* Bron: 	 	http://www.brackeen.com/vga/source/djgpp20/lines.c.html
	* Hoofdbron: 	http://www.brackeen.com/vga/shapes.html
	* Hoofdbron2:	https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
	*/
	  int dx,dy,sdx,sdy,px,py,dxabs,dyabs,i,j;
	  float slope;

	  dx=x2-x1;      /* the horizontal distance of the line */
	  dy=y2-y1;      /* the vertical distance of the line */
	  dxabs=abs(dx);
	  dyabs=abs(dy);
	  sdx=sgn(dx);
	  sdy=sgn(dy);

	  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
	  {
	    slope=(float)dy / (float)dx;

	    for(i=0;i!=dx;i+=sdx)
	    {
	    	px=i+x1;
	    	py=slope*i+y1;
	    	for(j = px; j<px+thickness; j++)
	    	{
	    		UB_VGA_SetPixel(j,py,color);
	    	}
	      UB_VGA_SetPixel(px,py,color);
	    }
	  }
	  else /* the line is more vertical than horizontal */
	  {
	    slope=(float)dx / (float)dy;
	    for(i=0;i!=dy;i+=sdy)
			{
			  px=slope*i+x1;
			  py=i+y1;
			  for(j = py; j<py+thickness; j++)
			  {
				  UB_VGA_SetPixel(px,j,color);
			  }
	      UB_VGA_SetPixel(px,py,color);
	    }
	  }
}

/**
  * @brief  Function for drawing a Mondriaan painting
  * @param  None
  * @retval None
  */
int IO_draw_mondriaan()
{
	int filled = 1;

		UB_VGA_FillScreen(VGA_COL_BLACK); //filling the background black
		//Drawing all the rectangles seperate
		IO_draw_rectangle(0,0,50,80,VGA_COL_WHITE,filled);
		IO_draw_rectangle(55,0,60,80,VGA_COL_YELLOW,filled);
		IO_draw_rectangle(120,0,80,80,VGA_COL_BLUE,filled);
		IO_draw_rectangle(205,0,100,80,VGA_COL_RED,filled);
		IO_draw_rectangle(310,0,10,80,VGA_COL_YELLOW,filled);
		IO_draw_rectangle(0,85,50,80,VGA_COL_WHITE,filled);
		IO_draw_rectangle(55,85,60,80,VGA_COL_WHITE,filled);
		IO_draw_rectangle(120,85,80,80,VGA_COL_WHITE,filled);
		IO_draw_rectangle(205,85,30,80,VGA_COL_WHITE,filled);
		IO_draw_rectangle(240,85,65,80,VGA_COL_BLUE,filled);
		IO_draw_rectangle(310,85,10,80,VGA_COL_RED,filled);
		IO_draw_rectangle(0,170,50,70,VGA_COL_WHITE,filled);
		IO_draw_rectangle(55,170,60,30,VGA_COL_WHITE,filled);
		IO_draw_rectangle(55,205,60,35,VGA_COL_BLUE,filled);
		IO_draw_rectangle(120,170,115,30,VGA_COL_RED,filled);
		IO_draw_rectangle(120,205,115,35,VGA_COL_YELLOW,filled);
		IO_draw_rectangle(240,170,65,30,VGA_COL_WHITE,filled);
		IO_draw_rectangle(240,205,80,35,VGA_COL_WHITE,filled);
		IO_draw_rectangle(310,170,10,30,VGA_COL_YELLOW,filled);
}

/**
  * @brief  Function for drawing a rectangle
  * @param  x_lup x-coordinate of the line
  * @param	y_lup y-coordinate of the line
  * @param  Width of the rectangle
  * @param  Height of the rectangle
  * @param 	color is the color of the figure
  * @param  Filled indicates whether the rectangle is filled
  * @retval None
  */
int IO_draw_rectangle(uint16_t x_lup, uint16_t y_lup, int width, int height, int color, int filled)
{
	int i;
	int j;

	if(filled == 1) //Checks whether the rectangle should be filled
	{
		for(i = y_lup; i<y_lup+height; i++)
		{
			for(j = x_lup; j<x_lup+width; j++)
			{
				UB_VGA_SetPixel(j,i,color);
			}
		}
	}

	if(filled == 0)
	{

		for(i = y_lup; i<y_lup+height+1; i++)
		{
			if(i == y_lup || i == y_lup +height)
			{
				for(j = x_lup; j<x_lup+width; j++)
				{
					UB_VGA_SetPixel(j,i,color);
				}
			}
			else
			{
				UB_VGA_SetPixel(j,i,color);
				UB_VGA_SetPixel(j-width,i,color);
			}
		}
	}
}

/**
  * @brief  Clearing the whole screen
  * @param 	Color is the color of the screen
  * @retval None
  */
int IO_clearscreen(int color)
{
	UB_VGA_FillScreen(color);
}

/**
  * @brief  Function for drawing a circle
  * @param  xc is the middle x-coordinate of the circle
  * @param	yc is the middle y-coordinate of the circle
  * @param  x
  * @param  y
  * @param 	color is the color of the circle
  * @retval None
  */
int drawCircle(int xc, int yc, int x, int y, byte color)
{
	//Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
	UB_VGA_SetPixel(xc+x, yc+y, color);
	UB_VGA_SetPixel(xc-x, yc+y, color);
	UB_VGA_SetPixel(xc+x, yc-y, color);
	UB_VGA_SetPixel(xc-x, yc-y, color);
	UB_VGA_SetPixel(xc+y, yc+x, color);
	UB_VGA_SetPixel(xc-y, yc+x, color);
	UB_VGA_SetPixel(xc+y, yc-x, color);
	UB_VGA_SetPixel(xc-y, yc-x, color);
}

/**
  * @brief  Function for drawing a circle
  * 		Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
  * @param  xc is the middle x-coordinate of the circle
  * @param	yc is the middle y-coordinate of the circle
  * @param 	color is the color of the figure
  * @param  Filled indicates whether the rectangle is filled
  * @retval None
  */
int IO_draw_circle(int xc, int yc, int radius, byte color)
{

    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    drawCircle(xc, yc, x, y, color);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y, color);
    }
}


int IO_draw_bitmap(int xlup, int ylup, int bmpnr)
{
	//bron: http://www.brackeen.com/vga/bitmaps.html
	const uint8_t *pbitmap;
	uint8_t temp;
	uint8_t bitmask;
	uint8_t bit;
	int color;
	int img_width, img_height;
	int x, y;

	switch(bmpnr)
	{
		case SAD_SMILEY:

			break;

		case HAPPY_SMILEY:

			break;

		case ARROW_UP:

			break;

		case ARROW_RIGHT:

			break;

		case ARROW_DOWN:

			break;

		case ARROW_LEFT:

			break;

		case MEGAMAN:
			pbitmap = megaman;
			color = 60;//define?
			img_width = 3; // define
			img_height = MEGAMAN_HEIGHT;
			break;


		default: break;
	}

	for(y=0; y<img_height;y++)
	  for(x=0; x<img_width;x++)
	  {
		 temp = *(pbitmap + (3*y) + x);// dit is een test

		 bitmask = 128;// B1000 0000
		 for(bit = 0; bit<8; bit++)
		 {
			if((temp & bitmask)!=0)
			{
			  UB_VGA_SetPixel(xlup + bit + (x*8), ylup,color);
			}
			bitmask = bitmask >> 1;
		 }

	  }

}

