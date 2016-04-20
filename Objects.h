#ifndef OBJECTS_H
#define OBJECTS_H

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"

enum ATTACK{FIREMAGIC, WATERMAGIC, EARTHMAGIC, WINDMAGIC};

class Objects : public Sprite {
public:
	ATTACK ID;
	int speed;
	int xDirect;
	int yDirect;
	int maxFrame;

	virtual void updateObj(Player *plyr);
	virtual void reset();
	virtual void initAtk(Player *plyr);
	virtual void startAtk(Player *plyr);
	void collideEnemy(Enemy *enemy);
	virtual void collidePlayer(Player *plyr){}

};
#endif