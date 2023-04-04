#pragma once

#include "CStackRecord.h"

class Sign:virtual public StackRecord
{
public:		
	Sign(int const t):StackRecord(),tag(t){}

	//copy constructor
	Sign(Sign const &rhs):StackRecord(rhs),tag(rhs.tag){}

	//redefine		
	int const Tag()const{return tag;}

	//redefine	
	~Sign()=0{}
	
private:
	int const tag;	//sign code
};