#pragma once

#include <map>
#include <string>
using std::map;
using std::multimap;
using std::string;
using std::pair;

class Pretreatment
{
	typedef string::size_type ssize;
	typedef multimap<size_t,string> ErrorRecord;
	typedef map<string,pair<int,bool> > addt_map;
	typedef map<string,pair<int,addt_map> > dev_map;

public:
	Pretreatment(ErrorRecord &e_record):err_record(e_record),ps_code(0){}
	bool preTreat(string &code,dev_map const &dev);	//预处理,入参为源代码串	

private:
	ssize preTreatSysApi(string const& name,ssize pos,size_t &line);	//预处理指定的库函数,返回剩余待处理部分的起始位置

	ssize leapWhite(ssize pos,size_t &line);		//前向吃掉空白,并累计行号
	ssize rleapWhite(ssize pos);		//反向吃掉空白
	 
	string getAlphaStr(ssize pos);		//前向抽取一个字母串
	string rgetAlphaStr(ssize pos);		//反向抽取一个字母串

	bool isNumber_(char c);		//判断是否数码或下划线
	bool isTypeKey(string const& str);		//判断是否类型关键字

	ssize match_left_bracket(string const& name,ssize pos,size_t const line);		//匹配左括号

	ssize preTreatDevName(string const& name,ssize pos,size_t &line,string &DevName,bool &leap);		//预处理设备名
	bool isDev(string const& DevName);		//查找是否设备
	size_t getDevCode(string const& DevName);	//获取设备编码

	ssize preTreatAddrType(string const& name,ssize pos,size_t &line,string const& DevName,string &AddrType,bool &leap);		//预处理设备地址类型
	bool isAddrType(string const& DevName,string const& AddrType);		//查找是否地址类型
	size_t getAddrTypeCode(string const& DevName,string const& AddrType);		//获取地址类型编码

	ssize preTreatAddr(string const& name,ssize pos,size_t &line,bool &leap,bool &colon);		//预处理设备地址
	ssize getColon(ssize pbegin,ssize pend);		//获取独立：的位置

	bool isBitAddr(string const& DevName,string const& AddrType);	//查询是否位地址

private:
	string *ps_code;		//源代码
	dev_map const *pdev;	//设备信息
	ErrorRecord	&err_record;		//预处理错误记录
};