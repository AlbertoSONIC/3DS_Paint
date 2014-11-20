#include "draw.h"
#include "memory.h"
#include "ascii64.h"


void clearScreen(u8* screen,gfxScreen_t screenPos)
{
	int width;
	int height=240;

	switch(screenPos){
	case GFX_BOTTOM:
		width=BOTTOM_WIDTH;
		break;
	default:
		width=TOP_WIDTH;
		break;
	}

	int i, j;
	for(i=1;i<width;i++)
	{
		for(j=1;j<height;j++)
		{
			drawPixel(i,j,0x00,0x00,0x00,screen);
		}
	}
}

void drawPixel(int x, int y, char r, char g, char b, u8* screen)
{
	int height=240;
	
	u32 v=(height-1-y+x*height)*3;
	screen[v]=b;
	screen[v+1]=g;
	screen[v+2]=r;
}


void drawChar(char letter,int x,int y, char r, char g, char b, u8* screen)
{
	int i, k;
	unsigned char mask;
	unsigned char l;

	for (i = 0; i < 8; i++){
		mask = 0b10000000;
		l = asciiData[(int)letter][i];
		for (k = 0; k < 8; k++){
			if ((mask >> k) & l){
				drawPixel(k+x,i+y,r,g,b,screen);
			}     
		}
	}
}

void drawString(char* word, int x,int y, char r, char g, char b, u8* screen,gfxScreen_t screenPos)
{
	int tmp_x =x;
	int i;
	int line = 0;

	int width;

	switch(screenPos){
	case GFX_BOTTOM:
		width=BOTTOM_WIDTH;
		break;
	default:
		width=TOP_WIDTH;
		break;
	}

	for (i = 0; i <strlen(word); i++){

		if (tmp_x+8 > width) {
			line++;
			tmp_x = x;
		}
		drawChar(word[i],tmp_x,y+(line*8),r,g,b, screen);

		tmp_x = tmp_x+8;
	}
}


/*
draw_line - H_line and V_line only
*/

void drawLine( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{

	int x, y;
	if (x1 == x2){
		if (y1<y2) for (y = y1; y < y2; y++) drawPixel(x1,y,r,g,b,screen);
		else for (y = y2; y < y1; y++) drawPixel(x1,y,r,g,b,screen);
	} else {
		if (x1<x2) for (x = x1; x < x2; x++) drawPixel(x,y1,r,g,b,screen);
		else for (x = x2; x < x1; x++) drawPixel(x,y1,r,g,b,screen);
	}
}

void drawRect( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{
	drawLine( x1, y1, x2, y1, r, g, b, screen);
	drawLine( x2, y1, x2, y2, r, g, b, screen);
	drawLine( x1, y2, x2, y2, r, g, b, screen);
	drawLine( x1, y1, x1, y2, r, g, b, screen);
}

void drawFillRect( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{
	int X1,X2,Y1,Y2,i,j;

	if (x1<x2){ 
		X1=x1;
		X2=x2;
	} else { 
		X1=x2;
		X2=x1;
	} 

	if (y1<y2){ 
		Y1=y1;
		Y2=y2;
	} else { 
		Y1=y2;
		Y2=y1;
	} 
	for(i=X1;i<=X2;i++){
		for(j=Y1;j<=Y2;j++){
			drawPixel(i,j, r, g, b, screen);
		}
	}
}

void drawCircle(int xCen, int yCen, int radius, char r, char g, char b, u8* screen)
{
	int x = 0;
	int y = radius;
	int p = (5 - radius*4)/4;
	drawCircleCircum(xCen, yCen, x, y, r, g, b, screen);
	while(x < y){
		x++;
		if(p < 0){
			p += 2*x+1;
		}
		else{
			y--;
			p += 2*(x-y)+1;
		}
		drawCircleCircum(xCen, yCen, x, y, r, g, b, screen);
	}
}

void drawFillCircle(int xCen, int yCen, int radius, char r, char g, char b, u8* screen)
{
	drawCircle(xCen, yCen, radius, r, g, b, screen);
	int x,y;
	for(y = -radius;y <= radius;y++){
		for(x = -radius;x <= radius;x++)
			if(x*x + y*y <= radius*radius + radius * .8f)
				drawPixel(xCen + x, yCen + y, r, g, b, screen);
	}
}

void drawCircleCircum(int cx, int cy, int x, int y, char r, char g, char b, u8* screen)
{
	//int tx, ty;

	if(x == 0){
		drawPixel(cx, cy + y, r, g, b, screen);
		drawPixel(cx, cy - y, r, g, b, screen);
		drawPixel(cx + y, cy, r, g, b, screen);
		drawPixel(cx - y, cy, r, g, b, screen);
	}
	if(x == y){
		drawPixel(cx + x, cy + y, r, g, b, screen);
		drawPixel(cx - x, cy + y, r, g, b, screen);
		drawPixel(cx + x, cy - y, r, g, b, screen);
		drawPixel(cx - x, cy - y, r, g, b, screen);
	}
	if(x < y){
		drawPixel(cx + x, cy + y, r, g, b, screen);
		drawPixel(cx - x, cy + y, r, g, b, screen);
		drawPixel(cx + x, cy - y, r, g, b, screen);
		drawPixel(cx - x, cy - y, r, g, b, screen);
		drawPixel(cx + y, cy + x, r, g, b, screen);
		drawPixel(cx - y, cy + x, r, g, b, screen);
		drawPixel(cx + y, cy - x, r, g, b, screen);
		drawPixel(cx - y, cy - x, r, g, b, screen);
	}
}
