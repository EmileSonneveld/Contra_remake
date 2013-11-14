//-----------------------------------------------------------------
// Game File
// C++ Header - Contra.h - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

//#include "../Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"
#include "ObjectBaseList.h"

#include "Player.h" 

//-----------------------------------------------------------------
// Contra Class																
//-----------------------------------------------------------------
class Contra : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Contra();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Contra();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	void GameEnd();
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	//void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	//void KeyPressed(TCHAR cKey);
	void GameTick(double deltaTime);
	void GamePaint(RECT rect);

	//void CallAction(Caller* callerPtr);

	// -------------------------
	// Member functions
	// -------------------------

private:
	// -------------------------
	// Member functions
	// -------------------------
	void Draw_Hitregions();
	void DoCameraMovement(double deltaTime, DOUBLE2 playerPos);

	// -------------------------
	// Datamembers
	// -------------------------
	double m_GameSize;

	// Spawners
	static const int NUM_SPAWNERS= 3;
	DOUBLE2 m_SpawnersArr[NUM_SPAWNERS];
	double m_SpawnTime;

	Player *m_PlayerPtr;
	
	DOUBLE2 m_PosCamera, m_LevelMax, m_MousePos;

	ObjectList * m_ObjectListPtr;
	Bitmap * m_BmpBackgroundPtr;
	HitRegion * m_HitTerrainPtr;

	MATRIX3X2 m_MatView;
	double m_ViewScale;

	int m_PersonageNum;

	bool m_LetsMakeSound;
	Audio *m_MusicPtr;
	//Grid *m_GridPtr;

	// Power up's constants
	int m_BulletType; // eigenlijk powerUpType
	static const int BULLET_NORMAL		= 0;
	static const int BULLET_MITRAILLEUR	= 1;
	static const int BULLET_SUPER		= 2;
	static const int BULLET_LAZER		= 3;
	static const int BULLET_FLAME		= 4;
	static const int BULLET_R			= 5; // Score ofzo?

	void PlaceEnemys(ObjectList * objectListPtr);

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Contra(const Contra& tRef);
	Contra& operator=(const Contra& tRef);
};
