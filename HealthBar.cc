#include "HealthBar.h"

HealthBar::HealthBar()
{
	image = NULL;
}
HealthBar::HealthBar(ALLEGRO_BITMAP *barimage, Sprite *sprite)
{
	frameWidth = 80;
	frameHeight = 5;
	maxHealth = frameWidth;
	health = maxHealth;

	x = sprite->x+8;
	y = sprite->y;

	image = barimage;
}
void HealthBar::draw(Sprite *sprite)
{
	x = sprite->x;
	y = sprite->y;

	health = static_cast<float>(sprite->health)/static_cast<float>(sprite->maxHealth)*maxHealth;

	al_draw_bitmap_region(image, 0,
		0, health, frameHeight, x, y, 0);
}