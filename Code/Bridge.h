#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h" // zit al in ObjectBaseList
#include "ObjectBaseList.h"

//-----------------------------------------------------
// Bridge Class									
//-----------------------------------------------------
class Bridge: public ObjectBase
{
public:
	Bridge(DOUBLE2 pos);				// Constructor
	virtual ~Bridge();		// Destructor

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


	double m_AnimationTick;
	double m_TimePerExplosion;
	bool m_UnderDestruction;

	static const int PIECES= 4;
	int m_PiecesLeft;
	//int m_Next;

	ObjectBase *m_PlayerPtr;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bridge(const Bridge& yRef);									
	Bridge& operator=(const Bridge& yRef);	
};

 
