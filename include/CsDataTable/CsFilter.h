#ifndef _CORE_FILTER_H_
#define _CORE_FILTER_H_

#include "CsObject.h"
#include "CsString.h"

class CsFilter_Ex;

class CS_API CsFilter 
	: public CsObject
{
public:
	CsFilter(const CsString &sFilter = "");
	CsFilter(const CsFilter &tFilter);
	~CsFilter();

	cs_bool SetFilter(const CsString &sFilter);
	cs_bool IsValid() const;
	CsString ToString() const;

	virtual CsFilter &operator=(const CsFilter &tFilter);

private:
	CsFilter_Ex *m_pFilter_Ex;
};

#endif // _CORE_FILTER_H_