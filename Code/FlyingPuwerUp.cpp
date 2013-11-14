//---------------------------
// Includes
//---------------------------
#include "FlyingPuwerUp.h"
#include "PowerUp.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * FlyingPuwerUp::m_BmpSpritePtr= 0;

FlyingPuwerUp::FlyingPuwerUp(DOUBLE2 pos, int powerUpType): ObjectBase(pos), m_AnimationTick(0), m_Activated(0), m_Velocity()
{
	m_Type= TYPE_ENEMY;

	m_PowerUpType= powerUpType;
	m_OriginalY= pos.y-20;

	/*int gs= 32; //GridSize, word door ObjectBase in het center van een cel gezet
	m_Pos.x= ((int)m_Pos.x/gs)*gs;
	m_Pos.y= ((int)m_Pos.y/gs)*gs;*/

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/FlyingPuwerUp.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth() +4;
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight()+4;

	m_HitRegionPtr->CreateFromRect(-2, -2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

FlyingPuwerUp::~FlyingPuwerUp(){ 
} // dont delete the static Bmp, windows will do it in the end

//---------------------------
// Own methods
//---------------------------

void FlyingPuwerUp::CollideWith( ObjectBase *colliderptr, int otherType)
{
	if( otherType == TYPE_PLAYER_BULLET && m_Activated ){
		m_ObjectListPtr->Delete( colliderptr );
			PowerUp *powerUpPtr= new PowerUp( m_Pos, m_PowerUpType);
			powerUpPtr->SetPlayerPtr( m_PlayerPtr );
			m_ObjectListPtr->Add( powerUpPtr );
			m_ObjectListPtr->Delete( this ); // suicide
			return;
	}
}

void FlyingPuwerUp::Tick(double deltaTime )
{

	m_AnimationTick+= deltaTime;


	if( m_Activated ){
		DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );
		m_Velocity.y+= 8*Sign(  m_OriginalY - m_Pos.y );
		m_Pos+= m_Velocity*deltaTime;
		m_HitRegionPtr->SetPos(m_Pos);
		if( m_Pos.x >schetmRechtsOnder.x ){
			m_ObjectListPtr->Delete( this ); // suicide
			return;
		}

	}else{ // sleeping...
		DOUBLE2 schetmLingsBoven= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
		if( m_Pos.x+m_SpriteSize.x < schetmLingsBoven.x ){
			m_Activated= true; 
			m_Velocity.x= 130;
		}

	}

}

void FlyingPuwerUp::Paint()
{
	if( !m_Activated ) return;


	GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	//GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);

	RECT2 clip;
	clip.left	= ((int)m_AnimationTick)%3* m_SpriteSize.x;
	clip.top	= 0;
	clip.right	= clip.left + m_SpriteSize.x;
	clip.bottom	= clip.top  + m_SpriteSize.y;

	GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, m_Pos);
}

