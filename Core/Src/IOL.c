/*
 * IOL.c
 *
 *  Created on: 26 apr. 2020
 *      Author: kelly
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

//void IO_bitmap(int nr, int x, int y)
//{
//
//	switch (nr)
//	​{
//	    case 0:
//	      // statements
//	      break;
//
//	    case 1:
//	      // statements
//	      break;
//
//	    default:
//	      // default statements
//	}
//}

int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color)
{
	  int a,b,c,d;
	  int array_ox[4] = {x1,x2,x3,x4,x5};
	  int array_oy[4] = {y1,y2,y3,y4,y5};
	  int array_nx[3] = {x2,x3,x4,x5};
	  int array_ny[3] = {y2,y3,y4,y5};
	  int dx,dy,sdx,sdy,px,py,dxabs,dyabs,i,j;
	  float slope;
	  for(a = 0; a<4; a++)
	  {
		  for(b = 0; b<4; b++)
		  {
			  for(c = 0; c<3; c++)
			  {
				  for(d = 0; d<3; d++)
				  {

	  dx=array_nx[c]-array_ox[a];      /* the horizontal distance of the line */
	  dy=array_ny[d]-array_oy[b];      /* the vertical distance of the line */
	  dxabs=abs(dx);
	  dyabs=abs(dy);
	  sdx=sgn(dx);
	  sdy=sgn(dy);
	  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
	  {
	    slope=(float)dy / (float)dx;

	    for(i=0;i!=dx;i+=sdx)
	    {
	    	px=i+array_ox[a];
	    	py=slope*i+array_oy[b];
	    	for(j = px; j<px; j++)
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
			  px=slope*i+array_ox[a];
			  py=i+array_oy[b];
			  for(j = py; j<py; j++)
			  {
				  UB_VGA_SetPixel(px,j,color);
			  }
	      UB_VGA_SetPixel(px,py,color);
	    }
	  }
}
			  }
		  }
	  }
}

int IO_draw_line(int x1, int y1, int x2, int y2, byte color, int thickness)
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
//	  FL_DEBUG_FUNC("gekke string");

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

int IO_draw_rectangle(int x_lup, int y_lup, int width, int height, int color, int filled)
{
	int i;
	int j;

	if(filled == 1)
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

int IO_clearscreen(int color)
{
	UB_VGA_FillScreen(color);
}

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

// Function for circle-generation
// using Bresenham's algorithm
int IO_draw_circle(int xc, int yc, int radius, byte color)
{
	//Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
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
//        delay(50);
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
	return 0;
}

int IO_repeat_commands(int aantal, int hoevaak)
{
	for(int i = 0; i < hoevaak; i++)
	{
		for(int k = (rb_vars.read_counter - aantal); k < rb_vars.read_counter; k++)
		{
			FL_uart_decode(rb[k].line_rx_buffer, rb[k].msglen);
			printf("k:\t%d\n", k);
		}

	}

	return 0;
}

