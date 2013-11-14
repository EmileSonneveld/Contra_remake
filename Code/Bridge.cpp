//---------------------------
// Includes
//---------------------------
#include "Bridge.h"
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Bridge::m_BmpSpritePtr= 0;

Bridge::Bridge(DOUBLE2 pos): ObjectBase(pos), m_UnderDestruction(false), 
	m_AnimationTick(999), m_TimePerExplosion(0.6), m_PiecesLeft(PIECES)
{
	m_Type= TYPE_ENEMY;

	int gs= 32; //GridSize
	m_Pos.x= ((int)m_Pos.x/gs)*gs;
	m_Pos.y= ((int)m_Pos.y/gs)*gs;

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/Bridge.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}

	m_SpriteSize.x= m_BmpSpritePtr->GetWidth() / PIECES;
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect( m_SpriteSize.x * (PIECES-m_PiecesLeft), 7, m_SpriteSize.x*m_PiecesLeft, 10 );
	m_HitRegionPtr->SetPos(m_Pos);
}

Bridge::~Bridge()
{

}

//---------------------------
// Own methods
//---------------------------

void Bridge::CollideWith( ObjectBase *colliderptr, int otherType)
{
	/*switch( otherType ){

	case TYPE_PLAYER:
		// 
		break;

	case TYPE_ENEMY_BULLET:
		// 
		break;
	
	case TYPE_PLAYER_BULLET:
		// 
		break;
	}//*/
}

void Bridge::Tick(double deltaTime )
{
	
	if( m_PlayerPtr->GetPos().x > m_Pos.x ){ // Let The explosions begin!
		m_UnderDestruction= true;
	}

	if( m_UnderDestruction && m_PiecesLeft>=0){
		//double prevTick= m_AnimationTick;
		m_AnimationTick+= deltaTime;

		if( m_AnimationTick >= m_TimePerExplosion ){
			m_AnimationTick= 0;

			m_ObjectListPtr->Add( new Explosion(DOUBLE2(m_Pos.x +m_SpriteSize.x * ( PIECES - m_PiecesLeft ), m_Pos.y+16)) );
			
			--m_PiecesLeft;

			m_HitRegionPtr->CreateFromRect( m_SpriteSize.x * (PIECES-m_PiecesLeft), 7, m_SpriteSize.x*m_PiecesLeft, 10 );
			m_HitRegionPtr->SetPos(m_Pos);

			if( m_PiecesLeft <= 0 )m_UnderDestruction= false; // destructed
			//m_ObjectListPtr->Delete(this); // suiside -> Player refereert naar mijn hitRegion
			
		}

		/*if( (int)prevTick/m_TimePerExplosion != (int)m_AnimationTick/m_TimePerExplosion ){ // er is een switch gebeurd.
			m_ObjectListPtr->Add( new Explosion(m_Pos) );
		}

		if( m_AnimationTick <= m_TimePerExplosion*PIECES ){
			//m_ObjectListPtr->Delete(this); // suiside
		}*/
	}
}

void Bridge::Paint()
{
	GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	/*MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize,  -bodySize.y+7);
	matScale.	SetAsScale( m_PointingDir.x, 1);
	matTranslate.SetAsTranslate( m_Pos );//*/

	
	/*GAME_ENGINE->SetColor(20, 255, 60);
	GAME_ENGINE->FillRect( m_Pos, m_SpriteSize.x, m_SpriteSize.y);*/

	

	RECT2 clip;
	clip.left	= m_SpriteSize.x * ( PIECES - m_PiecesLeft );
	clip.top	= 0;
	clip.right	= m_SpriteSize.x * PIECES;
	clip.bottom	= clip.top  + m_SpriteSize.y;

	GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, m_Pos.x +clip.left, m_Pos.y, clip );


	//GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
}

