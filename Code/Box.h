#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// Box Class
//-----------------------------------------------------
class Box : public ObjectBase
{
public:
	Box(DOUBLE2 pos);
	virtual ~Box();

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
	int m_bulletsToShoot;

	int m_State;
	static const int STATE_NORMAL = 0;
	static const int STATE_SHOOTING = 1;
	static const int STATE_DESACTACTIVATE = 2;

	static Bitmap *m_BmpSpritePtr;

	double m_AnimationTik;
	Player *m_PlayerPtr;
	double m_DirRadians;
	DOUBLE2 m_PointingDir;
	double m_ShootCounter;
	int m_Lives;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	Box(const Box& yRef);
	Box& operator=(const Box& yRef);
};
