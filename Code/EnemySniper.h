#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// EnemySniper Class									
//-----------------------------------------------------
class EnemySniper: public ObjectBase
{
public:
	EnemySniper(DOUBLE2 pos);				// Constructor
	virtual ~EnemySniper();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	void SetPlayerPtr(ObjectBase *playerPtr){m_PlayerPtr= playerPtr;}
	int Sign(double getal){ return (getal > 0) - (getal < 0); }

private: 
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

	int m_State; // +/- idem aan Player
	static const int STATE_NORMAL= 0;
	static const int STATE_SHOOTING	= 1;
	static const int STATE_DIE   = 5;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EnemySniper(const EnemySniper& yRef);									
	EnemySniper& operator=(const EnemySniper& yRef);	
};

 
