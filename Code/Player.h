#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"
#include "Bridge.h"

//-----------------------------------------------------
// Player Class
//-----------------------------------------------------
class Player : public ObjectBase
{

public:

	Player(int x, int y);
	virtual ~Player();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	void Jump(int force);

	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);

	void SetGlobalVars(ObjectList *objectListPtr, DOUBLE2 LevelMax);
	void SetPowerup(BulletType bulletType) {
		if (bulletType != BULLET_R)m_BulletType = bulletType;
		if (bulletType == -1) DebugBreak();
	}
	virtual DOUBLE2 GetPos() { return m_CenterPos; }

	void AddLevelHitRegion(HitRegion *levelHit) {
		m_LevelHitRegions.push_back(levelHit);
	}



private:

	enum PlayerState
	{
		STATE_NORMAL = 0,
		STATE_CRAWL = 1,
		STATE_JUMP = 2,
		STATE_SWIM = 3,
		STATE_DIVE = 4,
		STATE_DIE = 5,
	};

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

	// Power up's constants
	BulletType m_BulletType;


	/// VOOR DE SPRITES ///
	PlayerState m_State;

	static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_BodySize, m_LegsSize, m_BBoxSize;
	//MATRIX3X2 *m_MatViewPtr;
	double m_LegsFrame;
	int m_BodyFrame;
	double m_JumpRotation;
	DOUBLE2 m_CenterPos;

	static const int WALKSPEED = 100;

	double m_InvincebleTimer;

	bool m_AutomaticFinalRun; // vk_right

	int m_Lives;
	double m_TimeToDie;

	/// VOOR DE COLITIONS ///
	bool m_OnGround;

	HitRegion /*m_HitBBox, */*m_HitBBoxH, *m_HitBBoxV;
	//HitRegion *m_HitTerrainPtr;
	vector<HitRegion*> m_LevelHitRegions;
	bool m_Colide;
	DOUBLE2 m_Velocity, m_LevelMax, m_PointingDir, m_BulletSpawn;
	DOUBLE2 m_BulletDir;

	ObjectList *m_ObjectListPtr;

	double m_ShootCounter;

	// Funks -----------------------------
	bool DoCollitions(HitRegion *hitVertPtr, DOUBLE2& pos, DOUBLE2& velocity, HitRegion *levelHitPtr);
	double ReturnGoodLen(double getal1, double getal2, double centerXY);
	void DrawPlayer();
	void StartToDie();
	void DieAndRespawn();
	void CalculateStateAndFrame();
	void CalculateBulletSpawn();
	void Shoot();

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	Player(const Player& yRef);
	Player& operator=(const Player& yRef);
};
