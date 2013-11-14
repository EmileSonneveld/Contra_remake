#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// Explosion Class									
//-----------------------------------------------------
class Explosion: public ObjectBase
{
public:
	Explosion(DOUBLE2 pos);		// Constructor
	Explosion(DOUBLE2 pos, int num);		// Constructor
	virtual ~Explosion();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime );
	virtual void Paint();
	virtual void CollideWith( ObjectBase *colliderptr, int team);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSprite1Ptr;
	static Bitmap *m_BmpSprite2Ptr;

	Bitmap *m_BmpSpritePtr; // plaatselijke copie

	double m_AnimationTik;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Explosion(const Explosion& yRef);									
	Explosion& operator=(const Explosion& yRef);	
};

 
