#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h" // zit al in ObjectBaseList
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// FlyingPuwerUp Class									
//-----------------------------------------------------
class FlyingPuwerUp: public ObjectBase
{
public:
	FlyingPuwerUp(DOUBLE2 pos, int powerUpType);		// Constructor
	virtual ~FlyingPuwerUp();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	void SetPlayerPtr(Player *playerPtr){m_PlayerPtr= playerPtr;}
	int Sign(double getal){ return (getal > 0) - (getal < 0); }

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;

	int m_PowerUpType; // eigenlijk powerUpType
	static const int BULLET_NORMAL		= 0;
	static const int BULLET_MITRAILLEUR	= 1;
	static const int BULLET_SUPER		= 2;
	static const int BULLET_LAZER		= 3;
	static const int BULLET_FLAME		= 4;
	static const int BULLET_R			= 5; // Score ofzo?


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

 
