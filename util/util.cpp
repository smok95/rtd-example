#include "stdafx.h"
#include "util.h"

#if defined(DEBUG)||defined(_DEBUG)
#	pragma comment(lib,"comsuppwd")
#else
#	pragma comment(lib,"comsuppw")
#endif // DEBUG

using namespace util;

bool safearray::get_string(SAFEARRAY* pArr, LONG index, OUT std::string& rValue) {
	if(!pArr)
		return false;
	
	_variant_t var;
	if(FAILED(SafeArrayGetElement(pArr, &index, &var.GetVARIANT())))
		return false;

	rValue = (const char*)((_bstr_t)var);
	return true;
}
