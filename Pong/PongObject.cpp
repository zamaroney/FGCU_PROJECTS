/************************************************************
*File    : PongObject.cpp
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : Implimentaion file of a pong game object such
           as the ball, paddle and walls
************************************************************/
#include "PongObject.h"

/***CONSTRUCTORS***/

/**/
PongObject::PongObject() {
	height = 0;
	width = 0;
	current = { 0.0f, 0.0f };
	previous = { 0.0f, 0.0f };
	velocity = { 0.0f, 0.0f };
	ballIndicator = false;
	dirty = true;
}

/**/
PongObject::PongObject(int hieghtIn, int widthIn, Position currentIn, Position previousIn, Position velocityIn, bool ballIndicatorIn) {
	height = hieghtIn;
	width = widthIn;
	current = currentIn;
	previous = previousIn;
	velocity = velocityIn;
	ballIndicator = ballIndicatorIn;
	dirty = true;
}

/***ACESSOR METHODS***/
Position PongObject::getCurrent() { return current; }
Position PongObject::getPrevious() { return previous; }
Position PongObject::getVelocity() { return velocity; }

int PongObject::getHeight() { return height; }
int PongObject::getWidth() { return width; }

bool PongObject::isBall() { return ballIndicator; }

bool PongObject::isDirty() { return dirty; }

/***SETTER METHODS***/
void PongObject::setCurrent(Position value) { current = value; }
void PongObject::setPrevious(Position value) { previous = value; }
void PongObject::setVelocity(Position value) { velocity = value; }

void PongObject::setHeight(int value) { height = value; }
void PongObject::setWidth(int value) { width = value; }

void PongObject::setBall(bool value) { ballIndicator = value; }

void PongObject::setDirty(bool value) { dirty = value; }

/***HELPER METHODS***/

Position PongObject::getCurrent(float lag) {
	float xpos = current.xValue + (lag*velocity.xValue);
	float ypos = current.yValue + (lag*velocity.yValue);

	return {xpos, ypos};
}

bool PongObject::hasMoved(float lag) {
	Position adjusted = getCurrent(lag);

	return int(adjusted.xValue)!= int(previous.xValue)||int(adjusted.yValue)!=int(previous.yValue);
}

void PongObject::erase(HDC console) {
	int xpos = previous.xValue;
	int ypos = previous.yValue;

	// runs through the array
	for (int row = 0; row <= height - 1; row++)
	{
		for (int col = 0; col <= width - 1; col++)
		{
			SetPixel(console, xpos + col, ypos + row, BLACK);
		}
	}
}

void PongObject::draw(HDC console, float lag) {
	Position adjusted = getCurrent(lag);

	int xpos = adjusted.xValue;
	int ypos = adjusted.yValue;

	// runs through the array
	for (int row = 0; row <= height - 1; row++)
	{
		for (int col = 0; col <= width - 1; col++)    
		{
			COLORREF paint = PAINT;
			if (isBall()) {
				paint = BALL_PATTERN[row][col];
			}
			SetPixel(console, xpos + col, ypos + row, paint);
		}
	}
	setPrevious(adjusted);

}

void PongObject::render(HDC console, float lag) {
	if (hasMoved(lag) || isDirty()) {
		erase(console);
		draw(console, lag);
		setDirty(false);
	}
}

bool PongObject::intersects(PongObject* other) {
	float thisTop = current.yValue;
	float thisBottom = current.yValue + height;
	float thisLeft = current.xValue;
	float thisRight = current.xValue + width;
	float otherTop = other->getCurrent().yValue;
	float otherBottom = other->getCurrent().yValue + other->getHeight();
	float otherLeft = other->getCurrent().xValue;
	float otherRight = other->getCurrent().xValue + other->getWidth();

	return !(otherLeft > thisRight
		|| otherRight < thisLeft
		|| otherTop > thisBottom
		|| otherBottom < thisTop);
}