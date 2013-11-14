//---------------------------
// Includes
//---------------------------
#include "Box.h"
#include "Bullet.h"
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Box::m_BmpSpritePtr= 0;

Box::Box(DOUBLE2 pos): ObjectBase(pos), m_PointingDir(), m_ShootCounter(0), m_State(STATE_DESACTACTIVATE), m_bulletsToShoot(4)
{
	int gs= 32; //GridSize
	m_Pos.x= ((int)m_Pos.x/gs+0.5)*gs;
	m_Pos.y= ((int)m_Pos.y/gs+0.5)*gs;
	m_Type= TYPE_ENEMY; // voor collitions met bullets

	m_Lives= 7;

	m_AnimationTik=0;
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/box.gif");
		//m_BmpSpritePtr->SetTransparencyColor(0,0,0);
		if (!m_BmpSpritePtr->Exists())
			GAME_ENGINE->MessageBox("Box bitmap Fail!");
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth() /3;
	m_SpriteSize.y= m_SpriteSize.x;

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

Box::~Box(){ // static m_BmpSpritePtr word automatis gedeleet
	m_ObjectListPtr->Add( new Explosion(m_Pos) );
}

//---------------------------
// Own methods
//---------------------------

void Box::CollideWith( ObjectBase *colliderptr, int otherType){ // als dit word geCaled, dan is er al een collition
	//m_ObjectListPtr->Delete(colliderptr);
	if( otherType== TYPE_PLAYER_BULLET ){
		m_ObjectListPtr->Delete(colliderptr); // delete the bullet
		--m_Lives;
		if( m_Lives<=0 ){
			OutputDebugString("Box Died");

			m_ObjectListPtr->Delete(this);
		}
	}
}

void Box::Tick(double deltaTime )
{
	m_AnimationTik+=6*deltaTime;
	m_PointingDir= (m_PlayerPtr->GetPos() -m_Pos).Normalized();

	DOUBLE2 schetmLingsBoven=  (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
	DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

	/*m_State= STATE_DESACTACTIVATE;
	if( m_Pos.x<schetmRechtsOnder.x ){
	m_State= STATE_NORMAL;
	
	//if( m_Pos.x< schetmLingsBoven.x-20 )	m_ObjectListPtr->Delete(this);
	} */

	if( m_Pos.x < schetmRechtsOnder.x-16 )
	if(  m_State != STATE_DESACTACTIVATE ){
		if( m_Pos.x< schetmLingsBoven.x+16 )
			m_State= STATE_DESACTACTIVATE;

		m_ShootCounter+=0.5;
		if( m_ShootCounter>20 ){
			m_ShootCounter=0;


			double newMax= 2*M_PI/12; // Kartelig laten bewegen
			double tussenWaarde= -m_PointingDir.AngleWith(DOUBLE2(1,0));
			tussenWaarde /= newMax;
			double naKomma= tussenWaarde- (int)tussenWaarde;
			tussenWaarde= (int)tussenWaarde;
			if( naKomma>0.5 ) ++tussenWaarde;
			m_DirRadians= tussenWaarde *newMax;


			if( m_State == STATE_NORMAL ){
				++m_bulletsToShoot;
				if( m_bulletsToShoot>=5 ) m_State= STATE_SHOOTING;

			}else if( m_State == STATE_SHOOTING ){
				--m_bulletsToShoot;
				if( m_bulletsToShoot<=0 ) m_State= STATE_NORMAL;

				DOUBLE2 bulletDir( cos(m_DirRadians), sin(m_DirRadians) );
				ObjectBase *bulletPtr= new Bullet(m_Pos+bulletDir*15, bulletDir*100, TYPE_ENEMY_BULLET, 0);
				m_ObjectListPtr->Add(bulletPtr);
			}

		}

	}else { // STATE_DESACTACTIVATE
		if( m_Pos.x<schetmRechtsOnder.x )
			m_State= STATE_NORMAL;
	}

}

void Box::Paint()
{
	MATRIX3X2 matCenter, matRotate, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));


	RECT2 clip;
	clip.left	= ((int)m_AnimationTik)%3* m_SpriteSize.x;
	clip.top	= 0;
	clip.right	= clip.left + m_SpriteSize.x;
	clip.bottom	= clip.top  + m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, 0,0, clip );
	//*/

	if( m_State != STATE_DESACTACTIVATE ){
		DOUBLE2 cannonSize(22,13);
		
		//	radians= atan( m_PointingDir.y/ m_PointingDir.x) // te makkelijk om waar te zijn

		matCenter.   SetAsTranslate( -cannonSize.y/2, -cannonSize.y/2 );
		matRotate.   SetAsRotate( m_DirRadians );
		matTranslate.SetAsTranslate( m_Pos );

		GAME_ENGINE->SetTransformMatrix(matCenter * matRotate * matTranslate * (*m_MatViewPtr));

		clip.left	= 0;
		clip.top	= 2*m_SpriteSize.y;
		clip.right	= clip.left + cannonSize.x;
		clip.bottom	= clip.top  + cannonSize.y;
		GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, 0,0, clip );
	}

	/*GAME_ENGINE->SetTransformMatrix( *m_MatViewPtr );
	GAME_ENGINE->SetColor(255,20,20,50);
	GAME_ENGINE->FillHitRegion( m_HitRegionPtr );*/


}//*/
