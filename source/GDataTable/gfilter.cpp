#include "gfilter.h"
#include "gfilter_ex.h"

GFilter::GFilter(const GString &sFilter)
: m_pFilter_Ex(new GFilter_Ex(sFilter))
{
	GASSERT(m_pFilter_Ex);
}

GFilter::GFilter(const GFilter &tFilter)
: m_pFilter_Ex(new GFilter_Ex(*tFilter.m_pFilter_Ex))
{
	GASSERT(m_pFilter_Ex);
}

GFilter::~GFilter()
{
	delete m_pFilter_Ex;
}

gbool GFilter::SetFilter(const GString &sFilter)
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->SetFilter(sFilter);
}

gbool GFilter::IsValid() const
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->IsValid();
}

GString GFilter::ToString() const
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->ToString();
}

GFilter &GFilter::operator=(const GFilter &tFilter)
{
	GASSERT(m_pFilter_Ex);
	*m_pFilter_Ex = *tFilter.m_pFilter_Ex;
	return *this;
}