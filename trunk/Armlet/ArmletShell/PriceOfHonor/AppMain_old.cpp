#include <string.h>
#include "UpInterface.h"
#include "AppMain.h"
#include "TextField.h"
#include "GraphicRenderer.h"

TextField tf;
GraphicRenderer rend;

void __stdcall AppOnButtonClick(int button)
{
	if (button == BUTTON_Y) {
		Position pos = tf.GetScrollPosition();
		pos.Top++;
		tf.SetScrollPosition(pos);
		Clear(0);
		tf.Draw();
	}
	if (button == BUTTON_X) {
		Position pos = tf.GetScrollPosition();
		if (pos.Top==0)
			return;
		pos.Top--;
		tf.SetScrollPosition(pos);
		Clear(0);
		tf.Draw();
	}
	return;
}

void __stdcall AppOnButtonHold(int button)
{
	return;
}

int gx=0;
int gy=0;
int gc=0x0000;
bool __stdcall MoveBoxByTimer()
{
	DrawRect(gx,gy,30,30,0);
	gc+=0x111;
	if (gc>=0x1000) gc=0x0000;
	gx+=15; gy+=5;
	if (gx>SCREENX) gx-=SCREENX;
	if (gy>SCREENY) gy-=SCREENY;
	DrawRect(gx,gy,30,30,gc);
	return TRUE;
}

extern const unsigned char icon_help[];
extern const unsigned char icon_arrow_up[];
extern const unsigned char icon_arrow_down[];
void DrawIcons()
{
	for(int i=0;i<32;i++) 
	{
		for(int j=0;j<32;j++)
		{
			char c8 = icon_help[3+i+j*32];
			//8bit per pixel to 4 bit per pixel
			int c4 = (c8 >> 4);
			short c = (c4<<8)|(c4<<4)|(c4);
			DrawPixel(0+i,0+j,c);

			c8 = icon_arrow_up[3+i+j*32];
			//8bit per pixel to 4 bit per pixel
			c4 = (c8 >> 4);
			c = (c4<<8)|(c4<<4)|(c4);
			DrawPixel(0+i,32+j,c);

			c8 = icon_arrow_down[3+i+j*32];
			//8bit per pixel to 4 bit per pixel
			c4 = (c8 >> 4);
			c = (c4<<8)|(c4<<4)|(c4);
			DrawPixel(0+i,64+j,c);
		}
	}
}

void __stdcall AppMainThread(void* param)
{
	DrawIcons();
	return;

	const char* str = "PRICE of HONOR!";
	DrawTextString(10,10,str,strlen(str),0,0);

	Position pos;
	Size size,size2;	

	Clear(0);
	InitPositionAndSize(10,10,80,80, &pos, &size);
	tf.Init(size, pos, &rend);
	str = 
		"������: "
		"����: 12"
		"����� �4"
		"        "
		"� ������"
		"�����,  "
		"��������";
	size2.Height = 7; size2.Width = 8;
	tf.SetText(str,size2,TRUE, NULL);
	tf.Draw();
	RegisterButtonHandlers(AppOnButtonClick, AppOnButtonHold);
	RequestTimer(300, MoveBoxByTimer);
}