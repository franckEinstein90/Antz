// Environment.h: interface for the Environment class.
//
//////////////////////////////////////////////////////////////////////

class Environment : public CObject{
    
public:
	

protected:
	EnvObject**** EnvMap;
	vector<Marker*> Markers;
	vector<Organism*> Organisms;
	vector<collect_itemParticule*> collect_itemParticules;
	
	OrganismHill* Hill;
        
        int EnvThingsSize;
        int EnvOrganismsNum;
	
        int collect_itemNum;
	int Rows;
        int Cols;
        double m_markerDecayRate;
	

        bool addOrganism(Organism* A);
        bool addcollect_item(collect_itemParticule* F);   
        bool addMarker(Marker* P);
        void addToMarkerArray(Marker* P);
        bool addOrganismHill(OrganismHill* P);
        
        void removeEnvObject(EnvObject* o){
		EnvObject* temp = o;
		int he = 0;
		if(o){
			
			for(int k=0; k<MAXOBJPERMAPSQUARE; k++)
			if(EnvMap[o->getX()][o->getY()][k] == o){
				EnvMap[o->getX()][o->getY()][k] = (EnvObject*)0;
				if(iscollect_item(o)) collect_itemNum--;
				delete o;
				EnvThingsSize--;
				return;
		    }
	    }
             throw "Trying to remove an inexistOrganism object at Environment::removeEnvObject";
	};
        
        void updateMarkers(){
            for(int i=0; i<Markers.size(); i++)
                if(Markers[i]){
                    Markers[i]->decay();
                    if(Markers[i]->getStrength()<MarkerTOL){
                        removeEnvObject(Markers[i]);
                        Markers[i] = (Marker*) 0;               
                    }                    
                }
        };


        void updateOrganisms(const CDNAStatement& Instructions){
			for(int i=0; i<Organisms.size();i++)
				try {
					Instructions.Eval(Organisms[i]);
				}
				catch (LPTSTR ErrMessage){
					throw ErrMessage;
					break;
				}
		};

        void updateHill(){
             for(int i=0; i<MAXOBJPERMAPSQUARE; i++)
				 if(iscollect_item(EnvMap[Hill->getX()][Hill->getY()][i])&&(!((collect_itemParticule*)(EnvMap[Hill->getX()][Hill->getY()][i]))->isBeingCarried))
                    removeEnvObject(EnvMap[Hill->getX()][Hill->getY()][i]);
                    
         };
        
        void Destroy();    
        bool canGoTo(int x, int y){
            if(!inBounds(x, y)) return false;
            for(int k=0; k<MAXOBJPERMAPSQUARE;k++)
                    if(!EnvMap[x][y][k]) return true;
            return false;        
        }
        bool inBounds(int x, int y){
            if((x<0)||(x>=Rows)) return false;
            if((y<0)||(y>=Cols)) return false;
            return true;
        }
        
	int WrapCols(int NewTY) {return (NewTY >=0 )?NewTY%Cols:Cols+NewTY;};
	int WrapRows(int NewTX) { return (NewTX >=0 )?NewTX%Rows:Rows+NewTX;};
    public:
	
	bool viewMarker;
	int getTotalcollect_item(){return collect_itemNum;};
	unsigned int getRows(){return Rows;};
	unsigned int getCols(){return Cols;};


	double COLLMarkerSTRENGTHHere(int x, int y);
        
        
        bool isOrganismHill(EnvObject* o){
            if(o) return o->objectType() == OrganismHILL;
            return false;
        };
        bool iscollect_item(EnvObject* o){
            if(o) return o->objectType() == collect_item;
            return false;
        };
        bool isOrganism(EnvObject* o){
            if(o) return o->objectType() == Organism;
            return false;
        };


        bool Environment::isMarker(EnvObject* o){
            if(o) return o->objectType() == Marker;
            return false;
        };
        bool Environment::iscollect_itemMarker(EnvObject* o){
            if(o) if ((isMarker(o))&&(((Marker*)o)->iscollect_itemCarryingMarker())) return true; 
            return false;   
        };

        Orientation DirectionOfOrganismHill(int Posi, int Posj);
        collect_itemParticule* onCollectItem(int x, int y);        
        bool moveObject(EnvObject* o, int NewX, int NewY);
        bool addEnvObject(EnvObject* o);
        void draw(GLfloat GridWidth, GLfloat GridHeight);
        
        void timeTick(const CDNAStatement& Instructions){
            
            //Adding Organisms to population if we still
            //don't have the right number
            if(Organisms.size()<EnvOrganismsNum)
                addEnvObject( new Organism(Hill->getX(),Hill->getY(), this, NORTH, m_markerDecayRate));
            updateOrganisms(Instructions);      
            updateHill();
            updateMarkers();

        };
	

	void reset(){

		
		collect_itemNum = 0;
		int collect_itemctr1;
		int collect_itemctr2;
		for(collect_itemctr1 = Cols/4; collect_itemctr1<((2*Cols)/3)+rand()%Cols; collect_itemctr1++)
		for(collect_itemctr2 = rand()%2; collect_itemctr2<(rand()%7); collect_itemctr2++)
			addEnvObject( new collect_itemParticule(collect_itemctr1, collect_itemctr2));


		for(collect_itemctr1 = 4; collect_itemctr1<4+rand()%Rows; collect_itemctr1++)
			for(collect_itemctr2 = 10+rand()%4; collect_itemctr2<17+rand()%(Cols/3); collect_itemctr2++)
				addEnvObject( new collect_itemParticule(collect_itemctr1, collect_itemctr2));
		
		while(!addEnvObject( new OrganismHill(rand()%Rows, rand()%Cols)));

	};

	double evalCDNA(const CDNAStatement& Instructions, int EvalTime){
	
					double currentcollect_item = (double)getTotalcollect_item();
					for(int i=0; i<EvalTime;i++){
						try{
							timeTick(Instructions);
						}
						catch(LPTSTR ErrMessage){
							AfxMessageBox(ErrMessage);
						}
					}
					//reward for getting collect_item
					
					return ((currentcollect_item-(double)getTotalcollect_item())/currentcollect_item) * 15.0f;
	};
        
        Environment(int Rows, int Cols, int OrganismNum, double markerDecayRate=0.5);
        virtual ~Environment();
};
#endif // !defined(AFX_ENVIRONMENT_H__9D7BFE99_0B20_4BC1_985E_F68B1D203E70__INCLUDED_)
