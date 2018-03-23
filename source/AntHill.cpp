// AntHill.cpp: implementation of the AntHill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Assignment2.h"
#include "AntHill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AntHill::AntHill(int X, int Y):
EnvObject(X, Y){

}

void AntHill::draw(GLfloat hor_step, GLfloat vert_step){
        
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);          
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, vert_step, 0.0);
            glVertex3f(hor_step, vert_step, 0.0);
            glVertex3f(hor_step, 0.0, 0.0);
        glEnd();
}

AntHill::~AntHill()
{

}
