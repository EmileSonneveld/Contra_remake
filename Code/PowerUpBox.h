#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// PowerUpBox Class
//-----------------------------------------------------
class PowerUpBox : public ObjectBase
{
public:
	PowerUpBox(DOUBLE2 pos, BulletType type);
	virtual ~PowerUpBox();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	void SetPlayerPtr(Player *playerPtr) { m_PlayerPtr = playerPtr; }

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;


	double m_AnimationTick;
	int m_AnimationSense;

	Player *m_PlayerPtr;

	// Power up's constants
	BulletType m_BulletType; // eigenlijk powerUpType


	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	PowerUpBox(const PowerUpBox& yRef);
	PowerUpBox& operator=(const PowerUpBox& yRef);
};


