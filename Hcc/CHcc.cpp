#include "CHcc.h"

void const* CHcc::compile(use_map const &in_use, dev_map const &dev, size_t &len)
{
	return cmgr.compile(in_use, dev, len);
}
bool CHcc::compile(unsigned int code_id, string const &code, dev_map const &dev)
{
	return cmgr.compile(code_id, code, dev);
}
CHcc::ErrorRecord const& CHcc::getErrorRecord()
{
	return cmgr.getErrorRecord();
}
CHcc::key_word const& CHcc::getKeyWords()
{
	return cmgr.getKeyWords();
}
CHcc::fun_set const& CHcc::getFunSet()
{
	return cmgr.getFunSet();
}
FunInfo const* CHcc::getSignature(string const& name)
{
	return cmgr.getSignature(name);
}
CHcc::var_map const& CHcc::getVars(string const &code, dev_map const &dev)
{
	return cmgr.getVars(code, dev);
}
