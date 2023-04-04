#include "CSynRecord.h"

SynRecord* SynRecord::p_syn=0;

void SynRecord::Generate()
{
	p_syn=new SynRecord();
}
void SynRecord::Destroy()
{
	delete p_syn;
}