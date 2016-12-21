#ifndef _CORE_REGISTER_H_
#define _CORE_REGISTER_H_

#include "CsGlobal.h"
#include "CsSingleton.h"
#include "CsMutex.h"
#include "CsString.h"
#include "CsUnorderMap.h"

class CS_API CsRegister
	: public CsSingleton<CsRegister, CsMutex>
{
public:
	cs_bool Register(const CsString &sClassName, cs_uint nClassCode);
	cs_void Initialize();
	
private:
	CsUnorderMap<CsString, cs_uint> m_tClassName_ClassCode;
	CsUnorderMap<cs_uint, CsString> m_tClassCode_ClassName;
};

class CsString;

#endif // _CORE_REGISTER_H_