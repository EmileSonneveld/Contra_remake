//---------------------------
// Includes
//---------------------------
#include "Player.h"
#include "Bullet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Player::m_BmpSpritePtr = 0;

Player::Player(int x, int y) :ObjectBase(DOUBLE2(x, y))
, m_ObjectListPtr(0), m_ShootCounter(0), m_PointingDir()
, m_Colide(true), m_CenterPos(), m_Lives(5), m_BulletDir()
, m_JumpRotation(0), m_InvincebleTimer(3), m_AutomaticFinalRun(0)
{
	m_Type = TYPE_PLAYER;
	m_BulletType = BULLET_NORMAL;


	m_PointingDir.x = 1;
	m_PointingDir.y = 0;
	m_OnGround = false;

	if (m_BmpSpritePtr == 0) { // Load the bitmap:
		m_BmpSpritePtr = new Bitmap("./resources/Player.png");
		//m_BmpSpritePtr->SetTransparencyColor(0, 128, 0);
	}

	m_State = STATE_NORMAL;
	m_LegsFrame = 0;
	m_BodyFrame = 0;

	m_BodySize.x = 25;
	m_BodySize.y = 33;
	m_LegsSize.x = 21;
	m_LegsSize.y = 20;
	m_BBoxSize.x = max(m_BodySize.x, m_LegsSize.x); // tijdelijk
	m_BBoxSize.y = m_LegsSize.y;

	m_SpriteSize.x = 15;
	m_SpriteSize.y = 34;

	m_HitBBoxV = new HitRegion();
	m_HitBBoxV->CreateFromRect(-3, -m_BBoxSize.y, 6, m_BBoxSize.y);

	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x / 2, -m_SpriteSize.y, m_SpriteSize.x, m_SpriteSize.y);


}

Player::~Player()
{
	delete m_HitBBoxV;
	delete m_BmpSpritePtr;
	//m_HitBBox = 0;
	m_BmpSpritePtr = 0;
}






//---------------------------------------------------------------------------------
// Own methods
//---------------------------------------------------------------------------------


void Player::CollideWith(ObjectBase *colliderptr) {
	// At this point we are sure to have collided with something

	switch (colliderptr->GetType()) {
	case TYPE_ENEMY_BULLET:
		StartToDie();
		OutputDebugString(" (By ENEMY_BULLET)");
		m_ObjectListPtr->Delete(colliderptr); // delete the bullet
		break;

	case TYPE_ENEMY_WALKING:
		StartToDie();
		OutputDebugString(" (By ENEMY_WALKING)");
		break;


	case TYPE_POWERUP:
		OutputDebugString("\nPOWERUP!! ^^");
		break;
	}
}


void Player::StartToDie() {
	OutputDebugString("\nAauw, Player Hitted!");
	if (m_InvincebleTimer <= 0) {
		if (m_State != STATE_DIE) {
			m_State = STATE_DIE;
			m_TimeToDie = 1; // seconds
			m_Velocity.x = -m_PointingDir.x * 20;
			m_Velocity.y = -200;
		}
		else {
			OutputDebugString(", But he is already dead");
		}
	}
	else {
		OutputDebugString(", But he is invinsible =D");
	}
}


void Player::DieAndRespawn() {
	m_State = STATE_NORMAL;
	m_BulletType = BULLET_NORMAL;
	m_TimeToDie = 30;
	m_Velocity = DOUBLE2();

	if (m_Lives <= 0) {
		GAME_ENGINE->MessageBox("GAME OVER!!");
		GAME_ENGINE->QuitGame();
	}

	--m_Lives;

	DOUBLE2 schetmLingsBoven = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2());
	//DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );
	m_Pos = schetmLingsBoven + DOUBLE2(30, -40);
	m_InvincebleTimer = 3; // can't toutch this! in seconds

}


void Player::Tick(double deltaTime)
{
	if (m_InvincebleTimer > 0)
		m_InvincebleTimer -= deltaTime;


	// BASIC MOVEMENTS ------------------------------------------------------------------------ BASIC MOVEMENTS ----
	m_Velocity.y += 900 * deltaTime; // Gravity.
	m_Pos += m_Velocity*deltaTime;
	m_Velocity.x *= 0.8; // Friction.
	m_HitBBoxV->SetPos(m_Pos);
	//m_HitBBoxH->SetPos(m_Pos);


	// COLLISIONS WITH THE GROUND ------------------------------------------------------------- COLLISIONS WITH THE GROUND ----
	if (m_Colide) {
		m_OnGround = false;
		for (unsigned int i = 0; i < m_LevelHitRegions.size(); ++i) {
			if (DoCollitions(/*m_HitBBoxH, */m_HitBBoxV, m_Pos, m_Velocity, m_LevelHitRegions.at(i))) { // -> Paint
				m_OnGround = true;
				if (m_State == STATE_SWIM) m_State = STATE_NORMAL;
			}
		}
	}




	// Binnen de harde grenzen blijven: ----------------------------------------------
	m_Pos.x = min(m_LevelMax.x, max(0, m_Pos.x));
	m_Pos.y = min(m_LevelMax.y + 60, max(0, m_Pos.y));
	if (m_Pos.x >= m_LevelMax.x)
		GAME_ENGINE->QuitGame(); // gedaan!

	if (m_Pos.y > m_LevelMax.y + 30 && m_Pos.x > m_LevelMax.x / 2 + 100) { // kliff
		m_InvincebleTimer = 0;
		DieAndRespawn();
	}


	// Dood? Stop dan hier! ----------------------------------------------------------- Dood? Stop dan hier! ----
	if (m_State == STATE_DIE) {
		m_TimeToDie -= deltaTime;
		if (m_TimeToDie <= 0) {
			DieAndRespawn();
		}
		return; // Als hij dood aan het gaan is, dan stopt de code hier
	}


	/*if( m_AutomaticFinalRun ){
		m_Velocity.x= WALKSPEED;

	}*/

	// ROUWE RICHTING BEPALEN -------------------------------------------------
	m_PointingDir.y = 0;
	if (GAME_ENGINE->IsKeyDown(VK_RIGHT)) { m_PointingDir.x = 1; }
	if (GAME_ENGINE->IsKeyDown(VK_LEFT)) { m_PointingDir.x = -1; }
	if (GAME_ENGINE->IsKeyDown(VK_DOWN)) { m_PointingDir.y = 1; }
	if (GAME_ENGINE->IsKeyDown(VK_UP)) { m_PointingDir.y = -1; }



	CalculateStateAndFrame(); /// -----------------------------------------------





	// CONTROLS ---------------------------------------------------------------------- CONTROLS ----
	if (GAME_ENGINE->IsKeyDown('B')) {
		m_Pos.x = m_LevelMax.x - 300;
		m_Pos.y = 20;
	}


	// JUMPEN -------------------------
	if (GAME_ENGINE->IsKeyDown('X') && !GAME_ENGINE->IsKeyDown(VK_DOWN)) { Jump(300); }

	if (m_OnGround) { // BEWEGEN -----------------------------

		if ((GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_AutomaticFinalRun) || GAME_ENGINE->IsKeyDown(VK_LEFT)) { // gewone lings en rechtes
			//if( !GAME_ENGINE->IsKeyDown(VK_DOWN) ){
			m_Velocity.x = WALKSPEED * m_PointingDir.x;
			if (GAME_ENGINE->IsKeyDown('G')) m_Velocity.x *= 4; // GodMode
			m_LegsFrame += 10 * deltaTime;
			//}
		}

	}
	else { // springend bewgen
		if ((GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_AutomaticFinalRun) || GAME_ENGINE->IsKeyDown(VK_LEFT))
			m_Velocity.x = WALKSPEED*0.8 * m_PointingDir.x;
	}


	if (m_Colide == false) { // hij is door een platform aan het vallen
		int clolliding = false;
		for (unsigned int i = 0; i < m_LevelHitRegions.size(); ++i) {
			if (m_HitBBoxV->HitTest(m_LevelHitRegions.at(0))) // niet bukken op de brug...
				clolliding = true;
		}
		if (!clolliding) {
			m_Colide = true; // just er door gevallen
		}
		if (GAME_ENGINE->IsKeyDown('H')) m_Colide = true; // DEBUG
	}





	if (!GAME_ENGINE->IsKeyDown('G')) { // GOD MODE
		DOUBLE2 schetmLingsBoven = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2());
		m_Pos.x = max(schetmLingsBoven.x, m_Pos.x); // niet meer naar lings kunnen.
	}


	CalculateBulletSpawn();


	// SCHIETEN --------------------------------------------------------------
	m_ShootCounter += deltaTime; // in secondes

	if (GAME_ENGINE->IsKeyDown('Z')) Shoot();

	m_HitRegionPtr->SetPos(m_Pos);

}


void Player::Shoot()
{
	bool canIShoot = false;
	switch (m_BulletType) {

	case BULLET_NORMAL:
		if (m_ShootCounter > 0.5) canIShoot = true;
		break;

	case BULLET_MITRAILLEUR:
		if (m_ShootCounter > 0.1) canIShoot = true;
		break;

	case BULLET_SUPER: // spread gun
	{
		if (m_ShootCounter > 0.2) {
			canIShoot = true;
			double dir = m_BulletDir.AngleWith(DOUBLE2(1, 0));
			double angleWidth = M_PI_2 / 3;
			for (double i = -angleWidth; i <= angleWidth; i += angleWidth * 2 / 4) {
				double minniDir = dir + i;
				Bullet *bulletPtr = new Bullet(m_BulletSpawn, DOUBLE2(cos(minniDir), -sin(minniDir)) * 350, TYPE_PLAYER_BULLET, m_BulletType);
				m_ObjectListPtr->Add(bulletPtr);
			}
		}
		break;
	}
	case BULLET_LAZER:
		if (m_ShootCounter > 0.1) canIShoot = true;
		break;

	case BULLET_FLAME:
		if (m_ShootCounter > 1) canIShoot = true;
		break;

	}

	if (canIShoot) {

		m_ShootCounter = 0;
		Bullet *bulletPtr = new Bullet(m_BulletSpawn, m_BulletDir.Normalized() * 350, TYPE_PLAYER_BULLET, m_BulletType);
		m_ObjectListPtr->Add(bulletPtr);

	}

}

void Player::CalculateStateAndFrame() {

	if (!m_OnGround) {
		int onderMarge = 8;// Ondaraan in de map (Water/Kliff)
		double groundDist = m_LevelMax.y - onderMarge - (m_Pos.y);
		if (groundDist < 0) {
			if (m_Pos.x < m_LevelMax.x / 2 + 100) {// in het water
				m_Velocity.y = 0;
				m_Pos.y = m_LevelMax.y - onderMarge;
				m_State = STATE_SWIM;
				m_Colide = true;
				m_OnGround = true;
			}
		}
	}


	if (m_OnGround) { // on the ground (of in het water)

		if ((GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_AutomaticFinalRun) || GAME_ENGINE->IsKeyDown(VK_LEFT))
		{
			if (m_State == STATE_SWIM || m_State == STATE_DIVE)
			{
				//nix speciaal
			}
			else
			{
				m_State = STATE_NORMAL;
			}

		}
		else // No left or right
		{
			m_LegsFrame = 0;
			if (GAME_ENGINE->IsKeyDown(VK_DOWN))
			{
				if (m_State == STATE_SWIM) m_State = STATE_DIVE;
				if (m_State != STATE_DIVE) m_State = STATE_CRAWL;
				if (GAME_ENGINE->IsKeyDown('X')) { m_Colide = false; } // laten vallen
			}
			else
			{
				if (m_State == STATE_DIVE) m_State = STATE_SWIM;
				if (m_State != STATE_SWIM) m_State = STATE_NORMAL; // no up or down

			}
		}



		m_BodyFrame = 1; // BodyFrame Bepalen ---------------------------------------------------

		if ((GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_AutomaticFinalRun) || GAME_ENGINE->IsKeyDown(VK_LEFT))
		{
			if (GAME_ENGINE->IsKeyDown(VK_UP)) m_BodyFrame = 2;
			if (GAME_ENGINE->IsKeyDown(VK_DOWN)) m_BodyFrame = 0;
		}
		else
		{
			if (GAME_ENGINE->IsKeyDown(VK_UP)) m_BodyFrame = 3;
			if (GAME_ENGINE->IsKeyDown(VK_DOWN)) m_BodyFrame = 1;
		}



	}
	else { // in mid-air (not on ground)

		m_State = STATE_JUMP;
		m_JumpRotation += m_PointingDir.x / 12;

	}
}


void Player::CalculateBulletSpawn()
{
	// POINTING DIR RAFINEREN
	m_BulletDir = m_PointingDir;
	if (GAME_ENGINE->IsKeyDown(VK_UP) || GAME_ENGINE->IsKeyDown(VK_DOWN)) {
		if (!(GAME_ENGINE->IsKeyDown(VK_RIGHT) || m_AutomaticFinalRun) && !GAME_ENGINE->IsKeyDown(VK_LEFT)) {
			m_BulletDir.x = 0; // geen L of R
		}
		if (m_State == STATE_CRAWL) {
			m_BulletDir.x = m_PointingDir.x;
			m_BulletDir.y = 0;
		}
	}


	// SCHIET POS BEPALEN --------------------------------------------------------------
	m_CenterPos = m_Pos;
	m_CenterPos.y -= m_LegsSize.y;


	int xDis = 0; // hoe ver van de symmetrie lijn

	switch (m_State) {
	case STATE_NORMAL:

		if (GAME_ENGINE->IsKeyDown(VK_UP)) {
			m_BulletSpawn.y = m_CenterPos.y - 21;
			xDis = 3;
		}
		else {
			m_BulletSpawn.y = m_CenterPos.y - 5;
			xDis = 12;
		}
		// Hier moet meer blahblah...
		break;

	case STATE_CRAWL:
		m_BulletSpawn.y = m_CenterPos.y + 9;
		xDis = 20;
		break;

	case STATE_JUMP:
		m_BulletSpawn.y = m_CenterPos.y;
		xDis = 0;
		break;

	case STATE_SWIM:
		m_BulletSpawn.y = m_CenterPos.y;
		xDis = 12;
		if (GAME_ENGINE->IsKeyDown(VK_UP)) {
			m_BulletSpawn.y = m_CenterPos.y - 21;
			xDis = 3;
		}
		break;

	case STATE_DIVE:
		m_BulletSpawn.y = -999;
		break;

	case STATE_DIE:
		m_BulletSpawn.y = -999;
		break;
	}

	m_BulletSpawn.x = m_CenterPos.x + m_PointingDir.x*xDis;

}


void Player::Paint()
{
	// DEBUG ------------------------------------------------------------------------------------------------

	GAME_ENGINE->SetColor(255, 2, 2, 100);

	//GAME_ENGINE->FillEllipse(m_Pos, 3, 3);
	//GAME_ENGINE->FillHitRegion(m_HitRegionPtr);
	//DoCollitions(&m_HitBBoxH, &m_HitBBoxV, &m_Pos, &m_Velocety);


	if (m_InvincebleTimer > 0) {
		if (rand() % 4 < 3) {
			//--//--//--//--//
			DrawPlayer();   // large script
			//--//--//--//--//
		}
	}
	else {
		//--//--//--//--//
		DrawPlayer();   // large script
		//--//--//--//--//
	}


	GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr);
	DOUBLE2 schetmLingsBoven = (*m_MatViewPtr).Inverse().TransformPoint(DOUBLE2());
	//DOUBLE2 schetmRechtsOnder= (*m_MatViewPtr).Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

	GAME_ENGINE->SetColor(5, 2, 255, 100);
	DOUBLE2 MedailSize(8, 16);
	RECT2 clip;
	clip.left = 0;
	clip.top = 90;
	clip.right = clip.left + MedailSize.x;
	clip.bottom = clip.top + MedailSize.y;

	for (int i = 0; i < m_Lives; ++i) {
		//GAME_ENGINE->FillRect(schetmLingsBoven.x+10 + MedailSize.x*1.5*i, schetmLingsBoven.y+ 10, MedailSize.x, MedailSize.y);
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, schetmLingsBoven.x + 4 + MedailSize.x*1.2*i, schetmLingsBoven.y + 1, clip);
	}
}


void Player::DrawPlayer() {

	MATRIX3X2 matCenter, matTranslate, matScale, matRotate;
	matScale.SetAsScale(m_PointingDir.x, 1);
	RECT2 clip;
	DOUBLE2 croawlSize(34, 17), jumpSize(20, 16), swimSize(17, 15);

	/// EN NU DE GROTSTE SCITCH VAN MIJN LEVEN:
	switch (m_State) {

	case STATE_CRAWL:
		m_HitRegionPtr->CreateFromRect(-croawlSize.x / 2, -croawlSize.y, croawlSize.x, croawlSize.y);
		// ON THE GROUND -----------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-croawlSize.x / 2, -croawlSize.y);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y);

		m_BodyFrame = m_BodyFrame % 4;
		clip.left = 0;
		clip.top = m_BodySize.y + m_LegsSize.y;
		clip.right = clip.left + croawlSize.x;
		clip.bottom = clip.top + croawlSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap
		break;

	case STATE_NORMAL:
		m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x / 2, -m_SpriteSize.y, m_SpriteSize.x, m_SpriteSize.y);
		// LEGS ---------------------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-m_LegsSize.x / 2, -m_LegsSize.y);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y);

		clip.left = ((int)m_LegsFrame) % 3 * m_LegsSize.x;
		clip.top = m_BodySize.y;
		clip.right = clip.left + m_LegsSize.x;
		clip.bottom = clip.top + m_LegsSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap

		// BODY ---------------------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-m_BodySize.x / 2, -m_BodySize.y);
		matTranslate.SetAsTranslate(m_Pos.x + m_PointingDir.x * 4, m_Pos.y - m_LegsSize.y + 6);

		m_BodyFrame = m_BodyFrame % 4;
		clip.left = (int)m_BodyFrame *m_BodySize.x;
		clip.top = 0;
		clip.right = clip.left + m_BodySize.x;
		clip.bottom = clip.top + m_BodySize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap

		break;

	case STATE_JUMP:
		m_HitRegionPtr->CreateFromRect(-jumpSize.x / 2, -jumpSize.y, jumpSize.x, jumpSize.y);
		// NINJA JUMP BOLLEKE! ------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-jumpSize / 2);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y - 15);
		matRotate.SetAsRotate(m_JumpRotation);

		clip.left = croawlSize.x;
		clip.top = m_BodySize.y + m_LegsSize.y;
		clip.right = clip.left + jumpSize.x;
		clip.bottom = clip.top + jumpSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matRotate*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap
		break;


	case STATE_SWIM:
		m_HitRegionPtr->CreateFromRect(-swimSize.x / 2, -swimSize.y * 2, swimSize.x, swimSize.y);
		// SWIM: WATER RIPPLE ------------------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-jumpSize.x / 2, -jumpSize.y);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y - 15 + 5);

		clip.left = croawlSize.x + jumpSize.x + swimSize.x;
		//if (GAME_ENGINE->IsKeyDown( VK_DOWN ))
		clip.top = m_BodySize.y + m_LegsSize.y;
		clip.right = clip.left + swimSize.x;
		clip.bottom = clip.top + swimSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap

		// BODY --------------------------------------------------------------------
		matCenter.SetAsTranslate(-m_BodySize.x / 2, -m_BodySize.y);
		matTranslate.SetAsTranslate(m_Pos.x + m_PointingDir.x * 4, m_Pos.y - m_LegsSize.y + 6 + 5);

		m_BodyFrame = m_BodyFrame % 4;
		clip.left = (int)m_BodyFrame *m_BodySize.x;
		clip.top = 0;
		clip.right = clip.left + m_BodySize.x;
		clip.bottom = clip.top + m_BodySize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap
		break;

	case STATE_DIVE:
		m_HitRegionPtr->CreateFromRect(-99999, -99999, 0, 0); // practically untoutchable
		// SWIM: WATER RIPPLE ------------------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-jumpSize.x / 2, -jumpSize.y);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y - 15 + 5);

		clip.left = croawlSize.x + jumpSize.x;
		//if (GAME_ENGINE->IsKeyDown( VK_DOWN ))
		clip.left += swimSize.x;
		clip.top = m_BodySize.y + m_LegsSize.y;
		clip.right = clip.left + swimSize.x;
		clip.bottom = clip.top + swimSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap

		break;

	case STATE_DIE:
		m_HitRegionPtr->CreateFromRect(-croawlSize.x / 2, -croawlSize.y, croawlSize.x, croawlSize.y);
		// ON THE GROUND -----------------------------------------------------------------------------------
		matCenter.SetAsTranslate(-croawlSize.x / 2, -croawlSize.y);
		matTranslate.SetAsTranslate(m_Pos.x, m_Pos.y);

		m_BodyFrame = m_BodyFrame % 4;
		clip.left = 0;
		clip.top = m_BodySize.y + m_LegsSize.y + croawlSize.y;
		clip.right = clip.left + croawlSize.x;
		clip.bottom = clip.top + croawlSize.y;

		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*(*m_MatViewPtr));
		GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0, 0, clip); // Finaly, draw the bitmap
		break;
	}

}


void Player::SetGlobalVars(ObjectList *objectListPtr, DOUBLE2 LevelMax)
{
	//m_HitTerrainPtr = hitTerrainPtr;
	m_ObjectListPtr = objectListPtr;
	m_LevelMax = LevelMax;
}


void Player::Jump(int force)
{
	for (unsigned int i = 0; i < m_LevelHitRegions.size(); ++i) {
		if (m_LevelHitRegions.at(i)->HitTest(m_Pos.x, m_Pos.y)) {
			//if ( m_Pos.y+m_BBoxSize.y>= m_LevelMax.y || ){
			if (m_Velocity.y < 0.0000001) {
				m_Velocity.y = -force;
				m_State = STATE_JUMP;
			}
		}
	}
}


bool Player::DoCollitions(HitRegion *hitVertPtr, DOUBLE2& posRef, DOUBLE2& velocityRef, HitRegion *levelHitPtr)
{
	bool returnCollide = false;
	//GAME_ENGINE->SetColor(225,5,255,200);
	//GAME_ENGINE->FillHitRegion(*hitVertPtr);
	// Y
	if (m_Velocity.y >= 0) {
		RECT2 collisionRectV = hitVertPtr->CollisionTest(levelHitPtr);
		double deltaY = ReturnGoodLen(collisionRectV.top, collisionRectV.bottom, posRef.y - m_LegsSize.y);
		if (deltaY < 0) {
			RECT2 checkHeight = hitVertPtr->GetBounds();
			double height = abs(checkHeight.bottom - checkHeight.top);
			if (deltaY<height && deltaY>-height) {
				posRef.y += deltaY;
				if (deltaY* velocityRef.y < 0) // verschillend teken
					velocityRef.y = 0;
				returnCollide = true;
				//GAME_ENGINE->SetColor(5,5,255,200);
				//GAME_ENGINE->FillRect(collisionRectV);
			}
		}
	}

	hitVertPtr->SetPos(posRef);
	//hitHoriPtr->SetPos( posRef );


	// X
	/*RECT2 collisionRectH= (*hitHoriPtr)->CollisionTest(m_HitTerrainPtr);
	//RECT2 collisionRectH = m_GridPtr->ColWithGrid(m_RectBBox + m_Pos); // NEW!
	double deltaX= ReturnGoodLen(collisionrecth.left, collisionrecth.right, (*pos).x);

	if( deltaX!=0 ){
	RECT2 checkWidth= (*hitHoriPtr)->GetBounds();
	double width= abs( checkWidth.right- checkWidth.left );
	if( deltaX<width && deltaX>-width ){ //
	(*pos).x+= deltaX;
	if( deltaX* (*velocity).x <0 ) // verschillend teken
	(*velocity).x =0;
	}
	}

	(*hitVertPtr)->SetPos(*pos);
	(*hitHoriPtr)->SetPos(*pos);//*/
	return returnCollide;
}//*/


double Player::ReturnGoodLen(double getal1, double getal2, double centerXY)
{
	double delta = 0;
	delta = abs(getal1 - getal2);

	if (delta > 0.001) { // er is een botsing
		double colCenter = (getal1 + getal2) / 2;
		if (centerXY < colCenter) delta *= -1;
	}
	return delta;
}

