//---------------------------
// Includes
//---------------------------
#include "ObjectBaseList.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//Bitmap * ObjectBase::m_BmpSpritePtr= 0;

//---------------------------
// Constructor & Destructor		ObjectBase
//---------------------------
ObjectBase::ObjectBase():m_Pos(){}
ObjectBase::ObjectBase(DOUBLE2 pos): m_Pos(pos), m_SpriteSize(),
	m_MatViewPtr(0), m_HitRegionPtr(0), m_Type(0), m_ObjectListPtr(0)
{
	m_Type= TYPE_NOT_SET;
	m_HitRegionPtr= new HitRegion();

	//int gs= 32; //GridSize // may not affect bullets
	//m_Pos.x= ((int)m_Pos.x/gs+0.5)*gs;
	//m_Pos.y= ((int)m_Pos.y/gs+0.5)*gs;

	/*if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./resources/Enemy.gif");
		m_SpriteWidth= m_BmpSpritePtr->GetWidth() /5;
		m_SpriteHeight=40;//m_BmpSpritePtr->GetHeight()/4;
	}
	if (!m_BmpSpritePtr->Exists())
			GAME_ENGINE->MessageBox("bitmap Fail!");//*/

}

ObjectBase::~ObjectBase(){
	if( m_HitRegionPtr!=0 ){
		delete m_HitRegionPtr;
		m_HitRegionPtr=0;
	}
}

//---------------------------
// Own methods
//---------------------------

/*void ObjectBase::Paint() // deze functie kan de gepersonaliseerde m_BmpSpritePtr niet gebruiken!
{ 
	GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr );
	RECT2 clip;
	clip.left   = 0;
	clip.top    = 0;
	clip.right  = clip.left +m_SpriteSize.x;
	clip.bottom = clip.top  +m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, m_Pos, clip);
}//*/

//---------------------------
// Constructor & Destructor
//---------------------------
ObjectList::ObjectList(DOUBLE2 maxPos, MATRIX3X2 *matViewPtr, HitRegion *hitTerrainPtr): m_MaxPos(maxPos), m_MatViewPtr(matViewPtr)
{
	m_HitTerrainPtr= hitTerrainPtr;
	m_ObjectCount= 0;
	//for (int i=0; i<ARR_MAX; ++i){ m_ObjectPtr[i]=0; } 
	//for (int i=0; i<m_ObjectPtrVect.size(); ++i){  m_ObjectPtrVect.at(i)= 0;}
}

ObjectList::~ObjectList()
{
	//for (int i=0; i<ARR_MAX; ++i){ Delete(i); }
	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){  Delete(i);}
	OutputStatus();
}

//---------------------------
// Own methods
//---------------------------

int ObjectList::Add( ObjectBase * objectPtr )
{
	objectPtr->SetMatView(m_MatViewPtr);
	objectPtr->SetObjectList(this);

	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){
		if ( m_ObjectPtrVect.at(i)== 0){
			//m_ObjectPtr[i]= objectPtr;
			m_ObjectPtrVect.at(i)= objectPtr;
			++m_ObjectCount;
		//	OutputStatus();
			return i;
		}
	}
	m_ObjectPtrVect.push_back(objectPtr);
	//OutputStatus();
	++m_ObjectCount;
	return m_ObjectPtrVect.size()-1;
	return false;
}

bool ObjectList::Delete( int plaats )
{
	if( CheckIfPlaatsExist(plaats) ){
		delete m_ObjectPtrVect.at(plaats);
		m_ObjectPtrVect.at(plaats)= 0;
		--m_ObjectCount;
		if( m_ObjectCount<5 ) OutputStatus();
		return true;
	}
	return false;
}

bool ObjectList::Delete( ObjectBase *objPtr )
{
	for (int plaats=0; plaats<(int)m_ObjectPtrVect.size(); ++plaats){
		if( m_ObjectPtrVect.at(plaats)== objPtr ){
			return Delete(plaats);
		}
	}
	return false;
}

void ObjectList::Tick(double deltaTime){
	for (int plaats=0; plaats<(int)m_ObjectPtrVect.size(); ++plaats){

		if( CheckIfPlaatsExist(plaats) )
			m_ObjectPtrVect.at(plaats)->Tick(deltaTime); // maby he deleted himself?
		/*if( CheckIfPlaatsExist(plaats) ){ // te veel miserie
			DOUBLE2 pos= m_ObjectPtrVect[plaats]->GetPos();
			int marge= -150;
			if( pos.x<marge || pos.x>m_MaxPos.x-marge ){
				Delete(plaats);
			}//
			if( pos.y<marge || pos.y>m_MaxPos.y-marge ){
				Delete(plaats);
			}
		}//*/

	} // end for-loop


	ObjectBase *iPtr, *jPtr; // Colitions
	for (int i=0;   i<(int)m_ObjectPtrVect.size(); ++i){ if( CheckIfPlaatsExist(i) ){
	for (int j=i+1; j<(int)m_ObjectPtrVect.size(); ++j){ if( CheckIfPlaatsExist(j) ){
		if( CheckIfPlaatsExist(i) ){ // her-chekken, in deze for gebeuren er vreemde dingen...

			iPtr= m_ObjectPtrVect.at(i);
			jPtr= m_ObjectPtrVect.at(j);

			// check is the type is defined.
			int iType= iPtr->GetType();
			int jType= jPtr->GetType();

			if( iType== -1 || jType==-1 ){
				OutputDebugString("TYPE_NOT_SET");
				DebugBreak();
			}

			if( iPtr->GetHitRegion()->HitTest( jPtr->GetHitRegion() ) ){ // ze hitten
				
				iPtr->CollideWith( jPtr , jType ); // deze kan iPtr en jPtr deleten!!
				iPtr= m_ObjectPtrVect.at(i);
				jPtr= m_ObjectPtrVect.at(j);
				if( jPtr!=0 ) // jPtr kan ondertussen gedeleted zijn!!
					jPtr->CollideWith( iPtr, iType );
			}

		}
	}} // end for j
	}} // end For i
}

void ObjectList::Paint(){
	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){
		if( CheckIfPlaatsExist(i) ){
			//GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr); // die hebben ze nu zelf!
			m_ObjectPtrVect[i]->Paint();
		}
	}
}

DOUBLE2 ObjectList::GetPos( int plaats )
{
	if( CheckIfPlaatsExist(plaats) ){
			return m_ObjectPtrVect.at(plaats)->GetPos();
	}
	return DOUBLE2();
}

bool ObjectList::CheckIfPlaatsExist( int plaats )
{
	if( plaats>0 || plaats<(int)m_ObjectPtrVect.size()-1 ){
		if( m_ObjectPtrVect.at(plaats)!=0 ){
			return true;  // --- alles OK hier! ---
		}else{
			return false; //"Plaats is niet ingevuld
		}
	}else{
		GAME_ENGINE->MessageBox( String("plaats is niet in de list\n plaats= "+ plaats) );
	}

	return false;
}

void ObjectList::OutputStatus(){
	String output=String("\nListStatus: ")+m_ObjectCount + " / "+ m_ObjectPtrVect.capacity()+ " Objs";
	OutputDebugString(output);
	/*if( m_ObjectCount>ARR_MAX ){// geen nut met vector
		OutputDebugString("\nFOUT!");
		GAME_ENGINE->MessageBox(output);
	}*/
}