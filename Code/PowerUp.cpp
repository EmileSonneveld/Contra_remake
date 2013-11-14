//---------------------------
// Includes
//---------------------------
#include "PowerUp.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * PowerUp::m_BmpSpritePtr= 0;

PowerUp::PowerUp(DOUBLE2 pos, int type): ObjectBase(pos), m_Velocity(50-rand()%40,-200)
{
	m_Type= TYPE_POWERUP;
	m_BulletType= type;
	m_PlayerPtr= 0;

	if( m_BmpSpritePtr==0 ){ // Bmp nog niet ingeladen
		m_BmpSpritePtr= new Bitmap("./resources/PowerUp.png");
		//m_BmpSpritePtr->SetTransparencyColor(0,0,0);
	}
	m_SpriteSize.x= 24;
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

PowerUp::~PowerUp(){} // dont delete the static Bmp, windows will do it in the end

//---------------------------
// Own methods
//---------------------------

void PowerUp::Tick(double deltaTime )
{
	m_Velocity.y+= 300*deltaTime; // Gravity.
	m_Pos+= m_Velocity*deltaTime;

	m_HitRegionPtr->SetPos(m_Pos);
	//if( DoCollitions(&m_HitRegionPtr, &m_HitRegionPtr, &m_Pos, &m_Velocity) ){
	if( DoCollitions(m_HitRegionPtr, m_Pos, m_Velocity, m_ObjectListPtr->GetHitTerrain() ) ){
		m_Velocity.x= 0;
	}

}

void PowerUp::Paint()
{
	MATRIX3X2 matCenter, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));
	RECT2 clip;
	clip.left   = m_BulletType * m_SpriteSize.x; // kot overeen met de plaats in de sprite
	clip.top    = 0;
	clip.right  = clip.left +m_SpriteSize.x;
	clip.bottom = clip.top  +m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0, clip);
}


void PowerUp::CollideWith( ObjectBase *colliderptr, int otherType){
	if( otherType==TYPE_PLAYER ){
		OutputDebugString("\nPowerUp!");
		if( m_PlayerPtr == 0 ){
			OutputDebugString("\n m_PlayerPtr not set at creation.");
			DebugBreak();
		}
		m_PlayerPtr->SetPowerup(m_BulletType); // Hier is een bug!!!!!
		m_ObjectListPtr->Delete(this);
	}
}




bool PowerUp::DoCollitions(HitRegion *hitVertPtr, DOUBLE2& posRef, DOUBLE2& velocityRef, HitRegion *levelHitPtr)
{
	bool returnCollide= false;
	//GAME_ENGINE->SetColor(225,5,255,200);
	//GAME_ENGINE->FillHitRegion(*hitVertPtr);
	// Y
	if( m_Velocity.y>=0 ){
		RECT2 collisionRectV= hitVertPtr->CollisionTest(levelHitPtr);
		double deltaY= ReturnGoodLen( collisionRectV.top, collisionRectV.bottom, posRef.y);
		if( deltaY<0 ){
			RECT2 checkHeight= hitVertPtr->GetBounds();
			double height= abs( checkHeight.bottom- checkHeight.top );
			if( deltaY<height && deltaY>-height ){
				posRef.y+= deltaY;
				if( deltaY* velocityRef.y <0 ) // verschillend teken
					velocityRef.y =0;
				returnCollide= true;
				//GAME_ENGINE->SetColor(5,5,255,200);
				//GAME_ENGINE->FillRect(collisionRectV);
			}
		}
	}

	hitVertPtr->SetPos( posRef );

	return returnCollide;
}
/*
void PowerUp::DoCollitions(HitRegion **hitHoriPtr, HitRegion **hitVertPtr, DOUBLE2 *pos, DOUBLE2 *velocity)
{
//GAME_ENGINE->SetColor(225,5,255,200);
//GAME_ENGINE->FillHitRegion(*hitVertPtr);
// Y
m_OnGround= false;
if( m_Velocity.y>=0 ){
RECT2 collisionRectV= (*hitVertPtr)->CollisionTest( m_ObjectListPtr->GetHitTerrain() );
double deltaY= ReturnGoodLen(collisionRectV.top, collisionRectV.bottom, (*pos).y);
if( deltaY<0 ){
RECT2 checkHeight= (*hitVertPtr)->GetBounds();
double height= abs( checkHeight.bottom- checkHeight.top );
if( deltaY<height && deltaY>-height ){
(*pos).y+= deltaY;
if( deltaY* (*velocity).y <0 ) // verschillend teken
(*velocity).y =0;
m_OnGround= true;
//GAME_ENGINE->SetColor(5,5,255,200);
//GAME_ENGINE->FillRect(collisionRectV);
}
}
}

(*hitVertPtr)->SetPos(*pos);
(*hitHoriPtr)->SetPos(*pos);


// X niet
}//*/

double PowerUp::ReturnGoodLen(double getal1, double getal2, double centerXY)
{
	double delta= 0;
	delta=abs( getal1 - getal2 );

	if( delta >0.001){ // er is een botsing
		double colCenter= ( getal1 + getal2 ) /2;
		if(  centerXY< colCenter ) delta*=-1;
	}
	return delta;
}

