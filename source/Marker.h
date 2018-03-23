// Marker.h: interface for the Marker class.
//
//////////////////////////////////////////////////////////////////////



#define DROPMarkerTYPE (unsigned char)1
#define XPLOMarkerTYPE (unsigned char)2
#define COLLMarkerTYPE (unsigned char)3

#define DROPMarkerSTRENGTH (double)3.0f
#define XPLOMarkerSTRENGTH (double)3.0f
#define COLLMarkerSTRENGTH (double)3.0f

#define DROPMarkerDECAY (double)0.5f
#define XPLOMarkerDECAY (double)0.5f




class Marker : public EnvObject {

protected:
	double decayRate;
    double MaxStrength;
    double Strength;
    unsigned char Type;
    
   
public:
	//static void setMarkerDecay(double Deca){Marker::m_collect_itemMarkerDecay = Deca;};
	Marker(int X, int Y, unsigned char type, double = 0.5);
	Marker(const Marker& P);			
	virtual ~Marker();
    
    void decay(){
        if(isOrganismDROPMarker())     {Strength *= DROPMarkerDECAY; return;}
        if(isExploreMarker())     {Strength *= XPLOMarkerDECAY; return;}
		if(iscollect_itemCarryingMarker()){Strength *= decayRate; return;}
    }
    
    double getStrength(){return Strength;};
    
    void refreshMarker(){
        if(isOrganismDROPMarker())     {Strength += DROPMarkerSTRENGTH; return;}
        if(isExploreMarker())     {Strength += XPLOMarkerSTRENGTH; return;}
        if(iscollect_itemCarryingMarker()){Strength += COLLMarkerSTRENGTH; return;}
        throw "Unknown Marker Type at Marker::refreshMarker()";
    };
    
    
    bool isOrganismDROPMarker()       {return Type == DROPMarkerTYPE;};
    bool isExploreMarker()       {return Type == XPLOMarkerTYPE;};
    bool iscollect_itemCarryingMarker()  {return Type == COLLMarkerTYPE;};
    bool isSameType(const Marker& P){return P.Type == Type;};
    unsigned char getMarkerType(){return Type;};    
    
    void draw(GLfloat hor_step, GLfloat vert_step);
    ObjectType objectType(){return Marker;};
};



#endif // !defined(AFX_Marker_H__6E81BE89_A79D_451F_9ABD_5EEAD07C7C89__INCLUDED_)
