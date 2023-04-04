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
	bool preTreat(string &code,dev_map const &dev);	//Ԥ����,���ΪԴ���봮	

private:
	ssize preTreatSysApi(string const& name,ssize pos,size_t &line);	//Ԥ����ָ���Ŀ⺯��,����ʣ��������ֵ���ʼλ��

	ssize leapWhite(ssize pos,size_t &line);		//ǰ��Ե��հ�,���ۼ��к�
	ssize rleapWhite(ssize pos);		//����Ե��հ�
	 
	string getAlphaStr(ssize pos);		//ǰ���ȡһ����ĸ��
	string rgetAlphaStr(ssize pos);		//�����ȡһ����ĸ��

	bool isNumber_(char c);		//�ж��Ƿ�������»���
	bool isTypeKey(string const& str);		//�ж��Ƿ����͹ؼ���

	ssize match_left_bracket(string const& name,ssize pos,size_t const line);		//ƥ��������

	ssize preTreatDevName(string const& name,ssize pos,size_t &line,string &DevName,bool &leap);		//Ԥ�����豸��
	bool isDev(string const& DevName);		//�����Ƿ��豸
	size_t getDevCode(string const& DevName);	//��ȡ�豸����

	ssize preTreatAddrType(string const& name,ssize pos,size_t &line,string const& DevName,string &AddrType,bool &leap);		//Ԥ�����豸��ַ����
	bool isAddrType(string const& DevName,string const& AddrType);		//�����Ƿ��ַ����
	size_t getAddrTypeCode(string const& DevName,string const& AddrType);		//��ȡ��ַ���ͱ���

	ssize preTreatAddr(string const& name,ssize pos,size_t &line,bool &leap,bool &colon);		//Ԥ�����豸��ַ
	ssize getColon(ssize pbegin,ssize pend);		//��ȡ��������λ��

	bool isBitAddr(string const& DevName,string const& AddrType);	//��ѯ�Ƿ�λ��ַ

private:
	string *ps_code;		//Դ����
	dev_map const *pdev;	//�豸��Ϣ
	ErrorRecord	&err_record;		//Ԥ��������¼
};