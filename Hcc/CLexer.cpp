#include "CLexer.h"
#include "CHillock.h"
#include "CCharacter.h"
#include "CNumber.h"
#include "CReal.h"

Lexer::Lexer(ErrorRecord &e_record)
:
	peek(' '),
	line(1),
	err_record(e_record)
{
	//20个关键字作为保留字加入词法单元表
	reserve(new Word("break",Compiler::_BREAK));
	reserve(new Word("case",Compiler::_CASE));
	reserve(new Word("continue",Compiler::_CONTINUE));
	reserve(new Word("default",Compiler::_DEFAULT));
	reserve(new Word("do",Compiler::_DO));

	reserve(new Word("else",Compiler::_ELSE));
	reserve(new Word("false",Compiler::_FALSE));
	reserve(new Word("for",Compiler::_FOR));
	reserve(new Word("if",Compiler::_IF));
	reserve(new Word("return",Compiler::_RETURN));

	reserve(new Word("switch",Compiler::_SWITCH));
	reserve(new Word("true",Compiler::_TRUE));
	reserve(new Word("while",Compiler::_WHILE));
	reserve(new Word("bool",Compiler::_BOOL));
	reserve(new Word("char",Compiler::_CHAR));

	reserve(new Word("double",Compiler::_DOUBLE));
	reserve(new Word("float",Compiler::_FLOAT));
	reserve(new Word("int",Compiler::_INT));
	reserve(new Word("short",Compiler::_SHORT));
	reserve(new Word("void",Compiler::_VOID));


	//主程序入口函数名(main)作为保留字
	reserve(new Word("main",Compiler::_MAIN));

	key_words.clear();

	//生成关键字集合
	for(token_table::const_iterator citor=tokens.begin();citor!=tokens.end();++citor)
		key_words.insert(citor->first);
}
Lexer::key_word const& Lexer::getKeyWord()const
{
	return key_words;
}
Lexer::~Lexer()
{
	for(token_table::const_iterator citor=tokens.begin();citor!=tokens.end();++citor)
		delete citor->second;
}
Token *const Lexer::scanning()
{
	//read();
	while(true)
	{
		//去空白
		for( ;; read())
		{
			if(' '==peek || '	'==peek || '\r'==peek)
				continue;

			if('\n'==peek)
				++line;
			else
				break;
		}

		//处理操作符/注释/字符常量/结束标志Compiler::_END
		switch(peek)
		{
		case '.':
			read();

			//处理以'.'开头的小数
			if(Compiler::isDecDigit(peek))
			{
				string lexeme;
				lexeme.push_back('.');

				double x(0),d(10);
				do
				{
					lexeme.push_back(peek);
					x+=Compiler::digit(peek)/d;
					d*=10;
					read();
				}while(Compiler::isDecDigit(peek));

				//指数
				if('e'==peek || 'E'==peek)
				{
					//mode-exp
					lexeme.push_back(peek);

					read();
					if('+'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if('-'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//缩小
							x/=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if(Compiler::isDecDigit(peek))
					{
						//计算exp部分
						int e(0);
						do
						{
							lexeme.push_back(peek);
							e=10*e+Compiler::digit(peek);
							read();
						}while(Compiler::isDecDigit(peek));

						double d(1);

						//计算倍数
						for(int i=0;i<e;++i)
							d*=10;

						//放大
						x*=d;

						return new Real(x,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Real(x));
						//continue;
					}
					else
					{
						error("error: expect exp value, not \"",peek,"\".");
						continue;
					}
				}
				//纯小数
				else
				{
					return new Real(x,line);
					//if(vacant(lexeme))
					//	put(lexeme,new Real(x));
					//continue;
				}
			}
			else
			{
				return new Token('.',line);
				//if(vacant("."))
				//	put(".",new Token('.'));
				//continue;
			}			

		case '<':
			read();
			if('<'==peek)
			{
				read();
				if('='==peek)
				{					
					read();
					return new Word("<<=",Compiler::_LSHT_ASS,line);///
					//if(vacant("<<="))
					//	put("<<=",new Word("<<=",Compiler::_LSHT_ASS));
					//continue;
				}
				else
				{
					return new Word("<<",Compiler::_LSHT,line);///
					//if(vacant("<<"))
					//	put("<<",new Word("<<",Compiler::_LSHT));
					//continue;
				}
			}
			else if('='==peek)
			{
				read();
				return new Word("<=",Compiler::_LE,line);
				//if(vacant("<="))
				//	put("<=",new Word("<=",Compiler::_LE));
				//continue;
			}
			else
			{
				return new Token('<',line);
				//if(vacant("<"))
				//	put("<",new Token('<'));
				//continue;
			}

		case '>':
			read();
			if('>'==peek)
			{
				read();
				if('='==peek)
				{					
					read();
					return new Word(">>=",Compiler::_RSHT_ASS,line);
					//if(vacant(">>="))
					//	put(">>=",new Word(">>=",Compiler::_RSHT_ASS));
					//continue;
				}
				else
				{
					return new Word(">>",Compiler::_RSHT,line);
					//if(vacant(">>"))
					//	put(">>",new Word(">>",Compiler::_RSHT));
					//continue;
				}
			}
			else if('='==peek)
			{
				read();
				return new Word(">=",Compiler::_GE,line);
				//if(vacant(">="))
				//	put(">=",new Word(">=",Compiler::_GE));
				//continue;
			}
			else
			{
				return new Token('>',line);
				//if(vacant(">"))
				//	put(">",new Token('>'));
				//continue;
			}

		case '=':
			read();
			if('='==peek)
			{
				read();
				return new Word("==",Compiler::_EQ,line);
				//if(vacant("=="))
				//	put("==",new Word("==",Compiler::_EQ));
				//continue;
			}
			else
			{
				return new Token('=',line);
				//if(vacant("="))
				//	put("=",new Token('='));
				//continue;
			}

		case '!':
			read();
			if('='==peek)
			{
				read();
				return new Word("!=",Compiler::_NE,line);
				//if(vacant("!="))
				//	put("!=",new Word("!=",Compiler::_NE));
				//continue;
			}
			else
			{
				return new Token('!',line);
				//if(vacant("!"))
				//	put("!",new Token('!'));
				//continue;
			}

		case '*':
			read();
			if('='==peek)
			{
				read();
				return new Word("*=",Compiler::_MUL_ASS,line);
				//if(vacant("*="))
				//	put("*=",new Word("*=",Compiler::_MUL_ASS));
				//continue;
			}
			else
			{
				return new Token('*',line);
				//if(vacant("*"))
				//	put("*",new Token('*'));
				//continue;
			}

		case '%':
			read();
			if('='==peek)
			{
				read();
				return new Word("%=",Compiler::_MOD_ASS,line);
				//if(vacant("%="))
				//	put("%=",new Word("%=",Compiler::_MOD_ASS));
				//continue;
			}
			else
			{
				return new Token('%',line);
				//if(vacant("%"))
				//	put("%",new Token('%'));
				//continue;
			}

		case '^':
			read();
			if('='==peek)
			{
				read();
				return new Word("^=",Compiler::_BIT_XOR_ASS,line);
				//if(vacant("^="))
				//	put("^=",new Word("^=",Compiler::_BIT_XOR_ASS));
				//continue;
			}
			else
			{
				return new Token('^',line);
				//if(vacant("^"))
				//	put("^",new Token('^'));
				//continue;
			}

		case '&':
			read();
			if('&'==peek)
			{
				read();
				return new Word("&&",Compiler::_AND,line);
				//if(vacant("&&"))
				//	put("&&",new Word("&&",Compiler::_AND));
				//continue;
			}
			else if('='==peek)
			{
				read();
				return new Word("&=",Compiler::_BIT_AND_ASS,line);
				//if(vacant("&="))
				//	put("&=",new Word("&=",Compiler::_BIT_AND_ASS));
				//continue;
			}
			else
			{
				return new Token('&',line);
				//if(vacant("&"))
				//	put("&",new Token('&'));
				//continue;
			}

		case '|':
			read();
			if('|'==peek)
			{
				read();
				return new Word("||",Compiler::_OR,line);
				//if(vacant("||"))
				//	put("||",new Word("||",Compiler::_OR));
				//continue;
			}
			else if('='==peek)
			{
				read();
				return new Word("|=",Compiler::_BIT_OR_ASS,line);
				//if(vacant("|="))
				//	put("|=",new Word("|=",Compiler::_BIT_OR_ASS));
				//continue;
			}
			else
			{
				return new Token('|',line);
				//if(vacant("|"))
				//	put("|",new Token('|'));
				//continue;
			}

		case '+':
			read();
			if('+'==peek)
			{
				read();
				return new Word("++",Compiler::_PLUS_PLUS,line);
				//if(vacant("++"))
				//	put("++",new Word("++",Compiler::_PLUS_PLUS));
				//continue;
			}
			else if('='==peek)
			{
				read();
				return new Word("+=",Compiler::_ADD_ASS,line);
				//if(vacant("+="))
				//	put("+=",new Word("+=",Compiler::_ADD_ASS));
				//continue;
			}
			else
			{
				return new Token('+',line);
				//if(vacant("+"))
				//	put("+",new Token('+'));
				//continue;
			}

		case '-':
			read();
			if('-'==peek)
			{
				read();
				return new Word("--",Compiler::_MINUS_MINUS,line);
				//if(vacant("--"))
				//	put("--",new Word("--",Compiler::_MINUS_MINUS));
				//continue;
			}
			else if('='==peek)
			{
				read();
				return new Word("-=",Compiler::_SUB_ASS,line);
				//if(vacant("-="))
				//	put("-=",new Word("-=",Compiler::_SUB_ASS));
				//continue;
			}
			else
			{
				return new Token('-',line);
				//if(vacant("-"))
				//	put("-",new Token('-'));
				//continue;
			}

		case '/':
			read();
			if('='==peek)
			{
				read();
				return new Word("/=",Compiler::_DIV_ASS,line);
				//if(vacant("/="))
				//	put("/=",new Word("/=",Compiler::_DIV_ASS));
				//continue;
			}
			else if('/'==peek)
			{	
				//去单行注释
				do
				{
					read();
					if(Compiler::_END==peek)return new Token(Compiler::_END,(line ? line-1 : line));	//避免任何可能的死循环
				}while('\n'!=peek);
				++line;
				read();
				continue;
			}
			else if('*'==peek)
			{
				//去多行注释
				while(true)
				{
					//略去多个非'*'号
					do
					{
						if('\n'==peek)
							++line;		

						read();

						if(Compiler::_END==peek)return new Token(Compiler::_END,(line ? line-1 : line));	//避免任何可能的死循环
					}while('*'!=peek);
					
					//略去多个'*'号
					do
					{
						read();
					}while('*'==peek);

					//找到匹配的结尾
					if('/'==peek)
						break;
				}
				read();
				continue;
			}
			else
			{
				return new Token('/',line);
				//if(vacant("/"))
				//	put("/",new Token('/'));
				//continue;
			}

		//处理字符字面值
		case '\'':
			read();

			//转义序列
			if('\\'==peek)
			{
				read();

				//定义的转义序列
				switch(peek)
				{
				case 'n':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x0a,line);
						//if(vacant("\'n\'"))
						//	put("\'n\'",new Character(0x0a));
						//continue;
					}
					else
					{
						error("error: \"\'n\" expect suited \"\'\".");
						continue;
					}

				case 't':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x09,line);
						//if(vacant("\'t\'"))
						//	put("\'t\'",new Character(0x09));
						//continue;
					}
					else
					{
						error("error: \"\'t\" expect suited \"\'\".");
						continue;
					}

				case 'v':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x0b,line);
						//if(vacant("\'v\'"))
						//	put("\'v\'",new Character(0x0b));
						//continue;
					}
					else
					{
						error("error: \"\'v\" expect suited \"\'\".");
						continue;
					}

				case 'b':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x08,line);
						//if(vacant("\'b\'"))
						//	put("\'b\'",new Character(0x08));
						//continue;
					}
					else
					{
						error("error: \"\'b\" expect suited \"\'\".");
						continue;
					}

				case 'r':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x0d,line);
						//if(vacant("\'r\'"))
						//	put("\'r\'",new Character(0x0d));
						//continue;
					}
					else
					{
						error("error: \"\'r\" expect suited \"\'\".");
						continue;
					}

				case 'f':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x0c,line);
						//if(vacant("\'f\'"))
						//	put("\'f\'",new Character(0x0c));
						//continue;
					}
					else
					{
						error("error: \"\'f\" expect suited \"\'\".");
						continue;
					}

				case 'a':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x07,line);
						//if(vacant("\'a\'"))
						//	put("\'a\'",new Character(0x07));
						//continue;
					}
					else
					{
						error("error: \"\'a\" expect suited \"\'\".");
						continue;
					}

				case '\\':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x5c,line);
						//if(vacant("\'\\\'"))
						//	put("\'\\\'",new Character(0x5c));
						//continue;
					}
					else
					{
						error("error: \"\'\\\" expect suited \"\'\".");
						continue;
					}

				case '?':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x3f,line);
						//if(vacant("\'?\'"))
						//	put("\'?\'",new Character(0x3f));
						//continue;
					}
					else
					{
						error("error: \"\'?\" expect suited \"\'\".");
						continue;
					}

				case '\'':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x2e,line);
						//if(vacant("\'\'\'"))
						//	put("\'\'\'",new Character(0x2e));
						//continue;
					}
					else
					{
						error("error: \"\'\'\" expect suited \"\'\".");
						continue;
					}

				case '\"':
					read();
					if('\''==peek)
					{
						read();
						return new Character(0x22,line);
						//if(vacant("\'\"\'"))
						//	put("\'\"\'",new Character(0x22));
						//continue;
					}
					else
					{
						error("error: \"\'\"\" expect suited \"\'\".");
						continue;
					}
				}

				//通用转义序列--hex
				if('x'==peek || 'X'==peek)
				{
					string lexeme("\'\\"+peek);
					read();
					if(Compiler::isHexDigit(peek))
					{
						int v(0);
						do
						{
							lexeme.push_back(peek);
							v=16*v+Compiler::digit(peek,Compiler::HEX);
							read();
						}while(Compiler::isHexDigit(peek));

						if('\''==peek)
						{
							lexeme.push_back(peek);
							read();
							return new Character(v,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Character(v));
							//continue;
						}
						else
						{
							error(string("error: \"")+lexeme+"\" expect suited \"\'\".");
							continue;
						}	
					}
					else
					{
						error(string("error: \"")+lexeme+"\" expect hex digit.");
						continue;
					}
				}
				//通用转义序列--oct
				else if(Compiler::isOctDigit(peek))
				{
					string lexeme("\'\\");
					int v(0);
					do
					{
						lexeme.push_back(peek);
						v=8*v+Compiler::digit(peek,Compiler::OCT);
						read();
					}while(Compiler::isOctDigit(peek));

					if('\''==peek)
					{
						lexeme.push_back(peek);
						read();
						return new Character(v,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Character(v));
						//continue;
					}
					else
					{
						error(string("error: \"")+lexeme+"\" expect suited \"\'\".");
						continue;
					}				
				}
				else
				{
					error("error: \"\'\\\" expect escape sequences or \"x\"/\"X\" or oct digit.");
					continue;
				}

			}
			//可打印字符
			else if(Compiler::isPrint(peek))
			{
				char save=peek;

				read();
				if('\''==peek)
				{
					read();
					string s("\'");
					s.push_back(save);
					s.push_back('\'');

					return new Character(save,line);
					//if(vacant(s))
					//	put(s,new Character(save));
					//continue;
				}
				else
				{
					error("error: \"\'\" expect suited \"\'\".");
					continue;
				}
			}
			//出错
			else
			{
				error("error: \"\'\" expect \"\\\" or other printable character.");
				continue;
			}

		//结束标记
		case Compiler::_END:
			return new Token(Compiler::_END,(line ? line-1 : line));
		}


		//处理数字
		if(Compiler::isDecDigit(peek))
		{
			//[1~9]
			if('0'!=peek)
			{
				string lexeme;
				int v(0);
				do
				{
					lexeme.push_back(peek);
					v=10*v+Compiler::digit(peek);
					read();
				}while(Compiler::isDecDigit(peek));

				//浮点
				if('.'==peek)
				{
					lexeme.push_back(peek);
					double x(v),d(10);

					read();					
					while(Compiler::isDecDigit(peek))
					{
						lexeme.push_back(peek);
						x+=Compiler::digit(peek)/d;
						d*=10;
						read();
					}
				
					//指数
					if('e'==peek || 'E'==peek)
					{
						//mode-exp
						lexeme.push_back(peek);

						read();
						if('+'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if('-'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//缩小
								x/=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					//纯小数
					else
					{
						return new Real(x,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Real(x));
						//continue;
					}
				}
				//指数
				else if('e'==peek || 'E'==peek)
				{
					//mode-exp
					lexeme.push_back(peek);

					read();
					if('+'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(v),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if('-'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(v),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//缩小
							x/=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if(Compiler::isDecDigit(peek))
					{
						//计算exp部分
						int e(0);
						do
						{
							lexeme.push_back(peek);
							e=10*e+Compiler::digit(peek);
							read();
						}while(Compiler::isDecDigit(peek));

						double x(v),d(1);

						//计算倍数
						for(int i=0;i<e;++i)
							d*=10;

						//放大
						x*=d;

						return new Real(x,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Real(x));
						//continue;
					}
					else
					{
						error("error: expect exp value, not \"",peek,"\".");
						continue;
					}
				}
				//dec(非0)
				else
				{
					return new Number(v,line);
					//if(vacant(lexeme))
					//	put(lexeme,new Number(v));
					//continue;
				}
			}
			//[0]
			else
			{
				string lexeme;
				lexeme.push_back(peek);

				read();
				
				//浮点
				if('.'==peek)
				{
					lexeme.push_back(peek);
					double x(0),d(10);

					read();					
					while(Compiler::isDecDigit(peek))
					{
						lexeme.push_back(peek);
						x+=Compiler::digit(peek)/d;
						d*=10;
						read();
					}

					//指数
					if('e'==peek || 'E'==peek)
					{
						//mode-exp
						lexeme.push_back(peek);

						read();
						if('+'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if('-'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//缩小
								x/=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					//纯小数
					else
					{
						return new Real(x,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Real(x));
						//continue;
					}
				}
				//指数
				else if('e'==peek || 'E'==peek)
				{
					//mode-exp
					lexeme.push_back(peek);

					read();
					if('+'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(0),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if('-'==peek)
					{
						lexeme.push_back(peek);

						read();
						if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(0),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//缩小
							x/=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					else if(Compiler::isDecDigit(peek))
					{
						//计算exp部分
						int e(0);
						do
						{
							lexeme.push_back(peek);
							e=10*e+Compiler::digit(peek);
							read();
						}while(Compiler::isDecDigit(peek));

						double x(0),d(1);

						//计算倍数
						for(int i=0;i<e;++i)
							d*=10;

						//放大
						x*=d;

						return new Real(x,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Real(x));
						//continue;
					}
					else
					{
						error("error: expect exp value, not \"",peek,"\".");
						continue;
					}
				}
				//hex
				else if('x'==peek || 'X'==peek)
				{
					lexeme.push_back(peek);

					read();
					if(Compiler::isHexDigit(peek))
					{
						int v(0);
						do
						{
							lexeme.push_back(peek);
							v=16*v+Compiler::digit(peek,Compiler::HEX);
							read();
						}while(Compiler::isHexDigit(peek));

						return new Number(v,line);
						//if(vacant(lexeme))
						//	put(lexeme,new Number(v));
						//continue;
					}
					else
					{
						error(string("error: \"")+lexeme+"\" expect hex digit.");
						continue;
					}
				}
				//dec字符
				else if('8'==peek || '9'==peek)
				{
					char c_error=peek;

					int v(0);
					do
					{
						lexeme.push_back(peek);
						v=10*v+Compiler::digit(peek);
						read();
					}while(Compiler::isDecDigit(peek));

					//浮点
					if('.'==peek)
					{
						lexeme.push_back(peek);
						double x(v),d(10);

						read();					
						while(Compiler::isDecDigit(peek))
						{
							lexeme.push_back(peek);
							x+=Compiler::digit(peek)/d;
							d*=10;
							read();
						}

						//指数
						if('e'==peek || 'E'==peek)
						{
							//mode-exp
							lexeme.push_back(peek);

							read();
							if('+'==peek)
							{
								lexeme.push_back(peek);

								read();
								if(Compiler::isDecDigit(peek))
								{
									//计算exp部分
									int e(0);
									do
									{
										lexeme.push_back(peek);
										e=10*e+Compiler::digit(peek);
										read();
									}while(Compiler::isDecDigit(peek));

									double d(1);

									//计算倍数
									for(int i=0;i<e;++i)
										d*=10;

									//放大
									x*=d;

									return new Real(x,line);
									//if(vacant(lexeme))
									//	put(lexeme,new Real(x));
									//continue;
								}
								else
								{
									error("error: expect exp value, not \"",peek,"\".");
									continue;
								}
							}
							else if('-'==peek)
							{
								lexeme.push_back(peek);

								read();
								if(Compiler::isDecDigit(peek))
								{
									//计算exp部分
									int e(0);
									do
									{
										lexeme.push_back(peek);
										e=10*e+Compiler::digit(peek);
										read();
									}while(Compiler::isDecDigit(peek));

									double d(1);

									//计算倍数
									for(int i=0;i<e;++i)
										d*=10;

									//缩小
									x/=d;

									return new Real(x,line);
									//if(vacant(lexeme))
									//	put(lexeme,new Real(x));
									//continue;
								}
								else
								{
									error("error: expect exp value, not \"",peek,"\".");
									continue;
								}
							}
							else if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						//纯小数
						else
						{
							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
					}
					//指数
					else if('e'==peek || 'E'==peek)
					{
						//mode-exp
						lexeme.push_back(peek);

						read();
						if('+'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double x(v),d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if('-'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double x(v),d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//缩小
								x/=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(v),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					//出错
					else
					{
						error("error: \"",c_error,"\" is not an oct digit.");
						continue;
					}
				}
				//oct/dec字符
				else if(Compiler::isOctDigit(peek))
				{
					bool is_oct(true);
					char c_error;
					int v_dec(0),v_oct(0);
					do
					{
						lexeme.push_back(peek);
						v_dec=10*v_dec+Compiler::digit(peek);
						if(is_oct)v_oct=8*v_oct+Compiler::digit(peek,Compiler::OCT);
						read();
						if(is_oct && ('8'==peek || '9'==peek))c_error=peek,is_oct=false;
					}while(Compiler::isDecDigit(peek));

					//浮点
					if('.'==peek)
					{
						lexeme.push_back(peek);
						double x(v_dec),d(10);

						read();					
						while(Compiler::isDecDigit(peek))
						{
							lexeme.push_back(peek);
							x+=Compiler::digit(peek)/d;
							d*=10;
							read();
						}

						//指数
						if('e'==peek || 'E'==peek)
						{
							//mode-exp
							lexeme.push_back(peek);

							read();
							if('+'==peek)
							{
								lexeme.push_back(peek);

								read();
								if(Compiler::isDecDigit(peek))
								{
									//计算exp部分
									int e(0);
									do
									{
										lexeme.push_back(peek);
										e=10*e+Compiler::digit(peek);
										read();
									}while(Compiler::isDecDigit(peek));

									double d(1);

									//计算倍数
									for(int i=0;i<e;++i)
										d*=10;

									//放大
									x*=d;

									return new Real(x,line);
									//if(vacant(lexeme))
									//	put(lexeme,new Real(x));
									//continue;
								}
								else
								{
									error("error: expect exp value, not \"",peek,"\".");
									continue;
								}
							}
							else if('-'==peek)
							{
								lexeme.push_back(peek);

								read();
								if(Compiler::isDecDigit(peek))
								{
									//计算exp部分
									int e(0);
									do
									{
										lexeme.push_back(peek);
										e=10*e+Compiler::digit(peek);
										read();
									}while(Compiler::isDecDigit(peek));

									double d(1);

									//计算倍数
									for(int i=0;i<e;++i)
										d*=10;

									//缩小
									x/=d;

									return new Real(x,line);
									//if(vacant(lexeme))
									//	put(lexeme,new Real(x));
									//continue;
								}
								else
								{
									error("error: expect exp value, not \"",peek,"\".");
									continue;
								}
							}
							else if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						//纯小数
						else
						{
							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
					}
					//指数
					else if('e'==peek || 'E'==peek)
					{
						//mode-exp
						lexeme.push_back(peek);

						read();
						if('+'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));
							
								double x(v_dec),d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//放大
								x*=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if('-'==peek)
						{
							lexeme.push_back(peek);

							read();
							if(Compiler::isDecDigit(peek))
							{
								//计算exp部分
								int e(0);
								do
								{
									lexeme.push_back(peek);
									e=10*e+Compiler::digit(peek);
									read();
								}while(Compiler::isDecDigit(peek));

								double x(v_dec),d(1);

								//计算倍数
								for(int i=0;i<e;++i)
									d*=10;

								//缩小
								x/=d;

								return new Real(x,line);
								//if(vacant(lexeme))
								//	put(lexeme,new Real(x));
								//continue;
							}
							else
							{
								error("error: expect exp value, not \"",peek,"\".");
								continue;
							}
						}
						else if(Compiler::isDecDigit(peek))
						{
							//计算exp部分
							int e(0);
							do
							{
								lexeme.push_back(peek);
								e=10*e+Compiler::digit(peek);
								read();
							}while(Compiler::isDecDigit(peek));

							double x(v_dec),d(1);

							//计算倍数
							for(int i=0;i<e;++i)
								d*=10;

							//放大
							x*=d;

							return new Real(x,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Real(x));
							//continue;
						}
						else
						{
							error("error: expect exp value, not \"",peek,"\".");
							continue;
						}
					}
					//oct/error
					else
					{
						//oct
						if(is_oct)
						{
							return new Number(v_oct,line);
							//if(vacant(lexeme))
							//	put(lexeme,new Number(v_oct));
							//continue;
						}
						else
						{
							error("error: \"",c_error,"\" is not an oct digit.");
							continue;
						}
					}
				}
				//dec(0)
				else
				{
					return new Number(0,line);
					//if(vacant(lexeme))
					//	put(lexeme,new Number(0));
					//continue;					
				}
			}
		}		


		//处理关键字/标识符
		if(Compiler::isLetter(peek) || '_'==peek)
		{
			string lexeme;
			do
			{
				lexeme.push_back(peek);
				read();
			}while(Compiler::isLetterOrDigit(peek) || '_'==peek);

			token_table::const_iterator citor=tokens.find(lexeme);

			if(citor==tokens.end())
				return new Word(lexeme,Compiler::_ID,line);
			else
				return citor->second->clone(line);
			
			//if(vacant(lexeme))
			//	put(lexeme,new Word(lexeme,Compiler::_ID));
			//continue;	
		}


		//处理单词素词法单元
		if(Compiler::_END==peek)
			return new Token(Compiler::_END,(line ? line-1 : line));
		else
		{
			char c(peek);			
			read();
			return new Token(c,line);

			//string s;
			//s.push_back(c);
			//if(vacant(s))
			//	put(s,new Token(c));
			//continue;
		}
	}
}
inline void Lexer::reserve(Word *const pw)
{
	tokens.insert(make_pair(pw->toString(),pw));
}
inline void Lexer::read()
{
	peek=text.read();
}
inline void Lexer::error(string s)
{
	err_record.insert(make_pair(line,s));
}
inline void Lexer::error(string s,char c,string s2)
{
	s.push_back(c);
	s+=s2;
	err_record.insert(make_pair(line,s));
}
void Lexer::reset(string &code)
{
	peek=' ';
	line=1;
	text.reset(code);
}
