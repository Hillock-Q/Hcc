#include "CPretreatment.h"
#include <algorithm>
#include <stack>
#include <iostream>
#include "CHillock.h"
using std::stack;

bool Pretreatment::preTreat(string &code,dev_map const &dev)
{
	//重置分析源代码指针
	ps_code=&code;

	//重置设备指针
	pdev=&dev;

	//首先清空错误记录
	err_record.clear();

	//初始化当前行号
	size_t line=1;

	//初始化当前处理字符位置
	ssize pos=0;

	//一趟扫描完成预处理
	while(pos<ps_code->size())
	{
		//累计行号
		if('\n'==(*ps_code)[pos])
		{
			++line;
			++pos;
			continue;
		}	

		//处理注释
		if('/'==(*ps_code)[pos])
		{
			//到达末尾,跳出循环
			if(++pos>=ps_code->size())
				break;

			if('/'==(*ps_code)[pos])
			{	
				//去单行注释
				do
				{
					//到达末尾,跳出循环
					if(++pos>=ps_code->size())
						break;					
				}while('\n'!=(*ps_code)[pos]);

				//到达末尾,跳出循环
				if(pos>=ps_code->size())
					break;

				++line;
				++pos;
				continue;
			}
			else if('*'==(*ps_code)[pos])
			{
				//去多行注释
				while(++pos<ps_code->size())
				{
					//略去多个非'*'号
					while('*'!=(*ps_code)[pos])
					{
						if('\n'==(*ps_code)[pos])
							++line;		

						//到达末尾,跳出循环
						if(++pos>=ps_code->size())
							break;		
					}

					//到达末尾,跳出循环
					if(pos>=ps_code->size())
						break;

					//略去多个'*'号
					do
					{
						//到达末尾,跳出循环
						if(++pos>=ps_code->size())
							break;
					}while('*'==(*ps_code)[pos]);

					//到达末尾,跳出循环
					if(pos>=ps_code->size())
						break;

					//找到匹配的结尾
					if('/'==(*ps_code)[pos])
					{
						++pos;
						break;
					}
				}
				continue;
			}

			continue;
		}

		//处理关键字/标识符
		if(isalpha((*ps_code)[pos]) || '_'==(*ps_code)[pos])
		{
			string lexeme;
			do
			{
				lexeme.push_back((*ps_code)[pos]);
				++pos;
			}while( pos<ps_code->size() && ( isalnum((*ps_code)[pos]) || '_'==(*ps_code)[pos] ) );

			if("Get"==lexeme)
			{
				//预处理Get
				pos=preTreatSysApi("Get",pos,line);
			}
			else if("Set"==lexeme)
			{
				//预处理Set
				pos=preTreatSysApi("Set",pos,line);
			}			
			else if("GetBlock"==lexeme)
			{
				//预处理GetBlock
				pos=preTreatSysApi("GetBlock",pos,line);
			}
			else if("SetBlock"==lexeme)
			{
				//预处理SetBlock
				pos=preTreatSysApi("SetBlock",pos,line);
			}
			else if("Out"==lexeme)
			{
				//预处理Out
				pos=preTreatSysApi("Out",pos,line);
			}
			else if("In"==lexeme)
			{
				//预处理In
				pos=preTreatSysApi("In",pos,line);
			}

			if(pos<ps_code->size())
				continue;
			
			break;
		}

		//忽略其它符号
		++pos;
	}

	//std::cout<<(*ps_code)<<std::endl;

	//返回是否通过
	return err_record.empty();
}
Pretreatment::ssize Pretreatment::preTreatSysApi(string const& name,ssize pos,size_t &line)
{
	//若只有一个函数名
	if(string::npos==pos)
	{
		//产生预编译错误
		string str="库函数"+name+"调用错误。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		return string::npos;
	}

	//忽略声明
	if(name.size()<pos && isTypeKey(rgetAlphaStr(rleapWhite(pos-(name.size()+1)))))
	{
		return pos;
	}

	//处理函数调用

	//记录库函数名末端位置
	ssize name_end=pos;

	//跳过空白
	pos=leapWhite(pos,line);

	//匹配左括号
	pos=match_left_bracket(name,pos,line);

	//跳过空白
	pos=leapWhite(pos,line);

	bool leap;
	string DevName,AddrType;

	//处理设备名及其后的，
	pos=preTreatDevName(name,pos,line,DevName,leap);

	//如果遇到；
	if(leap || name=="Out" || name=="In")
		return pos;

	//跳过空白
	pos=leapWhite(pos,line);

	//处理地址类型名及其后的，
	pos=preTreatAddrType(name,pos,line,DevName,AddrType,leap);

	//如果遇到；
	if(leap)
		return pos;

	//跳过空白
	pos=leapWhite(pos,line);

	bool colon=false;

	//处理地址及其后的，
	pos=preTreatAddr(name,pos,line,leap,colon);

	//如果遇到；
	if(leap)
		return pos;

	//为库函数Get定义
	string type_name;

	//如果是库函数Get
	if("Get"==name && string::npos!=pos)
	{
		//跳过空白
		ssize tpos=leapWhite(pos,line);		

		//获取指定类型名
		type_name=getAlphaStr(tpos);

		//如果是合法类型名
		if("void"!=type_name && isTypeKey(type_name))
		{
			//之前的,替换为空格
			(*ps_code)[pos-1]=' ';

			//指定类型名替换为空格
			for(size_t i=0;i<type_name.size();++i)
				(*ps_code)[tpos+i]=' ';

			//为库函数Get加上"_type"后缀
			ps_code->insert(name_end,string("_")+type_name);

			//重定位库函数名末端位置
			name_end+=type_name.size()+1;

			//重定位下一处理起始位置
			pos+=type_name.size()+1;
		}
		else
		{
			//产生预编译错误
			string str="库函数Get的第四个参数应该使用合法的类型关键字。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			return pos;
		}
	}

	//地址格式中没有出现独立意义的:
	if(!colon)
	{
		//设备名和地址类型名均合法
		if(!DevName.empty() && !AddrType.empty())
		{
			//地址类型是位地址
			if(isBitAddr(DevName,AddrType))
			{
				//为库函数名字加上"_bit"后缀
				ps_code->insert(name_end,"_bit");

				//重定位下一处理起始位置
				pos+=4;
			}
			//地址类型是字地址
			else
			{
				//为库函数名字加上"_word"后缀
				ps_code->insert(name_end,"_word");

				//重定位下一处理起始位置
				pos+=5;
			}
		}
	}
	//带offset的位地址
	else if(string::npos!=pos)
	{
		//地址类型必须是位地址
		if(!DevName.empty() && !AddrType.empty() && !isBitAddr(DevName,AddrType))
		{
			//产生预编译错误
			string str="库函数"+name+"使用的地址类型"+AddrType+"不是位地址,应该使用位地址类型。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			return pos;
		}

		//为库函数名字加上"_offset"后缀
		ps_code->insert(name_end,"_offset");

		//重定位下一处理起始位置
		pos+=7;
	}

	return pos;
}
bool Pretreatment::isBitAddr(string const& DevName,string const& AddrType)
{
	return pdev->find(DevName)->second.second.find(AddrType)->second.second;
}
Pretreatment::ssize Pretreatment::leapWhite(ssize pos,size_t &line)
{
	if(pos==string::npos)
		return pos;

	while( pos<ps_code->size() && ((*ps_code)[pos]==' ' || (*ps_code)[pos]=='	' || ((*ps_code)[pos]=='\n' && ++line)) )
		++pos;

	if(pos<ps_code->size())
		return pos;

	return string::npos;
}
Pretreatment::ssize Pretreatment::rleapWhite(ssize pos)
{
	if(pos==string::npos)
		return pos;

	while( 0<pos && ((*ps_code)[pos]==' ' || (*ps_code)[pos]=='	' || (*ps_code)[pos]=='\n') )
		--pos;

	if( 0==pos )
	{
		if((*ps_code)[0]==' ' || (*ps_code)[0]=='	' || (*ps_code)[0]=='\n')
			return string::npos;

		return 0;
	}
	else
	{
		return pos;
	}
}
string Pretreatment::getAlphaStr(ssize pos)
{
	if(pos==string::npos)
		return "";

	string str;

	while( pos<ps_code->size() && isalpha((*ps_code)[pos]) )
		str.push_back((*ps_code)[pos++]);

	//要求是独立串
	if(pos<ps_code->size() && isNumber_((*ps_code)[pos]))
		return "";

	return str;
}
string Pretreatment::rgetAlphaStr(ssize pos)
{
	if(pos==string::npos)
		return "";

	string str;

	while( 0<pos && isalpha((*ps_code)[pos]) )
		str.push_back((*ps_code)[pos--]);

	if(0==pos)
	{
		if(isalpha((*ps_code)[0]))
		{
			str.push_back((*ps_code)[0]);
		}
		else
		{
			//要求是独立串
			if('_'==(*ps_code)[0])
				return "";
		}
	}
	//0<pos
	else
	{
		//要求是独立串
		if(isNumber_((*ps_code)[pos]))
			return "";
	}

	//逆序操作
	reverse(str.begin(),str.end());

	return str;
}
bool Pretreatment::isNumber_(char c)
{
	return ('_'==c || isdigit(c));
}
bool Pretreatment::isTypeKey(string const& str)
{
	if("void"==str)
		return true;

	if("bool"==str)
		return true;

	if("char"==str)
		return true;

	if("short"==str)
		return true;

	if("int"==str)
		return true;

	if("float"==str)
		return true;

	if("double"==str)
		return true;

	return false;
}
Pretreatment::ssize Pretreatment::match_left_bracket(string const& name,ssize pos,size_t const line)
{
	if(pos==string::npos)
		return pos;

	//匹配
	if('('==(*ps_code)[pos])
	{
		//当前位置后移
		++pos;

		if(pos<ps_code->size())
			return pos;

		return string::npos;
	}
	else
	{
		//产生预编译错误
		string str="库函数"+name+"后面缺少函数调用操作符“ ( ”。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		return pos;
	}
}
Pretreatment::ssize Pretreatment::preTreatDevName(string const& name,ssize pos,size_t &line,string &DevName,bool &leap)
{
	leap=false;
	DevName.clear();

	if(pos==string::npos)
		return pos;

	//，和；作为DevName终结的标志
	ssize end=ps_code->find_first_of(string(",;"),pos);
		
	//首先累计行号
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//查找失败
	if(string::npos==end)
	{
		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//查找到；
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		//返回;的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//查找到，
	else
	{
		//设备名为空
		if(end==pos)
		{
			//产生预编译错误
			string str="设备名不能为空。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//返回,的下一位置
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//定位到最后一个非空白字符
		ssize last=rleapWhite(end-1);

		//如果两端不是"或者只有一个"
		if('\"'!=(*ps_code)[pos] || '\"'!=(*ps_code)[last] || pos==last)
		{
			//产生预编译错误
			string str="设备名格式非法。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//返回,的下一位置
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}
			
		//获取设备名：两个"之间的内容视作设备名
		DevName=ps_code->substr(pos+1,last-pos-1);

		//查找设备
		if(isDev(DevName))
		{
			//生成设备Code对应的字符串
			string strCode=toString(int(getDevCode(DevName)));

			//将设备名替换为其Code字符串
			ps_code->replace(pos,DevName.size()+2,strCode);

			//重新定位，
			end=end+strCode.size()-(DevName.size()+2);
		}
		else
		{
			//产生预编译错误
			string str="\""+DevName+"\": 该设备不存在。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//出错时清空设备名
			DevName.clear();
		}

		//返回,的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
}
bool Pretreatment::isDev(string const& DevName)
{
	return pdev->find(DevName) != pdev->end();
}
Pretreatment::ssize Pretreatment::getDevCode(string const& DevName)
{
	return pdev->find(DevName)->second.first;
}
Pretreatment::ssize Pretreatment::preTreatAddrType(string const& name,ssize pos,size_t &line,string const& DevName,string &AddrType,bool &leap)
{
	leap=false;
	AddrType.clear();

	if(pos==string::npos)
		return pos;

	//，和；作为AddrType终结的标志
	ssize end=ps_code->find_first_of(string(",;"),pos);

	//首先累计行号
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//查找失败
	if(string::npos==end)
	{
		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//查找到；
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		//返回,的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//查找到，
	else
	{
		//如果设备名处理出错,不处理地址类型信息
		if(DevName.empty())
		{
			//返回,的下一位置
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//地址类型为空
		if(end==pos)
		{
			//产生预编译错误
			string str="设备地址类型不能为空。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//返回,的下一位置
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//定位到最后一个非空白字符
		ssize last=rleapWhite(end-1);

		//获取地址类型名
		AddrType=ps_code->substr(pos,last-pos+1);

		//查找地址类型
		if(isAddrType(DevName,AddrType))
		{
			//生成地址类型Code对应的字符串
			string strCode=toString(int(getAddrTypeCode(DevName,AddrType)));

			//将地址类型名替换为其Code字符串
			ps_code->replace(pos,AddrType.size(),strCode);

			//重新定位，
			end=end+strCode.size()-AddrType.size();
		}
		else
		{
			//产生预编译错误
			string str="\""+DevName+"\"不存在\""+AddrType+"\"地址类型。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//出错时清空地址类型名
			AddrType.clear();
		}

		//返回,的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
}
bool Pretreatment::isAddrType(string const& DevName,string const& AddrType)
{
	dev_map::const_iterator citor=pdev->find(DevName);

	if(citor==pdev->end())
		return false;

	return citor->second.second.find(AddrType) != citor->second.second.end();
}
Pretreatment::ssize Pretreatment::getAddrTypeCode(string const& DevName,string const& AddrType)
{
	return pdev->find(DevName)->second.second.find(AddrType)->second.first;
}
Pretreatment::ssize Pretreatment::preTreatAddr(string const& name,ssize pos,size_t &line,bool &leap,bool &colon)
{
	leap=false;
	colon=false;

	if(pos==string::npos)
		return pos;

	//，和；作为Addr终结的标志
	ssize end=ps_code->find_first_of(string(",;"),pos);

	//首先累计行号
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//查找失败
	if(string::npos==end)
	{
		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//查找到；
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//产生预编译错误
		string str="库函数"+name+"缺少调用参数。";

		//加入错误记录
		err_record.insert(make_pair(line,str));

		//返回,的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//查找到，
	else
	{
		//地址为空
		if(end==pos)
		{
			//产生预编译错误
			string str="设备地址不能为空。";

			//加入错误记录
			err_record.insert(make_pair(line,str));

			//返回,的下一位置
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//获取独立:的位置
		ssize colon_pos=getColon(pos,end);

		//如果?:不匹配
		if(string::npos==colon_pos)
		{
			//产生预编译错误
			string str="条件表达式?和:不匹配。";

			//加入错误记录
			err_record.insert(make_pair(line,str));
		}
		//?:匹配且不存在独立:
		else if(colon_pos==end)
		{
			//no-op
		}
		//处理独立:
		else
		{
			colon=true;

			//定位到最后一个非空白字符
			ssize last=rleapWhite(end-1);

			//如果缺少addr或offset
			if(pos==colon_pos || last==colon_pos)
			{
				//产生预编译错误
				string str="设备地址格式非法。";

				//加入错误记录
				err_record.insert(make_pair(line,str));
			}
			else
			{
				//将:替换成,
				(*ps_code)[colon_pos]=',';

				size_t templine=0;

				//获取offset表达式的开始位置
				ssize offset=leapWhite(colon_pos+1,templine);

				//如果offset表达式有且只有一个十六进制字符
				if(offset==last && isxdigit((*ps_code)[offset]))
				{
					//在offset表达式之前插入0x
					ps_code->insert(offset,"0x");

					//重新定位，
					end+=2;
				}
			}
		}

		//返回,的下一位置
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
}
Pretreatment::ssize Pretreatment::getColon(ssize pbegin,ssize pend)
{
	//初始化为末端位置
	ssize psave(pend);

	//匹配栈
	stack<char> match_stack;

	size_t cnt=0;
	while(pbegin!=pend)
	{
		if('?'==(*ps_code)[pbegin])
		{
			match_stack.push((*ps_code)[pbegin++]);
			continue;
		}

		if(':'==(*ps_code)[pbegin])
		{
			if(!match_stack.empty())
				match_stack.pop();
			else
				++cnt,psave=pbegin;
		}

		++pbegin;
	}

	//如果?:对匹配或出现单个独立:
	if(match_stack.empty() && cnt<2)
		return psave;
	else
		return string::npos;
}