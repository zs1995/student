//�ַ�ת��
#ifndef _CHARACTERCONVERSIONTOOL_H
#define _CHARACTERCONVERSIONTOOL_H

#include <iostream>
#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif


class CCHARACTERCONVERSIONTOOL
{
public:
	CCHARACTERCONVERSIONTOOL();
	~CCHARACTERCONVERSIONTOOL();

	//unicode ת Ansi
	std::string  UnicodeToAnsi(const std::wstring& unicode);
	//Ansi ת unicode
	std::wstring AnsiToUnicode(const std::string& ansi);

	//Ansi ת UTF-8
	std::string  AnsiToUtf8(const std::string& strSrc);
	//UTF-8 ת Ansi
	std::string  Utf8ToAnsi(const std::string& strSrc);

	//unicode ת utf-8
	std::string  UnicodeToUtf8(const std::wstring& wstrSrc);
	//utf-8 ת unicode
	std::wstring Utf8ToUnicode(const std::string& strSrc);

	//gbk ת UTF-8
	std::string  GBKToUtf8(const std::string& gbk);
	//UTF-8 ת gbk
	std::string  Utf8ToGBK(const std::string& utf8);

	//gb2312 ת Unicode
	std::wstring GB2312ToUnicode(const std::string& gb2312);
	//Unicode ת gb2312
	std::string  UnicodeToGB2312(const std::wstring& unicode);

	//big5 ת Unicode
	std::wstring BIG5ToUnicode(const std::string& big5);
	//Unicode ת big5
	std::string  UnicodeToBIG5(const std::wstring& unicode);

	//FBIG5 ת GB2312
	std::string  FBIG5ToGB2312(const std::string& big5);
	//gb2312 ת FBIG5
	std::string  GB2312ToFBIG5(const std::string gb2312);

	//�Ƿ�Ϊutf-8
	bool IsUTF8(const void* pBuffer, long size);

};




#endif