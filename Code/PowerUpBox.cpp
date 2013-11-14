//---------------------------
// Includes
//---------------------------
#include "PowerUpBox.h"
#include "Explosion.h"
#include "PowerUp.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * PowerUpBox::m_BmpSpritePtr= 0;

PowerUpBox::PowerUpBox(DOUBLE2 pos, int type): ObjectBase(pos), m_AnimationTick(0), m_AnimationSense(1)
{
	m_Type= TYPE_ENEMY;

	m_BulletType= type;

	/*int gs= 32; //GridSize, word door ObjectBase in het center van een cel gezet
	m_Pos.x= ((int)m_Pos.x/gs)*gs;
	m_Pos.y= ((int)m_Pos.y/gs)*gs;*/

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/PowerUpBox.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetHeight();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

PowerUpBox::~PowerUpBox(){  // dont delete the static Bmp, windows will do it in the end
	m_ObjectListPtr->Add( new Explosion(m_Pos) );
}

//---------------------------
// Own methods
//---------------------------

void PowerUpBox::CollideWith( ObjectBase *colliderptr, int otherType)
{
	if( otherType == TYPE_PLAYER_BULLET ){ // die and trow the powerup.
		m_ObjectListPtr->Delete(colliderptr); // delete the bullet
		if( (int)m_AnimationTick>2 ){
			PowerUp *objectPtr= new PowerUp( m_Pos, m_BulletType );
			objectPtr->SetPlayerPtr(m_PlayerPtr);
			m_ObjectListPtr->Add( objectPtr );

			m_ObjectListPtr->Delete(this);
		}
	}
}

void PowerUpBox::Tick(double deltaTime )
{
	m_AnimationTick+= deltaTime*8 * m_AnimationSense; // tick een  eetje.
	if( m_AnimationTick>= 5 ){
		m_AnimationTick= 4.99999;
		m_AnimationSense*= -1;
	}
	if( m_AnimationTick< 0 ){
		m_AnimationTick= 0;
		m_AnimationSense*= -1;
	}
}

void PowerUpBox::Paint()
{

	MATRIX3X2 matCenter, matTranslate;
	matCenter	.SetAsTranslate( -m_SpriteSize/2 );
	//matScale	.SetAsScale( m_Scale );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));
	

	//GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	GAME_ENGINE->FillHitRegion(m_HitRegionPtr);

	RECT2 clip;
	clip.left	= (int)m_AnimationTick* m_SpriteSize.x;
	clip.top	= 0;
	clip.right	= clip.left + m_SpriteSize.x;
	clip.bottom	= clip.top  + m_SpriteSize.y;

	GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, 0,0, clip );
}

