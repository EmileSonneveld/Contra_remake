//---------------------------
// Includes
//---------------------------
#include "HiddenSniper.h"
#include "Bullet.h"
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * HiddenSniper::m_BmpSpritePtr = 0;

HiddenSniper::HiddenSniper(DOUBLE2 pos) : ObjectBase(pos), m_AnimationTick(0), m_ShootSwitch(false), m_XScale(1), m_ShootCounter(0)
{
	m_Type = TYPE_ENEMY;

	int gs = 32; //GridSize, word door ObjectBase in het center van een cel gezet
	//m_Pos.x= ((int)m_Pos.x/gs+0.5)*gs;
	m_Pos.y = ((int)m_Pos.y / gs + 0.5)*gs;

	if (m_BmpSpritePtr == 0) {
		m_BmpSpritePtr = new Bitmap("./resources/HiddenSniper.png");
	}
	m_SpriteSize.x = m_BmpSpritePtr->GetHeight();
	m_SpriteSize.y = m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x / 2, -m_SpriteSize.y / 2, m_SpriteSize.x, m_SpriteSize.y);
	m_HitRegionPtr->SetPos(m_Pos);
}

HiddenSniper::~HiddenSniper() {
	m_ObjectListPtr->Add(new Explosion(m_Pos, 2));
}

//---------------------------
// Own methods
//---------------------------

void HiddenSniper::CollideWith(ObjectBase *colliderptr) {
	switch (colliderptr->GetType()) {

	case TYPE_PLAYER_BULLET:
		if (m_ShootSwitch) {
			// DIE
			m_ObjectListPtr->Delete(this);
			return;
		}
		break;
	}//*/
}

void HiddenSniper::Tick(double deltaTime)
{
	m_AnimationTick += deltaTime;

	if (m_AnimationTick > 3) {
		m_AnimationTick = 0;
		m_ShootSwitch = !m_ShootSwitch; // switch
	}

	double playerX = m_PlayerPtr->GetPos().x;

	if (playerX < m_Pos.x) { m_XScale = -1; }
	else { m_XScale = 1; }

	//DOUBLE2 screenLeftUp=  (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2() );
	DOUBLE2 screenRightDown = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()));

	if (m_Pos.x > screenRightDown.x - 16) return;


	if (m_ShootSwitch) {
		m_ShootCounter += deltaTime;
		if (m_ShootCounter >= 0.5) {
			m_ShootCounter = 0;
			DOUBLE2 shootPos;
			shootPos.x = m_Pos.x + m_XScale * 18;
			shootPos.y = m_Pos.y - 7;
			ObjectBase *bulletPtr = new Bullet(shootPos, DOUBLE2(m_XScale * 100, 0), TYPE_ENEMY_BULLET, 0);
			m_ObjectListPtr->Add(bulletPtr);
		}
	}

}

void HiddenSniper::Paint()
{

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter.SetAsTranslate(-m_SpriteSize / 2);
	matScale.SetAsScale(m_XScale, 1);
	matTranslate.SetAsTranslate(m_Pos);

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));


	RECT2 clip;
	clip.left = (int)(m_ShootSwitch * 2)* m_SpriteSize.x;
	clip.top = 0;
	clip.right = clip.left + m_SpriteSize.x;
	clip.bottom = clip.top + m_SpriteSize.y;

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip);



	GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));

	//GAME_ENGINE->SetColor(255,0,0, 100);   // Paint the HitRegion
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
}

