#include "CPretreatment.h"
#include <algorithm>
#include <stack>
#include <iostream>
#include "CHillock.h"
using std::stack;

bool Pretreatment::preTreat(string &code,dev_map const &dev)
{
	//���÷���Դ����ָ��
	ps_code=&code;

	//�����豸ָ��
	pdev=&dev;

	//������մ����¼
	err_record.clear();

	//��ʼ����ǰ�к�
	size_t line=1;

	//��ʼ����ǰ�����ַ�λ��
	ssize pos=0;

	//һ��ɨ�����Ԥ����
	while(pos<ps_code->size())
	{
		//�ۼ��к�
		if('\n'==(*ps_code)[pos])
		{
			++line;
			++pos;
			continue;
		}	

		//����ע��
		if('/'==(*ps_code)[pos])
		{
			//����ĩβ,����ѭ��
			if(++pos>=ps_code->size())
				break;

			if('/'==(*ps_code)[pos])
			{	
				//ȥ����ע��
				do
				{
					//����ĩβ,����ѭ��
					if(++pos>=ps_code->size())
						break;					
				}while('\n'!=(*ps_code)[pos]);

				//����ĩβ,����ѭ��
				if(pos>=ps_code->size())
					break;

				++line;
				++pos;
				continue;
			}
			else if('*'==(*ps_code)[pos])
			{
				//ȥ����ע��
				while(++pos<ps_code->size())
				{
					//��ȥ�����'*'��
					while('*'!=(*ps_code)[pos])
					{
						if('\n'==(*ps_code)[pos])
							++line;		

						//����ĩβ,����ѭ��
						if(++pos>=ps_code->size())
							break;		
					}

					//����ĩβ,����ѭ��
					if(pos>=ps_code->size())
						break;

					//��ȥ���'*'��
					do
					{
						//����ĩβ,����ѭ��
						if(++pos>=ps_code->size())
							break;
					}while('*'==(*ps_code)[pos]);

					//����ĩβ,����ѭ��
					if(pos>=ps_code->size())
						break;

					//�ҵ�ƥ��Ľ�β
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

		//����ؼ���/��ʶ��
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
				//Ԥ����Get
				pos=preTreatSysApi("Get",pos,line);
			}
			else if("Set"==lexeme)
			{
				//Ԥ����Set
				pos=preTreatSysApi("Set",pos,line);
			}			
			else if("GetBlock"==lexeme)
			{
				//Ԥ����GetBlock
				pos=preTreatSysApi("GetBlock",pos,line);
			}
			else if("SetBlock"==lexeme)
			{
				//Ԥ����SetBlock
				pos=preTreatSysApi("SetBlock",pos,line);
			}
			else if("Out"==lexeme)
			{
				//Ԥ����Out
				pos=preTreatSysApi("Out",pos,line);
			}
			else if("In"==lexeme)
			{
				//Ԥ����In
				pos=preTreatSysApi("In",pos,line);
			}

			if(pos<ps_code->size())
				continue;
			
			break;
		}

		//������������
		++pos;
	}

	//std::cout<<(*ps_code)<<std::endl;

	//�����Ƿ�ͨ��
	return err_record.empty();
}
Pretreatment::ssize Pretreatment::preTreatSysApi(string const& name,ssize pos,size_t &line)
{
	//��ֻ��һ��������
	if(string::npos==pos)
	{
		//����Ԥ�������
		string str="�⺯��"+name+"���ô���";

		//��������¼
		err_record.insert(make_pair(line,str));

		return string::npos;
	}

	//��������
	if(name.size()<pos && isTypeKey(rgetAlphaStr(rleapWhite(pos-(name.size()+1)))))
	{
		return pos;
	}

	//����������

	//��¼�⺯����ĩ��λ��
	ssize name_end=pos;

	//�����հ�
	pos=leapWhite(pos,line);

	//ƥ��������
	pos=match_left_bracket(name,pos,line);

	//�����հ�
	pos=leapWhite(pos,line);

	bool leap;
	string DevName,AddrType;

	//�����豸�������ģ�
	pos=preTreatDevName(name,pos,line,DevName,leap);

	//���������
	if(leap || name=="Out" || name=="In")
		return pos;

	//�����հ�
	pos=leapWhite(pos,line);

	//�����ַ�����������ģ�
	pos=preTreatAddrType(name,pos,line,DevName,AddrType,leap);

	//���������
	if(leap)
		return pos;

	//�����հ�
	pos=leapWhite(pos,line);

	bool colon=false;

	//�����ַ�����ģ�
	pos=preTreatAddr(name,pos,line,leap,colon);

	//���������
	if(leap)
		return pos;

	//Ϊ�⺯��Get����
	string type_name;

	//����ǿ⺯��Get
	if("Get"==name && string::npos!=pos)
	{
		//�����հ�
		ssize tpos=leapWhite(pos,line);		

		//��ȡָ��������
		type_name=getAlphaStr(tpos);

		//����ǺϷ�������
		if("void"!=type_name && isTypeKey(type_name))
		{
			//֮ǰ��,�滻Ϊ�ո�
			(*ps_code)[pos-1]=' ';

			//ָ���������滻Ϊ�ո�
			for(size_t i=0;i<type_name.size();++i)
				(*ps_code)[tpos+i]=' ';

			//Ϊ�⺯��Get����"_type"��׺
			ps_code->insert(name_end,string("_")+type_name);

			//�ض�λ�⺯����ĩ��λ��
			name_end+=type_name.size()+1;

			//�ض�λ��һ������ʼλ��
			pos+=type_name.size()+1;
		}
		else
		{
			//����Ԥ�������
			string str="�⺯��Get�ĵ��ĸ�����Ӧ��ʹ�úϷ������͹ؼ��֡�";

			//��������¼
			err_record.insert(make_pair(line,str));

			return pos;
		}
	}

	//��ַ��ʽ��û�г��ֶ��������:
	if(!colon)
	{
		//�豸���͵�ַ���������Ϸ�
		if(!DevName.empty() && !AddrType.empty())
		{
			//��ַ������λ��ַ
			if(isBitAddr(DevName,AddrType))
			{
				//Ϊ�⺯�����ּ���"_bit"��׺
				ps_code->insert(name_end,"_bit");

				//�ض�λ��һ������ʼλ��
				pos+=4;
			}
			//��ַ�������ֵ�ַ
			else
			{
				//Ϊ�⺯�����ּ���"_word"��׺
				ps_code->insert(name_end,"_word");

				//�ض�λ��һ������ʼλ��
				pos+=5;
			}
		}
	}
	//��offset��λ��ַ
	else if(string::npos!=pos)
	{
		//��ַ���ͱ�����λ��ַ
		if(!DevName.empty() && !AddrType.empty() && !isBitAddr(DevName,AddrType))
		{
			//����Ԥ�������
			string str="�⺯��"+name+"ʹ�õĵ�ַ����"+AddrType+"����λ��ַ,Ӧ��ʹ��λ��ַ���͡�";

			//��������¼
			err_record.insert(make_pair(line,str));

			return pos;
		}

		//Ϊ�⺯�����ּ���"_offset"��׺
		ps_code->insert(name_end,"_offset");

		//�ض�λ��һ������ʼλ��
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

	//Ҫ���Ƕ�����
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
			//Ҫ���Ƕ�����
			if('_'==(*ps_code)[0])
				return "";
		}
	}
	//0<pos
	else
	{
		//Ҫ���Ƕ�����
		if(isNumber_((*ps_code)[pos]))
			return "";
	}

	//�������
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

	//ƥ��
	if('('==(*ps_code)[pos])
	{
		//��ǰλ�ú���
		++pos;

		if(pos<ps_code->size())
			return pos;

		return string::npos;
	}
	else
	{
		//����Ԥ�������
		string str="�⺯��"+name+"����ȱ�ٺ������ò������� ( ����";

		//��������¼
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

	//���ͣ���ΪDevName�ս�ı�־
	ssize end=ps_code->find_first_of(string(",;"),pos);
		
	//�����ۼ��к�
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//����ʧ��
	if(string::npos==end)
	{
		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//���ҵ���
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		//����;����һλ��
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//���ҵ���
	else
	{
		//�豸��Ϊ��
		if(end==pos)
		{
			//����Ԥ�������
			string str="�豸������Ϊ�ա�";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����,����һλ��
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//��λ�����һ���ǿհ��ַ�
		ssize last=rleapWhite(end-1);

		//������˲���"����ֻ��һ��"
		if('\"'!=(*ps_code)[pos] || '\"'!=(*ps_code)[last] || pos==last)
		{
			//����Ԥ�������
			string str="�豸����ʽ�Ƿ���";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����,����һλ��
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}
			
		//��ȡ�豸��������"֮������������豸��
		DevName=ps_code->substr(pos+1,last-pos-1);

		//�����豸
		if(isDev(DevName))
		{
			//�����豸Code��Ӧ���ַ���
			string strCode=toString(int(getDevCode(DevName)));

			//���豸���滻Ϊ��Code�ַ���
			ps_code->replace(pos,DevName.size()+2,strCode);

			//���¶�λ��
			end=end+strCode.size()-(DevName.size()+2);
		}
		else
		{
			//����Ԥ�������
			string str="\""+DevName+"\": ���豸�����ڡ�";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����ʱ����豸��
			DevName.clear();
		}

		//����,����һλ��
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

	//���ͣ���ΪAddrType�ս�ı�־
	ssize end=ps_code->find_first_of(string(",;"),pos);

	//�����ۼ��к�
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//����ʧ��
	if(string::npos==end)
	{
		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//���ҵ���
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		//����,����һλ��
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//���ҵ���
	else
	{
		//����豸���������,�������ַ������Ϣ
		if(DevName.empty())
		{
			//����,����һλ��
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//��ַ����Ϊ��
		if(end==pos)
		{
			//����Ԥ�������
			string str="�豸��ַ���Ͳ���Ϊ�ա�";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����,����һλ��
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//��λ�����һ���ǿհ��ַ�
		ssize last=rleapWhite(end-1);

		//��ȡ��ַ������
		AddrType=ps_code->substr(pos,last-pos+1);

		//���ҵ�ַ����
		if(isAddrType(DevName,AddrType))
		{
			//���ɵ�ַ����Code��Ӧ���ַ���
			string strCode=toString(int(getAddrTypeCode(DevName,AddrType)));

			//����ַ�������滻Ϊ��Code�ַ���
			ps_code->replace(pos,AddrType.size(),strCode);

			//���¶�λ��
			end=end+strCode.size()-AddrType.size();
		}
		else
		{
			//����Ԥ�������
			string str="\""+DevName+"\"������\""+AddrType+"\"��ַ���͡�";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����ʱ��յ�ַ������
			AddrType.clear();
		}

		//����,����һλ��
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

	//���ͣ���ΪAddr�ս�ı�־
	ssize end=ps_code->find_first_of(string(",;"),pos);

	//�����ۼ��к�
	{
		ssize i=pos;
		while( (i=ps_code->find('\n',i)) < end )
		{
			++i;
			++line;
		}
	}

	//����ʧ��
	if(string::npos==end)
	{
		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		return string::npos;	
	}
	//���ҵ���
	else if(';'==(*ps_code)[end])
	{
		leap=true;

		//����Ԥ�������
		string str="�⺯��"+name+"ȱ�ٵ��ò�����";

		//��������¼
		err_record.insert(make_pair(line,str));

		//����,����һλ��
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
	//���ҵ���
	else
	{
		//��ַΪ��
		if(end==pos)
		{
			//����Ԥ�������
			string str="�豸��ַ����Ϊ�ա�";

			//��������¼
			err_record.insert(make_pair(line,str));

			//����,����һλ��
			if(end+1 < ps_code->size())
				return end+1;

			return string::npos;
		}

		//��ȡ����:��λ��
		ssize colon_pos=getColon(pos,end);

		//���?:��ƥ��
		if(string::npos==colon_pos)
		{
			//����Ԥ�������
			string str="�������ʽ?��:��ƥ�䡣";

			//��������¼
			err_record.insert(make_pair(line,str));
		}
		//?:ƥ���Ҳ����ڶ���:
		else if(colon_pos==end)
		{
			//no-op
		}
		//�������:
		else
		{
			colon=true;

			//��λ�����һ���ǿհ��ַ�
			ssize last=rleapWhite(end-1);

			//���ȱ��addr��offset
			if(pos==colon_pos || last==colon_pos)
			{
				//����Ԥ�������
				string str="�豸��ַ��ʽ�Ƿ���";

				//��������¼
				err_record.insert(make_pair(line,str));
			}
			else
			{
				//��:�滻��,
				(*ps_code)[colon_pos]=',';

				size_t templine=0;

				//��ȡoffset���ʽ�Ŀ�ʼλ��
				ssize offset=leapWhite(colon_pos+1,templine);

				//���offset���ʽ����ֻ��һ��ʮ�������ַ�
				if(offset==last && isxdigit((*ps_code)[offset]))
				{
					//��offset���ʽ֮ǰ����0x
					ps_code->insert(offset,"0x");

					//���¶�λ��
					end+=2;
				}
			}
		}

		//����,����һλ��
		if(end+1 < ps_code->size())
			return end+1;

		return string::npos;
	}
}
Pretreatment::ssize Pretreatment::getColon(ssize pbegin,ssize pend)
{
	//��ʼ��Ϊĩ��λ��
	ssize psave(pend);

	//ƥ��ջ
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

	//���?:��ƥ�����ֵ�������:
	if(match_stack.empty() && cnt<2)
		return psave;
	else
		return string::npos;
}