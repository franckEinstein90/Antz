// EnvObject.h: interface for the EnvObject class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
class EnvObject : public CObject{

    protected:
        int x;
        int y;
       
	static int MemTrace(int t)
	{
		static int Mem = 0;
		Mem += t;
		return Mem;
	}
	static int ObjNum(int t)
	{
		static int ObjNum = 0;
		ObjNum += t;
		return ObjNum;
	}

public:

	EnvObject(int X, int Y):x(X), y(Y){ObjNum(1);}
    virtual ~EnvObject(){ObjNum(-1);}

	//Dynamic memory allocators
	void *operator new(size_t size);
  	void *operator new[](size_t size);
  	void operator delete(void *p);
  	void operator delete[](void *p);
  
	int getX() const {return x;};   
    int getY() const {return y;};
    virtual void moveTo(int NewX, int NewY){x = NewX; y = NewY;};
    
    virtual void draw(float hor_step, float vert_step, 
    	void (drawFun)(float,float,int,int)) const
    {
    	(*drawFun)(hor_step, vert_step, x, y);
    }
	virtual ObjectType objectType() const = 0;
};



#endif // !defined(AFX_ENVOBJECT_H__CA579064_C020_4214_838B_71E4686F6C33__INCLUDED_)
