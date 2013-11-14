#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include <vector>

//-----------------------------------------------------------------
//  My first Forward Declarations!!! d=D
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
	ObjectBase(DOUBLE2 pos);//, Bitmap * BmpSpritePtr
	virtual ~ObjectBase();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime){};
	virtual void Paint()=0;
	virtual void CollideWith( ObjectBase *colliderptr, int otherType)=0; // moet iedereen op zich maken

	DOUBLE2 GetPos(){ return m_Pos; }

	void SetMatView(MATRIX3X2 *matView){m_MatViewPtr= matView;}
	void SetObjectList(ObjectList * objectListPtr)
	{ m_ObjectListPtr= objectListPtr;}
	HitRegion *GetHitRegion(){ return m_HitRegionPtr; }

	//void SetPlayerPtr(ObjectBase *playerPtr){m_PlayerPtr= playerPtr;}
	//Player *GetPlayerPtr(){ return m_PlayerPtr; }

	int GetType(){ return m_Type; }

protected:
	//static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_Pos;
	int m_Type; // 0: onpartijdig, 1: speler, 2:vijand
	static const int TYPE_NOT_SET		=-1;
	static const int TYPE_NO_COLLITION	=00;
	static const int TYPE_POWERUP		=01;
	static const int TYPE_PLAYER_BULLET	=10;
	static const int TYPE_PLAYER		=11;
	static const int TYPE_ENEMY_BULLET	=20;
	static const int TYPE_ENEMY			=21;
	static const int TYPE_ENEMY_BOX		=22;
	static const int TYPE_ENEMY_WALKING	=23;

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
	virtual ~ObjectList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	int Add( ObjectBase * objectPtr ); //Player
	bool Delete( int plaats );
	bool Delete( ObjectBase *objPtr );

	void Tick(double deltaTime);
	void Paint();
	DOUBLE2 GetPos( int plaats );
	ObjectBase *GetPointer( int plaats ){return m_ObjectPtrVect.at(plaats);}
	
	HitRegion *GetHitTerrain(){return m_HitTerrainPtr;}


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	//static const int ARR_MAX=100;
	//ObjectBase * m_ObjectPtr[ARR_MAX];

	vector<ObjectBase*> m_ObjectPtrVect;

	int m_ObjectCount; // optioneel

	// voor de inzittende objecten:
	DOUBLE2 m_MaxPos;
	MATRIX3X2 *m_MatViewPtr;

	//Bitmap *m_BmpSpritePtr;

	HitRegion *m_HitTerrainPtr;

	// Funcs ------------------------------------------
	bool CheckIfPlaatsExist( int plaats );
	void OutputStatus();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ObjectList(const ObjectList& yRef);									
	ObjectList& operator=(const ObjectList& yRef);	
};