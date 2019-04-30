/************************************************************
*File    : pong.cpp
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : Header file for the game pong
************************************************************/

#include <Windows.h>

#ifndef PONG_H
#define PONG_H

// screen dimensions
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 256;

// define color constants
const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF PAINT = WHITE;

// Update Frame Rate in Milliseconds
const float FRAME_RATE = 1000 / 60; // = 16.66666666

// ball dimenstions
const int BALL_WIDTH = 6;
const int BALL_HEIGHT = 6;

// Screen dimension Constants
const int SCREEN_OFFSET = 2;   // distance walls are from the screen edge

// wall dimension constants
const int WALL_THICKNESS = 1;   // how thick is a wall in pixels

// paddle dimensions constants
const int PADDLE_HEIGHT = 28;
const int PADDLE_WIDTH = 2;
const int PADDLE_OFFSET = 4;   // distance from the wall

// max velocity of the computer paddle
const int MAX_VELOCITY = 2;

// ball dimension constant
const int BALL_START_X = SCREEN_OFFSET + PADDLE_OFFSET + PADDLE_WIDTH + 10;
const int BALL_START_Y = SCREEN_HEIGHT / 2 - 10;
const int BALL_START_VEL_X = 2;
const int BALL_START_VEL_Y = -1;

// Key inputs and directives
enum Input {
	QUIT,
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

// Position coordinate structure
struct Position {
	float xValue;
	float yValue;
};

// Patterm pf 6x6 ball
const COLORREF BALL_PATTERN[BALL_HEIGHT][BALL_WIDTH] = {
	{ BLACK, BLACK, PAINT, PAINT, BLACK, BLACK },
	{ BLACK, PAINT, PAINT, PAINT, PAINT, BLACK },
	{ PAINT, PAINT, PAINT, PAINT, PAINT, PAINT },
	{ PAINT, PAINT, PAINT, PAINT, PAINT, PAINT },
	{ BLACK, PAINT, PAINT, PAINT, PAINT, BLACK },
	{ BLACK, BLACK, PAINT, PAINT, BLACK, BLACK } };

#endif // ends the ifndef PONG.H