#pragma once

class Collectible : public EnvObject{

	bool isBeingCarried;
		
public:
	bool beingCarried( ) const {return isBeingCarried;}
	void pickUp( )
	{
		if(!isBeingCarried) isBeingCarried = true;
		else throw "...";
	}
	void drop( )
	{
		if(isBeingCarried) isBeingCarried = false;
		else throw "...";}
	}
    Collectible::Collectible(int X, int Y):isBeingCarried(false), EnvObject(X, Y){}
	ObjectType objectType( ){return FOOD;};
};