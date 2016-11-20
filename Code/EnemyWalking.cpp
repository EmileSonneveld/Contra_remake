//---------------------------
// Includes
//---------------------------
#include "EnemyWalking.h"
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * EnemyWalking::m_BmpSpritePtr = 0;

EnemyWalking::EnemyWalking(DOUBLE2 pos) : ObjectBase(pos), m_AnimationTick(0), m_PointingDir(), m_TimeToDie(30)
{
	m_State = STATE_NORMAL;
	m_Type = TYPE_ENEMY_WALKING;

	if (m_BmpSpritePtr == 0) { // Bmp nog niet ingeladen
		m_BmpSpritePtr = new Bitmap("./resources/EnemyWalking.gif");
		m_BmpSpritePtr->SetTransparencyColor(255, 0, 255);
	}
	m_SpriteSize.x = m_BmpSpritePtr->GetWidth() / 6;
	m_SpriteSize.y = m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x / 2, -m_SpriteSize.y / 2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

EnemyWalking::~EnemyWalking() { // dont delete the static Bmp
	m_ObjectListPtr->Add(new Explosion(m_Pos, 2));
}

//---------------------------
// Own methods
//---------------------------

void EnemyWalking::CollideWith(ObjectBase *colliderptr) {
	if (m_State != STATE_DIE) {
		if (colliderptr->GetType() == TYPE_PLAYER_BULLET)
			m_ObjectListPtr->Delete(colliderptr); // delete the bullet
		if (colliderptr->GetType() == TYPE_PLAYER_BULLET) { // || colliderptr->GetType()==TYPE_PLAYER 
			StartToDie();
		}
	}
}


void EnemyWalking::SetPlayerPtr(ObjectBase *playerPtr) {
	m_PlayerPtr = playerPtr;
	m_PointingDir = m_PlayerPtr->GetPos() - m_Pos;
	if (m_PointingDir.x > 0) {
		m_PointingDir.x = 1;
	}
	else m_PointingDir.x = -1;
	m_Velocity.x = 100 * m_PointingDir.x;
}

void EnemyWalking::Tick(double deltaTime)
{
	if (m_State == STATE_DIE) {

		m_Pos += m_Velocity*deltaTime;

		--m_TimeToDie;
		if (m_TimeToDie <= 0) {
			m_ObjectListPtr->Delete(this);
		}
		return;
	}


	m_Velocity.y += 1000 * deltaTime; // Gravity.

	m_PointingDir = m_PlayerPtr->GetPos() - m_Pos;
	//if (GAME_ENGINE->IsKeyDown(VK_RIGHT	)) { m_PointingDir.x= 1;}
	//if (GAME_ENGINE->IsKeyDown( VK_LEFT	)) { m_PointingDir.x=-1;}
	if (m_PointingDir.x > 0) {
		m_PointingDir.x = 1;
	}
	else m_PointingDir.x = -1;
	//m_PointingDir.x= (int)(m_PointingDir.x);

	m_Pos += m_Velocity*deltaTime;

	m_HitRegionPtr->SetPos(m_Pos);
	DoCollitions(&m_HitRegionPtr, &m_HitRegionPtr, &m_Pos, &m_Velocity);

	//m_Velocity.x= 0;


	m_AnimationTick += 0.05;
	if (m_AnimationTick >= 6) {
		m_AnimationTick = 0;
		m_Velocity.x = 80 * m_PointingDir.x;
	}

	DOUBLE2 screenLeftTop = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2());
	DOUBLE2 screenRightDown = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()));


	if (m_Pos.x < screenLeftTop.x - m_SpriteSize.x)
		m_ObjectListPtr->Delete(this); // gevaarlijk!

}

void EnemyWalking::Paint()
{


	/* // HitRegion
	GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr );
	GAME_ENGINE->SetColor(255,5,5,200);
	GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
	GAME_ENGINE->FillEllipse(m_Pos, 5, 6);*/


	int flip = (int)m_Velocity.x;
	if (flip > 0) {
		flip = 1;
	}
	else flip = -1;

	MATRIX3X2 matCenter, matTranslate, matScale;
	matCenter.SetAsTranslate(-m_SpriteSize / 2);
	matScale.SetAsScale(flip, 1);
	matTranslate.SetAsTranslate(m_Pos);

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));

	RECT2 clip;
	clip.left = (int)m_AnimationTick*m_SpriteSize.x;
	clip.top = 0;
	clip.right = clip.left + m_SpriteSize.x;
	clip.bottom = clip.top + m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip);

}

void EnemyWalking::StartToDie() {
	m_State = STATE_DIE;
	m_AnimationTick = 5;
	m_TimeToDie = 30;
	m_Velocity.x = 90 * -m_PointingDir.x;
	m_Velocity.y = -100;
	m_HitRegionPtr->SetPos(999888, 999888);
}




void EnemyWalking::DoCollitions(HitRegion **hitHoriPtr, HitRegion **hitVertPtr, DOUBLE2 *pos, DOUBLE2 *velocity)
{

	// Y
	m_OnGround = false;
	if (m_Velocity.y >= 0) {
		RECT2 collisionRectV = (*hitVertPtr)->CollisionTest(m_ObjectListPtr->GetHitTerrain());
		double deltaY = ReturnGoodLen(collisionRectV.top, collisionRectV.bottom, (*pos).y);
		if (deltaY < 0) {
			RECT2 checkHeight = (*hitVertPtr)->GetBounds();
			double height = abs(checkHeight.bottom - checkHeight.top);
			if (deltaY<height && deltaY>-height) {
				(*pos).y += deltaY;
				if (deltaY* (*velocity).y < 0) // verschillend teken
					(*velocity).y = 0;
				m_OnGround = true;
				//GAME_ENGINE->SetColor(5,5,255,200);
				//GAME_ENGINE->FillRect(collisionRectV);
			}
		}
	}

	(*hitVertPtr)->SetPos(*pos);
	(*hitHoriPtr)->SetPos(*pos);


	// X
	/*RECT2 collisionRectH= (*hitHoriPtr)->CollisionTest(m_HitTerrainPtr);
	//RECT2 collisionRectH = m_GridPtr->ColWithGrid(m_RectBBox + m_Pos); // NEW!
	double deltaX= ReturnGoodLen(collisionRectH.left, collisionRectH.right, (*pos).x);

	if( deltaX!=0 ){
		RECT2 checkWidth= (*hitHoriPtr)->GetBounds();
		double width= abs( checkWidth.right- checkWidth.left );
		if( deltaX<width && deltaX>-width ){ //
			(*pos).x+= deltaX;
			if( deltaX* (*velocity).x <0 ) // verschillend teken
				(*velocity).x =0;
		}
	}//*/

	(*hitVertPtr)->SetPos(*pos);
	(*hitHoriPtr)->SetPos(*pos);
}//*/

double EnemyWalking::ReturnGoodLen(double getal1, double getal2, double centerXY)
{
	double delta = 0;
	delta = abs(getal1 - getal2);

	if (delta > 0.001) { // er is een botsing
		double colCenter = (getal1 + getal2) / 2;
		if (centerXY < colCenter) delta *= -1;
	}
	return delta;
}

