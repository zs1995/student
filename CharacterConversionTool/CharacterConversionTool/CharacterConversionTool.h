//字符转换
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

	//unicode 转 Ansi
	std::string  UnicodeToAnsi(const std::wstring& unicode);
	//Ansi 转 unicode
	std::wstring AnsiToUnicode(const std::string& ansi);

	//Ansi 转 UTF-8
	std::string  AnsiToUtf8(const std::string& strSrc);
	//UTF-8 转 Ansi
	std::string  Utf8ToAnsi(const std::string& strSrc);

	//unicode 转 utf-8
	std::string  UnicodeToUtf8(const std::wstring& wstrSrc);
	//utf-8 转 unicode
	std::wstring Utf8ToUnicode(const std::string& strSrc);

	//gbk 转 UTF-8
	std::string  GBKToUtf8(const std::string& gbk);
	//UTF-8 转 gbk
	std::string  Utf8ToGBK(const std::string& utf8);

	//gb2312 转 Unicode
	std::wstring GB2312ToUnicode(const std::string& gb2312);
	//Unicode 转 gb2312
	std::string  UnicodeToGB2312(const std::wstring& unicode);

	//big5 转 Unicode
	std::wstring BIG5ToUnicode(const std::string& big5);
	//Unicode 转 big5
	std::string  UnicodeToBIG5(const std::wstring& unicode);

	//FBIG5 转 GB2312
	std::string  FBIG5ToGB2312(const std::string& big5);
	//gb2312 转 FBIG5
	std::string  GB2312ToFBIG5(const std::string gb2312);

	//是否为utf-8
	bool IsUTF8(const void* pBuffer, long size);

};




#endif