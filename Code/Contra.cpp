//-----------------------------------------------------------------
// Game File
// C++ Source - Contra.cpp - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Contra.h"																				

#include "Box.h"
#include "PowerUp.h"
#include "EnemyWalking.h"
#include "EnemySniper.h"
#include "Bridge.h"
#include "BosSniper.h"
#include "PowerUpBox.h"
#include "EvilTurret.h"
#include "EndBoss.h"
#include "FlyingPuwerUp.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// Contra methods																				
//-----------------------------------------------------------------

Contra::Contra(): m_ObjectListPtr(0), m_BmpBackgroundPtr(0), 
	m_PersonageNum(0), m_HitTerrainPtr(0), m_ViewScale(1),
		m_PosCamera(), m_LevelMax(), m_PlayerPtr(0), m_SpawnTime(0), m_MousePos(),
		m_GameSize(800), m_LetsMakeSound( true )
{
	int i= 0;
	/*for( i=0; i<NUM_SPAWNERS; ++i ){
		m_SpawnersArr[i]= DOUBLE2();
	}*/
	i= 0;
	m_SpawnersArr[i++]= DOUBLE2(500 , 81);
	m_SpawnersArr[i++]= DOUBLE2(730 ,130);
	m_SpawnersArr[i++]= DOUBLE2(1500,130);
	//m_SpawnersArr[i++]= DOUBLE2();
}

Contra::~Contra(){}

void Contra::GameInitialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::GameInitialize(hInstance);
	GAME_ENGINE->SetTitle("Contra By Emile");					
	GAME_ENGINE->RunGameLoop(true);
	
	// Set the optional values
	GAME_ENGINE->SetWidth( (int)m_GameSize);
	GAME_ENGINE->SetHeight((int)m_GameSize);
    GAME_ENGINE->SetFrameRate(60);
	GAME_ENGINE->SetTickPaintRatio(2);
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);
}

void Contra::GameStart()
{
	GAME_ENGINE->SetBitmapInterpolationModeNearestNeighbor();
	if( m_LetsMakeSound ){
		// verveelend muziekje, het staat uit om te debuggen.
		m_MusicPtr= new Audio(IDR_MUSIC, "MID"); // neemt veel tijd
		m_MusicPtr->SetVolume(20); // Heeft geen invloed :(
		m_MusicPtr->Play(); //*/
	}

	m_BmpBackgroundPtr= new Bitmap("resources/Background.png");
	m_LevelMax= DOUBLE2(m_BmpBackgroundPtr->GetWidth(), m_BmpBackgroundPtr->GetHeight());
	m_ViewScale= m_LevelMax.y/GAME_ENGINE->GetHeight();
	if( m_LevelMax.x < GAME_ENGINE->GetWidth()*m_ViewScale )
		m_LevelMax.x = GAME_ENGINE->GetWidth()*m_ViewScale;
	

	m_HitTerrainPtr= new HitRegion();
	m_HitTerrainPtr->CreateFromFile("resources/bgHit.svg"); //Background_Hitregion2

	// OBJECT LIST
	m_ObjectListPtr= new ObjectList(m_LevelMax, &m_MatView, m_HitTerrainPtr); // Deze regelt alle objecten. inc deleten

	
	PlaceEnemys( m_ObjectListPtr ); // Spawnt alle enemys in het level.
}

void Contra::GameEnd()
{
	// Insert the code that needs to be executed at the closing of the game
	delete m_ObjectListPtr			; // Deze delete ook alles uit zijn lijst
	//delete m_MusicPtr			;
	delete m_BmpBackgroundPtr	;
	delete m_HitTerrainPtr		;

}

void Contra::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	m_MousePos.x= x;
	m_MousePos.y= y;
	m_MousePos= m_MatView.Inverse().TransformPoint(m_MousePos);
	OutputDebugString(String("\nclick: ")+m_MousePos.ToString());

	/*if (isLeft == true && isDown == true){	
		m_GridPtr->MouseClick(mousePos);
	}
	if (isLeft == false && isDown == true){	
		m_GridPtr->PrintArr();
	}*/
}

//void Contra::MouseMove(int x, int y, WPARAM wParam)
//{	
//	// Insert the code that needs to be executed when the mouse pointer moves across the game window
//
//	/* Example:
//	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
//	{
//		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
//		{
//			GAME_ENGINE->MessageBox("Da mouse wuz here.");
//		}
//	}
//	*/
//
//}
//
//void Contra::CheckKeyboard()
//{	
//	// Here you can check if a key of choice is held down
//	// Is executed once per frame 
//
//	/* Example:
//	if (GAME_ENGINE->IsKeyDown('K')) xIcon -= xSpeed;
//	if (GAME_ENGINE->IsKeyDown('L')) yIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('M')) xIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('O')) yIcon -= ySpeed;
//	*/
//}
//
//void Contra::KeyPressed(TCHAR cKey)
//{	
//	// DO NOT FORGET to use SetKeyList() !!
//
//	// Insert the code that needs to be executed when a key of choice is pressed
//	// Is executed as soon as the key is released
//	// You first need to specify the keys that the game engine needs to watch by using the SetKeyList() method
//
//	/* Example:
//	switch (cKey)
//	{
//	case 'K': case VK_LEFT:
//		MoveBlock(DIR_LEFT);
//		break;
//	case 'L': case VK_DOWN:
//		MoveBlock(DIR_DOWN);
//		break;
//	case 'M': case VK_RIGHT:
//		MoveBlock(DIR_RIGHT);
//		break;
//	case 'A': case VK_UP:
//		RotateBlock();
//		break;
//	case VK_ESCAPE:
//	}
//	*/
//}

void Contra::GameTick(double deltaTime)
{
	
	deltaTime= min( 0.007, deltaTime );

	if( GAME_ENGINE->IsKeyDown(VK_ESCAPE) ) GAME_ENGINE->QuitGame();

	// SCALEBLE WINDOW ------------------------------------------------------
	if( GAME_ENGINE->IsKeyDown('O') ) m_GameSize/=1.01;
	if( GAME_ENGINE->IsKeyDown('P') ) m_GameSize*=1.01;

	if(  GAME_ENGINE->IsKeyDown('O') || GAME_ENGINE->IsKeyDown('P') ){
		GAME_ENGINE->SetWidth(  (int)m_GameSize );
		GAME_ENGINE->SetHeight( (int)m_GameSize );
		OutputDebugString( String("m_GameSize: ")+m_GameSize );
		m_ViewScale= m_LevelMax.y/m_GameSize;
	}

	if( GAME_ENGINE->IsKeyDown('R') ){
		// OBJECT LIST RESETTEN
		delete m_ObjectListPtr;
		m_ObjectListPtr= new ObjectList(m_LevelMax, &m_MatView, m_HitTerrainPtr); // Deze regelt alle objecten. inc deleten
	
		PlaceEnemys( m_ObjectListPtr ); // Spawnt alle enemys in het level.

	}



	// SPAWN EemyWalking ------------------------------------------------------
	m_SpawnTime+=deltaTime;
	if( m_SpawnTime>=1.8 ){ // secondes
		
		DOUBLE2 schermLingsBoven=  m_MatView.Inverse().TransformPoint( DOUBLE2() );
		DOUBLE2 schermRechtsOnder= m_MatView.Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

		for( int i=0; i<NUM_SPAWNERS; ++i ){
			if( m_SpawnersArr[i].x>schermRechtsOnder.x && m_SpawnersArr[i].x<schermRechtsOnder.x+160){
				m_SpawnTime= 0;
				EnemyWalking *EnemyPtr= new EnemyWalking( m_SpawnersArr[i] );
				EnemyPtr->SetPlayerPtr(m_PlayerPtr);
				m_ObjectListPtr->Add( EnemyPtr );
			}
		}
	}


	if( m_LetsMakeSound )
		m_MusicPtr->Tick();

	
	m_ObjectListPtr->Tick(deltaTime); //  <- Hier

	DoCameraMovement(deltaTime, m_ObjectListPtr->GetPos(m_PersonageNum));
}

void Contra::GamePaint(RECT rect)
{
	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter		.SetAsTranslate(-GAME_ENGINE->GetWidth()/2,-GAME_ENGINE->GetHeight()/2);
	matScale		.SetAsScale(m_ViewScale);
	matTranslate	.SetAsTranslate(m_PosCamera);
	m_MatView= (matCenter * matScale * matTranslate).Inverse();

	
	GAME_ENGINE->SetTransformMatrix(m_MatView);
	//m_GridPtr->Paint();
	//if( GAME_ENGINE->IsKeyDown('B') )
	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr, 0,0);

	GAME_ENGINE->DrawBitmap(m_BmpBackgroundPtr, 0, m_LevelMax.y);

	//Draw_Hitregions();  // Debug
	m_ObjectListPtr->Paint();


	/*int infinity= 9999;
	DOUBLE2 schetmLingsBoven=  m_MatView.Inverse().TransformPoint( DOUBLE2() );
	DOUBLE2 schetmRechtsOnder= m_MatView.Inverse().TransformPoint( DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight()) );

	GAME_ENGINE->SetColor(0,0,0,200);
	GAME_ENGINE->SetTransformMatrix(m_MatView);
	GAME_ENGINE->FillRect(schetmRechtsOnder.x-5, schetmLingsBoven.y, infinity, infinity); // Rechts
	//GAME_ENGINE->FillRect(-infinity, schetmRechtsOnder.y, infinity, infinity); // Onder

	//GAME_ENGINE->DrawRect(m_PosCamera.x-m_GameSize, m_PosCamera.y-m_GameSize, m_PosCamera.x+m_GameSize, m_PosCamera.y+m_GameSize);
	*/

	// WATER
	GAME_ENGINE->SetTransformMatrix(m_MatView);
	GAME_ENGINE->SetColor(0,112,236);
	GAME_ENGINE->FillRect(0, m_LevelMax.y-9, m_LevelMax.x/2, 100);

	// buiten de viewport.
	GAME_ENGINE->SetColor(0,0,0,100);
	GAME_ENGINE->SetTransformMatrix(MATRIX3X2());
	//GAME_ENGINE->FillRect(-INFINITE, m_GameSize, INFINITE, INFINITE); // onder
	GAME_ENGINE->FillRect(m_GameSize, 0, INFINITE, m_GameSize); // rechts

	
}

//void Contra::CallAction(Caller* callerPtr)
//{
//	// Insert the code that needs to be executed when a Caller has to perform an action
//}


void Contra::Draw_Hitregions()
{
	GAME_ENGINE->SetColor(255,20,10,200); // De kleur
	GAME_ENGINE->SetTransformMatrix(m_MatView);
	GAME_ENGINE->FillHitRegion(m_HitTerrainPtr);
	//GAME_ENGINE->FillEllipse(m_PosCamera, 3, 3);
	for( int i=0; i<NUM_SPAWNERS; ++i ){
		GAME_ENGINE->FillEllipse(m_SpawnersArr[i],5,5);
	}
	GAME_ENGINE->FillEllipse(m_MousePos,5,5);
	
}

void Contra::DoCameraMovement(double deltaTime, DOUBLE2 playerPos)
{
	//-- De player blijft in het scherm--//
	
	m_PosCamera.x= max( m_PosCamera.x, playerPos.x-10 );
	m_PosCamera.x= min( m_PosCamera.x, playerPos.x+m_GameSize/2*m_ViewScale );
	/*if (m_PosCamera.x> playerPos.x+GAME_ENGINE->GetWidth() /deler*m_ViewScale)
		m_PosCamera.x= playerPos.x+GAME_ENGINE->GetWidth() /deler*m_ViewScale;
	if (m_PosCamera.y< playerPos.y-GAME_ENGINE->GetHeight()/deler*m_ViewScale)
		m_PosCamera.y= playerPos.y-GAME_ENGINE->GetHeight()/deler*m_ViewScale;
	if (m_PosCamera.y> playerPos.y+GAME_ENGINE->GetHeight()/deler*m_ViewScale)
		m_PosCamera.y= playerPos.y+GAME_ENGINE->GetHeight()/deler*m_ViewScale;*/

	//-- Camera volgt player --//
	//m_PosCamera=playerPos;

	//-- Besturing Camera --//
	/*double camSpeed= 250*deltaTime;
	if(GAME_ENGINE->IsKeyDown('D')) m_PosCamera.x+=camSpeed; // VK_RIGHT	
	if(GAME_ENGINE->IsKeyDown('Q')) m_PosCamera.x-=camSpeed; // VK_LEFT	
	if(GAME_ENGINE->IsKeyDown('S')) m_PosCamera.y+=camSpeed; // VK_DOWN	
	if(GAME_ENGINE->IsKeyDown('Z')) m_PosCamera.y-=camSpeed; // VK_UP		
	//*/

	//-- Binnen de wereld blijven --//
	
	if (m_PosCamera.x<				 m_GameSize/2*m_ViewScale)
		m_PosCamera.x=				 m_GameSize/2*m_ViewScale;
	if (m_PosCamera.x> m_LevelMax.x	-m_GameSize/2*m_ViewScale)
		m_PosCamera.x= m_LevelMax.x	-m_GameSize/2*m_ViewScale;
	if (m_PosCamera.y<				 m_GameSize/2*m_ViewScale)
		m_PosCamera.y=				 m_GameSize/2*m_ViewScale;
	if (m_PosCamera.y> m_LevelMax.y	-m_GameSize/2*m_ViewScale)
		m_PosCamera.y= m_LevelMax.y	-m_GameSize/2*m_ViewScale;

}

void Contra::PlaceEnemys(ObjectList * objectListPtr){

	m_PlayerPtr= new Player(120, 50); // waarschijnlijk op plaats '0'
	m_PlayerPtr->SetGlobalVars(objectListPtr, m_LevelMax);
	m_PlayerPtr->AddLevelHitRegion( m_HitTerrainPtr );
	// word later op het einde in de list gezet
	

	
	PowerUpBox *PowerUpBoxPtr;  // PowerUpBox ------------------------------------------------------
	
	PowerUpBoxPtr= new PowerUpBox(DOUBLE2(333,150), BULLET_MITRAILLEUR); 
	PowerUpBoxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( PowerUpBoxPtr );

	PowerUpBoxPtr= new PowerUpBox(DOUBLE2(1580,140), BULLET_FLAME);
	PowerUpBoxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( PowerUpBoxPtr );

	PowerUpBoxPtr= new PowerUpBox(DOUBLE2(2290,180), BULLET_SUPER);
	PowerUpBoxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( PowerUpBoxPtr );


	FlyingPuwerUp *flyingPuwerUpPtr; // FlyingPuwerUp -----------------------------------------------

	flyingPuwerUpPtr= new FlyingPuwerUp(DOUBLE2(250,50), BULLET_R);
	flyingPuwerUpPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( flyingPuwerUpPtr );

	flyingPuwerUpPtr= new FlyingPuwerUp(DOUBLE2(2425,32), BULLET_R);
	flyingPuwerUpPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( flyingPuwerUpPtr );

	flyingPuwerUpPtr= new FlyingPuwerUp(DOUBLE2(2425,106), BULLET_LAZER);
	flyingPuwerUpPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( flyingPuwerUpPtr );

	Box *boxPtr; // BOXES ---------------------------------------------------------------------

	boxPtr= new Box(DOUBLE2(1250,140));
	boxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( boxPtr );

	boxPtr= new Box(DOUBLE2(1650,111));
	boxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( boxPtr );

	boxPtr= new Box(DOUBLE2(1840,111));
	boxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( boxPtr );

	boxPtr= new Box(DOUBLE2(2990,180));
	boxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( boxPtr );
	
	boxPtr= new Box(DOUBLE2(3117,180));
	boxPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( boxPtr );



	EvilTurret * evilTurretPtr; // EVIL TURRETS ------------------------------------------------

	/*evilTurretPtr= new EvilTurret(DOUBLE2(240,88)); // DEBUG
	evilTurretPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( evilTurretPtr );*/

	evilTurretPtr= new EvilTurret(DOUBLE2(2060,144));
	evilTurretPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( evilTurretPtr );

	evilTurretPtr= new EvilTurret(DOUBLE2(2190,50));
	evilTurretPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( evilTurretPtr );

	evilTurretPtr= new EvilTurret(DOUBLE2(2770,120));
	evilTurretPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( evilTurretPtr );



	EnemySniper *enemySniperPtr; // STAANDE SNIPERS ------------------------------------------------
	

	enemySniperPtr= new EnemySniper(DOUBLE2(300,180));
	enemySniperPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( enemySniperPtr );

	enemySniperPtr= new EnemySniper(DOUBLE2(625,180));
	enemySniperPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( enemySniperPtr );

	enemySniperPtr= new EnemySniper(DOUBLE2(2350,111));
	enemySniperPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( enemySniperPtr );

	enemySniperPtr= new EnemySniper(DOUBLE2(3240,55));
	enemySniperPtr->SetPlayerPtr( m_PlayerPtr );
	objectListPtr->Add( enemySniperPtr );


	// VARIA ---------------------------------------------------------------------------
	/*PowerUp *objectPtr= new PowerUp(DOUBLE2(150,10), -1);
	objectPtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( objectPtr );*/

	EnemyWalking *EnemyPtr= new EnemyWalking(DOUBLE2(250,10));
	EnemyPtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( EnemyPtr );

	Bridge *BridgePtr; // BRUGGEN --------------------------------------------------------

	BridgePtr= new Bridge(DOUBLE2(770,100));
	BridgePtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( BridgePtr );
	m_PlayerPtr->AddLevelHitRegion( BridgePtr->GetHitRegion() ); // !

	BridgePtr= new Bridge(DOUBLE2(1070,100));
	BridgePtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( BridgePtr );
	m_PlayerPtr->AddLevelHitRegion( BridgePtr->GetHitRegion() ); // !



	BosSniper *bosSniperPtr; // BOSJESSNIPERS---------------------

	bosSniperPtr= new BosSniper(DOUBLE2(1360,80));
	bosSniperPtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( bosSniperPtr );

	bosSniperPtr= new BosSniper(DOUBLE2(1555,55));
	bosSniperPtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( bosSniperPtr );
	

	m_PersonageNum= objectListPtr->Add( m_PlayerPtr ); // Nu pas de player erin gooien, dan drawt hij  van boven

	EndBoss *endBossPtr= new EndBoss( DOUBLE2(m_LevelMax.x, 0) );
	//endBossPtr->SetPlayerPtr(m_PlayerPtr);
	objectListPtr->Add( endBossPtr );
}
	