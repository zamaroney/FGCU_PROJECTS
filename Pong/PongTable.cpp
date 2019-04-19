/************************************************************
*File    : PongTable.h
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : Implimentation file for all the objects in the pong game
************************************************************/

#include "PongTable.h"

PongTable::PongTable() {
	Position ballCurrent = { BALL_START_X, BALL_START_Y };
	Position ballPrevious = { 0, 0 };
	Position ballVelocity= { BALL_START_VEL_X, BALL_START_VEL_Y };
	ball = PongObject(BALL_HEIGHT, BALL_WIDTH, ballCurrent, ballPrevious, ballVelocity, true);

	// top wall
	int topHeight = WALL_THICKNESS;
	int topWidth = SCREEN_WIDTH - (2 * SCREEN_OFFSET);
	Position topCurrent = { SCREEN_OFFSET, SCREEN_OFFSET };
	Position topPrevious = { 0, 0 };
	Position topVelocity = { 0,0 };
	topWall = PongObject(topHeight, topWidth, topCurrent, topPrevious, topVelocity, false);

	// bottom wall
	int bottomHeight = WALL_THICKNESS;
	int bottomWidth = SCREEN_WIDTH - (2 * SCREEN_OFFSET);
	Position bottomCurrent = { SCREEN_OFFSET, SCREEN_HEIGHT - SCREEN_OFFSET - WALL_THICKNESS };
	Position bottomPrevious = { 0, 0 };
	Position bottomVelocity = { 0,0 };
	bottomWall = PongObject(bottomHeight, bottomWidth, bottomCurrent, bottomPrevious, bottomVelocity, false);

	// left wall
	int leftHeight = SCREEN_HEIGHT - (2 * SCREEN_OFFSET);
	int leftWidth = WALL_THICKNESS;
	Position leftCurrent = { SCREEN_OFFSET, SCREEN_OFFSET };
	Position leftPrevious = { 0, 0 };
	Position leftVelocity = { 0,0 };	
	leftWall = PongObject(leftHeight, leftWidth, leftCurrent, leftPrevious, leftVelocity, false);

	// right wall
	int rightHeight = SCREEN_HEIGHT - (2 * SCREEN_OFFSET);
	int rightWidth = WALL_THICKNESS;
	Position rightCurrent = { SCREEN_WIDTH - SCREEN_OFFSET - WALL_THICKNESS, SCREEN_OFFSET };
	Position rightPrevious = { 0, 0 };
	Position rightVelocity = { 0,0 };
	rightWall = PongObject(rightHeight, rightWidth, rightCurrent, rightPrevious, rightVelocity, false);
}

PongObject* PongTable::getBall() { return &ball; }

PongObject* PongTable::getBottomWall() { return &bottomWall; }

PongObject* PongTable::getTopWall() { return &topWall; }

PongObject* PongTable::getLeftWall() { return &leftWall; }

PongObject* PongTable::getRightWall() { return &rightWall; }

void PongTable::render(HDC console, float lag) {
	//draw the ball
	ball.render(console, lag);

	//draw bottom wall
	bottomWall.render(console, 0);

	//draw top wall
	topWall.render(console, 0);

	//draw left wall
	leftWall.render(console, 0);

	//draw right wall
	rightWall.render(console, 0);

}

// checks for collisions of the ball with the walls
void PongTable::collisions() {
	Position ballCurrent = ball.getCurrent();
	Position ballVelocity = ball.getVelocity();

}