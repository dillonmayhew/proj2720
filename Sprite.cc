#include <iostream>
#include "Sprite.h"

int Sprite::getCurRow()
{
	return curRow;
}
int Sprite::getCurColumn()
{
	return curColumn;
}
void Sprite::setCurRow(int curFr)
{
	curRow = curFr;
}
void Sprite::setCurColumn(int curCo)
{
	curColumn = curCo;
}
void Sprite::draw()
{
	int fx = getCurColumn() * frameWidth;
	int fy = getCurRow() * frameHeight;

	al_draw_bitmap_region(image, fx,
		fy, frameWidth, frameHeight, x, y, 0);


	/*al_draw_filled_rectangle(x+frameWidth/2 - boundx, y+frameHeight/2 - boundy,
								 x+frameWidth/2 + boundx, y+frameHeight/2 + boundy,
								 al_map_rgba(255, 0, 255, 5));*/
}
void Sprite::moveDirect(DIRECTION D)
{
	switch(D)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
		break;
	case 4:
		x += speed;
		y -= speed;
		break;
	case 5:
		x -= speed;
		y -= speed;
		break;
	case 6:
		x += speed;
		y += speed;
		break;
	case 7:
		x -= speed;
		y += speed;
		break;
	default:
		break;
	}
}
void Sprite::walk(DIRECTION D)
{
	if(getCurRow() != D)
		setCurRow(D);
	moveDirect(D);
	if(++frameCount >= frameDelay)
	{
		if((getCurColumn() + 1) >= maxFrameWalk)
		{
			setCurColumn(1);
		}
		setCurColumn(getCurColumn() + 1);
		frameCount = 0;
	}
	if(y < 0)
		y = 0;
	if(x < 0)
		x = 0;
	if(x > gameWidth - frameWidth)
		x = gameWidth - frameWidth;
	if(y > gameHeight - frameHeight)
		y = gameHeight - frameHeight;
}