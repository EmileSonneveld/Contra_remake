//---------------------------
// Includes
//---------------------------
#include "EndBoss.h"
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * EndBoss::m_BmpSpritePtr= nullptr;

EndBoss::EndBoss(DOUBLE2 pos): ObjectBase(pos), m_AnimationTick(0), m_Lives(5), m_ShieldPos(-93, -165), m_ShieldSize(24,31)
{
	m_Type= TYPE_ENEMY;

	/*int gs= 32; //GridSize, word door ObjectBase in het center van een cel gezet
	m_Pos.x= ((int)m_Pos.x/gs)*gs;
	m_Pos.y= ((int)m_Pos.y/gs)*gs;*/

	if( m_BmpSpritePtr==nullptr ){
		m_BmpSpritePtr= new Bitmap("./resources/EndBoss.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x+7, 0, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

EndBoss::~EndBoss(){ } // dont delete the static Bmp, windows will do it in the end

//---------------------------
// Own methods
//---------------------------

void EndBoss::CollideWith( ObjectBase *colliderptr, int otherType)
{
	if( otherType == TYPE_PLAYER_BULLET ){
		--m_Lives;
		m_ObjectListPtr->Delete( colliderptr );
		if( m_Lives == 0 ){
			m_ObjectListPtr->Add( new Explosion( m_Pos + m_ShieldPos ) );
			m_ObjectListPtr->Add( new Explosion( m_Pos ) );
			//m_ObjectListPtr->Delete( this ); // suicide
			return;
		}else{
		//	m_ObjectListPtr->Delete( colliderptr );
		}
	}
}

void EndBoss::Tick(double deltaTime )
{
	m_AnimationTick+= deltaTime;

}

void EndBoss::Paint()
{

	/*MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter	.SetAsTranslate( -m_SpriteSize/2 );
	//matScale	.SetAsScale( m_Scale );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));
	*/

	GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	//GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);

	if( m_Lives > 0 ){
		RECT2 clip; // BASE --------------------
		clip.left	= 0;
		clip.top	= 0;
		clip.right	= clip.left + m_SpriteSize.x;
		clip.bottom	= clip.top  + m_SpriteSize.y;

		GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, m_Pos.x-m_SpriteSize.x, 0, clip );

		// SHIELD --------------------
		clip.left	= ((int)m_AnimationTick)%2* m_ShieldSize.x;
		clip.top	= 0;
		clip.right	= clip.left + m_ShieldSize.x;
		clip.bottom	= clip.top  + m_ShieldSize.y;

		GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, m_Pos-m_ShieldPos, clip );
	}
}

