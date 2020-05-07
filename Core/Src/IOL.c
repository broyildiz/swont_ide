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
  * @brief  Function for drawing a figure
  * @param  x1...x5, x-coordinate of the line
  * @param	y1...y5, y-coordinate of the line
  * @param 	color is the color of the figure
  * @retval None
  */
int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color)
{
	int thickness = 1;
	int error = NO_ERROR;
    //Drawing all lines seperate
	error = IO_draw_line(x1, y1, x2, y2, color, thickness);
	error = IO_draw_line(x2, y2, x3, y3, color, thickness);
	error = IO_draw_line(x3, y3, x4, y4, color, thickness);
	error = IO_draw_line(x4, y4, x5, y5, color, thickness);
	error = IO_draw_line(x5, y5, x1, y1, color, thickness);

	if(error)
	{
		Error_Tx("Draw Figure Function: wrong argument passed to the Line function");
		return error;
	}
	return error;
}

/**
  * @brief  Function for drawing a line
  * @param  x1 & x2, x-coordinate of the line
  * @param	y1 & y2, y-coordinate of the line
  * @param 	color is the color of the figure
  * @param  thickness is the thickness of the line
  * @retval None
  */
int IO_draw_line(int x1, int y1, int x2, int y2, byte color, int thickness)
{
	/*
	* Bron: 	 	http://www.brackeen.com/vga/source/djgpp20/lines.c.html
	* Hoofdbron: 	http://www.brackeen.com/vga/shapes.html
	* Hoofdbron2:	https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
	*/
	  int dx,dy,sdx,sdy,px,py,dxabs,dyabs,i,j;
	  float slope;
	  int error = NO_ERROR;

	  if((x1 < 0) || x1 > VGA_DISPLAY_X) error = IOL_LINE_INVALID_ARG_VALUE;
	  if((y1 < 0) || y1 > VGA_DISPLAY_Y) error = IOL_LINE_INVALID_ARG_VALUE;
	  if((x2 < 0) || x2 > VGA_DISPLAY_X) error = IOL_LINE_INVALID_ARG_VALUE;
	  if((y2 < 0) || y2 > VGA_DISPLAY_Y) error = IOL_LINE_INVALID_ARG_VALUE;
	  if(thickness < 0) error = IOL_LINE_INVALID_ARG_VALUE;
	  if(error) {
		  Error_Tx("Line function: Invalid argument(s)");
		  return error;
	  }

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
	  return error;
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
	int error = NO_ERROR;
	if((x_lup < 0) || x_lup > VGA_DISPLAY_X) error = IOL_LINE_INVALID_ARG_VALUE;
	if((y_lup < 0) || y_lup > VGA_DISPLAY_Y) error = IOL_LINE_INVALID_ARG_VALUE;

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
	return error;
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
  * @brief  Clearing the whole screen
  * @param 	Color is the color of the screen
  * @retval None
  */
int IO_clearscreen(int color)
{
	printf("clearing screen\n");
	UB_VGA_FillScreen(color);

//	IOL_error_handler("Did not recognise function number, line 34");
	return 0;
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

	return NO_ERROR;
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
	int error = NO_ERROR;
		//Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
	    int x = 0, y = radius;
	    int d = 3 - 2 * radius;
	    error = drawCircle(xc, yc, x, y, color);
	    if(error) {
	    	Error_Tx("Draw Circle function: Unexpected error");
			return error;
	    }
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
	        error = drawCircle(xc, yc, x, y, color);

	    if(error) {
	    	Error_Tx("Draw Circle function: Unexpected error");
			return error;
	    }

	    return error;
}





int IO_draw_bitmap(int xlup, int ylup, int bmpnr)
{
//  bron: http://www.brackeen.com/vga/bitmaps.html
	const uint8_t *pbitmap;
//	uint8_t temp;
//	uint8_t bitmask;
//	uint8_t bit;
//	int color;
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

	const uint8_t  *pfont;
	const uint16_t *pdescript;
	uint8_t font_temp;
	uint8_t temp;
	uint8_t bitmask;
	uint8_t bit;
	uint16_t symbol_width = 0, symbol_width_pixels, symbol_height;
	int x, y;
	int i = 0;
	uint16_t symbol_nr; // used for searching the descriptor
	uint16_t symbol_start;


	printf("help in IO_draw_text: regel 294\n");

	#ifdef DEBUG_IO
	printf("within IO_draw_text \n");
	#endif

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

	printf("font_temp= %d\n", font_temp);
	printf("font_stye= %d\n", font_style);
	printf("font_size= %d\n", font_size);

	switch(font_temp)/* picks font */
	{
		case ARIAL:
			switch(font_style)
			{
				case ARIAL_NORMAL:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_8ptBitmaps;		/* font bitmap pointer */
						pdescript 	  = arial_8ptDescriptors[0]; 	/* font descriptor pointer */
						symbol_height = ARIAL_SMALL_HEIGHT; 	/* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_11ptBitmaps;	   	/* font bitmap pointer */
						pdescript 	  = arial_11ptDescriptors[0]; 	/* font descriptor pointer */
						symbol_height = ARIAL_LARGE_HEIGHT;    	/* font height in pixels */
					}
					break;

				case ARIAL_ITALIC:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_italic_8ptBitmaps;	 /* font bitmap pointer */
						pdescript 	  = arial_italic_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_SMALL_ITALIC_HEIGHT;   /* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_italic_11ptBitmaps;	  /* font bitmap pointer */
						pdescript 	  = arial_italic_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_LARGE_ITALIC_HEIGHT;    /* font height in pixels */
					}
					break;

				case ARIAL_BOLD:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_bold_8ptBitmaps;	   	/* font bitmap pointer */
						pdescript 	  = arial_bold_8ptDescriptors[0]; 	/* font descriptor pointer */
						symbol_height = ARIAL_SMALL_BOLD_HEIGHT; 	/* font height in pixels */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_bold_11ptBitmaps;		/* font bitmap pointer */
						pdescript 	  = arial_bold_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_LARGE_BOLD_HEIGHT; 	/* font height in pixels */
					}
					break;
				default:
				//	return error /* define maken */
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
					pdescript 	  = consolas_8ptDescriptors[0]; 	/* font descriptor pointer */
					symbol_height = CONSOLAS_SMALL_HEIGHT; 	/* font height in pixels */
				}
				else if(font_size == LARGE_FONT)
				{
					pfont         = consolas_11ptBitmaps;	   	/* font bitmap pointer */
					pdescript 	  = consolas_11ptDescriptors[0]; 	/* font descriptor pointer */
					symbol_height = CONSOLAS_LARGE_HEIGHT;    	/* font height in pixels */
				}
				break;

			case CONSOLAS_ITALIC:
				if (font_size == SMALL_FONT)
				{
					pfont         = consolas_italic_8ptBitmaps;	 /* font bitmap pointer */
					pdescript 	  = consolas_italic_8ptDescriptors[0]; /* font descriptor pointer */
					symbol_height = CONSOLAS_SMALL_ITALIC_HEIGHT;   /* font height in pixels */
				}
				else if(font_size == LARGE_FONT)
				{
					pfont         = consolas_italic_11ptBitmaps;	  /* font bitmap pointer */
					pdescript 	  = consolas_italic_11ptDescriptors[0]; /* font descriptor pointer */
					symbol_height = CONSOLAS_LARGE_ITALIC_HEIGHT;    /* font height in pixels */
				}
				break;

			case CONSOLAS_BOLD:
				if (font_size == SMALL_FONT)
				{
					pfont         = consolas_bold_8ptBitmaps;	   	/* font bitmap pointer */
					pdescript 	  = consolas_bold_8ptDescriptors[0]; 	/* font descriptor pointer */
					symbol_height = CONSOLAS_SMALL_BOLD_HEIGHT; 	/* font height in pixels */
				}
				else if(font_size == LARGE_FONT)
				{
					pfont         = consolas_bold_11ptBitmaps;		/* font bitmap pointer */
					pdescript 	  = consolas_bold_11ptDescriptors[0]; /* font descriptor pointer */
					symbol_height = CONSOLAS_LARGE_BOLD_HEIGHT; 	/* font height in pixels */
				}
				break;
		}
		break;

	default: break;
	}

	printf("text parameters selected \n");

	for(i=0;i<strlen(text);i++)/* loop to print each charcter from the text buffer */
	{
		symbol_nr = (*(text+i)) - ASCII_OFFSET;/* determines which symbol from the font library should be selected */
		symbol_width_pixels = *(pdescript + symbol_nr * ARRAY_DIMENSION); /* retrieves the symbol width expressed in pixels */
		symbol_start = *(pdescript + symbol_nr * ARRAY_DIMENSION + CHAR_START_OFFSET); /* retrieves the starting elecment in the font bitmap */

		/* determines how many bytes are used in width per character */
		symbol_width =  symbol_width_pixels/BYTE_SIZE;
		if (symbol_width_pixels % BYTE_SIZE != 0) //voor het aantal bytes
			symbol_width++;

		/*
		 *  Hier moet een if statement die zegt dat hij naar de volgende regel mag
		 */

		for(y=0; y<symbol_height;y++)//puttting symbol on screen
		{
			for(x=0; x<symbol_width;x++)//puttting symbol on screen
			{

				temp = 	*(pfont + symbol_start + y*symbol_width + x); /* retrieves byte from character bitmap */

				bitmask = BITMASK ;// B1000 0000
				for(bit = 0; bit<BYTE_SIZE; bit++) //check per byte
				{
					if((temp & bitmask)!=0)
					{
						UB_VGA_SetPixel(xlup + bit + x*BYTE_SIZE , ylup + y, color); /* sets pixel*/
					}
					bitmask = bitmask >> 1; //define ipv 1 ??
				}
			}
		}

		xlup = xlup + symbol_width_pixels + 1;// 1 pixel offset for spacing between symbols
		//check voor out of bounds
	}

	printf("finished text \n");
	return 0;
}




















