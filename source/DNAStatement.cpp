// DNAStatement.cpp: implementation of the CDNAStatement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Assignment2.h"
#include "DNAStatement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDNAStatement, CObject, 1)

void CDNAStatement::copy(const CDNAStatement& S){
        
        destroy();
        arity   = S.arity; 
        Type    = S.Type;
	fitness = S.fitness;
        MutationPbblty   =  S.MutationPbblty;   
        CrossOverMaxDepth = S.CrossOverMaxDepth;
        
		for(unsigned int j=0; j<S.SubStatements.size(); j++)
			SubStatements.push_back(new CDNAStatement(*(S.SubStatements[j])));
			
}

void CDNAStatement::destroy(){
        
        arity   = 0; 
        Type    = SNULL;
        for(unsigned int i=0; i<SubStatements.size(); i++)
            delete  SubStatements[i];
        SubStatements.clear();

}


void CDNAStatement::CompleteConstruction(){

	while(SubStatements.size() < arity)
		SubStatements.push_back(new CDNAStatement(SNULL));
	

	//for(int i=0; i<SubStatements.size(); i++)

	MutationPbblty		= DEFAULTMUTPROB;
	CrossOverMaxDepth   = DEFAULTCROSSOVERMAXDEPTH;
	fitness = 0.0f;
}
CDNAStatement::CDNAStatement(const CDNAStatement& S)
{
	copy(S);
	MemTrace(1);
}


CDNAStatement::CDNAStatement(GENEStatementType S):
Type(S){
                      
    switch (Type){
    
        //Moving instructions
	case SNULL:
        case MOVE_RANDOM:
        case MOVE_TO_ADJACENT_FOOD:
        case MOVE_TO_ADJACENT_PHEROMONE:
        case MOVE_TO_NEST:
        
        //pick/drop instructions
        case DROP_FOOD:                                
        case PICK_UP_FOOD:
        case DROP_PHEROMONE:
        
        //position information
        case IS_ADJACENT_PHEROMONE:
        case IS_ADJACENT_FOOD:
        case IS_CARRYING_FOOD:
        case FOOD_HERE:
        case IS_HOME:
        
            arity = 0;
            break;
                            
       case MOVE_TO_ADJACENT_PHEROMONE_ELSE:
		Type = IF;
		SubStatements.push_back(new CDNAStatement(IS_ADJACENT_PHEROMONE));
		SubStatements.push_back(new CDNAStatement(MOVE_TO_ADJACENT_PHEROMONE));
		arity = 3;
		break;     
            
        case MOVE_TO_ADJACENT_FOOD_ELSE:
		Type = IF;
		SubStatements.push_back(new CDNAStatement(IS_ADJACENT_FOOD));
		SubStatements.push_back(new CDNAStatement(MOVE_TO_ADJACENT_FOOD));
		arity = 3;
		break;
            
	case IF_CARRYING_FOOD:
		Type = IF;
		SubStatements.push_back(new CDNAStatement(IS_CARRYING_FOOD));
		arity = 3;
		break;
       
	case IF_FOOD_HERE:
		Type = IF;
		SubStatements.push_back(new CDNAStatement(FOOD_HERE));
		arity = 3;
		break;
                    
        case IF:
		arity = 3;
		break;
                                    
        case PROGN:
		arity = MAXARITY;
		break;
            
        default:
            throw "Unknown instruction in Statement constructor";
    }
	MemTrace(1);		
	CompleteConstruction();
}

CDNAStatement::CDNAStatement(CTreeCtrl* Tctrl, HTREEITEM hParent){
	
	if(hParent == Tctrl->GetRootItem())
		Type = PROGN;
	else{
		CString Statemente(Tctrl->GetItemText(hParent));
		Type = CDNAStatement::fromString(Statemente);
	}

	switch (Type){

				case  PROGN:
					arity = MAXARITY;
					if(Tctrl->ItemHasChildren(hParent)){
							HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
							while((Kid) && (Tctrl->GetItemText(Kid) != CString(TreeTag(SNULL)))){
								SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
								Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
							}
					}
					break;

				case SNULL:
				case MOVE_RANDOM:
				case MOVE_TO_ADJACENT_FOOD:
				case MOVE_TO_ADJACENT_PHEROMONE:
				case MOVE_TO_NEST:
		        
				//pick/drop instructions
				case DROP_FOOD:                                
				case PICK_UP_FOOD:
				case DROP_PHEROMONE:
		        
				//position information
				case IS_ADJACENT_PHEROMONE:
				case IS_ADJACENT_FOOD:
				case IS_CARRYING_FOOD:
				case FOOD_HERE:
				case IS_HOME:
					
					arity = 0;
					break;
		                            
			case MOVE_TO_ADJACENT_PHEROMONE_ELSE:
					Type = IF;
					SubStatements.push_back(new CDNAStatement(IS_ADJACENT_PHEROMONE));
					SubStatements.push_back(new CDNAStatement(MOVE_TO_ADJACENT_PHEROMONE));
					arity = 3;
					if(Tctrl->ItemHasChildren(hParent)){
								HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
								Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
								if(Kid) {
										Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
										if(Kid) SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
								}
					}
					break;     
            
			case MOVE_TO_ADJACENT_FOOD_ELSE:
				Type = IF;
				SubStatements.push_back(new CDNAStatement(IS_ADJACENT_FOOD));
				SubStatements.push_back(new CDNAStatement(MOVE_TO_ADJACENT_FOOD));
				arity = 3;
				if(Tctrl->ItemHasChildren(hParent)){
								HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
								Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
								if(Kid) {
										Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
										if(Kid) SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
								}
				}
				break;
	            
			case IF_CARRYING_FOOD:
				Type = IF;
				SubStatements.push_back(new CDNAStatement(IS_CARRYING_FOOD));
				arity = 3;
				if(Tctrl->ItemHasChildren(hParent)){
									HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
									Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
									if(Kid) {
											SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
											Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
											if(Kid) SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
									}
						}
				break;
       
			case IF_FOOD_HERE:
				Type = IF;
				SubStatements.push_back(new CDNAStatement(FOOD_HERE));
				arity = 3;
				if(Tctrl->ItemHasChildren(hParent)){
									HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
									Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
									if(Kid) {
											SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
											Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
											if(Kid) SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
									}
						}
				break;
                    
        case IF:
            arity = 3;
			if(Tctrl->ItemHasChildren(hParent)){
								HTREEITEM Kid = Tctrl->GetNextItem(hParent, TVGN_CHILD);
								if(Kid){
									SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
									Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
									if(Kid) {
										SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
										Kid = Tctrl->GetNextItem(Kid, TVGN_NEXT);
										if(Kid) SubStatements.push_back(new CDNAStatement(Tctrl, Kid));
									}
								}
					}
            break;
        
        default:
            throw "Unknown instruction in Statement constructor";
    }	

	MemTrace(1);	
	CompleteConstruction();    
}

bool CDNAStatement::operator==(const CDNAStatement& S){
        if((arity-S.arity)||((int)Type-(int)S.Type)) return false;            
        if (!arity) return true;
        
        for(unsigned int i=0; i<SubStatements.size();i++)
            if(!(*SubStatements[i] == *S.SubStatements[i]))
                return false;
        
        return true;
}


const CDNAStatement& CDNAStatement::operator[] (unsigned int i){

    if(i >= arity)
        throw "out of bound";
    return *(SubStatements[i]);
}




CDNAStatement::~CDNAStatement()
{
		destroy();
		MemTrace(-1);
}



const CDNAStatement& CDNAStatement::operator=(const CDNAStatement& S){
    copy(S);
    return *this;
}

bool CDNAStatement::Eval(Ant* A) const{

    switch (Type){
        
	case MOVE_RANDOM:
        case MOVE_TO_NEST:                                
        case PICK_UP_FOOD:
        case DROP_PHEROMONE:
        case IS_ADJACENT_PHEROMONE:
        case IS_ADJACENT_FOOD:
        case IS_CARRYING_FOOD:
	case MOVE_TO_ADJACENT_FOOD:
	case MOVE_TO_ADJACENT_PHEROMONE:
        case FOOD_HERE:
        case IS_HOME:
        case DROP_FOOD:
		return A->play(Type);
		break;	                                              
 
        case IF:
		if(SubStatements[0]->Eval(A))
			return SubStatements[1]->Eval(A);
		else
			return SubStatements[2]->Eval(A);
		break;
                                    
        case PROGN:
		for(unsigned int i=0; i<SubStatements.size();i++)
			SubStatements[i]->Eval(A);
		break;

	case SNULL:
		break;

	default:
		throw _T("Unknown statement eval");
       }
       return true;        
}


void CDNAStatement::Serialize( CArchive& archive ){
    
         CObject::Serialize( archive );

         if( archive.IsStoring() ){
					archive<<arity;
					archive<<(int)Type;
					archive<<MutationPbblty;
					archive<<CrossOverMaxDepth;
					archive<<SubStatements.size();
					for(unsigned int i=0; i<SubStatements.size(); i++){
						 SubStatements[i]->Serialize(archive);   
			}
         }
        else{
				destroy();
				archive>>arity;
				int inType;
				archive>>inType;
				Type = (GENEStatementType)inType;
				SubStatements.clear();
				archive>>MutationPbblty;
				archive>>CrossOverMaxDepth;
				int StateSize;
				archive>>StateSize;
				for(int i=0; i<StateSize; i++){
						CDNAStatement* Sub = new CDNAStatement(SNULL);
						Sub->Serialize(archive);
						SubStatements.push_back(Sub);   
             }
        }
}




bool CDNAStatement::replaceBranch(unsigned int branchNum, const CDNAStatement& S){
	
	if(removeBranch(branchNum)) {
		addBranch(branchNum, S);	
		return true;
	}

	return false;
	
}


void CDNAStatement::addBranch(unsigned int branchNum, const CDNAStatement& S){
	SubStatements[branchNum] = new CDNAStatement(S);
}






bool CDNAStatement::removeBranch(unsigned int branchNum){

		//Can't remove root
		if(branchNum >= this->arity) return false;
		
		//special conditions. some of these guys have branch that shouldn't be removed
		switch (Type){
			case MOVE_TO_ADJACENT_PHEROMONE_ELSE:
			case MOVE_TO_ADJACENT_FOOD_ELSE:
					if(branchNum == 1) return false; 

			case IF_FOOD_HERE:
			case IF_CARRYING_FOOD:				
					if(branchNum == 0) return false; 

		}


		if(SubStatements[branchNum]) {
				delete SubStatements[branchNum];
				SubStatements[branchNum] = new CDNAStatement(SNULL);
		}
		return true;
}

LPCTSTR CDNAStatement::TreeTag(GENEStatementType S){

	TOSTRING(S, IS_ADJACENT_PHEROMONE);
	TOSTRING(S, IS_ADJACENT_FOOD);
	TOSTRING(S, IS_HOME);
	TOSTRING(S, FOOD_HERE);
	TOSTRING(S, MOVE_RANDOM);
	TOSTRING(S, MOVE_TO_NEST);
	TOSTRING(S, PICK_UP_FOOD);
	TOSTRING(S, IS_CARRYING_FOOD);
	TOSTRING(S, DROP_PHEROMONE);
	TOSTRING(S, DROP_FOOD);
	TOSTRING(S, MOVE_TO_ADJACENT_FOOD);
	TOSTRING(S, MOVE_TO_ADJACENT_PHEROMONE);
	TOSTRING(S, MOVE_TO_ADJACENT_FOOD_ELSE);
	TOSTRING(S, MOVE_TO_ADJACENT_PHEROMONE_ELSE);
	TOSTRING(S, IF);
	TOSTRING(S, IF_FOOD_HERE);
	TOSTRING(S, IF_CARRYING_FOOD);
	TOSTRING(S, PROGN);
	TOSTRING(S, SNULL);

	throw _T("Unknown Statement Formation atempt at CDNAStatement::TreeTag");
}


GENEStatementType CDNAStatement::fromString (const CString& Str){

	FROMSTRING(Str, IS_ADJACENT_PHEROMONE);
	FROMSTRING(Str, IS_ADJACENT_FOOD);
	FROMSTRING(Str, IS_HOME);
	FROMSTRING(Str, FOOD_HERE);
	FROMSTRING(Str, MOVE_RANDOM);
	FROMSTRING(Str, MOVE_TO_NEST);
	FROMSTRING(Str, PICK_UP_FOOD);
	FROMSTRING(Str, IS_CARRYING_FOOD);
	FROMSTRING(Str, DROP_PHEROMONE);
	FROMSTRING(Str, DROP_FOOD);
	FROMSTRING(Str, MOVE_TO_ADJACENT_FOOD);
	FROMSTRING(Str, MOVE_TO_ADJACENT_PHEROMONE);
	FROMSTRING(Str, MOVE_TO_ADJACENT_FOOD_ELSE);
	FROMSTRING(Str, MOVE_TO_ADJACENT_PHEROMONE_ELSE);
	FROMSTRING(Str, IF);
	FROMSTRING(Str, IF_FOOD_HERE);
	FROMSTRING(Str, IF_CARRYING_FOOD);
	FROMSTRING(Str, PROGN);
	return SNULL;
}

unsigned int CDNAStatement::getLength() const{

  

 if(!arity) return (unsigned int)0;

    unsigned int res = 0;
    unsigned int temp;
    
    for(unsigned int i=0; i<SubStatements.size();i++){
            temp = SubStatements[i]->getDepth();       
            if(temp > res)
                res = temp; 
    }
    return res + 1;
}

unsigned int CDNAStatement::getDepth() const{

	if(Type == SNULL) return (unsigned int)0;
	if(!arity) return (unsigned int)1;
    
	unsigned int res = 0;
	for(unsigned int i=0; i < SubStatements.size(); i++){
		unsigned int d = SubStatements[i]->getDepth();
		if(d > res) res = d;
	}
    
	return res +1 ;
}


 CDNAStatement& CDNAStatement::operator*(CDNAStatement& Dad) {

		CDNAStatement* Kid = new CDNAStatement(*this);
		
		unsigned int DadDepth = Dad.getDepth();
		unsigned int MomDepth = getDepth();
		int CrossDepthKid = (rand()%CrossOverMaxDepth)%
                            ((MomDepth < DadDepth)? MomDepth:DadDepth);
		CrossDepthKid++;
		if(CrossDepthKid < 2) CrossDepthKid = 2;
		//Always cutoff the longest branch
		
		//Get the part from dad that we need 
		CDNAStatement* DadPart = Dad.getBranchRandomType(CrossOverMaxDepth, FUNC);
		if(!DadPart)
			DadPart = Dad.getBranchRandomType(CrossOverMaxDepth, TERMINAL);

		if(!DadPart)
			DadPart = Dad.getBranchRandomType(CrossOverMaxDepth, BOOLFUNC);

		if(DadPart){
			//figure out how deep we can cut
			int KidCrossDepth = Kid->getDepth() - DadPart->getDepth();

			if(KidCrossDepth > 1){
			//find a suitable cross in that range
				CDNAStatement* KidCross = 
					Kid->getBranchRandomType(KidCrossDepth, 
						CFunctionSet::GetTypeClass(DadPart->Type));
					if(KidCross)
						*KidCross = *DadPart;
			}
		}
		
		double MutRate = MutationPbblty;
		while (rand()% 1000 <(MutRate * 1000)){
			Kid->mutate();
			MutRate/=2.0;
		}
		Kid->fitness = 0.0f;
		return *Kid;

 }

 void CDNAStatement::mutate(){
	
	int MutDepthKid = (rand()%getDepth())+1;
	if(MutDepthKid < 2) MutDepthKid = 2;

	CDNAStatement* MutPart = this->getBranchRandomType(MutDepthKid, TERMINAL);
	if(!MutPart)
		CDNAStatement* MutPart = this->getBranchRandomType(MutDepthKid, BOOLFUNC);

	if(MutPart){
		CDNAStatement T;
		switch(CFunctionSet::GetTypeClass(MutPart->Type)){
		
			case (BOOLFUNC):
				T = CDNAStatement(CFunctionSet::getRandBoolFunction());
				break;
			
			case(TERMINAL):
				T = CDNAStatement(CFunctionSet::getRandTerminal());
		}
		*MutPart = T;	
	}
 }
 
 CDNAStatement* CDNAStatement::getBranchRandomType(unsigned int MaxDepth, FUNCTIONTYPECLASS BranchType){

		vector<CDNAStatement*> candidates;
		FUNCTIONTYPECLASS m_ClassType = CFunctionSet::GetTypeClass(this->Type);

		if	((this->getDepth() <= MaxDepth) &&
			( (m_ClassType == BranchType ))) 
				candidates.push_back(this);
		
				
		
		for(COUNTER i=0; i<this->SubStatements.size(); i++){
			CDNAStatement* candidate = SubStatements[i]->getBranchRandomType(MaxDepth, BranchType);
			if(candidate) candidates.push_back(candidate);
		}

		if(candidates.size())
			return candidates[rand()%candidates.size()];
		else 
			return ((CDNAStatement*)0);
}

 CDNAStatement* CDNAStatement::getBranchAt(int Depth, int BranchType) {
 //Always goes along the longest branching
	if(Depth > this->getDepth()) Depth = this->getDepth();

        CDNAStatement* Iterator1 = this;
        CDNAStatement* Iterator2 = this;
        
	int diver = 0;
        bool go = true;
        
	while((diver < Depth)&&(go)){
		Iterator2 = Iterator1;
		int maxBranch = 0;
		for(int i=0; i<(Iterator2->getArity());i++)

			if((*Iterator2)[i].getDepth() > maxBranch){

				maxBranch   =  (*Iterator2)[i].getDepth();
				Iterator1   =    Iterator2->SubStatements[i];

			}

			if(!maxBranch) 
				go = false;
			else 
				diver++;
        }
	if((BranchType == ANYTYPE)||(Iterator2->Type == ANYTYPE))
		return  Iterator2;
	if((BranchType == ANYTYPE)||(CFunctionSet::GetTypeClass(Iterator2->Type) == BranchType))
		return  Iterator2;

//	if((Iterator2->arity > 0))
//		while((Iterator2->Type != ANYTYPE)&&(Iterator2->Type != BranchType))
	AfxMessageBox(_T("Type Mismatch"));	
	return  Iterator2;
 }


 void CDNAStatement::grow(int MaxDepth){
                    //If at the end, we need a terminal.
                    //If not at the end, we might get a Terminal 
                    //or a function. So i flip a coin

		    	
                    if((MaxDepth + 1 <= 0)||((rand()%2))){
                        copy(CDNAStatement(CFunctionSet::getRandTerminal()));
                        return;
                    }    
                    else{
                        //we could get either a function or a progn (with lower pbblty). 
                        //flip a heavily function sided coin ?
                       /* if((rand()% 10) == 0)
                            copy(CDNAStatement());
                        else*/
                        copy(CDNAStatement(CFunctionSet::getRandFunction()));
                         
			for(unsigned int i = 0; i < SubStatements.size(); i++){
				if(SubStatements[i]->Type == SNULL)
                                //If we are looking at an inconditionned IF statement
                                //provide a condition
                                if((Type == IF) &&(!i))
                                    SubStatements[i]->copy(CDNAStatement(CFunctionSet::getRandBoolFunction()));
                                else
                                    SubStatements[i]->grow(MaxDepth - 1);        
			}
		
		    }
};





