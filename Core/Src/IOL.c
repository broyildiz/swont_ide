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
#include "string.h"



void IOL()
{

	HAL_Delay(1000);

	while(1)
	{


	}
}

/**
  * @brief  This function is for drawing a figure
  * @retval None
  */
int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color)
{
	int thickness = 1;
	IO_draw_line(x1, y1, x2, y2, color, thickness);
	IO_draw_line(x2, y2, x3, y3, color, thickness);
	IO_draw_line(x3, y3, x4, y4, color, thickness);
	IO_draw_line(x4, y4, x5, y5, color, thickness);
	IO_draw_line(x5, y5, x1, y1, color, thickness);
}

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

int IO_draw_rectangle(uint16_t x_lup, uint16_t y_lup, int width, int height, int color, int filled)
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
	printf("clearing screen\n");
	UB_VGA_FillScreen(color);

	IOL_error_handler("Did not recognise function number, line 34");
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

//	Error_Tx("within IO_draw_bitmap()\n");
	printf("within IO_draw_bitmap (printf)\n");
	printf("bmpnr = %d\n",bmpnr);

	switch(bmpnr)
	{
		case SMILEY_HAPPY:
			pbitmap    = smiley_happy;
			img_width  = SMILEY_WIDTH;
			img_height = SMILEY_HEIGHT;
			break;

		case SMILEY_SAD:
			pbitmap    = smiley_sad;
			img_width  = SMILEY_WIDTH;
			img_height = SMILEY_HEIGHT;
			break;

		case ARROW_UP:
			pbitmap    = arrow_up;
			img_width  = ARROW_UP_WIDTH;
			img_height = ARROW_UP_HEIGHT;
			break;

		case ARROW_RIGHT:
			pbitmap    = arrow_right;
			img_width  = ARROW_RIGHT_WIDTH;
			img_height = ARROW_RIGHT_HEIGHT;
			break;

		case ARROW_DOWN:
			pbitmap    = arrow_down;
			img_width  = ARROW_DOWN_WIDTH;
			img_height = ARROW_DOWN_HEIGHT;

			break;

		case ARROW_LEFT:
			pbitmap    = arrow_left;
			img_width  = ARROW_LEFT_WIDTH;
			img_height = ARROW_LEFT_HEIGHT;

			break;

		case MEGAMAN:
			pbitmap	   = megaman_2;
			img_width  = MEGAMAN_WIDTH;
			img_height = MEGAMAN_HEIGHT;
			break;


		default: break;
	}

	printf("bitmap parameters selected \n");

	for(y=0; y<img_height;y++)
	{

		for(x=0; x<img_width;x++)
		{
//			printf("%d, %d ", x, *(pbitmap + (y*img_width) + x) );
			UB_VGA_SetPixel(xlup + x, ylup + y, *(pbitmap + (y*img_width) + x));
		}
		printf("\n");
	}
	printf("bitmap done \n");

	return 0;
}






int IO_draw_text(uint16_t xlup, uint16_t ylup, int color, char* text, char* font, int font_size, int font_style)
{

	const uint8_t *pfont;
	const uint16_t *pdescript;
	uint8_t font_temp;
	uint8_t temp;
	uint8_t bitmask;
	uint8_t bit;
	uint16_t symbol_width, symbol_width_pixels, symbol_height;
	int x, y;
	int i = 0;
	uint16_t symbol_nr; // used for searching the descriptor
	uint16_t symbol_start;

	#ifdef DEBUG_IO
	printf("within IO_draw_text \n");
	#endif

	// niet nodig
	//Hoe lang is de string in font
	//tel spaties niet mee

	/* while font is not a case
	 *  dont compare
	 *
	 *  when a case is found check input
	 *  if c then consolas
	 *  if a then arial
	 *
	 */
	while((isalpha(*(font+i)) == False) && (i != MAX_LEN_FONTNAME)) /* determines where the first letter in the buffer is*/
	{
		i++;
	}

	if(i == MAX_LEN_FONTNAME) /* no fontname in buffer found */
	{
		return ERROR_FONTNAME;
	}
	else if((*(font+i) == LETTERA) || (*(font+i) == LETTERA - CASE_OFFSET)) /* check for arial font */
	{
		font_temp = 0;
	}
	else if((*(font+i) == LETTERC) || (*(font+i) == LETTERC - CASE_OFFSET)) /* check for consolas font */
	{
		font_temp = 1;
	}
	else
		return ERROR_FONTNAME_UNKNOWN; /* no fontname in buffer found or fontname invalid*/


		switch(font_temp)/* picks font */
		{
			case ARIAL:
				switch(font_style)
				{
					case ARIAL_NORMAL:
						if (font_size == SMALL_FONT)
						{
							pfont         = arial_8ptBitmaps;		/* font bitmap pointer */
							pdescript 	  = arial_8ptDescriptors; 	/* font descriptor pointer */
							symbol_height = ARIAL_SMALL_HEIGHT; 	/* font height in pixels */
						}
						else if(font_size == LARGE_FONT)
						{
							pfont         = arial_11ptBitmaps;	   	/* font bitmap pointer */
							pdescript 	  = arial_11ptDescriptors; 	/* font descriptor pointer */
							symbol_height = ARIAL_LARGE_HEIGHT;    	/* font height in pixels */
						}
						break;

					case ARIAL_ITALIC:
						if (font_size == SMALL_FONT)
						{
							pfont         = arial_italic_8ptBitmaps;	 /* font bitmap pointer */
							pdescript 	  = arial_italic_8ptDescriptors; /* font descriptor pointer */
							symbol_height = ARIAL_SMALL_ITALIC_HEIGHT;   /* font height in pixels */
						}
						else if(font_size == LARGE_FONT)
						{
							pfont         = arial_italic_11ptBitmaps;	  /* font bitmap pointer */
							pdescript 	  = arial_italic_11ptDescriptors; /* font descriptor pointer */
							symbol_height = ARIAL_LARGE_ITALIC_HEIGHT;    /* font height in pixels */
						}
						break;

					case ARIAL_BOLD:
						if (font_size == SMALL_FONT)
						{
							pfont         = arial_bold_8ptBitmaps;	   	/* font bitmap pointer */
							pdescript 	  = arial_bold_8ptDescriptors; 	/* font descriptor pointer */
							symbol_height = ARIAL_SMALL_BOLD_HEIGHT; 	/* font height in pixels */
						}
						else if(font_size == LARGE_FONT)
						{
							pfont         = arial_bold_11ptBitmaps;		/* font bitmap pointer */
							pdescript 	  = arial_bold_11ptDescriptors; /* font descriptor pointer */
							symbol_height = ARIAL_LARGE_BOLD_HEIGHT; 	/* font height in pixels */
						}
						break;
				}
				break;

			case CONSOLAS:
				switch(font_style) //3 options
				{
				case CONSOLAS_NORMAL:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_8ptBitmaps;		/* font bitmap pointer */
						pdescript 	  = consolas_8ptDescriptors; 	/* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_HEIGHT; 	/* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_11ptBitmaps;	   	/* font bitmap pointer */
						pdescript 	  = consolas_11ptDescriptors; 	/* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_HEIGHT;    	/* font height in pixels */
					}
					break;

				case CONSOLAS_ITALIC:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_italic_8ptBitmaps;	 /* font bitmap pointer */
						pdescript 	  = consolas_italic_8ptDescriptors; /* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_ITALIC_HEIGHT;   /* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_italic_11ptBitmaps;	  /* font bitmap pointer */
						pdescript 	  = consolas_italic_11ptDescriptors; /* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_ITALIC_HEIGHT;    /* font height in pixels */
					}
					break;

				case CONSOLAS_BOLD:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_bold_8ptBitmaps;	   	/* font bitmap pointer */
						pdescript 	  = consolas_bold_8ptDescriptors; 	/* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_BOLD_HEIGHT; 	/* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_bold_11ptBitmaps;		/* font bitmap pointer */
						pdescript 	  = consolas_bold_11ptDescriptors; /* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_BOLD_HEIGHT; 	/* font height in pixels */
					}
					break;
			}
			break;

		default: break;
		}

		printf("text parameters selected \n");

		printf("%s\n",text);
		//teller
		//hoe weet ik hoe lang het bericht is?
		//character aan het eind plaatsen
		//for loop -> while loop

		/* loops through the message to display each character */
		for(i=0;i<16;i++)
		{


			symbol_nr = (*(text+i)) - ASCII_OFFSET;/* determines which symbol from the font library should be selected */
			symbol_width_pixels = *(pdescript + symbol_nr * ARRAY_DIMENSION); /* retrieves the symbol width expressed in pixels */
			symbol_start = *(pdescript + symbol_nr * ARRAY_DIMENSION + CHAR_START_OFFSET); /* retrieves the starting elecment in the font bitmap */


			/* determines how many bytes are used in width per character */
			symbol_width =  symbol_width_pixels/BYTE_SIZE;
			if (symbol_width_pixels % BYTE_SIZE != 0) //voor het aantal bytes
				symbol_width++;

//			printf("text = %d, \n", *(text+i));
//			printf("symbol_width = %d\n",symbol_width);

//			printf("i =%d ", i);
//			printf("|| symbol_nr = %d || ",symbol_nr*2);
//			printf("symbol_start = %d\n",symbol_start);
//			printf("\n");

//			if(symbol_width==2)
//			{
//				printf("symbol_nr = %d\n",symbol_nr);
//				printf("symbol_start = %d\n",symbol_start);
//
//			}

			/*
			 *  Hier moet een if statement die zegt dat hij naar de volgende regel mag
			 */

			for(y=0; y<symbol_height;y++)//puttting symbol on screen
			{
	//
				for(x=0; x<symbol_width;x++)//puttting symbol on screen
				{
//					printf("height %d: ",y);

					temp = 	*(pfont + symbol_start + y*symbol_width + x);

//					if(symbol_width==2)
//					{
//						printf("x=%d ,y= %d ",xlup + bit + x*8 , ylup + y);
//						printf("temp = 0x%X ",temp);
//						printf("pfont = %d \t",symbol_start + y + x);
//					}

					bitmask = BITMASK ;// B1000 0000
					for(bit = 0; bit<BYTE_SIZE; bit++) //check per byte
					{

						if((temp & bitmask)!=0)
						{
	//						printf("1");
//							if(symbol_width==2)
//							{
////								printf("x=%d ,y= %d ",xlup + bit + x*8 , ylup + y);
//								printf("1");
//							}
	//						printf("x=%d ,y= %d ",xlup+bit,ylup+y);




							UB_VGA_SetPixel(xlup + bit + x*BYTE_SIZE , ylup + y, 255);




						}
						else
						{
	//						printf("0");
//							if(symbol_width==2)
//							{
//								printf("0");
//							}
						}

						bitmask = bitmask >> 1; //define ipv 1 ??
					}
//					if(symbol_width==2)
//					{
//						printf("\t");
//					}
				}
//				if(symbol_width==2)
//				{
//					printf("\n");
//				}
//				printf("\n");
			}
//			printf("new character\n");
			xlup = xlup + symbol_width_pixels + 1;// 1 pixel offset for spacing between symbols
			//check voor out of bounds
		}

//		for(i=0;i<190;i++)
//		{
//			printf("i = %d, pdescript = %d\n",i ,*(pdescript + i));
//		}


		printf("finished text \n");
		return 0;
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

<<<<<<< HEAD
void IOL_error_handler(char *pErrorString)
{
	while(1);
}

//for(x=0; x<symbol_width;x++)
//				{
//					temp = 	*(pfont + symbol_start + y*symbol_width);
//
//					bitmask = 0x80;// B1000 0000
//					for(bit = 0; bit<8; bit++)
//					{
//
//						if((temp & bitmask)!=0)
//						{
////							printf("1");
//							UB_VGA_SetPixel(xlup + x, ylup + y, color);
//
//						}
//						else
//						{
////							printf("0");
//						}
//
//						bitmask = bitmask >> 1;
//					}
//				}







//	for(y=0; y<symbol_height;y++)
//		{
////			printf("height %d: ",y);
//			for(x=0; x<symbol_width;x++)
//			{
//
//
//				temp = *(pbitmap + (3*y) + x);
//
//				bitmask = 0x80;// B1000 0000
//				for(bit = 0; bit<8; bit++)
//				{
//
//					if((temp & bitmask)!=0)
//					{
//	//				    printf("%d ", 0);
//
//					}
//					else
//					{
//						UB_VGA_SetPixel(xlup + bit + (x*8), ylup+y,color);
//	//					printf("x = %d, y = %d ",xlup + bit + (x*8),ylup+y);
//	//					printf("%d ", 1);
//					}
//
//					bitmask = bitmask >> 1;
//				}
//
//			}
//			printf("\n");
//		}
//		printf("x = %d, y =%d\n",x,y);




//for(y=0; y<img_height;y++)
//		{
//			printf("height %d: ",y);
//			for(x=0; x<img_width;x++)
//			{
//				temp = *(pbitmap + (3*y) + x);//dit kan beter voor tekst gebruikt worden
//
//				bitmask = 0x80;// B1000 0000
//				for(bit = 0; bit<8; bit++)
//				{
//
//					if((temp & bitmask)!=0)
//					{
//	//				    printf("%d ", 0);
//
//					}
//					else
//					{
//						UB_VGA_SetPixel(xlup + bit + (x*8), ylup+y,color);
//	//					printf("x = %d, y = %d ",xlup + bit + (x*8),ylup+y);
//	//					printf("%d ", 1);
//					}
//
//					bitmask = bitmask >> 1;
//				}
//
//			}
//			printf("\n");
//		}
//		printf("x = %d, y =%d\n",x,y);


















