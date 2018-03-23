#pragma once

enum GENEStatementType{ 
    
    SNULL = 0,

    //Bool Functions
    IS_ADJACENT_PHEROMONE,
    IS_ADJACENT_FOOD,
    IS_HOME,
    FOOD_HERE,
    IS_CARRYING_FOOD,
    
    //Terminals
    MOVE_RANDOM,
    MOVE_TO_NEST,
    PICK_UP_FOOD,
    DROP_PHEROMONE,
    DROP_FOOD,
    MOVE_TO_ADJACENT_FOOD,
    MOVE_TO_ADJACENT_PHEROMONE,
    
    //Functions
    MOVE_TO_ADJACENT_FOOD_ELSE,
    MOVE_TO_ADJACENT_PHEROMONE_ELSE,
    IF,
    IF_FOOD_HERE,
    IF_CARRYING_FOOD,
    
    PROGN

};

#define FUNCTIONTYPECLASS unsigned char
#define ANYTYPE	(FUNCTIONTYPECLASS)0
#define TERMINAL	(FUNCTIONTYPECLASS)1
#define BOOLFUNC	(FUNCTIONTYPECLASS)2
#define FUNC		(FUNCTIONTYPECLASS)3
#define NOTYPE		(FUNCTIONTYPECLASS)4
// CFunctionSet command target

class CFunctionSet : public CObject
{

public:
		static bool isBoolFunction(GENEStatementType T){
                    return (((unsigned int)T>=(unsigned int)IS_ADJACENT_PHEROMONE)
                            &&((unsigned int)T<=(unsigned int)IS_CARRYING_FOOD));              
              };
		static bool isFunction(GENEStatementType T){
                    return (((unsigned int)T>=(unsigned int)MOVE_TO_ADJACENT_FOOD_ELSE)
                            &&((unsigned int)T<=(unsigned int)IF_CARRYING_FOOD));              
              };
		static bool isTerminal(GENEStatementType T){
                    return (((unsigned int)T>=(unsigned int)MOVE_RANDOM)
                    &&((unsigned int)T<=(unsigned int)MOVE_TO_ADJACENT_PHEROMONE));              
              };
              
		static GENEStatementType getRandBoolFunction(){
					
                    unsigned int FuncNums = (unsigned int)MOVE_RANDOM - 
                                            (unsigned int)IS_ADJACENT_PHEROMONE;
                    return (GENEStatementType)((rand()%FuncNums)+
                                            (unsigned int) IS_ADJACENT_PHEROMONE);
			};
		static GENEStatementType getRandTerminal(){
                    unsigned int FuncNums = (unsigned int)MOVE_TO_ADJACENT_FOOD_ELSE - 
                                            (unsigned int)MOVE_RANDOM;
                    return (GENEStatementType)((rand()%FuncNums)+
                                            (unsigned int) MOVE_RANDOM);
              };
              
		static GENEStatementType getRandFunction(){
                    unsigned int FuncNums = (unsigned int)PROGN - 
                                            (unsigned int)MOVE_TO_ADJACENT_FOOD_ELSE;
                    return (GENEStatementType)((rand()%FuncNums)+
                                            (unsigned int) MOVE_TO_ADJACENT_FOOD_ELSE);    
              };

		static bool isSameFunctionTypeClass(GENEStatementType T1, GENEStatementType T2){
				
				return(((isBoolFunction(T1))&&(isBoolFunction(T2)))||
						((isFunction(T1))&&(isFunction(T2)))||
						((isTerminal(T1))&&(isTerminal(T2))));
		}

		static FUNCTIONTYPECLASS GetTypeClass(GENEStatementType T2){

			if(isBoolFunction(T2))	return BOOLFUNC;
			if(isTerminal(T2))		return TERMINAL;
			if(isFunction(T2))		return FUNC;
			
			return NOTYPE;
		}

	

		CFunctionSet();
		virtual ~CFunctionSet();
};


