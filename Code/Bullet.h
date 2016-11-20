#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "ObjectBaseList.h"

//-----------------------------------------------------
// Bullet Class
//-----------------------------------------------------
class Bullet : public ObjectBase
{
public:
	Bullet(DOUBLE2 pos, DOUBLE2 velocity, ObjectType team, BulletType bulletType);
	virtual ~Bullet();

	//-------------------------------------------------
	// Own methods
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void CollideWith(ObjectBase *colliderptr);
	//void SetVelocity(DOUBLE2 velocity){m_Velocity= velocity;}

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------

	// Power up's constants
	BulletType m_BulletType;

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


