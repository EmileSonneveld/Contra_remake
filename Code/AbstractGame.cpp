//-----------------------------------------------------------------
// AbstractGame Object
// C++ Source - AbstractGame.cpp - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "../Resource.h"	// include file to use resources
#include "GameEngine.h" // include file to use the game engine
#include "AbstractGame.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// AbstractGame methods
//-----------------------------------------------------------------

void AbstractGame::GameInitialize(HINSTANCE hInstance)
{
	// Set the required values
	GAME_ENGINE->SetTitle("Game Engine version 2_10");
	GAME_ENGINE->SetIcon(IDI_BIG);
	GAME_ENGINE->SetSmallIcon(IDI_SMALL);
	//GAME_ENGINE->RunGameLoop(true);
	
	// Set the optional values
	GAME_ENGINE->SetWidth(640);
	GAME_ENGINE->SetHeight(480);
	GAME_ENGINE->SetFrameRate(50);
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);
}