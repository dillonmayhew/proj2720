//#include <iostream>
#include "Sprite.h"
#include "Player.h"

void Player::runDirect(DIRECTION D)
{
	switch(D)
	{
	case 0:
		y -= runSpeed;
		break;
	case 1:
		x += runSpeed;
		break;
	case 2:
		y += runSpeed;
		break;
	case 3:
		x -= runSpeed;
		break;
	case 4:
		x += runSpeed;
		y -= runSpeed;
		break;
	case 5:
		x -= runSpeed;
		y -= runSpeed;
		break;
	case 6:
		x += runSpeed;
		y += runSpeed;
		break;
	case 7:
		x -= runSpeed;
		y += runSpeed;
		break;
	default:
		break;
	}
}
void Player::run(DIRECTION D)
{
	if(getCurRow() != D)
		setCurRow(D);
	if(getCurColumn() < 31)
		setCurColumn(31);
	runDirect(D);
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
	if(x < 0)
		x = 0;
	if(x > gameWidth - frameWidth)
		x = gameWidth - frameWidth;
	if(y > gameHeight - frameHeight)
		y = gameHeight - frameHeight;
}
void Player::beenHit()
{
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
void Player::attack()
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
void Player::stop()
{
	setCurColumn(0);
}