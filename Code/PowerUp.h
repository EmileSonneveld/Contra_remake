#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"
#include "Player.h"

//-----------------------------------------------------
// PowerUp Class									
//-----------------------------------------------------
class PowerUp: public ObjectBase
{
public:
	PowerUp(DOUBLE2 pos, int type);	// Constructor
	virtual ~PowerUp();		// Destructor

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int otherType);
	void SetPlayerPtr(Player *playerPtr){m_PlayerPtr= playerPtr;}
	//void SetPlayerPtr(ObjectBase *playerPtr){m_PlayerPtr= playerPtr;}

private: 
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

	// Power up's constants
	int m_BulletType; // eigenlijk powerUpType
	static const int BULLET_NORMAL		= 0;
	static const int BULLET_MITRAILLEUR	= 1;
	static const int BULLET_SUPER		= 2;
	static const int BULLET_LAZER		= 3;
	static const int BULLET_FLAME		= 4;


	static Bitmap *m_BmpSpritePtr;

	Player *m_PlayerPtr;

	//HitRegion *m_HitTerrainPtr;
	double m_OnGround;
	DOUBLE2 m_Velocity;
	// Funks -----------------------------
	bool DoCollitions(HitRegion *hitVertPtr, DOUBLE2& pos, DOUBLE2& velocity, HitRegion *levelHitPtr);
	/*void DoCollitions(
		HitRegion **hitHoriPtr, HitRegion **hitVertPtr,
		DOUBLE2 *pos, DOUBLE2 *velocity);*/
	double ReturnGoodLen(double getal1, double getal2, double centerXY);

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PowerUp(const PowerUp& yRef);									
	PowerUp& operator=(const PowerUp& yRef);	
};