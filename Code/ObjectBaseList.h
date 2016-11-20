#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include <vector>


enum BulletType {
	BULLET_NORMAL = 0,
	BULLET_MITRAILLEUR = 1,
	BULLET_SUPER = 2,
	BULLET_LAZER = 3,
	BULLET_FLAME = 4,
	BULLET_R = 5, // Just for score?
};

enum ObjectType {
	TYPE_NOT_SET = -1,
	TYPE_NO_COLLITION = 00,
	TYPE_POWERUP = 01,
	TYPE_PLAYER_BULLET = 10,
	TYPE_PLAYER = 11,
	TYPE_ENEMY_BULLET = 20,
	TYPE_ENEMY = 21,
	TYPE_ENEMY_BOX = 22,
	TYPE_ENEMY_WALKING = 23,
};


//-----------------------------------------------------------------
//  Forward declarations
//-----------------------------------------------------------------
class ObjectBase;
class ObjectList;


//-----------------------------------------------------
// ObjectBase Class
//-----------------------------------------------------
class ObjectBase
{
public:
	ObjectBase();
	ObjectBase(DOUBLE2 pos);
	virtual ~ObjectBase();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime) {};
	virtual void Paint() = 0;
	virtual void CollideWith(ObjectBase *colliderptr) = 0; // needs to be implemented by every control

	DOUBLE2 GetPos() { return m_Pos; }

	void SetMatView(MATRIX3X2 *matView) { m_MatViewPtr = matView; }
	void SetObjectList(ObjectList * objectListPtr)
	{
		m_ObjectListPtr = objectListPtr;
	}
	HitRegion *GetHitRegion() { return m_HitRegionPtr; }

	ObjectType GetType() { return m_Type; }
	//bool stagedForDeletion = false;

protected:
	//static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_Pos;

	// [0-9] Neutral
	// [10-19] Player
	// [20-29] Enemy
	ObjectType m_Type;

	DOUBLE2 m_SpriteSize;
	MATRIX3X2 *m_MatViewPtr;
	HitRegion *m_HitRegionPtr;
	ObjectList *m_ObjectListPtr;


private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	//Player *m_PlayerPtr;

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	ObjectBase(const ObjectBase& yRef);
	ObjectBase& operator=(const ObjectBase& yRef);
};



//-----------------------------------------------------
// ObjectList Class
//-----------------------------------------------------
class ObjectList
{
public:
	ObjectList(DOUBLE2 maxPos, MATRIX3X2 *matViewPtr, HitRegion *hitTerrainPtr); // Constructor
	virtual ~ObjectList();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	int Add(ObjectBase * objectPtr); //Player
	bool Delete(ObjectBase *objPtr);

	void Tick(double deltaTime);
	void Paint();
	DOUBLE2 GetPos(int plaats);
	ObjectBase *GetPointer(int plaats) { return m_ObjectPtrVect.at(plaats); }

	HitRegion *GetHitTerrain() { return m_HitTerrainPtr; }


private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
	//static const int ARR_MAX=100;
	//ObjectBase * m_ObjectPtr[ARR_MAX];
	bool DeleteNow(int plaats);

	vector<ObjectBase*> m_ObjectPtrVect;
	vector<ObjectBase*> m_ObjectPtrToDeleteVect;

	void DeleteStagedObjects();
	int m_ObjectCount; // optioneel

	// voor de inzittende objecten:
	DOUBLE2 m_MaxPos;
	MATRIX3X2 *m_MatViewPtr;

	//Bitmap *m_BmpSpritePtr;

	HitRegion *m_HitTerrainPtr;

	// Funcs ------------------------------------------
	bool CheckIfPlaatsExist(int plaats);
	void OutputStatus();

	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	ObjectList(const ObjectList& yRef);
	ObjectList& operator=(const ObjectList& yRef);
};
