#ifndef _CORE_VARIANT_EX_H_
#define _CORE_VARIANT_EX_H_

#include "gglobal.h"
#include "gvariant.h"

class CsVariant_Ex
	: public GNewT<CsVariant_Ex>
{
public:
	CsVariant_Ex();
	CsVariant_Ex(gbool bValue);
	CsVariant_Ex(gchar cValue);
	CsVariant_Ex(gschar cValue);
	CsVariant_Ex(guchar cValue);
	CsVariant_Ex(gwchar cValue);
	CsVariant_Ex(gshort nValue);
	CsVariant_Ex(gushort nValue);
	CsVariant_Ex(gint nValue);
	CsVariant_Ex(guint nValue);
	CsVariant_Ex(glong nValue);
	CsVariant_Ex(gulong nValue);
	CsVariant_Ex(glonglong nValue);
	CsVariant_Ex(gulonglong nValue);
	CsVariant_Ex(gfloat nValue);
	CsVariant_Ex(gdouble nValue);
	CsVariant_Ex(gdecimal nValue);
	CsVariant_Ex(const GString &sValue);
	CsVariant_Ex(const GObject &tValue);
	CsVariant_Ex(const GObjectP &pValue);
	CsVariant_Ex(const gpointer pValue);
	CsVariant_Ex(const CsVariant_Ex &tOther);
	~CsVariant_Ex();

	G_VARIANT_TYPE GetVariantType() const;
	gpointer GetPoiter() const;
	gvoid SetPoiter(const gpointer pValue);

	gvoid SetValue(gbool bValue);
	gvoid SetValue(gchar cValue);
	gvoid SetValue(gschar cValue);
	gvoid SetValue(guchar cValue);
	gvoid SetValue(gwchar cValue);
	gvoid SetValue(gshort nValue);
	gvoid SetValue(gushort nValue);
	gvoid SetValue(gint nValue);
	gvoid SetValue(guint nValue);
	gvoid SetValue(glong nValue);
	gvoid SetValue(gulong nValue);
	gvoid SetValue(glonglong nValue);
	gvoid SetValue(gulonglong nValue);
	gvoid SetValue(gfloat nValue);
	gvoid SetValue(gdouble nValue);
	gvoid SetValue(gdecimal nValue);
	gvoid SetValue(const GString &sValue);
	gvoid SetValue(const GObject &tValue);

	gbool ToBool(const gbool bDefValue) const;
	gchar ToChar(const gchar cDefValue) const;
	gschar ToSChar(const gschar cDefValue) const;
	guchar ToUChar(const guchar cDefValue) const;
	gwchar ToWChar(const gwchar cDefValue) const;
	gsmall ToSmall(const gsmall nDefValue) const;
	gusmall ToUSmall(const gusmall nDefValue) const;
	gshort ToShort(const gshort nDefValue) const;
	gushort ToUShort(const gushort nDefValue) const;
	gint ToInt(const gint nDefValue) const;
	guint ToUInt(const guint nDefValue) const;
	glong ToLong(const glong nDefValue) const;
	gulong ToULong(const gulong nDefValue) const;
	glonglong ToLongLong(const glonglong nDefValue) const;
	gulonglong ToULongLong(const gulonglong nDefValue) const;
	gfloat ToFloat(const gfloat nDefValue) const;
	gdouble ToDouble(const gdouble nDefValue) const;
	gdecimal ToDecimal(const gdecimal nDefValue) const;
	GString ToString(const GString &sDefValue) const;
	GObject *ToObject() const;

	gbool IsValid() const;

	CsVariant_Ex &operator=(const CsVariant_Ex &var);
	
private:
	gvoid ClearMemery();

	template<typename BaseT, typename PackageT>
	BaseT ToNumber(const guint nClassCode, const BaseT &nDefValue) const;

	union
	{
		gbool			m_bVal;
		gchar			m_cVal;
		gschar		m_scVal;
		guchar		m_ucVal;
		gwchar		m_wcVal;
		gshort		m_sVal;
		gushort		m_usVal;
		gint			m_iVal;
		guint			m_uiVal;
		glong			m_lVal;
		gulong		m_ulVal;
		glonglong		m_llVal;
		gulonglong	m_ullVal;
		gfloat		m_fVal;
		gdouble		m_dVal;
		gdecimal		m_decVal;
		gpointer		m_pVal;
		GStringStore	m_strVal;
	};
	gbyte m_nType;
};

template<typename BaseT, typename PackageT>
BaseT CsVariant_Ex::ToNumber(const guint nClassCode, const BaseT &nDefValue) const
{
	// TODO
	return BaseT();
}

#endif // _CORE_VARIANT_PRIVATE_H_