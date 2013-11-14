//---------------------------
// Includes
//---------------------------
#include "EvilTurret.h"
#include "Explosion.h"
#include "Bullet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * EvilTurret::m_BmpSpritePtr= 0;

EvilTurret::EvilTurret(DOUBLE2 pos): ObjectBase(pos), m_DirectionFrame(0), m_ScrolIn(0), 
	m_ColorTick(0), m_bulletsCounter(0), m_Lives(10), m_ShootSwitch(0), m_ShootTimer(0)
{
	m_Type= TYPE_ENEMY;


	int gs= 16; //GridSize
	m_Pos.x= ((int)m_Pos.x/gs)*gs;
	m_Pos.y= ((int)m_Pos.y/gs)*gs;

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/EvilTurret.png");
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth()/3;
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight()/3;

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

EvilTurret::~EvilTurret(){ 
	m_ObjectListPtr->Add( new Explosion( m_Pos ) );
} // dont delete the static Bmp, windows will do it in the end

//---------------------------
// Own methods
//---------------------------

void EvilTurret::CollideWith( ObjectBase *colliderptr, int otherType)
{
	if( otherType == TYPE_PLAYER_BULLET ){
		--m_Lives;
		m_ObjectListPtr->Delete( colliderptr );
		if( m_Lives <= 0 ){
			m_ObjectListPtr->Delete( this ); // suicide
			return;
		}
	}
}

void EvilTurret::Tick(double deltaTime )
{
	
	m_ColorTick+= deltaTime*9;
	if( m_ColorTick >=3 ) m_ColorTick= 0;


	//DOUBLE2 schetmLingsBoven= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
	DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

	
	//m_DirectionFrame+= deltaTime*2; // tmp

	if( m_ScrolIn == 0 ){

		if( (*m_MatViewPtr) != MATRIX3X2() ){
			if( m_Pos.x < schetmRechtsOnder.x){ 
				m_ScrolIn+= 0.0001; // geactiveert door != 0 te zijn
			}
		}

	} else if( m_ScrolIn != 0 ){ // geactiveerd

		double newMax= 2*M_PI /12; // Kartelig laten bewegen
		double tussenWaarde= -m_PointingDir.AngleWith(DOUBLE2(1,0));
		tussenWaarde /= newMax;
		double naKomma= tussenWaarde- (int)tussenWaarde;
		tussenWaarde= (int)tussenWaarde;
		if( naKomma>0.5 ) ++tussenWaarde;
		m_DirRadians= tussenWaarde *newMax;


		//if( sin(paintDirRadians) < sin(M_PI/8*3) ){ // De y-as is geflipt!! de sinus geeft een omgekeerd resultaat
		m_DirectionFrame= 0;
		if( sin(m_DirRadians) < sin(-M_PI/12*1) ){
			m_DirectionFrame= 1;
			if( sin(m_DirRadians) < sin(-M_PI/12*3) ){
				m_DirectionFrame= 2;
			}
		}
		//}


		if( m_ScrolIn>m_SpriteSize.y){
			m_ScrolIn= m_SpriteSize.y; // heelemaal
		}else if (m_ScrolIn >= m_SpriteSize.y ){ // gewapend

			m_PointingDir= m_PlayerPtr->GetPos() - m_Pos;
			if( m_PlayerPtr->GetPos().x> m_Pos.x ) return;
			if( m_PlayerPtr->GetPos().y> m_Pos.y+32 ) return;

			// SCHIETEN ----------------------------------------
			m_ShootTimer+= deltaTime;
			if( m_ShootTimer>0.2 ){
				m_ShootTimer= 0;
				++m_bulletsCounter;
				if( m_bulletsCounter%7 < 3 ){
					DOUBLE2 bulletDir( cos(m_DirRadians), sin(m_DirRadians) );
					ObjectBase *bulletPtr= new Bullet(m_Pos+bulletDir*15, bulletDir*150, TYPE_ENEMY_BULLET, 0);
					m_ObjectListPtr->Add(bulletPtr);

				}

			}
			// -------------------------
		}else{ // nog aan het scrolen
			m_ScrolIn+= deltaTime*33;
		}

	}


}

void EvilTurret::Paint()
{

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter	.SetAsTranslate( -m_SpriteSize/2 );
	//matScale	.SetAsScale( m_Scale );
	matTranslate.SetAsTranslate( m_Pos.x, m_Pos.y +m_SpriteSize.x - m_ScrolIn );

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));
	

	

	RECT2 clip;
	clip.left	= ((int)m_DirectionFrame)%3* m_SpriteSize.x;
	clip.top	= (int)m_ColorTick * m_SpriteSize.y;
	clip.right	= clip.left + m_SpriteSize.x;
	clip.bottom	= clip.top  + m_ScrolIn;

	GAME_ENGINE->DrawBitmap( m_BmpSpritePtr, 0,0, clip );



	GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
}

