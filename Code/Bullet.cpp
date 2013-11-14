//---------------------------
// Includes
//---------------------------
#include "Bullet.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Bullet::m_BmpSpritePtr= 0;

Bullet::Bullet(DOUBLE2 pos, DOUBLE2 velocity, int type, int bulletType): 
	ObjectBase(pos), m_Velocity(velocity), m_Scale(1)
{
	m_Type= type; // voor collitions met bullets
	m_BulletType= bulletType;

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/Bullet.png");
		/*m_BmpSpritePtr->SetTransparencyColor(0,0,0);*/
	}
	m_SpriteSize.x= 3;
	m_SpriteSize.y= m_SpriteSize.x;
	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
}

Bullet::~Bullet() {} // dont delete m_BmpSpritePtr;, it wille automaticaly be deleted at the end.

//---------------------------
// Own methods
//---------------------------

void Bullet::Tick(double deltaTime)
{
	m_Pos+=m_Velocity* deltaTime;
	m_HitRegionPtr->SetPos(m_Pos);


	switch( m_BulletType ){

	case BULLET_NORMAL		:
		break;

	case BULLET_MITRAILLEUR	:
	case BULLET_SUPER		:
		m_Scale+= 0.4* deltaTime;
		m_Scale= min(5, m_Scale );
		break;

	case BULLET_LAZER		:

		break;

	case BULLET_FLAME		:

		break;

	}
	

	// Deleten op de goeie momenten. (delicate code!)
	/*int marge= -150;
	if( m_Pos.x<marge || m_Pos.x>m_MaxPos.x-marge ){
		m_ObjectListPtr->Delete(this);
		return;
	}
	if( m_Pos.y<marge || m_Pos.y>m_MaxPos.y-marge ){
		m_ObjectListPtr->Delete(this);
		return;
	}*/
	
	DOUBLE2 schetmLingsBoven=  (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
	DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

	if( m_Pos.x>schetmRechtsOnder.x+10 ){
		m_ObjectListPtr->Delete(this);
		return;
	}
	if( m_Pos.x<schetmLingsBoven.x-10 ){
		m_ObjectListPtr->Delete(this);
		return;
	}
}

void Bullet::Paint()
{
	MATRIX3X2 matCenter, matScale, matTranslate;
	matScale	.SetAsScale( m_Scale );
	matTranslate.SetAsTranslate( m_Pos );

	RECT2 clip;
	DOUBLE2 size(0,0);

	switch( m_BulletType ){
	case BULLET_NORMAL		:
		
		size.x= 3;
		size.y= 3;

		matCenter	.SetAsTranslate( -size/2 );
		//matScale	.SetAsScale( m_Scale );
		//matTranslate.SetAsTranslate( m_Pos );

		GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));

		clip.left	= 0;
		clip.top	= 0;
		clip.right	= clip.left	+size.x;
		clip.bottom	= clip.top	+size.y;

		GAME_ENGINE->SetColor(rand()%255,0,0);
		GAME_ENGINE->FillRect(clip);
		break;

	case BULLET_MITRAILLEUR	:
	case BULLET_SUPER		:

		size.x= 5;
		size.y= 5;
		
		matCenter	.SetAsTranslate( -size/2 );
		matScale	.SetAsScale( m_Scale + 0.2*(rand()%100)/100 );
		//matTranslate.SetAsTranslate( m_Pos );
		
		GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));

		clip.left	= 0;
		clip.top	= 3;
		clip.right	= clip.left	+size.x;
		clip.bottom	= clip.top	+size.y;

		
		break;


	case BULLET_LAZER		: // nog geen sprite

		size.x= 15;
		size.y= 6;
		
		matCenter	.SetAsTranslate( -size/2 );
		//matScale	.SetAsScale( m_Scale );
		//matTranslate.SetAsTranslate( m_Pos );

		GAME_ENGINE->SetTransformMatrix( matCenter * matScale * matTranslate * (*m_MatViewPtr) );

		clip.left	= 0;
		clip.top	= 8;
		clip.right	= clip.left	+size.x; // lazer waarden.
		clip.bottom	= clip.top	+size.y;

		
		break;

	case BULLET_FLAME		: // nog geen sprite

		size.x= 10;
		size.y= 10;
		
		matCenter	.SetAsTranslate( -size/2 );
		//matScale	.SetAsScale( m_Scale );
		//matTranslate.SetAsTranslate( m_Pos );

		GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));

		clip.left	= 5;
		clip.top	= 0;
		clip.right	= clip.left	+size.x; // lazer waarden.
		clip.bottom	= clip.top	+size.y;

		break;

	}

	//GAME_ENGINE->SetColor(200,100,0);
	//GAME_ENGINE->FillRect(clip);
	
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip);

	//GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));
	//GAME_ENGINE->SetColor(255,0,0,100);
	//GAME_ENGINE->DrawLine(m_Pos.x-10, m_Pos.y, m_Pos.x+10, m_Pos.y, 0.3);
	//GAME_ENGINE->DrawLine(m_Pos.x, m_Pos.y-10, m_Pos.x, m_Pos.y+10, 0.3);
	//GAME_ENGINE->DrawLine(-10, 0, 10, 0);
	//GAME_ENGINE->DrawLine(0, -10, 0, 10);
	
}

void Bullet::CollideWith( ObjectBase *colliderptr, int otherType){
	// Bullet wordt geledeet door de tegenpartij
	/*if( m_Type==TYPE_ENEMY_BULLET ){
		if( otherType == TYPE_PLAYER )
			m_ObjectListPtr->Delete(this);
	}else if( m_Type==TYPE_PLAYER_BULLET ){
		if( otherType != TYPE_PLAYER )
			m_ObjectListPtr->Delete(this);
	}*/
}