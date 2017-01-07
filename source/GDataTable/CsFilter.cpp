#include "CsFilter.h"
#include "CsFilter_Ex.h"

CsFilter::CsFilter(const GString &sFilter)
: m_pFilter_Ex(new CsFilter_Ex(sFilter))
{
	GASSERT(m_pFilter_Ex);
}

CsFilter::CsFilter(const CsFilter &tFilter)
: m_pFilter_Ex(new CsFilter_Ex(*tFilter.m_pFilter_Ex))
{
	GASSERT(m_pFilter_Ex);
}

CsFilter::~CsFilter()
{
	delete m_pFilter_Ex;
}

gbool CsFilter::SetFilter(const GString &sFilter)
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->SetFilter(sFilter);
}

gbool CsFilter::IsValid() const
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->IsValid();
}

GString CsFilter::ToString() const
{
	GASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->ToString();
}

CsFilter &CsFilter::operator=(const CsFilter &tFilter)
{
	GASSERT(m_pFilter_Ex);
	*m_pFilter_Ex = *tFilter.m_pFilter_Ex;
	return *this;
}