#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// EndBoss Class
//-----------------------------------------------------
class EndBoss : public ObjectBase
{
public:
	EndBoss(DOUBLE2 pos);
	virtual ~EndBoss();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	void SetPlayerPtr(ObjectBase *playerPtr) { m_PlayerPtr = playerPtr; }

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;


	double m_AnimationTick;

	int m_Lives;

	DOUBLE2 m_ShieldPos, m_ShieldSize;

	ObjectBase *m_PlayerPtr;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	EndBoss(const EndBoss& yRef);
	EndBoss& operator=(const EndBoss& yRef);
};


