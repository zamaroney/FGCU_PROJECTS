/************************************************************
*File    : PongObject.h
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : header file of a pong game object such
           as the ball, paddle and walls
************************************************************/
#include "pong.h"

#ifndef PONGOBJECT_H
#define PONGOBJECT_H

class PongObject {
	
public:
	PongObject();

	PongObject(int heightIn, int widthIn, Position currentIn, Position previousIn, Position velocityIn, bool ballIndicatorIn);

	Position getCurrent();
	Position getPrevious();
	Position getVelocity();

	void setCurrent(Position value);

	void setPrevious(Position value);
	void setVelocity(Position value);
	
	Position getCurrent(float lag);

	bool hasMoved(float lag);

	int getHeight();
	int getWidth();

	void setHeight(int value);
	void setWidth(int value);

	bool isBall();

	void setBall(bool value);

	void erase(HDC console);

	void draw(HDC console, float lag);

	void render(HDC console, float lag);

	bool intersects(PongObject* other);

	bool isDirty();

	void setDirty(bool dirty);

private:
	Position current;
	Position previous;
	Position velocity;

	int height;
	int width;

	bool ballIndicator;

	bool dirty;

}; // end class PongObject

#endif
