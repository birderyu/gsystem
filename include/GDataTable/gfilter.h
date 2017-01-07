#ifndef _CORE_FILTER_H_
#define _CORE_FILTER_H_

#include "GCore/gobject.h"
#include "GCore/gstring.h"

class GFilter_Ex;

class GAPI GFilter 
	: public GObject
{
public:
	GFilter(const GString &sFilter = "");
	GFilter(const GFilter &tFilter);
	~GFilter();

	gbool SetFilter(const GString &sFilter);
	gbool IsValid() const;
	GString ToString() const;

	virtual GFilter &operator=(const GFilter &tFilter);

private:
	GFilter_Ex *m_pFilter_Ex;
};

#endif // _CORE_FILTER_H_