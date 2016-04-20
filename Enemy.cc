#include "Enemy.h"

bool Enemy::isClose(Player *plyr)
{
	if( plyr->x+24 - x < 500 && plyr->x+24 - x > -500 &&
		plyr->y+12 - y < 500 && plyr->y+12 - y > -500)
		return true;
	else
		return false;
}
void Enemy::moveTowards(Player *plyr)
{
	facePlyr(plyr);
	if(getCurRow() == 0)
		walk(N);
	if(getCurRow() == 1)
		walk(E);
	if(getCurRow() == 2)
		walk(S);
	if(getCurRow() == 3)
		walk(W);
	if(getCurRow() == 4)
		walk(NE);
	if(getCurRow() == 5)
		walk(NW);
	if(getCurRow() == 6)
		walk(SE);
	if(getCurRow() == 7)
		walk(SW);
}
bool Enemy::inAtkDist(Player *plyr)
{
	if( plyr->x+24 - x < 250 && plyr->x+24 - x > -250 &&
		plyr->y+12 - y < 250 && plyr->y+12 - y > -250)
		return true;
	else
		return false;
}
void Enemy::facePlyr(Player *plyr)
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
void Enemy::attack(Player *plyr)
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
void Enemy::stop()
{
	setCurColumn(0);
}
void Enemy::updateTroll(Player *plyr)
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
void Enemy::beenHit()
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