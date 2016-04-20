#include "StoneAtk.h"

StoneAtk::StoneAtk(){image = 0;}
StoneAtk::StoneAtk(ALLEGRO_BITMAP *stoneimage)
{
	maxFrame = 23;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 64;
	frameHeight = 64;
	dmg = 3;
	setCurRow(0);
	setCurColumn(0);

	imageChange = false;
	live = false;

	speed = 7;

	boundx = 20;
	boundy = 20;

	image = stoneimage;
}
void StoneAtk::updateObj(Enemy *enemy, Player *plyr)
{
	if(live)
	{
		if(enemy->getCurColumn() > 9 && enemy->getCurColumn() < 17 && getCurColumn() <= 1)
		{
			setCurRow(enemy->getCurRow());
			setCurColumn(0);
		}
		else
		{
			if(enemy->getCurColumn() < 27 && getCurColumn() > 5 && enemy->inAtkDist(plyr))
				enemy->stop();
			y += yDirect*speed;
			x += xDirect*speed;
			frameDelay = 5;
		}
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrame)
			{
				reset();
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}	
		if(enemy->health < enemy->maxHealth/2 && !imageChange){
			dmg *= 2;
			speed = 9;
			image = al_load_bitmap("rolllavastone.png");
			al_convert_mask_to_alpha(image, al_map_rgb(97, 68, 43));
			imageChange = true;	
		}
	}
}