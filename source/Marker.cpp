// Marker.cpp: implementation of the Marker class.
//
//////////////////////////////////////////////////////////////////////

#include "Marker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Marker::Marker(int X, int Y, unsigned char type, double fer):
EnvObject(X, Y), Type(type), Strength(0.0f), MaxStrength(0.0f), decayRate(fer){

	if(isOrganismDROPMarker())     
		{MaxStrength = DROPMarkerSTRENGTH;}
	else
    if(isExploreMarker())     
		{MaxStrength = XPLOMarkerSTRENGTH;}
	else
	if(iscollect_itemCarryingMarker())
		{MaxStrength = COLLMarkerSTRENGTH;}

        refreshMarker();
}


Marker::Marker(const Marker& P)
:EnvObject(P.x, P.y),  Type(P.Type), Strength(P.Strength), MaxStrength(P.MaxStrength), decayRate(P.decayRate){}


void Marker::draw(GLfloat hor_step, GLfloat vert_step){
		glColor3f(1.0f, 0.7f, 0.85f);
		glBegin(GL_QUADS);          
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, vert_step, 0.0);
            glVertex3f((hor_step*Strength)/(MaxStrength), vert_step/2.0f, 0.0);
            glVertex3f(hor_step/2.0f, 0.0, 0.0);
        glEnd();
}

Marker::~Marker()
{

}
