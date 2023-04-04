#include "CConstTable.h"
#include "CHillock.h"
#include "CDataType.h"

Address ConstTable::getAddress(bool const val)
{
	Address addr;
	addr.section=section;

	bool_map::const_iterator citor=bool_const.find(val);

	if(citor!=bool_const.end())
	{
		addr.offset=citor->second;
	}
	else
	{
		addr.offset=offset;
		bool_const[val]=offset++;
	}

	return addr;
}
Address ConstTable::getAddress(unsigned char const val)
{
	Address addr;
	addr.section=section;

	ascii_map::const_iterator citor=ascii_const.find(val);

	if(citor!=ascii_const.end())
	{
		addr.offset=citor->second;
	}
	else
	{
		addr.offset=offset;
		ascii_const[val]=offset++;
	}

	return addr;
}
Address ConstTable::getAddress(int const val)
{
	Address addr;
	addr.section=section;

	number_map::const_iterator citor=number_const.find(val);

	if(citor!=number_const.end())
	{
		addr.offset=citor->second;
	}
	else
	{
		addr.offset=offset;
		number_const[val]=offset++;
	}

	return addr;
}
Address ConstTable::getAddress(double const val)
{
	Address addr;
	addr.section=section;

	real_map::const_iterator citor=real_const.find(val);

	if(citor!=real_const.end())
	{
		addr.offset=citor->second;
	}
	else
	{
		addr.offset=offset;
		real_const[val]=offset++;
	}

	return addr;
}
void ConstTable::Clear()
{
	Table::Clear();

	bool_const.clear();
	ascii_const.clear();
	number_const.clear();
	real_const.clear();
}
void ConstTable::BuildByteCode(byte_cont &byte_code)const
{
	//首先进行offset-value位置互换

	typedef map<size_t,bool> map_bool;
	typedef map<size_t,unsigned char> map_ascii;
	typedef map<size_t,int> map_number;
	typedef map<size_t,double> map_real;
	using std::make_pair;

	map_bool bool_val;
	map_ascii ascii_val;
	map_number number_val;
	map_real real_val;

	for(bool_map::const_iterator citb=bool_const.begin();citb!=bool_const.end();++citb)
		bool_val.insert(make_pair(citb->second,citb->first));

	for(ascii_map::const_iterator cita=ascii_const.begin();cita!=ascii_const.end();++cita)
		ascii_val.insert(make_pair(cita->second,cita->first));

	for(number_map::const_iterator citn=number_const.begin();citn!=number_const.end();++citn)
		number_val.insert(make_pair(citn->second,citn->first));

	for(real_map::const_iterator citr=real_const.begin();citr!=real_const.end();++citr)
		real_val.insert(make_pair(citr->second,citr->first));

	map_bool::const_iterator citbv;
	map_ascii::const_iterator citav;
	map_number::const_iterator citnv;
	map_real::const_iterator citrv;	


	//	format:
	//	[Number]:unsigned int
	//	[Data]:	format->[type-flag][value],type-flag->unsigned char,value->bool/unsigned char/int/double
	//	[Data]
	//	[Data]
	//  ...
	

	// [Number]
	Compiler::Enqueue(byte_code,unsigned int(offset));

	size_t cnt=0;
	while(cnt<offset)
	{
		citbv=bool_val.find(cnt);
		if(citbv!=bool_val.end())
		{
			// [type-flag]
			Compiler::Enqueue(byte_code,unsigned char(t_BOOL));

			// [value]
			Compiler::Enqueue(byte_code,citbv->second);

			bool_val.erase(citbv);
			++cnt;
			continue;
		}

		citav=ascii_val.find(cnt);
		if(citav!=ascii_val.end())
		{
			// [type-flag]
			Compiler::Enqueue(byte_code,unsigned char(t_CHAR));

			// [value]
			Compiler::Enqueue(byte_code,citav->second);

			ascii_val.erase(citav);
			++cnt;
			continue;	
		}

		citnv=number_val.find(cnt);
		if(citnv!=number_val.end())
		{
			// [type-flag]
			Compiler::Enqueue(byte_code,unsigned char(t_INT));

			// [value]
			Compiler::Enqueue(byte_code,citnv->second);

			number_val.erase(citnv);
			++cnt;
			continue;
		}

		citrv=real_val.find(cnt);
		if(citrv!=real_val.end())
		{
			// [type-flag]
			Compiler::Enqueue(byte_code,unsigned char(t_DOUBLE));

			// [value]
			Compiler::Enqueue(byte_code,citrv->second);

			real_val.erase(citrv);
			++cnt;
			continue;
		}

		++cnt;
	}
}