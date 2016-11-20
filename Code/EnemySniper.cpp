//---------------------------
// Includes
//---------------------------
#include "EnemySniper.h"
#include "Explosion.h"
#include "Bullet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * EnemySniper::m_BmpSpritePtr = 0;
EnemySniper::EnemySniper(DOUBLE2 pos) : ObjectBase(pos), m_PlayerPtr(0), m_State(STATE_NORMAL),
m_AnimationFrame(0), m_TimeToDie(0.1), m_bulletsToShoot(0), m_ShootCounter(0)
{
	m_Type = TYPE_ENEMY;

	int gs = 32; //GridSize
	m_Pos.x = ((int)m_Pos.x / gs + 0.5)*gs;
	m_Pos.y = ((int)m_Pos.y / gs + 0.5)*gs;

	if (m_BmpSpritePtr == 0) { // Bmp nog niet ingeladen
		m_BmpSpritePtr = new Bitmap("./resources/EnemySniper.png");
		m_BmpSpritePtr->SetTransparencyColor(255, 0, 255);
	}

	m_SpriteSize.x = 15;
	m_SpriteSize.y = 30;

	m_HitRegionPtr->CreateFromRect(-13 / 2, -29 / 2 + 5, 13, 29);
	m_HitRegionPtr->SetPos(m_Pos);
}

EnemySniper::~EnemySniper() {
	m_ObjectListPtr->Add(new Explosion(m_Pos, 2));
}



//---------------------------
// Own methods
//---------------------------



void EnemySniper::Tick(double deltaTime) {

	if (m_State != STATE_DIE) {

		m_PointingDir = m_PlayerPtr->GetPos() - m_Pos;


		//DOUBLE2 screenLeftTop=  (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
		DOUBLE2 screenRightDown = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()));

		if (m_Pos.x > screenRightDown.x - 16) return;

		double newMax = 2 * M_PI / 12; // Kartelig laten bewegen
		double tussenWaarde = -m_PointingDir.AngleWith(DOUBLE2(1, 0));
		tussenWaarde /= newMax;
		double naKomma = tussenWaarde - (int)tussenWaarde;
		tussenWaarde = (int)tussenWaarde;
		if (naKomma > 0.5) ++tussenWaarde;
		m_DirRadians = tussenWaarde *newMax;

		m_Pos = m_Pos;

		++m_ShootCounter;
		if (m_ShootCounter > 20) {
			m_ShootCounter = 0;
			if (m_State == STATE_NORMAL) {
				++m_bulletsToShoot; // Switch systeem
				if (m_bulletsToShoot >= 3) m_State = STATE_SHOOTING;

			}
			else if (m_State == STATE_SHOOTING) {
				--m_bulletsToShoot; // Switch systeem
				if (m_bulletsToShoot <= 0) m_State = STATE_NORMAL;

				DOUBLE2 bulletDir(cos(m_DirRadians), sin(m_DirRadians));
				ObjectBase *bulletPtr = new Bullet(m_Pos + bulletDir * 15, bulletDir * 100, TYPE_ENEMY_BULLET, BULLET_NORMAL);
				m_ObjectListPtr->Add(bulletPtr);
			}
		}

	}
	else { //STATE_DIE

		m_Pos += DOUBLE2(100 * -Sign(m_PointingDir.x), -110)*deltaTime;

		m_TimeToDie -= deltaTime;
		if (m_TimeToDie <= 0) {
			m_ObjectListPtr->Delete(this);
		}

	}
}

void EnemySniper::Paint()
{
	DOUBLE2 bodySize(24, 26), leggSize(16, 21);

	//if( m_AnimationFrame>=3) m_AnimationFrame=0;

	double newMax = 2 * M_PI / 8; // Kartelig laten bewegen
	double tussenWaarde = -m_PointingDir.AngleWith(DOUBLE2(1, 0));
	tussenWaarde /= newMax;
	double naKomma = tussenWaarde - (int)tussenWaarde;
	tussenWaarde = (int)tussenWaarde;
	if (naKomma > 0.5) ++tussenWaarde;
	double paintDirRadians = tussenWaarde *newMax;


	//if( sin(paintDirRadians) < sin(M_PI/8*3) ){ // De y-as is geflipt!! de sinus geeft een omgekeerd resultaat
	m_AnimationFrame = 0;
	if (sin(paintDirRadians) < sin(M_PI / 8 * 1)) {
		m_AnimationFrame = 1;
		if (sin(paintDirRadians) < sin(-M_PI / 8 * 1)) {
			m_AnimationFrame = 2;
		}
	}
	//}


	MATRIX3X2 matCenter, matScale, matTranslate;

	matCenter.SetAsTranslate(-bodySize.x / 2 + 4, -bodySize.y + 7);
	if (m_PointingDir.x > 0) { // voor te scalen/flippen
		matScale.SetAsScale(1, 1);
	}
	else matScale.SetAsScale(-1, 1);

	matTranslate.SetAsTranslate(m_Pos);
	RECT2 clip;

	// BODY ---------------------------------------
	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));

	clip.left = m_AnimationFrame * bodySize.x;
	clip.top = 0;
	clip.right = clip.left + bodySize.x;
	clip.bottom = clip.top + bodySize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip);

	// LEGS ---------------------------------------
	matCenter.SetAsTranslate(-leggSize.x / 2, 0);
	//matScale.	SetAsScale( m_PointingDir.x, 1);
	matTranslate.SetAsTranslate(m_Pos);

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));
	clip.left = 0;
	clip.top = bodySize.y;
	clip.right = clip.left + leggSize.x;
	clip.bottom = clip.top + leggSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip);


	/*GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));
	GAME_ENGINE->SetColor(255,0,0, 200);
	GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
	GAME_ENGINE->FillEllipse(m_Pos,2,2);//*/
}

void EnemySniper::CollideWith(ObjectBase *colliderptr) {
	if (m_State != STATE_DIE)
		if (colliderptr->GetType() == TYPE_PLAYER_BULLET) {
			m_State = STATE_DIE;
			m_ObjectListPtr->Delete(colliderptr); // delete the bullet
		}
}
