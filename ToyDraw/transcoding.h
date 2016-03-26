#pragma once
#include <Windows.h>
#include <string>
using namespace std;

wstring ANSI2Unicode(const string & strin);
string  Unicode2UTF8(const wstring & strin);
string  ANSI2UTF8(const string & strin);
string  Unicode2ANSI(const wstring & strin);
wstring UTF82Unicode(const string & strin);
string  UTF82ANSI(const string & strin);
//Converting a WChar string to a Ansi string  
string	WChar2string(LPCWSTR pwszSrc);
string  wstring2string(wstring& inputws);
//Converting a Ansi string to WChar string 
wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
wstring string2wstring(const string& s);
