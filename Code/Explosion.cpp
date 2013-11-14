//---------------------------
// Includes
//---------------------------
#include "Explosion.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Explosion::m_BmpSprite1Ptr= 0;
Bitmap * Explosion::m_BmpSprite2Ptr= 0;

Explosion::Explosion(DOUBLE2 pos): ObjectBase(pos)
{
	m_Type= TYPE_NO_COLLITION;

	m_AnimationTik=0;
	if( m_BmpSprite1Ptr==0 ){
		m_BmpSprite1Ptr= new Bitmap("./resources/explosion.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}

	m_BmpSpritePtr= m_BmpSprite1Ptr; 
	m_SpriteSize.x= m_BmpSpritePtr->GetHeight();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

Explosion::Explosion(DOUBLE2 pos, int num): ObjectBase(pos)
{
	m_Type= TYPE_NO_COLLITION;

	m_AnimationTik=0;
	if( m_BmpSprite2Ptr==0 ){
		m_BmpSprite2Ptr= new Bitmap(String("./resources/explosion") +num +".png");
	}

	m_BmpSpritePtr= m_BmpSprite2Ptr; 

	m_SpriteSize.x= m_BmpSpritePtr->GetHeight();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

Explosion::~Explosion(){}

//---------------------------
// Own methods
//---------------------------

void Explosion::Tick(double deltaTime)
{
	m_AnimationTik+=0.1;
	if( m_AnimationTik>4 ){
		m_ObjectListPtr->Delete(this); // suieside!
	}
}

void Explosion::Paint()
{
	MATRIX3X2 matCenter, matTranslate;

	matCenter.	SetAsTranslate( -m_SpriteSize/2 );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix( matCenter * matTranslate * (*m_MatViewPtr) );
	RECT2 clip;
	clip.left   = (int)m_AnimationTik*m_SpriteSize.x ;
	clip.top    = 0;
	clip.right  = clip.left +m_SpriteSize.x;
	clip.bottom = clip.top  +m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0, clip);
}//*/


void Explosion::CollideWith( ObjectBase *colliderptr, int otherType){
	//Do nothing
}