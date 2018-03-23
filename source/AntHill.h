// AntHill.h: interface for the AntHill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANTHILL_H__42F5E49B_C5C5_49ED_8C39_8C7E359E76DA__INCLUDED_)
#define AFX_ANTHILL_H__42F5E49B_C5C5_49ED_8C39_8C7E359E76DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class AntHill  : public EnvObject
{
public:
    AntHill(int X, int Y);
    virtual ~AntHill();

    void draw(GLfloat hor_step, GLfloat vert_step);
    ObjectType objectType(){return ANTHILL;};
};

#endif // !defined(AFX_ANTHILL_H__42F5E49B_C5C5_49ED_8C39_8C7E359E76DA__INCLUDED_)
