#include "transcoding.h"

wstring ANSI2Unicode(const string & strin)
{
	wstring strout;

	// 预计算所需空间大小（已包含结束字符）,单位wchar_t
	int dwNum = MultiByteToWideChar (CP_ACP, 0,strin.c_str(), -1, 0 , 0);
	wchar_t * pBuffer = new wchar_t[dwNum];
	if (!pBuffer)
	{
		return strout;
	}
	memset(pBuffer,0,(dwNum)*sizeof(wchar_t));

	if(MultiByteToWideChar(CP_ACP, 0, strin.c_str(),-1,pBuffer,dwNum) >= 0)
	{
		strout = pBuffer;
	}

	delete[] pBuffer;
	return strout;
}

string  Unicode2UTF8(const wstring & strin)
{
	string strout;

	//测试所需存储空间大小（已包含结束字符）,单位char
	int dwNum = WideCharToMultiByte(CP_UTF8,0,strin.c_str(),-1,0,0,0,0);
	char* pBuffer = new char[dwNum];
	if (!pBuffer)
	{
		return strout;
	}
	memset(pBuffer,0,dwNum);

	if(WideCharToMultiByte(CP_UTF8,0,strin.c_str(),-1,pBuffer,dwNum,0,0) >= 0)
	{
		strout = pBuffer;
	}

	delete[] pBuffer;
	return strout;
}

string  ANSI2UTF8(const string & strin)
{
	return Unicode2UTF8(ANSI2Unicode(strin));
}

string  Unicode2ANSI(const wstring & strin)
{
	string strout;

	//测试所需存储空间大小（已包含结束字符）,单位char
	int dwNum = WideCharToMultiByte(CP_ACP,0,strin.c_str(),-1,0,0,0,0);
	char* pBuffer = new char[dwNum];
	if (!pBuffer)
	{
		return strout;
	}
	memset(pBuffer,0,dwNum);

	BOOL use_def_char = FALSE;
	if(WideCharToMultiByte(CP_ACP,0,strin.c_str(),-1,pBuffer,dwNum,"?",&use_def_char) >= 0)
	{
		strout = pBuffer;
	}

	delete[] pBuffer;
	return strout;
}

wstring UTF82Unicode(const string & strin)
{
	wstring strout;

	// 预计算所需空间大小（已包含结束字符）,单位wchar_t
	int dwNum = MultiByteToWideChar (CP_UTF8, 0,strin.c_str(), -1, 0 , 0);
	wchar_t* pBuffer = new wchar_t[dwNum];
	if (!pBuffer)
	{
		return strout;
	}
	memset(pBuffer,0,dwNum*sizeof(wchar_t));

	if(MultiByteToWideChar(CP_UTF8,0,strin.c_str(),-1,pBuffer,dwNum) >= 0)
	{
		strout = pBuffer;
	}

	delete[] pBuffer;
	return strout;
}

string  UTF82ANSI(const string & strin)
{
	return Unicode2ANSI(UTF82Unicode(strin));
}

//Converting a WChar string to a Ansi string  
string	WChar2string(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);  
	if (nLen<= 0) return std::string("");  
	char* pszDst = new char[nLen];  
	if (NULL == pszDst) return std::string("");  
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);  
	pszDst[nLen -1] = 0;  
	std::string strTemp(pszDst);  
	delete [] pszDst;  
	return strTemp;  
}

string  wstring2string(wstring& inputws)
{
	return WChar2string(inputws.c_str());
}

//Converting a Ansi string to WChar string 
wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);  
	if(nSize <= 0) return NULL;  
	WCHAR *pwszDst = new WCHAR[nSize+1];  
	if( NULL == pwszDst) return NULL;  
	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);  
	pwszDst[nSize] = 0;  
	if( pwszDst[0] == 0xFEFF) // skip Oxfeff  
		for(int i = 0; i < nSize; i ++)   
			pwszDst[i] = pwszDst[i+1];   
	wstring wcharString(pwszDst);  
	delete pwszDst;  
	return wcharString;  
}

wstring string2wstring(const string& s)
{
	return Ansi2WChar(s.c_str(),s.size());
}
