#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// EnemyWalking Class
//-----------------------------------------------------
class EnemyWalking : public ObjectBase
{
public:
	EnemyWalking(DOUBLE2 pos);
	virtual ~EnemyWalking();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	void SetPlayerPtr(ObjectBase *playerPtr);
	void StartToDie();


private:
	enum EnemyWalkingState {
		STATE_NORMAL = 0,
		STATE_JUMP = 2,
		STATE_DIE = 5,
	};
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	DOUBLE2 m_PointingDir;

	EnemyWalkingState m_State;

	double m_AnimationTick;
	double m_TimeToDie;

	ObjectBase *m_PlayerPtr;
	static Bitmap *m_BmpSpritePtr;

	double m_OnGround;
	DOUBLE2 m_Velocity;
	// Funks -----------------------------
	void DoCollitions(
		HitRegion **hitHoriPtr, HitRegion **hitVertPtr,
		DOUBLE2 *pos, DOUBLE2 *velocity);
	double ReturnGoodLen(double getal1, double getal2, double centerXY);
	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	EnemyWalking(const EnemyWalking& yRef);
	EnemyWalking& operator=(const EnemyWalking& yRef);
};


