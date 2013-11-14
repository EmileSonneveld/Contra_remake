#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h" // zit al in ObjectBaseList
#include "ObjectBaseList.h"

//-----------------------------------------------------
// BosSniper Class									
//-----------------------------------------------------
class BosSniper: public ObjectBase
{
public:
	BosSniper(DOUBLE2 pos);		// Constructor
	virtual ~BosSniper();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	void SetPlayerPtr(ObjectBase *playerPtr){m_PlayerPtr= playerPtr;}

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
	BosSniper(const BosSniper& yRef);									
	BosSniper& operator=(const BosSniper& yRef);	
};
