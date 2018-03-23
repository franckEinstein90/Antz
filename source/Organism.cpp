// Organism.cpp: implementation of the Organism class.
//
//////////////////////////////////////////////////////////////////////
#include "Organism.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Organism::Organism(int X, int Y, Environment* e, Orientation Oriented, double markerDecayRate):
EnvObject(X, Y), Env(e), myOrientation(Oriented),
collect_item((CollectUnit*)0), decayRate(markerDecayRate){}

void Organism::moveTo(int NewX, int NewY){
    EnvObject::moveTo(NewX, NewY);
    if(carryingCollectible()){  
		if(!Env->moveObject(collect_item, NewX, NewY))
            collect_item = (CollectUnit*)0;
    }
}

void Organism::getRight(int* Coord){
    if(orientedNorth()) {Coord[0] = getX(); Coord[1] = getY()+1; return;}
    if(orientedSouth()) {Coord[0] = getX(); Coord[1] = getY()-1; return;}
    if(orientedWest())  {Coord[0] = getX()-1; Coord[1] = getY(); return;}
    if(orientedEast())  {Coord[0] = getX()+1; Coord[1] = getY(); return;}
}

void Organism::getLeft(int* Coord){
    if(orientedNorth()) {Coord[0] = getX(); Coord[1] = getY()-1; return;}
    if(orientedSouth()) {Coord[0] = getX(); Coord[1] = getY()+1; return;}
    if(orientedWest())  {Coord[0] = getX()+1; Coord[1] = getY(); return;}
    if(orientedEast())  {Coord[0] = getX()-1; Coord[1] = getY(); return;}
}

void Organism::getFront(int* Coord){
    if(orientedNorth()) {Coord[0] = getX()-1; Coord[1] = getY(); return;}
    if(orientedSouth()) {Coord[0] = getX()+1; Coord[1] = getY(); return;}
    if(orientedWest())  {Coord[0] = getX(); Coord[1] = getY()-1; return;}
    if(orientedEast())  {Coord[0] = getX(); Coord[1] = getY()+1; return;}
}


void Organism::moveRight(){
    int Coord[2];
    getRight(Coord);
    Env->moveObject(this, Coord[0], Coord[1]); 
    if(orientedNorth()) {myOrientation = EAST; return;}
    if(orientedSouth()) {myOrientation = WEST; return;}
    if(orientedWest())  {myOrientation = NORTH; return;}
    if(orientedEast())  {myOrientation = SOUTH; return;}
};

void Organism::moveLeft(){
    int Coord[2];
    getLeft(Coord);
    Env->moveObject(this, Coord[0], Coord[1]); 

    if(orientedNorth()) {myOrientation = WEST; return;}
    if(orientedSouth()) {myOrientation = EAST; return;}
    if(orientedWest())  {myOrientation = SOUTH; return;}
    if(orientedEast())  {myOrientation = NORTH; return;}
};          
void Organism::moveFront(){
    int Coord[2];
    getFront(Coord);
    Env->moveObject(this, Coord[0], Coord[1]); 
};    

bool Organism::isHome(){
    return Env->DirectionOfOrganismHill(getX(), getY()) == HERE;
}
void Organism::moveToDrop(){
            switch (Env->DirectionOfOrganismHill(getX(), getY()))
            {
                case EAST:
                    if(orientedEast()) moveFront();
                    else if(orientedNorth()) moveRight();
                    else moveLeft();
                    break;
                
                case WEST:
                    if(orientedWest()) moveFront();
                    else if(orientedSouth()) moveRight();
                    else moveLeft();
                    break;

                case NORTH:
                    if(orientedNorth()) moveFront();
                    else if(orientedWest()) moveRight();
                    else moveLeft();
                    break;

                case SOUTH:
                    if(orientedSouth()) moveFront();
                    else if(orientedEast()) moveRight();
                    else moveLeft();
                    break;
            }
}


void Organism::moveAdjacentMarker(){

			int Coord[2];
    	
            getLeft(Coord);
			double d1 =  Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1]);

			getRight(Coord);
            double d2 = Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1]);

            getFront(Coord);
            double d3 = Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1]);

			if(d1 < d2) 
				if(d1 < d3) moveLeft(); else moveFront();
			else
				if(d2 < d3) moveRight(); else moveFront();	
}

void Organism::moveAdjacentCollectibleItem(){
	int Coord[2];
	getLeft(Coord);
	if (Env->onCollectItem(Coord[0], Coord[1])) moveLeft();
	getRight(Coord);
	if (Env->onCollectItem(Coord[0], Coord[1])) moveRight();
	getFront(Coord);
	if (Env->onCollectItem(Coord[0], Coord[1])) moveFront();
}
void Organism::moveRandom( void ){
	int TurnSpike = rand()%3;
	if(TurnSpike == 0) {moveRight(); return;}
	if(TurnSpike == 1) {moveLeft(); return;}
	if(TurnSpike == 2) {moveFront(); return;}
}   
void Organism::dropMarker(){
  Marker* P;
  P = new Marker(getX(), getY(), COLLMarkerTYPE, decayRate);
  Env->addEnvObject(P);
}
bool Organism::pickUpCollectUnit(CollectUnit* F){
	if((F)&&(!carryingCollectible()))
    if(!F->isBeingCarried){
		collect_item = F;
        F->isBeingCarried = true;
        return true;
     }
     return false;
}

bool Organism::adjacentMarker(){
            int Coord[2];
            getLeft(Coord);
            if(Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1])) return true;
            getRight(Coord);
            if(Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1])) return true;
            getFront(Coord);
            if(Env->COLLMarkerSTRENGTHHere(Coord[0], Coord[1])) return true;
            
            return false;
}

bool Organism::adjacentCollectItem(){
	int Coord[2];
	getLeft(Coord);
	if(Env->onCollectItem(Coord[0], Coord[1])) return true;
	getRight(Coord);
	if(Env->onCollectItem(Coord[0], Coord[1])) return true;
	getFront(Coord);
	if(Env->onCollectItem(Coord[0], Coord[1])) return true;
	return false;
}
void Organism::dropCollectItem(){
	if(collect_item){
		collect_item->isBeingCarried = false;
		collect_item = ((CollectUnit*)0);
	}
}

CollectUnit* Organism::senseCollectItem(){
    return Env->onCollectItem(getX(), getY());
}


void Organism::draw(GLfloat hor_step, GLfloat vert_step){


	GLfloat Orient;
	switch(myOrientation){

		case NORTH:
			Orient = 0.0f;
			break;
		case SOUTH:
			Orient = 180.0f;
			break;
		case EAST:
			Orient = -90.0f;
			break;
		case WEST:
			Orient = 90.0f;
			break;
	}
	
	
	
	::glPushMatrix();
	::glRotatef(Orient, 0.0, 0.0, 1.0);
	::glBegin(GL_TRIANGLES);      
		
		glColor3f(1.0f, 0.5f, 0.0f);
		::glVertex3f(0.0, vert_step/2.0f, 0.0);
		::glVertex3f(hor_step/2.0f, vert_step, 0.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		::glVertex3f(hor_step, vert_step/2.0f, 0.0);
		if(carryingCollectible())
		    glColor3f(1.0f, 0.5f, 0.7f);
		else
		glColor3f(0.0f, 0.7f, 0.15f);
		::glVertex3f(0.0, 0.0, 0.0);
		::glVertex3f(hor_step/2.0f, vert_step/2.0f, 0.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		::glVertex3f(hor_step, 0.0, 0.0);
	::glEnd();
	::glPopMatrix();
}

bool Organism::play(GENEStatementType S){




    switch(S){
         
         case adjacentMarker:
                            return adjacentMarker();
         case adjacentCollectItem:
                            return adjacentCollectItem();
         case IS_CARRYING_collect_item:
                            return carryingCollectible();                
         case collect_item_HERE:
                            return (!(!senseCollectItem()));
         case IS_HOME:
                            return isHome();
         
         case MOVE_TO_ADJACENT_Marker:
							moveAdjacentMarker();
							break;
         
         case MOVE_TO_ADJACENT_collect_item:
							moveadjacentCollectItem();
							break;
         
         case MOVE_RANDOM:
                            moveRandom();
                            break;        
         case MOVE_TO_NEST:                                
                            moveHome();
                            break;
         case PICK_UP_collect_item:
                            if(senseCollectItem())
                                pickUpCollectUnit(senseCollectItem());
                            break;
         case DROP_Marker:
                            dropMarker();
                            break;
        
	case DROP_collect_item:
                            dropCollectItem();
                            
    }  
      
    return true;
}           

Organism::~Organism(){
    
}
