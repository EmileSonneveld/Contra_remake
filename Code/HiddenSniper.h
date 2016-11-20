#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// BosSniper Class
//-----------------------------------------------------
class HiddenSniper : public ObjectBase
{
public:
	HiddenSniper(DOUBLE2 pos);
	virtual ~HiddenSniper();

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
	bool m_ShootSwitch;
	int m_XScale;

	double m_ShootCounter;

	ObjectBase *m_PlayerPtr;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	HiddenSniper(const HiddenSniper& yRef);
	HiddenSniper& operator=(const HiddenSniper& yRef);
};
