#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// EnemySniper Class
//-----------------------------------------------------
class EnemySniper : public ObjectBase
{
public:
	EnemySniper(DOUBLE2 pos);
	virtual ~EnemySniper();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	void SetPlayerPtr(ObjectBase *playerPtr) { m_PlayerPtr = playerPtr; }
	int Sign(double getal) { return (getal > 0) - (getal < 0); }

private:
	enum EnemySniperState {
		STATE_NORMAL = 0,
		STATE_SHOOTING = 1,
		STATE_DIE = 5,
	};

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;

	DOUBLE2 m_PointingDir;
	double m_DirRadians;

	int m_bulletsToShoot;

	int m_AnimationFrame;
	double m_TimeToDie;

	double m_ShootCounter;

	ObjectBase *m_PlayerPtr;

	EnemySniperState m_State;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	EnemySniper(const EnemySniper& yRef);
	EnemySniper& operator=(const EnemySniper& yRef);
};


