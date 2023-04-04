#include "CActRecord.h"

ActRecord* ActRecord::p_act=0;

void ActRecord::Generate()
{
	p_act=new ActRecord();
}
void ActRecord::Destroy()
{
	delete p_act;
}