#include "common.h"
#include "../public/Strings.h"

std::wstring copyMMString(mmString* mmStr)
{
	std::wstring ret;
	if (mmStr->pUnicode && *mmStr->pUnicode) {
		ret.assign(mmStr->pUnicode,mmStr->Mysize);
	}
	return ret;
}

mmString::mmString()
{
	pUnicode = 0x0;
	Mysize = 0x0;
	Myres = 0x0;
	pUTF8 = 0x0;
	uLen = 0x0;
}


void mmString::assign(const wchar_t* src, int len)
{
	this->pUnicode = 0;
	this->Mysize = 0;
	this->Myres = 0;
	this->pUTF8 = 0;
	this->uLen = 0;
	if (!src || !len) {
		return;
	}
	wchar_t* pBuf = new wchar_t[len + 1];
	if (pBuf) {
		wmemcpy(pBuf, src, len);
		pBuf[len] = 0x0;
		this->pUnicode = pBuf;
		this->Mysize = len;
		this->Myres = len;
	}
}

void mmString::assignUTF8(const char* src)
{
	std::wstring wStr = Utf8ToUnicode(src);
	this->assign(wStr.c_str(), wStr.size());
}

void mmString::assign(const char* src)
{
	std::wstring wStr = AnsiToUnicode(src);
	this->assign(wStr.c_str(),wStr.size());
}

void mmString::free()
{
	if (this->pUnicode) {
		delete this->pUnicode;
		this->pUnicode = 0x0;
	}
	this->Mysize = 0x0;
	this->Myres = 0x0;
	if (this->pUTF8) {
		delete this->pUTF8;
		this->pUTF8 = 0x0;
	}
	this->uLen = 0x0;
}

MymmString::MymmString(const MymmString& s)
{
	if (!s.Mysize) {
		return;
	}
	wchar_t* pBuf = new wchar_t[s.Mysize + 1];
	if (pBuf) {
		wmemcpy(pBuf, s.pUnicode, s.Mysize);
		pBuf[s.Mysize] = 0x0;
		this->pUnicode = pBuf;
		this->Mysize = s.Mysize;
		this->Myres = s.Mysize;
	}
}

MymmString::MymmString()
{

}

MymmString::~MymmString()
{
	free();
}

