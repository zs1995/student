#include "CharacterConversionTool.h"

CCHARACTERCONVERSIONTOOL::CCHARACTERCONVERSIONTOOL()
{

}

CCHARACTERCONVERSIONTOOL::~CCHARACTERCONVERSIONTOOL()
{

}

std::string CCHARACTERCONVERSIONTOOL::UnicodeToAnsi(const std::wstring& unicode)
{
#ifdef WIN32
	LPCWCH ptr = unicode.c_str();
	/** ����Ŀ��ռ�, һ��16λUnicode�ַ�������תΪ4���ֽ�int size = static_cast<int>( wstrSrc.size() * 4 + 10 );*/
	int size = WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, -1, NULL, 0, NULL, NULL);

	std::string strRet(size, 0);
	int len = WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, -1, (LPSTR)strRet.c_str(), size, NULL, NULL);
#else
	
#endif

	return strRet;
}

std::wstring CCHARACTERCONVERSIONTOOL::AnsiToUnicode(const std::string& ansi)
{
	LPCCH ptr = ansi.c_str();
	int size = MultiByteToWideChar(CP_ACP, 0, ptr, -1, NULL, NULL);

	std::wstring wstrRet(size, 0);
	int len = MultiByteToWideChar(CP_ACP, 0, ptr, -1, (LPWSTR)wstrRet.c_str(), size);

	return wstrRet;
}

std::string CCHARACTERCONVERSIONTOOL::AnsiToUtf8(const std::string& ansi)
{
	LPCCH ptr = ansi.c_str();
	/* ����Ŀ��ռ�, ����Ϊ Ansi ��������� */
	int size = MultiByteToWideChar(CP_ACP, 0, ptr, -1, NULL, NULL);

	std::wstring wstrTemp(size, 0);
	int len = MultiByteToWideChar(CP_ACP, 0, ptr, -1, (LPWSTR)wstrTemp.c_str(), size);

	return UnicodeToUtf8(wstrTemp);
}

std::string CCHARACTERCONVERSIONTOOL::Utf8ToAnsi(const std::string& utf8)
{
	std::wstring wstrTemp = Utf8ToUnicode(utf8);

	LPCWCH ptr = wstrTemp.c_str();
	int size = WideCharToMultiByte(CP_ACP, 0, ptr, -1, NULL, 0, NULL, NULL);

	std::string strRet(size, 0);
	int len = WideCharToMultiByte(CP_ACP, 0, ptr, -1, (LPSTR)strRet.c_str(), size, NULL, NULL);

	return strRet;
}

std::string CCHARACTERCONVERSIONTOOL::UnicodeToUtf8(const std::wstring& unicode)
{
	/* ����Ŀ��ռ�, һ��16λUnicode�ַ�������תΪ4���ֽ� */
	LPCWCH ptr = unicode.c_str();
	int size = WideCharToMultiByte(CP_UTF8, 0, ptr, -1, NULL, 0, NULL, NULL);

	std::string strRet(size, 0);
	int len = WideCharToMultiByte(CP_UTF8, 0, ptr, -1, (char*)strRet.c_str(), size, NULL, NULL);

	return strRet;
}

std::wstring CCHARACTERCONVERSIONTOOL::Utf8ToUnicode(const std::string& utf8)
{
	LPCCH ptr = utf8.c_str();
	int size = MultiByteToWideChar(CP_UTF8, 0, ptr, -1, NULL, NULL);

	std::wstring wstrRet(size, 0);
	int len = MultiByteToWideChar(CP_UTF8, 0, ptr, -1, (LPWSTR)wstrRet.c_str(), size);

	return wstrRet;
}


std::string CCHARACTERCONVERSIONTOOL::GBKToUtf8(const std::string& gbk)
{
	return AnsiToUtf8(gbk);
}

std::string CCHARACTERCONVERSIONTOOL::Utf8ToGBK(const std::string& utf8)
{
	return Utf8ToAnsi(utf8);
}

bool CCHARACTERCONVERSIONTOOL::IsUTF8(const void* pBuffer, long size)
{
	bool isUTF8 = true;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
	while (start < end)
	{
		if (*start < 0x80) { /*(10000000): ֵС��0x80��ΪASCII�ַ�*/
			start++;
		}
		else if (*start < (0xC0)) { /*(11000000): ֵ����0x80��0xC0֮���Ϊ��ЧUTF-8�ַ�*/
			isUTF8 = false;
			break;
		}
		else if (*start < (0xE0)) { /*(11100000): �˷�Χ��Ϊ2�ֽ�UTF-8�ַ�  */
			if (start >= end - 1) {
				break;
			}
			if ((start[1] & (0xC0)) != 0x80) {
				isUTF8 = false;
				break;
			}
			start += 2;
		}
		else if (*start < (0xF0)) { /**(11110000): �˷�Χ��Ϊ3�ֽ�UTF-8�ַ�*/
			if (start >= end - 2) {
				break;
			}
			if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80) {
				isUTF8 = false;
				break;
			}
			start += 3;
		}
		else {
			isUTF8 = false;
			break;
		}
	}

	return isUTF8;
}



//GB2312 ת���� Unicode
std::wstring CCHARACTERCONVERSIONTOOL::GB2312ToUnicode(const std::string& gb2312)
{
	UINT nCodePage = 936; //GB2312
	int size = MultiByteToWideChar(nCodePage, 0, gb2312.c_str(), -1, NULL, 0);

	std::wstring wstrRet(size, 0);
	MultiByteToWideChar(nCodePage, 0, gb2312.c_str(), -1, (LPWSTR)wstrRet.c_str(), size);

	return wstrRet;
}

//BIG5 ת���� Unicode
std::wstring CCHARACTERCONVERSIONTOOL::BIG5ToUnicode(const std::string& big5)
{
	UINT nCodePage = 950; //BIG5
	int size = MultiByteToWideChar(nCodePage, 0, big5.c_str(), -1, NULL, 0);

	std::wstring wstrRet(size, 0);
	MultiByteToWideChar(nCodePage, 0, big5.c_str(), -1, (LPWSTR)wstrRet.c_str(), size);

	return wstrRet;
}

//Unicode ת���� GB2312
std::string CCHARACTERCONVERSIONTOOL::UnicodeToGB2312(const std::wstring& unicode)
{
	UINT nCodePage = 936; //GB2312
	int size = WideCharToMultiByte(nCodePage, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);

	std::string strRet(size, 0);
	WideCharToMultiByte(nCodePage, 0, unicode.c_str(), -1, (LPSTR)strRet.c_str(), size, NULL, NULL);

	return strRet;
}

//Unicode ת���� BIG5
std::string CCHARACTERCONVERSIONTOOL::UnicodeToBIG5(const std::wstring& unicode)
{
	UINT nCodePage = 950; //BIG5
	int size = WideCharToMultiByte(nCodePage, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);

	std::string strRet(size, 0);
	WideCharToMultiByte(nCodePage, 0, unicode.c_str(), -1, (LPSTR)strRet.c_str(), size, NULL, NULL);

	return strRet;
}

//��������BIG5 ת���� �������� GB2312
std::string CCHARACTERCONVERSIONTOOL::FBIG5ToGB2312(const std::string& big5)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
	std::wstring unicode = BIG5ToUnicode(big5);

	std::string gb2312 = UnicodeToGB2312(unicode);
	int size = LCMapStringA(lcid, LCMAP_SIMPLIFIED_CHINESE, gb2312.c_str(), -1, NULL, 0);

	std::string strRet(size, 0);
	LCMapStringA(0x0804, LCMAP_SIMPLIFIED_CHINESE, gb2312.c_str(), -1, (LPSTR)strRet.c_str(), size);

	return strRet;
}

//�������� GB2312 ת���� ��������BIG5
std::string CCHARACTERCONVERSIONTOOL::GB2312ToFBIG5(const std::string gb2312)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
	int size = LCMapStringA(lcid, LCMAP_TRADITIONAL_CHINESE, gb2312.c_str(), -1, NULL, 0);

	std::string strRet(size, 0);
	LCMapStringA(lcid, LCMAP_TRADITIONAL_CHINESE, gb2312.c_str(), -1, (LPSTR)strRet.c_str(), size);

	std::wstring unicode = GB2312ToUnicode(strRet);
	std::string big5 = UnicodeToBIG5(unicode);

	return big5;
}