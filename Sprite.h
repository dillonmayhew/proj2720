#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

enum DIRECTION{N, E, S, W, NE, NW, SE, SW};

const int screenWidth = 1280;
const int screenHeight = 720;
const int gameWidth = 3200;
const int gameHeight = 2400;

class Sprite {
private:
	int curRow;
	int curColumn;
public:
	int pOffsetx;
	int pOffsety;
	int getCurRow();
	int getCurColumn();
	void setCurRow(int curFr);
	void setCurColumn(int curCo);
	
	int x;
	int y;
	int soulCount;
	int maxHealth;
	int health;
	float dmg;
	float speed;
	float runSpeed;
	int boundx;
	int boundy;
	bool live;
	bool hit;
	int maxFrameWalk;
	int maxFrameRun;
	int maxFrameAtk;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;

	ALLEGRO_BITMAP *healthimage;
	ALLEGRO_BITMAP *image;

	virtual void beenHit(){}
	virtual void draw();
	void moveDirect(DIRECTION D);
	void walk(DIRECTION D);
};
#endif