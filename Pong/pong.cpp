/************************************************************
*File    : pong.cpp
*Author  : Zachary Maroney
*Class   : COP 2001 201901 10410
*Purpose : main application file for the game pong
************************************************************/

#include <iostream>    // input/output
#include <time.h>      // for timing methods
#include "pong.h"      // main application
#include "PongTable.h" // Pong game object

using namespace std;

// function prototype
HDC initConsole();

Input playerInput();

bool update(PongTable& table);

bool inPlayerInput(PongTable& table);

int main()
{
	/* inialize console window and get
	a handle to its device context
	for drawing */
	HDC hdc = initConsole();

	/*************************************************************************/
	/*Declare and initialize time component
	for frame rate calculation*/
	LARGE_INTEGER frequency;        // factor of how fast the CPU clock ticks
	LARGE_INTEGER lastTime;         // when the last frame started
	LARGE_INTEGER currentTime;      // when the current frame started
	LARGE_INTEGER elapsedTime;       // time between last and current
	float deltaTime = 0;            // left over frame time

									// get cpu clock frequency
	QueryPerformanceFrequency(&frequency);

	// set starting current time to now
	QueryPerformanceCounter(&currentTime);

	// set initial last time to starting time
	lastTime = currentTime;
	/*************************************************************************/

	PongTable table = PongTable();

	// call to draw function
	table.render(hdc, 0);

	bool quit = update(table);

	// player input
	while (!quit)	// not exit
	{
		// get current frame times
		QueryPerformanceCounter(&currentTime);
		// get time elapsed between last frame and the start of this one
		elapsedTime.QuadPart = currentTime.QuadPart - lastTime.QuadPart;
		//set last frame to current
		lastTime = currentTime;
		// add to delta the current elapsed time converted to MS divided by the CPU Freq
		deltaTime += (double)elapsedTime.QuadPart * 1000 / (double)frequency.QuadPart;

		quit = inPlayerInput(table);

		while (deltaTime >= FRAME_RATE) {

			quit = update(table);

			deltaTime -= FRAME_RATE;
		}

		// call to draw funtion
		table.render(hdc, (deltaTime / FRAME_RATE));
	}

	return 0;
}
/**********************************************************
* Initializes the console window for drawing, and returns
* a handle to a drawing context for the console.
* @returns HDC	- handle to console's device context
**********************************************************/
HDC initConsole()
{
	//Get a handle to console window
	HWND conWindow = GetConsoleWindow();

	//Get handle to console standard output stream
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get a handle to a device context for drawing on the console
	HDC conDc = GetDC(conWindow);

	// resize the console window
	RECT conDimensions;
	GetWindowRect(conWindow, &conDimensions);
	MoveWindow(conWindow, conDimensions.left, conDimensions.top, SCREEN_WIDTH + 36, SCREEN_HEIGHT + 42, true);

	// turn off the blinking cursor
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(conOut, &cursor);

	return conDc;
}

/**********************************************************
* reads player input and moves the pixels accordingly with
* either the WASD keys or the arrow keys.
* @returns Input - none, up, down, left, right, exit
**********************************************************/
Input playerInput()
{
	Input input = NONE;	// return direction to move

						//define key constants for WASD (hex literals)
	const WORD VK_W = 0x57;
	const WORD VK_A = 0x41;
	const WORD VK_S = 0x53;
	const WORD VK_D = 0x44;
	const WORD VK_X = 0x58;

	//Get handle to console standard input stream
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD eventBuff[128];				// event buffer
	unsigned long eventCount, eventsRead, i;

	// see if there are any events on the standard input stream
	GetNumberOfConsoleInputEvents(hin, &eventCount);

	if (eventCount > 0)
	{
		// read all events availabe into an array buffer
		ReadConsoleInput(
			hin,
			eventBuff,
			128,
			&eventsRead);

		/* see if any of the events read are keyboard events
		and specifically one of the keys we care about */
		i = 0;
		while (input == NONE && i < eventsRead)
		{
			if (eventBuff[i].EventType == KEY_EVENT)
			{
				switch (eventBuff[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_W:		// player hit W key
				case VK_UP:		// or up arrow
					input = UP;	// move up
					break;

				case VK_S:		// player hit S key
				case VK_DOWN:	// or down arrow
					input = DOWN;  // move down
					break;

				case VK_A:		// player hit A key
				case VK_LEFT:	// or left arrow
					input = LEFT;  // move left
					break;

				case VK_D:		// player hit D key
				case VK_RIGHT:	// or right arrow
					input = RIGHT;  // move right
					break;

				case VK_X:		// player hit X key
					input = QUIT;	// exit game
					break;

				default:		// some other key was pressed
					input = NONE;
				} //end case statement

			} // end keyboard event type

			i++;
		} // end while events exist

	}

	// get rid of any other input in the stream
	FlushConsoleInputBuffer(hin);

	return input;
}

/***************************************************************
* Calls playerInput and adjust the player's paddles velocity
* @param {PongObject} location - current location and
* velocity of ball (in/out)
* return quit - if true then it quits the program
****************************************************************/
bool inPlayerInput(PongTable& table) {
	bool quit = false;

	PongObject *playerPaddle = table.getPlayerPaddle();

	Position paddleVelocity = playerPaddle->getVelocity();

	// get user input
	Input input = playerInput();

	switch (input)
	{
	case UP: 
			paddleVelocity.yValue -= 1;
		break;
	case DOWN: 		
		paddleVelocity.yValue += 1;
		break;
	/*case LEFT: velocity.xValue -= .25;
		break;
	case RIGHT: velocity.xValue += .25;
		break; */
	case QUIT: quit = true;
		break;
	case NONE:
		break;
	}

	playerPaddle->setVelocity(paddleVelocity);

	// call to MoveComputer Paddle
	table.moveComputerPaddle();

	return quit;
}

/***************************************************************
* updates the x and y velocity to what ever the user inputs
* @param {PongObject} location - current location and
* velocity of ball (in/out)
****************************************************************/
bool update(PongTable& table)
{
	bool gameEnd = false;

	PongObject *ball = table.getBall();
	PongObject *computerPaddle = table.getComputerPaddle();
	PongObject *playerPaddle = table.getPlayerPaddle();

	Position ballCurrent = ball->getCurrent();
	Position ballVelocity = ball->getVelocity();

	Position computerPaddleCurrent = computerPaddle->getCurrent();
	Position computerPaddleVelocity = computerPaddle->getVelocity();

	Position playerPaddleCurrent = playerPaddle->getCurrent();
	Position playerPaddleVelocity = playerPaddle->getVelocity();

	// Add or subtract velocity from ball X/y pos
	ballCurrent.xValue += ballVelocity.xValue;
	ballCurrent.yValue += ballVelocity.yValue;

	ball->setCurrent(ballCurrent);

	// add or subtract velocity from computer paddle x/y
	computerPaddleCurrent.yValue += computerPaddleVelocity.yValue;
	
	computerPaddle->setCurrent(computerPaddleCurrent);

	// updates the location of player's paddle
	playerPaddleCurrent.yValue += playerPaddleVelocity.yValue;

	// added this for extra credit to slow the player's paddld down to zero from what ever direction the paddle is going.
	if (playerPaddleVelocity.yValue > 0.0) {
		playerPaddleVelocity.yValue -= .06;
		playerPaddle->setVelocity(playerPaddleVelocity);
	}
	else if (playerPaddleVelocity.yValue < 0.0) {
		playerPaddleVelocity.yValue += .06;
		playerPaddle->setVelocity(playerPaddleVelocity);
	}

	playerPaddle->setCurrent(playerPaddleCurrent);


	// call to collisions funtion
	gameEnd = table.collisions();

	return gameEnd;
}