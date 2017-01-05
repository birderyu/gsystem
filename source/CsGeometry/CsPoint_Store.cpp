#include "CsPoint_Store.h"
#include "CsCoordinate.h"
#include "CsNew.h"

cs_void CsPoint2D_Store::Initialize()
{
	CsMemSet(m_tCoord, 0, sizeof(cs_real)* 2);
}

cs_void CsPoint2D_Store::Initialize(cs_real x, cs_real y)
{
	m_tCoord[0] = x;
	m_tCoord[1] = y;
}

cs_void CsPoint2D_Store::Initialize(const CsCoordinate &c)
{
	m_tCoord[0] = c.X();
	m_tCoord[1] = c.Y();
}

cs_void CsPoint2D_Store::Initialize(const CsPoint2D_Store &p_s)
{
	if (this != &p_s)
	{
		CsMemCopy(m_tCoord, p_s.m_tCoord, sizeof(cs_real)* 2);
	}
}

cs_real &CsPoint2D_Store::X()
{
	return m_tCoord[0];
}

cs_real CsPoint2D_Store::X() const
{
	return m_tCoord[0];
}

cs_real &CsPoint2D_Store::Y()
{
	return m_tCoord[1];
}

cs_real CsPoint2D_Store::Y() const
{
	return m_tCoord[1];
}

cs_void CsPoint2D_Store::SetX(cs_real x)
{
	m_tCoord[0] = x;
}

cs_void CsPoint2D_Store::SetY(cs_real y)
{
	m_tCoord[0] = y;
}
