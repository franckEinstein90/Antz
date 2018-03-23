// DNAStatement.h: interface for the CDNAStatement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DNASTATEMENT_H__DCFC8BA5_4599_4DA0_BEE9_E75AF010251E__INCLUDED_)
#define AFX_DNASTATEMENT_H__DCFC8BA5_4599_4DA0_BEE9_E75AF010251E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"


#define MAXARITY 15
#define DEFAULTMUTPROB 0.01f
#define DEFAULTCROSSOVERMAXDEPTH 10

#define FROMSTRING(str, statement) \
	if (str == CString(_T(#statement)))\
				return statement


#define TOSTRING(var, statement) \
	if(var == statement) return #statement


class CDNAStatement : public CObject {

   
        protected:
		
		unsigned int arity; 
                GENEStatementType Type;
                vector<CDNAStatement*> SubStatements; 
                
		void copy(const CDNAStatement& S);  
		void destroy();
		void CompleteConstruction();

		//returns a branch at the specified depth (if there is one)
		

		void addBranch(unsigned int i, const CDNAStatement& S);
		bool removeBranch(unsigned int i);
			  
		double MutationPbblty;
		int CrossOverMaxDepth;
			
        public:
		
		CDNAStatement* getBranchAt(int Depth, int BranchType) ;
		static int MemTrace(int t){
			static int Mem = 0;
			Mem += t;
			return Mem;
		}
		void mutate();
		double fitness;
		static GENEStatementType fromString(const CString& Str);
		static LPCTSTR TreeTag(GENEStatementType S);

		void setCrossOverMaxDepth(int Depth){CrossOverMaxDepth = Depth;};
		void setMutationProb(double Prob){
                if(Prob<0.0f)
                     MutationPbblty = 0.0f;
                else
                    if(Prob>1.0f)
                         MutationPbblty = 1.0f;
                    else
                        MutationPbblty = Prob;
		};
	
		unsigned int getLength() const;
		unsigned int getDepth() const;
		unsigned int getArity() const { 
			return arity; 
		}
		
		
		;
		GENEStatementType getRoot() const {
			return Type;
		};

	

		DECLARE_SERIAL( CDNAStatement );

		CDNAStatement(GENEStatementType S = PROGN);
		CDNAStatement(CTreeCtrl* Tctrl, HTREEITEM hParent = TVI_ROOT);
		CDNAStatement(const CDNAStatement& S);
		const CDNAStatement& operator=(const CDNAStatement& S);
		CDNAStatement& operator*(CDNAStatement& C) ;
		

		virtual ~CDNAStatement();
		virtual void Serialize( CArchive& archive );
		
		bool operator == (const CDNAStatement& S);
		const CDNAStatement& operator[] (unsigned int i);
		CDNAStatement* getBranchRandomType(unsigned int MaxDepth, FUNCTIONTYPECLASS BranchType);
			

		CString toString(){

			CString Res;
			Res = _T("(");
			
			try{
				Res += TreeTag(Type);
			}
			catch(LPCTSTR ErrStatement){
				Res += ErrStatement;	
			}

			for(COUNTER i=0; i<this->SubStatements.size(); i++)
				Res += this->SubStatements[i]->toString();
				
			Res += _T(")");
			return Res;
			
		}


			
		friend bool operator!(const CDNAStatement& S){
			return (S.Type == SNULL);
		}

		void grow(int MaxDepth);
		void growCreate(int Maxdepth){
			
			ASSERT (this->Type == PROGN);
			//for(int i=0; i<this->SubStatements.size();i++)

			
			
			//copy(CDNAStatement());
			for(COUNTER i=0; i<this->SubStatements.size();i++)
				this->SubStatements[i]->grow(Maxdepth-1);

			//while(SubStatements.size())
		}
		
		
		bool Eval(Ant* A) const;
		bool replaceBranch(unsigned int i, const CDNAStatement& S);
		void toTreeCtrl(CTreeCtrl* Tctrl, HTREEITEM branch){
				
				
					if(!branch) branch = Tctrl->InsertItem((LPCTSTR)" ");
			
				
					Tctrl->SetItemText(branch, TreeTag(Type));
				
					for(unsigned int i=0; i<SubStatements.size(); i++)
						if(SubStatements[i]){
							HTREEITEM Root =  Tctrl->InsertItem(TreeTag(Type), branch);	
							SubStatements[i]->toTreeCtrl(Tctrl, Root);
					}
				
				
			};


};

#endif // !defined(AFX_DNASTATEMENT_H__DCFC8BA5_4599_4DA0_BEE9_E75AF010251E__INCLUDED_)
















