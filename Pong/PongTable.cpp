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

	// camputer paddle
	Position aiPaddlePos;
	aiPaddlePos.xValue = rightWall.getCurrent().xValue - PADDLE_OFFSET - PADDLE_WIDTH;
	aiPaddlePos.yValue = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	computerPaddle = PongObject(PADDLE_HEIGHT, PADDLE_WIDTH, aiPaddlePos, { 0, 0 }, { 0, 0 }, false);

	// player paddle
	Position playerPaddlePos;
	playerPaddlePos.xValue = leftWall.getCurrent().xValue + PADDLE_OFFSET + PADDLE_WIDTH;
	playerPaddlePos.yValue = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	playerPaddle = PongObject(PADDLE_HEIGHT, PADDLE_WIDTH, playerPaddlePos, { 0, 0 }, { 0, 0 }, false);
}

PongObject* PongTable::getBall() { return &ball; }

PongObject* PongTable::getBottomWall() { return &bottomWall; }

PongObject* PongTable::getTopWall() { return &topWall; }

PongObject* PongTable::getLeftWall() { return &leftWall; }

PongObject* PongTable::getRightWall() { return &rightWall; }

PongObject* PongTable::getComputerPaddle() { return &computerPaddle; }

PongObject* PongTable::getPlayerPaddle() { return &playerPaddle; }

void PongTable::render(HDC console, float lag) {
	//draw the ball
	ball.render(console, lag);

	//draw the computer paddle
	computerPaddle.render(console, lag);

	//draw the player's paddle
	playerPaddle.render(console, lag);

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
bool PongTable::collisions() {
	bool gameEnd = false;

	Position ballCurrent = ball.getCurrent();
	Position ballVelocity = ball.getVelocity();

	// ball collides with computer paddle
	if (ball.intersects(&computerPaddle)) {
		ballCurrent.xValue = computerPaddle.getCurrent().xValue - ball.getWidth() - 1;
		ballVelocity.xValue *= -1;
		computerPaddle.setDirty(true);
	}
	// ball collides with player's paddle
	else if (ball.intersects(&playerPaddle)) {
		ballCurrent.xValue = playerPaddle.getCurrent().xValue + ball.getWidth() + 1;
		ballVelocity.xValue *= -1;
		computerPaddle.setDirty(true);
	}
	//ball with left wall
	else if (ball.intersects(&leftWall)) {
		ballCurrent.xValue = leftWall.getCurrent().xValue + leftWall.getWidth() + 1;
		ballVelocity.xValue *= -1;
		leftWall.setDirty(true);
		gameEnd = true;
	}
	//ball with right wall
	else if (ball.intersects(&rightWall)) {
		ballCurrent.xValue = rightWall.getCurrent().xValue - ball.getWidth() - 1;
		ballVelocity.xValue *= -1;
		rightWall.setDirty(true);
		gameEnd = true;
	}
	//ball with top wall
	else if (ball.intersects(&topWall)) {
		ballCurrent.yValue = topWall.getCurrent().yValue + topWall.getHeight() + 1;
		ballVelocity.yValue *= -1;
		topWall.setDirty(true);
	}
	//ball with bottom wall
	else if (ball.intersects(&bottomWall)) {
		ballCurrent.yValue = bottomWall.getCurrent().yValue - ball.getHeight() - 1;
		ballVelocity.yValue *= -1;
		bottomWall.setDirty(true);
	}

	ball.setCurrent(ballCurrent);
	ball.setVelocity(ballVelocity);

	//collision check for the Computer paddle and the walls
	Position computerPaddleCurrent = computerPaddle.getCurrent();
	Position computerPaddleVelocity = computerPaddle.getVelocity();

	if (computerPaddle.intersects(&topWall)) {
		computerPaddleCurrent.yValue = topWall.getCurrent().yValue + topWall.getHeight() + 1;
		computerPaddleVelocity.yValue = 0.0;
		topWall.setDirty(true);
	}
	else if (computerPaddle.intersects(&bottomWall)) {
		computerPaddleCurrent.yValue = bottomWall.getCurrent().yValue - PADDLE_HEIGHT - 1;
		computerPaddleVelocity.yValue = 0.0;
		bottomWall.setDirty(true);
	}

	computerPaddle.setCurrent(computerPaddleCurrent);
	computerPaddle.setVelocity(computerPaddleVelocity);

	//collision check for the Player's paddle and the walls
	Position playerPaddleCurrent = playerPaddle.getCurrent();
	Position playerPaddleVelocity = playerPaddle.getVelocity();

	if (playerPaddle.intersects(&topWall)) {
		playerPaddleCurrent.yValue = topWall.getCurrent().yValue + topWall.getHeight() + 1;
		playerPaddleVelocity.yValue = 0.0;
		topWall.setDirty(true);
	}
	else if (playerPaddle.intersects(&bottomWall)) {
		playerPaddleCurrent.yValue = bottomWall.getCurrent().yValue - PADDLE_HEIGHT - 1;
		playerPaddleVelocity.yValue = 0.0;
		bottomWall.setDirty(true);
	}

	playerPaddle.setCurrent(playerPaddleCurrent);
	playerPaddle.setVelocity(playerPaddleVelocity);

	return gameEnd;
}

// moves the paddle of the AI
void PongTable::moveComputerPaddle() {
	Position ballCurrent = ball.getCurrent();
	Position computerPaddleCurrent = computerPaddle.getCurrent();
	Position computerPaddleVelocity = computerPaddle.getVelocity();

	float paddleTop = computerPaddleCurrent.yValue;
	float paddleBottom = paddleTop + computerPaddleCurrent.yValue;
	paddleTop += PADDLE_HEIGHT / 3;
	paddleBottom -= PADDLE_HEIGHT / 3;
	float ballTop = ballCurrent.yValue;
	float ballBottom = ballTop + ballCurrent.yValue;

	if (ballBottom < paddleTop) {
		computerPaddleVelocity.yValue -= 0.02;
	}
	else if (ballTop > paddleTop) {
		computerPaddleVelocity.yValue += 0.02;
	}
	else {
		computerPaddleVelocity.yValue = 0.0;
	}

	computerPaddle.setVelocity(computerPaddleVelocity);
}