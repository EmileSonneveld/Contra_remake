#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// FlyingPuwerUp Class
//-----------------------------------------------------
class FlyingPuwerUp : public ObjectBase
{
public:
	FlyingPuwerUp(DOUBLE2 pos, BulletType powerUpType);
	virtual ~FlyingPuwerUp();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	void SetPlayerPtr(Player *playerPtr) { m_PlayerPtr = playerPtr; }
	int Sign(double getal) { return (getal > 0) - (getal < 0); }

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;

	BulletType m_PowerUpType; // eigenlijk powerUpType


	double m_AnimationTick;

	DOUBLE2 m_Velocity;
	double m_OriginalY;

	bool m_Activated;

	Player *m_PlayerPtr;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	FlyingPuwerUp(const FlyingPuwerUp& yRef);
	FlyingPuwerUp& operator=(const FlyingPuwerUp& yRef);
};


