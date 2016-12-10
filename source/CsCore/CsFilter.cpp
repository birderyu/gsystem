#include "CsFilter.h"
#include "CsFilter_Ex.h"

CsFilter::CsFilter(const CsString &sFilter)
: m_pFilter_Ex(new CsFilter_Ex(sFilter))
{
	CS_ASSERT(m_pFilter_Ex);
}

CsFilter::CsFilter(const CsFilter &tFilter)
: m_pFilter_Ex(new CsFilter_Ex(*tFilter.m_pFilter_Ex))
{
	CS_ASSERT(m_pFilter_Ex);
}

CsFilter::~CsFilter()
{
	delete m_pFilter_Ex;
}

cs_bool CsFilter::SetFilter(const CsString &sFilter)
{
	CS_ASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->SetFilter(sFilter);
}

cs_bool CsFilter::IsValid() const
{
	CS_ASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->IsValid();
}

CsString CsFilter::ToString() const
{
	CS_ASSERT(m_pFilter_Ex);
	return m_pFilter_Ex->ToString();
}

CsFilter &CsFilter::operator=(const CsFilter &tFilter)
{
	CS_ASSERT(m_pFilter_Ex);
	*m_pFilter_Ex = *tFilter.m_pFilter_Ex;
	return *this;
}