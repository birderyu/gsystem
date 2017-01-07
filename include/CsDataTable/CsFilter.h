#ifndef _CORE_FILTER_H_
#define _CORE_FILTER_H_

#include "gobject.h"
#include "gstring.h"

class CsFilter_Ex;

class GAPI CsFilter 
	: public GObject
{
public:
	CsFilter(const GString &sFilter = "");
	CsFilter(const CsFilter &tFilter);
	~CsFilter();

	gbool SetFilter(const GString &sFilter);
	gbool IsValid() const;
	GString ToString() const;

	virtual CsFilter &operator=(const CsFilter &tFilter);

private:
	CsFilter_Ex *m_pFilter_Ex;
};

#endif // _CORE_FILTER_H_