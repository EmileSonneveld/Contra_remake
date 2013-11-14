//-----------------------------------------------------------------
// AbstractGame Object
// C++ Header - AbstractGame.h - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//
// AbstractGame is the abstract class which defines the functions that a 
// game class can implement for use in the game engine
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

//-----------------------------------------------------------------
// AbstractGame Class
//-----------------------------------------------------------------
class AbstractGame
{
public : 	
	AbstractGame() 
	{
		// nothing to create
	}

	virtual ~AbstractGame() 
	{
		// nothing to destroy
	}

	virtual void GameInitialize(HINSTANCE hInstance);											// defined in cpp file
	virtual void GameStart(void) {}																// empty definition
	virtual void GameEnd(void) {}																// empty definition
	virtual void GameActivate() {}																// empty definition
	virtual void GameDeactivate() {}															// empty definition
	virtual void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) {}	// empty definition
	virtual void MouseMove(int x, int y, WPARAM wParam) {}										// empty definition
	virtual void CheckKeyboard(void) {}															// empty definition
	virtual void KeyPressed(TCHAR cKey) {}														// empty definition
	virtual void GamePaint(RECT rect) {}														// empty definition
	virtual void GameTick(double deltaTime) {}													// empty definition

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	AbstractGame(const AbstractGame& agRef);
	AbstractGame& operator=(const AbstractGame& agRef);
};