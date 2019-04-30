/************************************************************
*File    : PongTable.h
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : Header file for all the objects in the pong game
************************************************************/

#include "PongObject.h"

#ifndef PONGTABLE_H
#define PONGTABLE_H

class PongTable {

public:

	PongTable();

	PongObject* getBall();

	PongObject* getTopWall();

	PongObject* getBottomWall();

	PongObject* getLeftWall();

	PongObject* getRightWall();

	void render(HDC console, float lag);

	bool collisions();

	PongObject* getComputerPaddle();

	void moveComputerPaddle();

	PongObject* getPlayerPaddle();

private:

	PongObject ball;

	PongObject topWall;

	PongObject bottomWall;

	PongObject leftWall;

	PongObject rightWall;

	PongObject computerPaddle;

	PongObject playerPaddle;

	Position ballHitsPaddle(PongObject paddle);
};

#endif // ends the ifndef PONGTABLE_H