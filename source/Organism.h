// Organism.h: interface for the Organism class.
//
//////////////////////////////////////////////////////////////////////

#define MAXOBJPERMAPSQUARE 10
#define MarkerTOL 0.001

class Environment;
class Organism : public EnvObject{

protected:
    Environment * Env;
    CollectUnit* collect_item;
    Orientation myOrientation;    
    double decayRate;
    
public:
    Organism(int X, int Y, Environment* e, Orientation Oriented = NORTH, double markerDecayRate=0.5);
	virtual ~Organism();
        
    bool play(GENEStatementType S);   
    void moveTo(int NewX, int NewY);

    virtual void setOrientation(Orientation newOrientation){myOrientation = newOrientation;};
    virtual bool orientedEast(){return  myOrientation == EAST;};
    virtual bool orientedWest(){return  myOrientation == WEST;};
    virtual bool orientedNorth(){return myOrientation == NORTH;};
    virtual bool orientedSouth(){return myOrientation == SOUTH;};
        
    void getRight(int* Coord);
    void getLeft(int* Coord);
	void getFront(int* Coord);
    
protected:

	//actuators
    virtual void moveRight( void );                            
    virtual void moveLeft( void );
    virtual void moveFront( void );    
    void moveRandom( void );

    void moveToDrop();
	void moveAdjacentMarker();
	void moveAdjacentCollectibleItem();
	void dropMarker();
	bool pickUpCollectUnit(CollectUnit* F);
	void Organism::dropCollectItem();

	//Sensors
	bool adjacentMarker( void ) const;
    bool adjacentCollectItem( void ) const;
    bool isHome (void) const;
	bool carryingCollectible( void ) const {return (!(!collect_item));};
    CollectUnit* senseCollectItem() const;

public:
	void draw(GLfloat hor_step, GLfloat vert_step);
    ObjectType objectType(){return Organism;};
};
