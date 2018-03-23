// Environment.cpp: implementation of the Environment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Assignment2.h"
#include "REnvironment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



void Environment::Destroy(){
    if (EnvMap){    
        for(int i=0; i<Rows; i++){
            for(int j=0; j<Cols; j++){
                for(int k=0; k<MAXOBJPERMAPSQUARE; k++){
                    if(EnvMap[i][j][k])
                        delete EnvMap[i][j][k];
                }
                delete [] EnvMap[i][j];
            }
            delete [] EnvMap[i];            
        }
        delete [] EnvMap;
        EnvMap = (EnvObject****)0;
    }
    

    Markers.erase(Markers.begin(), Markers.end());
}





bool Environment::moveObject(EnvObject* o, int NewTX, int NewTY){

	int NewX = WrapRows(NewTX);
	int NewY = WrapCols(NewTY); 
	
	
	if(!canGoTo(NewX, NewY)) return false;
	if(o){
		for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
			if(o == EnvMap[o->getX()][o->getY()][k]){
				EnvMap[o->getX()][o->getY()][k] = (EnvObject*) 0;
				for(int i = 0; i<MAXOBJPERMAPSQUARE; i++)
					if(!EnvMap[NewX][NewY][i]){
						EnvMap[NewX][NewY][i] = o;
						o->moveTo(NewX, NewY);
						return true;                                
				}                         
			}    
	}
	return false;
}





Environment::Environment(int rows, int cols, int OrganismNum, double markerDecayRate):
EnvMap((EnvObject****)0), Rows(rows), Cols(cols),
EnvThingsSize(0), EnvOrganismsNum(OrganismNum), Hill((OrganismHill*)0), collect_itemNum(0), m_markerDecayRate(markerDecayRate),
viewMarker(false){

    
    EnvMap = new EnvObject***[Rows];
    for(int i=0; i<Rows; i++){
        EnvMap[i] = new EnvObject**[Cols];   
        for(int j=0; j<Cols; j++){
            EnvMap[i][j] = new EnvObject* [MAXOBJPERMAPSQUARE];
            for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
                EnvMap[i][j][k] = (EnvObject*) 0;
        }
    }


    reset();
    
}


collect_itemParticule* Environment::onCollectItem(int x, int y){
    
    collect_itemParticule* F = (collect_itemParticule*)0;

    if(inBounds(x, y))
    for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
        if((iscollect_item(EnvMap[x][y][k])) &&
            (!((collect_itemParticule*)EnvMap[x][y][k])->isBeingCarried)) 
            return (collect_itemParticule*)EnvMap[x][y][k];    

    return F;
}


double Environment::COLLMarkerSTRENGTHHere(int x, int y){
    
    if(inBounds(x, y))
    for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
        if(iscollect_itemMarker(EnvMap[x][y][k])) 
            return ((Marker*)EnvMap[x][y][k])->getStrength();    

    return 0.0f;
}

bool  Environment::addOrganism(Organism* A){

    for(int ctr =0; ctr<MAXOBJPERMAPSQUARE; ctr++)
        if(!(EnvMap[A->getX()][A->getY()][ctr])){
            EnvMap[A->getX()][A->getY()][ctr] = A;
            Organisms.push_back(A);
            return true;
        }
	delete A;
	return false;
}

bool Environment::addcollect_item(collect_itemParticule* F){
	for(int ctr =0; ctr<MAXOBJPERMAPSQUARE; ctr++)
		if(!(EnvMap[F->getX()][F->getY()][ctr])){
			 EnvMap[F->getX()][F->getY()][ctr] = F;
			collect_itemParticules.push_back(F);
			collect_itemNum++;
			return true;
		}
	delete F;
	return false;
}

bool Environment::addMarker(Marker* P){
    int OpenIndex = -1;
    for(int ctr =0; ctr<MAXOBJPERMAPSQUARE; ctr++){
        bool ok = isMarker(EnvMap[P->getX()][P->getY()][ctr]);
        if((ok) && P->isSameType(*((Marker*)EnvMap[P->getX()][P->getY()][ctr]))){
            ((Marker*)EnvMap[P->getX()][P->getY()][ctr])->refreshMarker();
	    delete P;
            return true;   
        }
        if((!(EnvMap[P->getX()][P->getY()][ctr]))&&(OpenIndex < 0))
            OpenIndex = ctr;
    }

   if(OpenIndex >= 0){
        EnvMap[P->getX()][P->getY()][OpenIndex] = P;  
        EnvThingsSize++; 
        addToMarkerArray(P);
        return true;
    }  
    delete P;
    return false;
}

void Environment::addToMarkerArray(Marker* P){
        for(int PherCtr = 0; PherCtr<Markers.size(); PherCtr++)
            if(!(Markers[PherCtr])){
                Markers[PherCtr] = P;
                return;
            }
        Markers.push_back(P); 
}

bool Environment::addOrganismHill(OrganismHill* AH){
	for(int ctr =0; ctr<MAXOBJPERMAPSQUARE; ctr++)
		if(!(EnvMap[AH->getX()][AH->getY()][ctr])){
			EnvMap[AH->getX()][AH->getY()][ctr] = AH;
			Hill = (OrganismHill*)EnvMap[AH->getX()][AH->getY()][ctr];
			return true;
		}
	
	delete AH;
	return false;
}

bool  Environment::addEnvObject(EnvObject* o){

	o->moveTo(WrapRows(o->getX()), WrapCols(o->getY()));

	if(canGoTo(o->getX(), o->getY())){
		if(isMarker(o)){ return addMarker((Marker*)o);}
		if(isOrganism(o)){ return addOrganism((Organism*) o); }
		if(iscollect_item(o)){ return addcollect_item((collect_itemParticule*)o); } 
		if(isOrganismHill(o)) { return addOrganismHill((OrganismHill*)o); }
	}

	delete o;
	return false;
}


Orientation Environment::DirectionOfOrganismHill(int Posi, int Posj){

	//some vague homeward direction

	
	if((Posi == Hill->getX()) && (Posj == Hill->getY()))return HERE;    

	while(1){

			int a = rand()%4;

			switch(a){
				case 0:
					if(Posi < Hill->getX()) return SOUTH;
			    
				case 1:
					if(Posi > Hill->getX()) return NORTH;
			    
				case 2:
					if(Posj > Hill->getY()) return WEST;
			    
				case 3:
					if(Posj < Hill->getY()) return EAST;

			}
	}
	throw "Direction Mischief";
	
}


Environment::~Environment(){
    Destroy();
}

void Environment::draw(GLfloat GridWidth, GLfloat GridHeight){

        GLfloat GridTop  = GridHeight/(GLfloat)2.0f;
        GLfloat GridLeft = GridWidth / (GLfloat)-2.0f;
        GLfloat hor_step  = GridWidth/Cols;
        GLfloat vert_step = GridHeight/Rows;
        if (EnvMap)    
            for(int i=0; i<Rows; i++)
                for(int j=0; j<Cols; j++){
                    glPushMatrix();
                    glTranslatef(GridLeft+(j*hor_step), GridTop-((i+1)*vert_step), 0.0f);
                    for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
                        if(EnvMap[i][j][k])
				if(viewMarker)
					EnvMap[i][j][k]->draw(hor_step, vert_step);
				else
					if(!isMarker(EnvMap[i][j][k]))
						EnvMap[i][j][k]->draw(hor_step, vert_step);
                    glPopMatrix();
                }
}

