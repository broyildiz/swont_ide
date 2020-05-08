/**
  ******************************************************************************
  * @file           : IO.c
  * @brief          : This file contains the IO layer code
  * @author			: Groep 8
  * @date			: 08-05-2020
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "IOL.h"
#include "string.h"


/********************************************************************************************************
  * @brief  Function for drawing a figure
  *
  * @param  x1    : 1st x-coordinate of the figure
  * @param	y1    : 1st y-coordinate of the figure
  * @param  x2    : 2nd x-coordinate of the figure
  * @param	y2    : 2nd y-coordinate of the figure
  * @param  x3    : 3rd x-coordinate of the figure
  * @param	y3    : 3rd y-coordinate of the figure
  * @param  x4    : 4th x-coordinate of the figure
  * @param	y4    : 4th y-coordinate of the figure
  * @param  x5    : 5th x-coordinate of the figure
  * @param	y5    : 5th y-coordinate of the figure
  * @param 	color : is the color of the figure
  * @retval error : Error codes
  *******************************************************************************************************/
int IO_draw_figure(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t x4,uint16_t y4,uint16_t x5,uint16_t y5, byte color)
{
	int thickness = 1;
	int error = NO_ERROR;
    /* Drawing all lines seperate */
	error = IO_draw_line(x1, y1, x2, y2, color, thickness);
	error = IO_draw_line(x2, y2, x3, y3, color, thickness);
	error = IO_draw_line(x3, y3, x4, y4, color, thickness);
	error = IO_draw_line(x4, y4, x5, y5, color, thickness);
	error = IO_draw_line(x5, y5, x1, y1, color, thickness);

	if(error)
	{
		FL_error_tx("Draw Figure Function: wrong argument passed to the Line function");
		return error;
	}
	return error;
}

/********************************************************************************************************
  * @brief  Function for drawing a line
  *
  * @param  x1        : 1st x-coordinate of the figure
  * @param	y1        : 1st y-coordinate of the figure
  * @param  x2        : 2nd x-coordinate of the figure
  * @param	y2        : 2nd y-coordinate of the figure
  * @param 	color 	  : is the color of the figure
  * @param  thickness : is the thickness of the line
  * @retval error 	  : error codes
  *******************************************************************************************************/
int IO_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, byte color, int thickness)
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
		  FL_error_tx("Line function: Invalid argument(s)");
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

/********************************************************************************************************
  * @brief  Function for drawing a rectangle
  *
  * @param  x_lup  : x-coordinate of the line
  * @param	y_lup  : y-coordinate of the line
  * @param  width  : Width of the rectangle
  * @param  height : Height of the rectangle
  * @param 	color  : is the color of the figure
  * @param  filled : Filled indicates whether the rectangle is filled
  * @retval error  : error codes
  *******************************************************************************************************/
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


/********************************************************************************************************
  * @brief  Function for drawing a Mondriaan painting
  *
  * @param  None
  * @retval error : error codes
  *******************************************************************************************************/
int IO_draw_mondriaan()
{
	int filled = 1;

		UB_VGA_FillScreen(VGA_COL_BLACK); /* make background black */
		/* Drawing all the rectangles separately */
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
		return 0;
}



/********************************************************************************************************
  * @brief  Clearing the whole screen
  * @param 	color : Color is the color of the screen
  * @retval error : error codes
  *******************************************************************************************************/
int IO_clearscreen(int color)
{
	//color too large check?
	FL_debug_tx("clearing screen\n");
	UB_VGA_FillScreen(color);

	return 0;
}

/********************************************************************************************************
  * @brief  Function for drawing a circle
  *
  * @param  xc    : is the middle x-coordinate of the circle
  * @param	yc    : is the middle y-coordinate of the circle
  * @param  x 	  : starting pixel x-coordinate on screen
  * @param  y 	  : starting pixel y-coordinate on screen
  * @param 	color : is the color of the circle
  * @retval error : error codes
  *******************************************************************************************************/
int drawCircle(int xc, int yc, int x, int y, byte color)
{
	/* Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */
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

/********************************************************************************************************
  * @brief  Function for drawing a circle
  * 		Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
  *
  * @param  xc     : is the middle x-coordinate of the circle
  * @param	yc     : is the middle y-coordinate of the circle
  * @param 	color  : is the color of the figure
  * @param  filled : indicates whether the rectangle is filled
  * @retval error  : error codess
  *******************************************************************************************************/
int IO_draw_circle(int xc, int yc, int radius, byte color)
{
		int error = NO_ERROR;
		/* Source: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */
	    int x = 0, y = radius;
	    int d = 3 - 2 * radius;
	    error = drawCircle(xc, yc, x, y, color);
	    if(error) {
	    	FL_error_tx("Draw Circle function: Unexpected error");
			return error;
	    }
	    while (y >= x)
	    {
	        /* for each pixel we will */
	        /* draw all eight pixels  */

	        x++;
            
	        /* check for decision parameter */
	        /* and correspondingly			*/
	        /* update d, x, y				*/
	        if (d > 0)
	        {
	            y--;
	            d = d + 4 * (x - y) + 10;
	        }
	        else
	            d = d + 4 * x + 6;
	        error = drawCircle(xc, yc, x, y, color);
	    }
	    if(error)
	    {
	    	FL_error_tx("Draw Circle function: Unexpected error");
			return error;
	    }

	    return error;
}


/********************************************************************************************************
  * @brief  Draws one of the stored bitmaps.
  * 		Starts drawing in the top left corner.
  *
  * @param  xlup  : Is the starting x-coordinate on screen
  * @param  ylup  : Is the starting x-coordinate on screen
  * @param  bmpnr : Determines which of the stored bitmaps is retrieved
  * @retval error : Error codes
  *******************************************************************************************************/
int IO_draw_bitmap(int xlup, int ylup, int bmpnr)
{
	/* bron: http://www.brackeen.com/vga/bitmaps.html */
	const uint8_t *pbitmap;
	int img_width, img_height;
	int error = 0;
	int x, y;

	if((xlup < 0) || xlup > VGA_DISPLAY_X) error = IOL_LINE_INVALID_ARG_VALUE;
	if((ylup < 0) || ylup > VGA_DISPLAY_Y) error = IOL_LINE_INVALID_ARG_VALUE;

	FL_debug_tx("within IO_draw_bitmap\n");
	FL_debug_int(bmpnr);

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


		default:
			return IOL_BITMAP_NON_EXISTENT;
			break;
	}

	FL_debug_tx("bitmap parameters selected \n");

	/* prints the bitmap starting from the top left pixel */
	for(y=0; y<img_height;y++)
	{
		for(x=0; x<img_width;x++)
		{
			/* sets specific pixel with retrieved value from bitmap */
			UB_VGA_SetPixel(xlup + x, ylup + y, *(pbitmap + (y*img_width) + x));
		}
	}
	FL_debug_tx("bitmap done \n");

	return error;
}

/********************************************************************************************************
  * @brief  Draws text on screen.
  *
  * @param  xlup 	   : Is the starting x-coordinate on screen
  * @param  ylup 	   : Is the starting x-coordinate on screen
  * @param  color 	   : Determines the color of the text
  * @param  *text 	   : Pointer to buffer with the to be printed text
  * @param  *font 	   : Determines the color of the text
  * @param  font_size  : Determines text size
  * @param  font_style : Determines the style: Normal, Italic or Bold
  * @retval Error 	   : Various error codes
  *******************************************************************************************************/
int IO_draw_text(uint16_t xlup, uint16_t ylup, int color, char* text, char* font, int font_size, int font_style)
{

	const uint8_t  *pfont;        /* pointer to font bitmap 		  	  */
	const uint16_t *pdescript;    /* pointer to index for font bitmap     */
	uint8_t font_compare_val;     /* used to store the font compare value */
	uint8_t temp;
	uint8_t bitmask;		      /* used to store a bitmask 			*/
	uint8_t bit;			      /* used as counter through a byte 	*/
	uint16_t symbol_width = 0;    /* symbol width in bytes 				*/
	uint16_t symbol_width_pixels; /* symbol width in pixels 			*/
	uint16_t symbol_height;		  /* symbol height in pixels 			*/
	uint16_t symbol_nr; 		  /* used for searching the descriptor 	*/
	uint16_t symbol_start;		  /* index nr in character bitmap 		*/
	int x, y;
	int i = 0;
	int error = 0;

	if((xlup < 0) || xlup > VGA_DISPLAY_X) error = IOL_LINE_INVALID_ARG_VALUE;
	if((ylup < 0) || ylup > VGA_DISPLAY_Y) error = IOL_LINE_INVALID_ARG_VALUE;

	FL_debug_tx("Enterred the IO_draw_text\n");

	while((isalpha(*(font+i)) == FALSE) && (i != MAX_LEN_FONTNAME)) /* determines where the first letter in the buffer is*/
	{
		i++;
	}

	if(i == MAX_LEN_FONTNAME) /* no fontname in buffer found */
	{
		return IOL_ERROR_FONTNAME;
	}
	else if((*(font+i) == LETTERA) || (*(font+i) == LETTERA - CASE_OFFSET)) /* check for arial font */
	{
		font_compare_val = ARIAL;
	}
	else if((*(font+i) == LETTERC) || (*(font+i) == LETTERC - CASE_OFFSET)) /* check for consolas font */
	{
		font_compare_val = CONSOLAS;
	}
	else
		return IOL_ERROR_FONTNAME_UNKNOWN; /* no fontname in buffer found or fontname invalid*/

	FL_debug_tx("font_compare_val:\n");
	FL_debug_int(font_compare_val);
	FL_debug_tx("font style\n");
	FL_debug_int(font_style);
	FL_debug_tx("font_size:\n");
	FL_debug_int(font_size);


	switch(font_compare_val) /* picks font */
	{
		case ARIAL:
			switch(font_style)
			{
				case ARIAL_NORMAL:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_8ptBitmaps;		 /* font bitmap pointer     */
						pdescript 	  = arial_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_SMALL_HEIGHT; 	 /* font height in pixels   */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_11ptBitmaps;	   	  /* font bitmap pointer     */
						pdescript 	  = arial_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_LARGE_HEIGHT;		  /* font height in pixels   */
					}
					break;

				case ARIAL_ITALIC:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_italic_8ptBitmaps;	 	/* font bitmap pointer 	   */
						pdescript 	  = arial_italic_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_SMALL_ITALIC_HEIGHT;   	/* font height in pixels   */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_italic_11ptBitmaps;	  	 /* font bitmap pointer 	*/
						pdescript 	  = arial_italic_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_LARGE_ITALIC_HEIGHT;    	 /* font height in pixels 	*/
					}
					break;

				case ARIAL_BOLD:
					if (font_size == SMALL_FONT)
					{
						pfont         = arial_bold_8ptBitmaps;	   	  /* font bitmap pointer 	 */
						pdescript 	  = arial_bold_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_SMALL_BOLD_HEIGHT; 	  /* font height in pixels   */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = arial_bold_11ptBitmaps;		   /* font bitmap pointer     */
						pdescript 	  = arial_bold_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = ARIAL_LARGE_BOLD_HEIGHT; 	   /* font height in pixels   */
					}
					break;
				default:
					return IOL_ARIAL_FONT_ERROR;
					break;
			}
			break;

		case CONSOLAS:
			switch(font_style)
			{
				case CONSOLAS_NORMAL:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_8ptBitmaps;		/* font bitmap pointer	   */
						pdescript 	  = consolas_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_HEIGHT; 		/* font height in pixels   */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_11ptBitmaps;	   	 /* font bitmap pointer     */
						pdescript 	  = consolas_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_HEIGHT;    	 /* font height in pixels   */
					}
					break;

				case CONSOLAS_ITALIC:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_italic_8ptBitmaps;		   /* font bitmap pointer 	  */
						pdescript 	  = consolas_italic_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_ITALIC_HEIGHT;      /* font height in pixels   */
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_italic_11ptBitmaps;	    /* font bitmap pointer 	   */
						pdescript 	  = consolas_italic_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_ITALIC_HEIGHT;       /* font height in pixels   */
					}
					break;

				case CONSOLAS_BOLD:
					if (font_size == SMALL_FONT)
					{
						pfont         = consolas_bold_8ptBitmaps;	   	 /* font bitmap pointer 	*/
						pdescript 	  = consolas_bold_8ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_SMALL_BOLD_HEIGHT; 	 /* font height in pixels 	*/
					}
					else if(font_size == LARGE_FONT)
					{
						pfont         = consolas_bold_11ptBitmaps;		  /* font bitmap pointer 	 */
						pdescript 	  = consolas_bold_11ptDescriptors[0]; /* font descriptor pointer */
						symbol_height = CONSOLAS_LARGE_BOLD_HEIGHT; 	  /* font height in pixels 	 */
					}
					break;

				default:
					return IOL_CONSOLAS_FONT_ERROR;
					break;
			}
			break;

		default:
			return IOL_FONT_ERROR;
			break;
	}

	FL_debug_tx("text parameters selected \n");

	for(i=0;i<strlen(text);i++) /* loop to print each character from the text buffer */
	{
		symbol_nr = (*(text+i)) - ASCII_OFFSET; /* determines which symbol from the font library should be selected */
		if((symbol_nr<0) || symbol_nr>=ASCII_DEL)
		{
			FL_debug_tx("symbol_nr invalid: \n");
			FL_debug_int(symbol_nr);
			continue;
		}

		symbol_width_pixels = *(pdescript + symbol_nr * ARRAY_DIMENSION); /* retrieves the symbol width expressed in pixels */
		symbol_start = *(pdescript + symbol_nr * ARRAY_DIMENSION + CHAR_START_OFFSET); /* retrieves the starting element for the font bitmap */

		/* determines how many bytes are used in width per character */
		symbol_width =  symbol_width_pixels/BYTE_SIZE;
		if (symbol_width_pixels % BYTE_SIZE != 0)
			symbol_width++;


		for(y=0; y<symbol_height;y++) /* symbol height in pixels */
		{
			for(x=0; x<symbol_width;x++)  /* symbol width in bytes */
			{
				temp = 	*(pfont + symbol_start + y*symbol_width + x); /* retrieves byte from character bitmap */
				bitmask = BITMASK ; /* B1000 0000 */
				for(bit = 0; bit<BYTE_SIZE; bit++) /* check per byte */
				{
					if((temp & bitmask)!=0)
					{
						UB_VGA_SetPixel(xlup + bit + x*BYTE_SIZE , ylup + y, color); /* sets pixel */
					}
					bitmask = bitmask >> 1;
				}
			}
		}
		xlup = xlup + symbol_width_pixels + 1; /* 1 pixel offset for spacing between symbols */
	}

	FL_debug_tx("finished text \n");
	return error;
}
