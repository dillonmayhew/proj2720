#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <ctime>
#include "mappy_A5.h"

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, R, ONE, TWO, THREE, P};
enum DIRECTION{N, E, S, W, NE, NW, SE, SW};
enum ENEMY{LAVATROLL, ICETROLL, GREYTROLL};
enum ATTACK{FIREMAGIC, WATERMAGIC, EARTHMAGIC, WINDMAGIC};

const int screenWidth = 1280;
const int screenHeight = 720;
const int gameWidth = 3200;
const int gameHeight = 2400;

class Sprite {
private:
	int curRow;
	int curColumn;
public:
	int getCurRow(){
		return curRow;
	}
	int getCurColumn(){
		return curColumn;
	}
	void setCurRow(int curFr){
		curRow = curFr;
	}
	void setCurColumn(int curCo){
		curColumn = curCo;
	}
	
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
	virtual void draw()
	{
		int fx = getCurColumn() * frameWidth;
		int fy = getCurRow() * frameHeight;

		al_draw_bitmap_region(image, fx,
			fy, frameWidth, frameHeight, x, y, 0);


		/*al_draw_filled_rectangle(x+frameWidth/2 - boundx, y+frameHeight/2 - boundy,
								 x+frameWidth/2 + boundx, y+frameHeight/2 + boundy,
								 al_map_rgba(255, 0, 255, 5));*/
	}
};
class Player : public Sprite {
public:
	void walkN()
	{
		if(getCurRow() != 0)
			setCurRow(0);
		y -= speed;
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
	}
	void walkE()
	{
		if(getCurRow() != 1)
			setCurRow(1);
		x += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
	}
	void walkS()
	{
		if(getCurRow() != 2)
			setCurRow(2);
		y += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}
	void walkW()
	{
		if(getCurRow() != 3)
			setCurRow(3);
		x -= speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
	}

	void walkNE()
	{
		if(getCurRow() != 4)
			setCurRow(4);
		x += speed;
		y -= speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
		if(y < 0)
			y = 0;
	}
	void walkNW()
	{
		if(getCurRow() != 5)
			setCurRow(5);
		x -= speed;
		y -= speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0;
	}
	void walkSE()
	{
		if(getCurRow() != 6)
			setCurRow(6);
		x += speed;
		y += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}
	void walkSW()
	{
		if(getCurRow() != 7)
			setCurRow(7);
		x -= speed;
		y += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}

	void runN()
	{
		if(getCurRow() != 0)
			setCurRow(0);
		if(getCurColumn() < 31)
			setCurColumn(31);
		y -= runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(y < 0)
			y = 0;
	}
	void runE()
	{
		if(getCurRow() != 1)
			setCurRow(1);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x += runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
	}
	void runS()
	{
		if(getCurRow() != 2)
			setCurRow(2);
		if(getCurColumn() < 31)
			setCurColumn(31);
		y += runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}
	void runW()
	{
		if(getCurRow() != 3)
			setCurRow(3);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x -= runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
	}

	void runNE()
	{
		if(getCurRow() != 4)
			setCurRow(4);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x += runSpeed;
		y -= runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
		if(y < 0)
			y = 0;
	}
	void runNW()
	{
		if(getCurRow() != 5)
			setCurRow(5);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x -= runSpeed;
		y -= runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0;
	}
	void runSE()
	{
		if(getCurRow() != 6)
			setCurRow(6);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x += runSpeed;
		y += runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x > gameWidth - frameWidth)
			x = gameWidth - frameWidth;
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}
	void runSW()
	{
		if(getCurRow() != 7)
			setCurRow(7);
		if(getCurColumn() < 31)
			setCurColumn(31);
		x -= runSpeed;
		y += runSpeed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameRun)
			{
				setCurColumn(31);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		if(y > gameHeight - frameHeight)
			y = gameHeight - frameHeight;
	}

	void beenHit(){
		if(hit){
		if(getCurColumn() <= 23)
			setCurColumn(23);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 30)
			{
				hit = false;
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(health <=0)
			live = false;
		}
	}

	void attack()
	{
		if(getCurColumn() <= 9)
			setCurColumn(9);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameAtk)
			{
				setCurColumn(9);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}

	void stop()
	{
		setCurColumn(0);
	}

};
class Enemy : public Sprite {
public:
	//Enemy(){image = NULL;}
	int xDirect;
	int yDirect;
	int dBound;
	ENEMY ID;
	Enemy(){}
	
	void walkN()
	{
		if(getCurRow() != 0)
			setCurRow(0);
		y -= speed;
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
	}
	void walkE()
	{
		if(getCurRow() != 1)
			setCurRow(1);
		x += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		/*if(x > width - frameWidth)
			x = width - frameWidth;*/
	}
	void walkS()
	{
		if(getCurRow() != 2)
			setCurRow(2);
		y += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		/*if(y > height - frameHeight)
			y = height - frameHeight;*/
	}
	void walkW()
	{
		if(getCurRow() != 3)
			setCurRow(3);
		x -= speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		/*if(x > width - frameWidth)
			x = 0;*/
	}
	void walkNE()
	{
		if(getCurRow() != 4)
			setCurRow(4);
		y -= speed;
		x += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		/*if(x > width - frameWidth)
			x = width - frameWidth;*/
		if(y < 0)
			y = 0;
	}
	void walkNW()
	{
		if(getCurRow() != 5)
			setCurRow(5);
		y -= speed;
		x -= speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0;
	}
	void walkSE()
	{
		if(getCurRow() != 6)
			setCurRow(6);
		y += speed;
		x += speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		/*if(x > width - frameWidth)
			x = width - frameWidth;
		if(y > height - frameHeight)
			y = height - frameHeight;*/
	}
	void walkSW()
	{
		if(getCurRow() != 7)
			setCurRow(7);
		y += speed;
		x -=speed;
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameWalk)
			{
				setCurColumn(1);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
		if(x < 0)
			x = 0;
		/*if(y > height - frameHeight)
			y = height - frameHeight;*/
	}
	bool isClose(Player *plyr)
	{
		if( plyr->x+24 - x < 500 && plyr->x+24 - x > -500 &&
			plyr->y+12 - y < 500 && plyr->y+12 - y > -500)
			return true;
		else
			return false;
	}
	void moveTowards(Player *plyr)
	{
		facePlyr(plyr);
		if(getCurRow() == 0)
			walkN();
		if(getCurRow() == 1)
			walkE();
		if(getCurRow() == 2)
			walkS();
		if(getCurRow() == 3)
			walkW();
		if(getCurRow() == 4)
			walkNE();
		if(getCurRow() == 5)
			walkNW();
		if(getCurRow() == 6)
			walkSE();
		if(getCurRow() == 7)
			walkSW();
	}
	bool inAtkDist(Player *plyr)
	{
		if( plyr->x+24 - x < 250 && plyr->x+24 - x > -250 &&
			plyr->y+12 - y < 250 && plyr->y+12 - y > -250)
			return true;
		else
			return false;
	}
	void facePlyr(Player *plyr)
	{
		if(plyr->x >= x+dBound && plyr->y < y-dBound)
			setCurRow(4);
		else if(plyr->x < x-dBound && plyr->y < y-dBound)
			setCurRow(5);
		else if(plyr->x >= x+dBound && plyr->y >= y+dBound)
			setCurRow(6);
		else if(plyr->x < x-dBound && plyr->y >= y+dBound)
			setCurRow(7);
		else if(plyr->y < y && (plyr->x >= x-dBound && plyr->x < x+dBound))
			setCurRow(0);
		else if(plyr->x > x && (plyr->y >= y-dBound && plyr->y < y+dBound))
			setCurRow(1);
		else if(plyr->y > y && (plyr->x >= x-dBound && plyr->x < x+dBound))
			setCurRow(2);
		else if(plyr->x < x && (plyr->y >= y-dBound && plyr->y < y+dBound))
			setCurRow(3);
		
	}
	void attack(Player *plyr)
	{
		facePlyr(plyr);
		if(getCurColumn() <= 9)
			setCurColumn(9);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrameAtk)
			{
				setCurColumn(9);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	void stop()
	{
		setCurColumn(0);
	}
	virtual void pace(){}
	virtual void disintegrate(){}
	void updateTroll(Player *plyr)
	{
		if(health <= 0){
			hit = false;
			disintegrate();
		}
		else if(hit)
			beenHit();
		else if(!hit)
		{
			if(isClose(plyr))
			{
				if(inAtkDist(plyr))
					attack(plyr);
				else
					moveTowards(plyr);
			}
			else
			{
				pace();
			}
		}
	}
	void beenHit()
	{
		if(getCurColumn() <= 23)
			setCurColumn(23);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 26)
			{
				hit = false;
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
};
class Wizard : public Player {
public:
	Wizard(ALLEGRO_BITMAP *wizimage)
	{
		soulCount = 0;
		maxFrameWalk = 9;
		maxFrameRun = 38;
		maxFrameAtk = 22;
		maxHealth = 50;
		health = 50;
		setCurRow(0);
		setCurColumn(0);
		frameCount = 0;
		frameDelay = 5;
		frameWidth = 96;
		frameHeight = 96;

		speed = 2;
		runSpeed = speed*1.75;
		x = gameWidth / 2 - (frameWidth / 2);
		y = gameHeight / 2 - (frameHeight / 2);

		boundx = 15;
		boundy = 30;

		hit = false;
		live = true;

		image = wizimage;
	}
	
};
class LavaTroll	 : public Enemy {
public:
	LavaTroll()
	{
		ID = LAVATROLL;
		image = NULL;
	}
	LavaTroll(ALLEGRO_BITMAP *trollImage)
	{
		ID = LAVATROLL;
		maxFrameWalk = 9;
		maxFrameAtk = 22;
		speed = 1.5;

		dBound = 50;
		setCurRow(0);
		setCurColumn(0);
		frameCount = 0;
		frameDelay = 5;
		frameWidth = 96;
		frameHeight = 96;
		maxHealth = 2;
		health = 2;
	
		yDirect = 1;

		boundx = 15;
		boundy = 30;

		x = rand()%gameWidth - frameWidth;
		y = rand()%gameHeight - frameHeight;

		hit = false;
		live = true;

		image = trollImage;
	}

	void disintegrate()
	{
		if(getCurColumn() <= 27)
			setCurColumn(27);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 43)
			{
				setCurColumn(27);
				live = false;
				hit = false;
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	/*void paused()
	{
		if(getCurColumn() <= 44)
			setCurColumn(44);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 48)
			{
				setCurColumn(44);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}*/
	void pace()
	{
		if(getCurRow() != 1 && getCurRow() != 3)
			setCurRow(1);
		if(getCurRow() == 1)
			walkE();
		else if(getCurRow() == 3)
			walkW();
		if(getCurColumn()+1 >= maxFrameWalk)
		{
			if(getCurRow() == 1){
				setCurRow(3);
				setCurColumn(1);
			}
			else if(getCurRow() == 3){
				setCurRow(1);
				setCurColumn(1);
			}
		}
		//stop();
	}
};
class IceTroll: public Enemy {
public:
	IceTroll()
	{
		ID = ICETROLL;
		image = NULL;
	}
	IceTroll(ALLEGRO_BITMAP *trollImage)
	{
		ID = ICETROLL;
		maxFrameWalk = 9;
		maxFrameAtk = 22;
		dBound = 50;
		speed = 1;

		setCurRow(0);
		setCurColumn(0);
		frameCount = 0;
		frameDelay = 5;
		frameWidth = 96;
		frameHeight = 96;
		maxHealth = 3;
		health = 3;

		yDirect = 1;

		boundx = 15;
		boundy = 30;

		x = rand()%gameWidth - frameWidth;
		y = rand()%gameHeight - frameHeight;

		hit = false;
		live = true;

		image = trollImage;
	}
	
	void disintegrate()
	{
		if(getCurColumn() <= 27)
			setCurColumn(27);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 43)
			{
				setCurColumn(27);
				live = false;
				hit = false;
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	void pace()
	{
		if(getCurRow() != 0 && getCurRow() != 2)
			setCurRow(0);
		if(getCurRow() == 0)
			walkN();
		else if(getCurRow() == 2)
			walkS();
		if(getCurColumn()+1 >= maxFrameWalk)
		{
			if(getCurRow() == 0){
				setCurRow(2);
				setCurColumn(1);
			}
			else if(getCurRow() == 2){
				setCurRow(0);
				setCurColumn(1);
			}
		}
		//stop();
	}
};
class GreyTroll: public Enemy {
public:
	GreyTroll()
	{
		ID = GREYTROLL;
		image = NULL;
	}
	GreyTroll(ALLEGRO_BITMAP *trollImage)
	{
		ID = GREYTROLL;
		maxFrameWalk = 9;
		maxFrameAtk = 22;
		dBound = 50;
		speed = 1;

		setCurRow(0);
		setCurColumn(0);
		frameCount = 0;
		frameDelay = 5;
		frameWidth = 96;
		frameHeight = 96;
		maxHealth = 10;
		health = 10;

		yDirect = 1;

		boundx = 15;
		boundy = 30;

		x = rand()%gameWidth - frameWidth;
		y = rand()%gameHeight - frameHeight;

		hit = false;
		live = true;

		image = trollImage;
	}
	
	void disintegrate()
	{
		if(getCurColumn() <= 27)
			setCurColumn(27);
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= 43)
			{
				setCurColumn(27);
				live = false;
				hit = false;
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	void pace()
	{
		if(getCurRow() != 0 && getCurRow() != 2)
			setCurRow(0);
		if(getCurRow() == 0)
			walkN();
		else if(getCurRow() == 2)
			walkS();
		if(getCurColumn()+1 >= maxFrameWalk)
		{
			if(getCurRow() == 0){
				setCurRow(2);
				setCurColumn(1);
			}
			else if(getCurRow() == 2){
				setCurRow(0);
				setCurColumn(1);
			}
		}
		//stop();
	}
};
class Objects : public Sprite {
public:
	ATTACK ID;
	int speed;
	int xDirect;
	int yDirect;
	int maxFrame;

	virtual void updateObj(Player *plyr)
	{
		if(live)
		{
			//setCurRow(plyr->getCurRow());
			if(plyr->getCurColumn() > 9 && plyr->getCurColumn() < 17 && getCurColumn() <= 1)
			{
				setCurRow(plyr->getCurRow());
				setCurColumn(0);
			}
			else
			{
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
		}
		
	}
	virtual void reset()
	{
		live = false;
		setCurRow(0);
		setCurColumn(0);
		frameDelay = 2;
	}
	virtual void startAtk(Player *plyr)
	{
		if(!live && plyr->getCurRow() == 0)
		{
			x = plyr->x + 24;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 1)
		{
			x = plyr->x + 60;
			y = plyr->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 2)
		{
			x = plyr->x + 24;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 3)
		{
			x = plyr->x - 12;
			y = plyr->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 4)
		{
			x = plyr->x + 48;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 5)
		{
			x = plyr->x;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 6)
		{
			x = plyr->x + 48;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 7)
		{
			x = plyr->x;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
	}
	void collideEnemy(Enemy *enemy)
	{
		if(live)
		{
				if(enemy->live)
				{
					if(x+boundx > (enemy->x - enemy->boundx) &&
						x-boundx < (enemy->x + enemy->boundx) &&
						y+boundx > (enemy->y - enemy->boundy) &&
						y-boundx < (enemy->y + enemy->boundy))
					{
						enemy->hit = true;
						enemy->beenHit();
						reset();
						if(ID == FIREMAGIC && enemy->ID == LAVATROLL)
							enemy->health += dmg;
						else if(ID == FIREMAGIC && enemy->ID == ICETROLL)
							enemy->health -= dmg*3;
						else if(ID == WATERMAGIC && enemy->ID == LAVATROLL)
							enemy->health -= dmg*2;
						else if(ID == WATERMAGIC && enemy->ID == ICETROLL)
							enemy->health += dmg;
						else if(ID == WINDMAGIC)
							enemy->health -= dmg;
						else if(ID == EARTHMAGIC && enemy->ID == GREYTROLL)
							enemy->health -= dmg*2;
						else
							enemy->health -= dmg;

					}
				}
			
		}
	}
	virtual void collidePlayer(Player *plyr){}

};
class enemyAtk : public Objects{
public:
	enemyAtk(){image = 0;}
	enemyAtk(ALLEGRO_BITMAP *atkimage)
	{
		maxFrame = 15;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		//curRow = 0;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 7;

		boundx = 15;
		boundy = 25;

		image = atkimage;
	}
	virtual void startAtk(Enemy *enemy, Player *plyr)
	{
		if(enemy->inAtkDist(plyr) && enemy->getCurColumn()<27)
		{
		if(!live && enemy->getCurRow() == 0)
		{
			x = enemy->x + 24;
			y = enemy->y - 12;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 1)
		{
			x = enemy->x + 60;
			y = enemy->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 2)
		{
			x = enemy->x + 24;
			y = enemy->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 3)
		{
			x = enemy->x - 12;
			y = enemy->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 4)
		{
			x = enemy->x + 48;
			y = enemy->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 5)
		{
			x = enemy->x;
			y = enemy->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 6)
		{
			x = enemy->x + 48;
			y = enemy->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && enemy->getCurRow() == 7)
		{
			x = enemy->x;
			y = enemy->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
		}
	}
	virtual void reset(){
		live = false;
		frameDelay = 4;
		setCurRow(0);
		setCurColumn(0);
	}
	virtual void updateObj(Enemy *enemy, Player *plyr)
	{
		if(live)
		{
			if(getCurRow() > 1)
			{
				reset();
			}
			if(getCurRow() > 0)
			{
				if(enemy->getCurColumn() < 27 && enemy->inAtkDist(plyr))
					enemy->stop();
				y += yDirect*speed;
				x += xDirect*speed;
				frameDelay = 5;
			}
			if(++frameCount >= frameDelay)
			{
				if((getCurColumn() + 1) >= maxFrame)
				{
					setCurColumn(0);
					setCurRow(getCurRow() + 1);
				}
				setCurColumn(getCurColumn() + 1);
				frameCount = 0;
			}
		}
	}
	virtual void collidePlayer(Player *plyr)
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
					plyr->hit = true;
					reset();
					//if(getCurRow() > 0)
						plyr->health -= dmg;
				}
				plyr->beenHit();
			}
		}
	}
};
class LavaAtk : public enemyAtk{
public:
	LavaAtk(){image = 0;}
	LavaAtk(ALLEGRO_BITMAP *lavaimage)
	{
		maxFrame = 15;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 2;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 7;

		boundx = 15;
		boundy = 25;

		image = lavaimage;
	}
};
class WaterAtk : public enemyAtk{
public:
	WaterAtk(){image = 0;}
	WaterAtk(ALLEGRO_BITMAP *waterimage)
	{
		maxFrame = 15;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 1;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 7;

		boundx = 15;
		boundy = 25;

		image = waterimage;
	}
};
class StoneAtk : public enemyAtk{
public:
	bool imageChange;
	StoneAtk(){image = 0;}
	StoneAtk(ALLEGRO_BITMAP *stoneimage)
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
	void updateObj(Enemy *enemy, Player *plyr)
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

};
class FireMagic : public Objects {
public:
	FireMagic(ALLEGRO_BITMAP *firimage)
	{
		ID = FIREMAGIC;
		maxFrame = 20;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 1;
		//curRow = 0;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 6;

		boundx = 10;
		boundy = 10;

		image = firimage;
	}
	void startAtk(Player *plyr)
	{
		plyr->frameDelay = 5;
		if(!live && plyr->getCurRow() == 0)
		{
			x = plyr->x + 18;
			y = plyr->y - 18;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 1)
		{
			x = plyr->x + 60;
			y = plyr->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 2)
		{
			x = plyr->x + 18;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 3)
		{
			x = plyr->x - 12;
			y = plyr->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 4)
		{
			x = plyr->x + 48;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 5)
		{
			x = plyr->x;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 6)
		{
			x = plyr->x + 48;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 7)
		{
			x = plyr->x;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
	}
	
};
class WaterMagic : public Objects {
public:
	WaterMagic(ALLEGRO_BITMAP *waterimage)
	{
		ID = WATERMAGIC;
		maxFrame = 20;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 1;
		//curRow = 0;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 6;

		boundx = 10;
		boundy = 10;

		image = waterimage;
	}
	void startAtk(Player *plyr)
	{
		plyr->frameDelay = 5;
		if(!live && plyr->getCurRow() == 0)
		{
			x = plyr->x + 18;
			y = plyr->y - 18;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 1)
		{
			x = plyr->x + 60;
			y = plyr->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 2)
		{
			x = plyr->x + 18;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 3)
		{
			x = plyr->x - 12;
			y = plyr->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 4)
		{
			x = plyr->x + 48;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 5)
		{
			x = plyr->x;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 6)
		{
			x = plyr->x + 48;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 7)
		{
			x = plyr->x;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
	}

};
class EarthMagic : public Objects {
public:
	EarthMagic(ALLEGRO_BITMAP *earthimage)
	{
		ID = EARTHMAGIC;
		maxFrame = 20;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 2;
		//curRow = 0;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 4;

		boundx = 10;
		boundy = 10;

		image = earthimage;
	}
	void startAtk(Player *plyr)
	{
		plyr->frameDelay = 5;
		if(!live && plyr->getCurRow() == 0)
		{
			x = plyr->x + 18;
			y = plyr->y - 18;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 1)
		{
			x = plyr->x + 60;
			y = plyr->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 2)
		{
			x = plyr->x + 18;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 3)
		{
			x = plyr->x - 12;
			y = plyr->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 4)
		{
			x = plyr->x + 48;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 5)
		{
			x = plyr->x;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 6)
		{
			x = plyr->x + 48;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 7)
		{
			x = plyr->x;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
	}

};
class WindMagic : public Objects {
public:
	WindMagic(ALLEGRO_BITMAP *windimage)
	{
		ID = WINDMAGIC;
		maxFrame = 20;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		dmg = 1;
		//curRow = 0;
		setCurRow(0);
		setCurColumn(0);

		live = false;
		speed = 10;

		boundx = 10;
		boundy = 10;

		image = windimage;
	}
	void startAtk(Player *plyr)
	{
		plyr->frameDelay = 4;
		if(!live && plyr->getCurRow() == 0)
		{
			x = plyr->x + 18;
			y = plyr->y - 18;
			yDirect = -1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 1)
		{
			x = plyr->x + 60;
			y = plyr->y;
			yDirect = 0;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 2)
		{
			x = plyr->x + 18;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 0;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 3)
		{
			x = plyr->x - 12;
			y = plyr->y;
			yDirect = 0;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 4)
		{
			x = plyr->x + 48;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 5)
		{
			x = plyr->x;
			y = plyr->y - 12;
			yDirect = -1;
			xDirect = -1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 6)
		{
			x = plyr->x + 48;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = 1;
			live = true;
		}
		else if(!live && plyr->getCurRow() == 7)
		{
			x = plyr->x;
			y = plyr->y + 32;
			yDirect = 1;
			xDirect = -1;
			live = true;
		}
	}

};

class SoulStones : public Objects {
public:
	SoulStones()
	{
		image = NULL;
	}
	SoulStones(ALLEGRO_BITMAP *soulimage)
	{
		maxFrame = 49;
		frameCount = 0;
		frameDelay = 2;
		frameWidth = 64;
		frameHeight = 64;
		
		setCurRow(rand()%19);
		setCurColumn(0);

		boundx = 15;
		boundy = 15;

		hit = false;
		live = true;
		x = rand()%gameWidth - frameWidth;
		y = rand()%gameHeight - frameHeight;

		image = soulimage;
	}
	void updateObj()
	{
		if(live)
		{
			if(++frameCount >= frameDelay)
			{
				if((getCurColumn() + 1) >= 32)
				{
					setCurColumn(0);
				}
				setCurColumn(getCurColumn() + 1);
				frameCount = 0;
			}
		}
		else
		{
			dissapear();
		}	
	}
	void dissapear()
	{
		if(getCurColumn() < 33){
			hit = true;
			setCurColumn(33);
		}
		if(++frameCount >= frameDelay)
		{
			if((getCurColumn() + 1) >= maxFrame)
			{
				hit = false;
				setCurColumn(maxFrame);
			}
			setCurColumn(getCurColumn() + 1);
			frameCount = 0;
		}
	}
	void collidePlayer(Player *plyr)
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
					plyr->soulCount += 1;
					live = false;
				}
			}
		}
	}
	void reset()
	{
		//live = false;
		//setCurRow(0);
		setCurColumn(0);
		frameDelay = 2;
	}
};
class HealthBar : public Sprite {
	public:
	HealthBar()
	{
		image = NULL;
	}
	HealthBar(ALLEGRO_BITMAP *barimage, Sprite *sprite)
	{
		frameWidth = 80;
		frameHeight = 5;
		maxHealth = frameWidth;
		health = maxHealth;

		x = sprite->x+8;
		y = sprite->y;

		image = barimage;
	}
	void draw(Sprite *sprite)
	{
		x = sprite->x;
		y = sprite->y;

		health = static_cast<float>(sprite->health)/static_cast<float>(sprite->maxHealth)*maxHealth;

		al_draw_bitmap_region(image, 0,
			0, health, frameHeight, x, y, 0);
	}


};
class HealPad : public Objects{
public:
	HealPad(ALLEGRO_BITMAP *healimage)
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
	void collidePlayer(Player *plyr)
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
};

void updateCam(float *camPos, float x, float y, float pWidth, float pHeight);
//void destroy();

int main()
{
	//variables
	bool done = false;
	bool keys[10] = {false, false, false, false, false, false, false, false, false, false};
	float camPos[2] = {0,0};
	float enemies = 30;
	const int maxEnemyAmnt = 30;
	const int soulStoneAmnt = 10;
	bool gameOver = false;


	srand(time(0));

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *wizardImage;
	ALLEGRO_BITMAP *fireImage;
	ALLEGRO_BITMAP *waterImage;
	ALLEGRO_BITMAP *enemyImage[maxEnemyAmnt];
	ALLEGRO_BITMAP *earthImage;
	ALLEGRO_BITMAP *windImage;
	ALLEGRO_BITMAP *enemyAtkImage[maxEnemyAmnt];
	ALLEGRO_BITMAP *soulStoneImage[soulStoneAmnt];
	ALLEGRO_BITMAP *healthImage;
	ALLEGRO_BITMAP *healImage;


	ALLEGRO_SAMPLE *trollHit = NULL;
	ALLEGRO_SAMPLE *plyrHit = NULL;
	ALLEGRO_SAMPLE *soulSound = NULL;
	ALLEGRO_SAMPLE *step = NULL;
	ALLEGRO_SAMPLE *atkSound = NULL;
	ALLEGRO_SAMPLE *healSound = NULL;
	ALLEGRO_SAMPLE *tetris = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance4 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance5 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance6 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance7 = NULL;

	ALLEGRO_TRANSFORM camera;
	
	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(screenWidth, screenHeight);			//create our display object

	if(!display)										//test display object
		return -1;


	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(10);

	trollHit = al_load_sample("bwah.wav");
	plyrHit = al_load_sample("uuh.wav");
	soulSound = al_load_sample("disinter.wav");
	step = al_load_sample("step.wav");
	atkSound = al_load_sample("attack.wav");
	healSound = al_load_sample("heal.wav");
	tetris = al_load_sample("tetris.ogg");

	instance1 = al_create_sample_instance(trollHit);
	instance2 = al_create_sample_instance(plyrHit);
	instance3 = al_create_sample_instance(soulSound);
	instance4 = al_create_sample_instance(step);
	instance5 = al_create_sample_instance(atkSound);
	instance6 = al_create_sample_instance(healSound);
	instance7 = al_create_sample_instance(tetris);

	al_set_sample_instance_gain(instance1, 0.8);
	al_set_sample_instance_gain(instance2, 0.75);
	al_set_sample_instance_gain(instance3, 0.6);
	al_set_sample_instance_length(instance4, 0.5);
	al_set_sample_instance_gain(instance6, 0.75);
	al_set_sample_instance_gain(instance7, 0.2);
	al_set_sample_instance_playmode(instance7, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance4, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance5, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance6, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance7, al_get_default_mixer());

	ALLEGRO_FONT *font36 = al_load_font("Dorovar_Carolus.ttf", 36, 0);
	ALLEGRO_FONT *font48 = al_load_font("Dorovar_Carolus.ttf", 48, 0);

	if(MapLoad("mapS.fmp", 1))
		return -5;

	Player *plyr;

	wizardImage = al_load_bitmap("wizard.png");
	al_convert_mask_to_alpha(wizardImage, al_map_rgb(105, 74, 46));
	plyr = new Wizard(wizardImage);

	fireImage = al_load_bitmap("firemagic.png");
	al_convert_mask_to_alpha(fireImage, al_map_rgb(215, 33, 33));
	FireMagic fire(fireImage);

	waterImage = al_load_bitmap("watermagic.png");
	al_convert_mask_to_alpha(waterImage, al_map_rgb(64, 111, 255));
	WaterMagic water(waterImage);

	earthImage = al_load_bitmap("earthmagic.png");
	al_convert_mask_to_alpha(earthImage, al_map_rgb(204, 173, 97));
	EarthMagic earth(earthImage);

	windImage = al_load_bitmap("windmagic.png");
	al_convert_mask_to_alpha(windImage, al_map_rgb(107, 124, 123));
	WindMagic wind(windImage);

	healthImage = al_load_bitmap("healthBar.png");
	HealthBar *pHealth;
	pHealth = new HealthBar(healthImage, plyr);
	
	SoulStones soulStone[soulStoneAmnt];
	for(int i=0; i<soulStoneAmnt; i++){
		soulStoneImage[i] = al_load_bitmap("soulstones.png");
		al_convert_mask_to_alpha(soulStoneImage[i], al_map_rgb(105, 111, 110));
		soulStone[i] = soulStoneImage[i];
	}
	enemyAtk *enemyAttack[maxEnemyAmnt];
	Enemy *enemy[maxEnemyAmnt];
	HealthBar *eHealth[maxEnemyAmnt];
	for(int i=0; i<maxEnemyAmnt; i++){
		if(i%3 == 0){
			enemyImage[i] = al_load_bitmap("lavaTroll.png");
			enemyAtkImage[i] = al_load_bitmap("lavaAtk.png");
			enemy[i] = new LavaTroll(enemyImage[i]);
			enemyAttack[i] = new LavaAtk(enemyAtkImage[i]);
		}
		else if(i%3 == 1){
			enemyImage[i] = al_load_bitmap("iceTroll.png");
			enemyAtkImage[i] = al_load_bitmap("waterAtk.png");
			enemy[i] = new IceTroll(enemyImage[i]);
			enemyAttack[i] = new WaterAtk(enemyAtkImage[i]);
		}
		else{
			enemyImage[i] = al_load_bitmap("greyTroll.png");
			enemyAtkImage[i] = al_load_bitmap("rollstone.png");
			enemy[i] = new GreyTroll(enemyImage[i]);
			enemyAttack[i] = new StoneAtk(enemyAtkImage[i]);
		}
		eHealth[i] = new  HealthBar(healthImage, enemy[i]);
		al_convert_mask_to_alpha(enemyImage[i], al_map_rgb(106, 76, 48));
		al_convert_mask_to_alpha(enemyAtkImage[i], al_map_rgb(97, 68, 43));
	}
	healImage = al_load_bitmap("healpad.bmp");
	al_convert_mask_to_alpha(healImage, al_map_rgb(207, 143, 211));
	HealPad heal(healImage);
	
	Objects *attack = &wind;

	/*backG = al_load_bitmap("map.fmp");
	al_convert_mask_to_alpha(backG, al_map_rgb(106, 76, 48));*/

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_play_sample_instance(instance7);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_R:
					if(!keys[R])
						keys[R] = true;
					else
						keys[R] = false;
					break;
				case ALLEGRO_KEY_1:
					attack = &wind;
					break;
				case ALLEGRO_KEY_2:
					if(enemies <= 25)
						attack = &fire;
					break;
				case ALLEGRO_KEY_3:
					if(enemies <= 27)
						attack = &water;
					break;
				case ALLEGRO_KEY_4:
					if(enemies <= 25)
						attack = &earth;
					break;
				case ALLEGRO_KEY_P:
					if(!keys[P])
						keys[P] = true;
					else
						keys[P] = false;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					if(plyr->getCurColumn() > 9 && plyr->getCurColumn() < 17)
					{
						attack->reset();
					}
					break;
				/*case ALLEGRO_KEY_1:
					keys[ONE] = false;
					break;*/
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if(keys[P])
				for(int i=0; i<9; i++)
					keys[i] = false;
			if(keys[SPACE]){
				if(plyr->hit)
					attack->reset();
				plyr->hit = false;
				plyr->attack();
				attack->startAtk(plyr);
				/*if(attack->live)
					al_play_sample_instance(instance5);*/
			}
			else if(keys[UP] && keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runNE();
				else
					plyr->walkNE();
			}
			else if(keys[UP] && keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runNW();
				else
					plyr->walkNW();
			}
			else if(keys[DOWN] && keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runSE();
				else
					plyr->walkSE();
			}
			else if(keys[DOWN] && keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runSW();
				else
					plyr->walkSW();
			}
			else if(keys[UP]){
				plyr->hit = false;
				if(keys[R])
					plyr->runN();
				else
					plyr->walkN();
			}
			else if(keys[RIGHT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runE();
				else
					plyr->walkE();
			}
			else if(keys[DOWN]){
				plyr->hit = false;
				if(keys[R])
					plyr->runS();
				else
					plyr->walkS();
			}
			else if(keys[LEFT]){
				plyr->hit = false;
				if(keys[R])
					plyr->runW();
				else
					plyr->walkW();
			}
			else
				if(!plyr->hit && !keys[P])
					plyr->stop();
			/*if(keys[R] && (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN]))
				al_play_sample_instance(instance4);*/
			if(!keys[P] && plyr->soulCount != soulStoneAmnt)
			{
				attack->updateObj(plyr);
				for(int i=0; i<soulStoneAmnt; i++){
					soulStone[i].updateObj();
				}
				for(int i=0; i<maxEnemyAmnt; i++){
					if(enemy[i]->live)
					{
						enemy[i]->updateTroll(plyr);
						enemyAttack[i]->startAtk(enemy[i], plyr);
						enemyAttack[i]->updateObj(enemy[i], plyr);
					}
				}
				for(int i=0; i<maxEnemyAmnt; i++){
					if(enemy[i]->getCurColumn() >= 42)
						enemies -= static_cast<float>(1)/static_cast<float>(5);
				}
				if(attack->getCurRow() > 0 && attack->getCurColumn() > 2 && keys[SPACE])
					plyr->stop();
			}
			updateCam(camPos, plyr->x, plyr->y, plyr->frameWidth, plyr->frameHeight);

			al_identity_transform(&camera);
			al_translate_transform(&camera, -camPos[0], -camPos[1]);
			al_use_transform(&camera);

			for(int i=0; i<maxEnemyAmnt; i++){
				attack->collideEnemy(enemy[i]);
				if(enemy[i]->hit)
					al_play_sample_instance(instance1);
			}
			for(int i=0; i<maxEnemyAmnt; i++){
				enemyAttack[i]->collidePlayer(plyr);
				if(plyr->hit && plyr->live)
					al_play_sample_instance(instance2);
			}
			for(int i=0; i<soulStoneAmnt; i++){
				soulStone[i].collidePlayer(plyr);
				if(soulStone[i].hit)
					al_play_sample_instance(instance3);
			}
			heal.collidePlayer(plyr);
			if(heal.hit)
				al_play_sample_instance(instance6);
		}
		/*al_draw_bitmap(backG, screenWidth / 2 - 4224 / 2, screenHeight / 2 - 768 / 2, 0);*/
		/*al_draw_bitmap(backG, 0, 0, 0);*/
		MapDrawBG(0, 0, 0, 0, gameWidth, gameHeight);
		heal.draw();
		for(int i=0; i<soulStoneAmnt; i++)
		{
			soulStone[i].draw();
		}
		for(int i=0; i<maxEnemyAmnt; i++)
		{
			if(enemy[i]->live){
				enemy[i]->draw();
				eHealth[i]->draw(enemy[i]);
				if(enemyAttack[i]->live)
					enemyAttack[i]->draw();
			}
		}
		if(plyr->live)
		{
			if(attack->live && plyr->getCurRow() == 2)
			{
				plyr->draw();
				attack->draw();
			}
			if(attack->live && (plyr->getCurRow() == 0 || plyr->getCurRow() == 4 || plyr->getCurRow() == 5))
			{
				attack->draw();
				plyr->draw();
			}
			else
			{
				plyr->draw();
				if(attack->live)
					attack->draw();
			}
		}
		else
			gameOver = true;
		//al_draw_bitmap(healPad, healPadx, healPady, 0);
		pHealth->draw(plyr);
		/*plyr->health = static_cast<int>(plyr->health);*/
		al_draw_textf(font36, al_map_rgb(255,255,255), camPos[0]+5, camPos[1]+5, 0,
			"Health : %i", plyr->health);
		al_draw_textf(font36, al_map_rgb(255,255,255), camPos[0]+5, camPos[1]+35, 0,
			"Soul Stones Collected : %i / %i", plyr->soulCount, soulStoneAmnt);
		if(enemies <= 27)
		{
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+65, 0,
				"Attack Unlocked :  key2");
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+95, 0,
				"Attack Unlocked :  key3");
		}
		if(enemies <= 25)
		{
			al_draw_text(font36, al_map_rgb(242,251,85), camPos[0]+5, camPos[1]+125, 0,
				"Attack Unlocked :  key4");
		}
		if(keys[P])
			al_draw_text(font48, al_map_rgb(255, 255, 255), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "pause");
		if(plyr->soulCount == soulStoneAmnt)
		{
			for(int i=0; i<maxEnemyAmnt; i++)
				enemy[i]->disintegrate();
			al_draw_text(font48, al_map_rgb(255, 255, 0), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "WINNER");
		}
		if(gameOver)
			al_draw_text(font48, al_map_rgb(255, 0, 0), camPos[0]+screenWidth/2, camPos[1]+screenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");


		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	MapFreeMem();
	al_destroy_bitmap(wizardImage);
	al_destroy_bitmap(healthImage);
	al_destroy_bitmap(waterImage);
	al_destroy_bitmap(fireImage);
	al_destroy_bitmap(earthImage);
	al_destroy_bitmap(windImage);
	al_destroy_bitmap(healImage);
	al_destroy_sample(trollHit);
	al_destroy_sample(plyrHit);
	al_destroy_sample(soulSound);
	al_destroy_sample(step);
	al_destroy_sample(atkSound);
	al_destroy_sample(healSound);
	al_destroy_sample_instance(instance1);
	al_destroy_sample_instance(instance2);
	al_destroy_sample_instance(instance3);
	al_destroy_sample_instance(instance4);
	al_destroy_sample_instance(instance5);
	al_destroy_sample_instance(instance6);
	for(int i=0; i<soulStoneAmnt; i++)
		al_destroy_bitmap(soulStoneImage[i]);
	for(int i=0; i<maxEnemyAmnt; i++){
		al_destroy_bitmap(enemyImage[i]);
		al_destroy_bitmap(enemyAtkImage[i]);
		delete enemy[i];
		delete eHealth[i];
		delete enemyAttack[i];
	}
	delete plyr;
	delete pHealth;
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);	

	return 0;
}
void updateCam(float *camPos, float x, float y, float pWidth, float pHeight)
{
	camPos[0] = -(screenWidth/2) + (x + pWidth/2);
	camPos[1] = -(screenHeight/2) + (y + pHeight/2);

	if(camPos[0] < 0)
		camPos[0] = 0;
	if(camPos[1] < 0)
		camPos[1] = 0;
}