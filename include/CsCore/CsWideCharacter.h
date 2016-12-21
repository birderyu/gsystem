#ifndef _CORE_WIND_CHARACTER_H_
#define _CORE_WIND_CHARACTER_H_

#include "CsPackage.h"

class CS_API CsWideCharacter 
	: public CsPackage<cs_wchar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_WIND_CHARACTER, };

public:
	CsWideCharacter(cs_wchar val);
	CsWideCharacter(const CsWideCharacter &);

	cs_uint ClassCode() const;
};

typedef CsWideCharacter CsWCharacter;
typedef CsWideCharacter CsWindChar;
typedef CsWideCharacter CsWChar;

#endif // _CORE_WIND_CHARACTER_H_