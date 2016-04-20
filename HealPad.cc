#include "HealPad.h"

HealPad::HealPad(ALLEGRO_BITMAP *healimage)
{
	frameWidth = 128;
	frameHeight = 96;
	setCurRow(0);
	setCurColumn(0);

	hit = false;
	live = true;
	speed = 6;

	x = rand()%gameWidth - frameWidth;
	y = rand()%gameHeight - frameHeight;

	boundx = 25;
	boundy = 25;

	image = healimage;
}
void HealPad::collidePlayer(Player *plyr)
{
	if(live)
	{
		if(plyr->live)
		{
			if(x+boundx > (plyr->x - plyr->boundx) &&
				x-boundx < (plyr->x + plyr->boundx) &&
				y+boundy > (plyr->y - plyr->boundy) &&
				y-boundy < (plyr->y + plyr->boundy))
			{
				plyr->health = plyr->maxHealth;
				hit = true;
				live = false;
			}
		}
	}
	else
		hit = false;
}