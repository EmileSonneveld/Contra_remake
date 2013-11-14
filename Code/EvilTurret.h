#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h" // zit al in ObjectBaseList
#include "ObjectBaseList.h"

//-----------------------------------------------------
// EvilTurret Class									
//-----------------------------------------------------
class EvilTurret: public ObjectBase
{
public:
	EvilTurret(DOUBLE2 pos);				// Constructor
	virtual ~EvilTurret();		// Destructor

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

	DOUBLE2 m_PointingDir;
	double m_DirRadians;

	double m_DirectionFrame;
	double m_ColorTick;

	double m_ScrolIn;

	double m_ShootTimer;
	int m_bulletsCounter;
	bool m_ShootSwitch;

	int m_Lives;

	ObjectBase *m_PlayerPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EvilTurret(const EvilTurret& yRef);									
	EvilTurret& operator=(const EvilTurret& yRef);	
};

 
