#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// Bullet Class									
//-----------------------------------------------------
class Bullet: public ObjectBase
{
public:
	Bullet(DOUBLE2 pos, DOUBLE2 velocity, int team, int bulletType);		// Constructor
	virtual ~Bullet();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	//void SetVelocity(DOUBLE2 velocity){m_Velocity= velocity;}

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	// Power up's constants
	int m_BulletType;
	static const int BULLET_NORMAL		= 0;
	static const int BULLET_MITRAILLEUR	= 1;
	static const int BULLET_SUPER		= 2;
	static const int BULLET_LAZER		= 3;
	static const int BULLET_FLAME		= 4;

	double m_Scale;

	static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_Velocity;
	bool m_Friendly; // true: from player, false: from ennemy

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bullet(const Bullet& yRef);									
	Bullet& operator=(const Bullet& yRef);	
};

 
