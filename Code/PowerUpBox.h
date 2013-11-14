#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h" // zit al in ObjectBaseList
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// PowerUpBox Class									
//-----------------------------------------------------
class PowerUpBox: public ObjectBase
{
public:
	PowerUpBox(DOUBLE2 pos, int type);				// Constructor
	virtual ~PowerUpBox();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	//void SetPlayerPtr(ObjectBase *playerPtr){m_PlayerPtr= playerPtr;}
	void SetPlayerPtr(Player *playerPtr){m_PlayerPtr= playerPtr;}

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;


	double m_AnimationTick;
	int m_AnimationSense;

	Player *m_PlayerPtr;

	// Power up's constants
	int m_BulletType; // eigenlijk powerUpType
	static const int BULLET_NORMAL		= 0;
	static const int BULLET_MITRAILLEUR	= 1;
	static const int BULLET_SUPER		= 2;
	static const int BULLET_LAZER		= 3;
	static const int BULLET_FLAME		= 4;


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PowerUpBox(const PowerUpBox& yRef);									
	PowerUpBox& operator=(const PowerUpBox& yRef);	
};

 
