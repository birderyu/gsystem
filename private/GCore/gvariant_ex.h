#ifndef _CORE_VARIANT_EX_H_
#define _CORE_VARIANT_EX_H_

#include "gglobal.h"
#include "gvariant.h"

class GVariant_Ex
	: public GNewT<GVariant_Ex>
{
public:
	GVariant_Ex();
	GVariant_Ex(gbool bValue);
	GVariant_Ex(gchar cValue);
	GVariant_Ex(gschar cValue);
	GVariant_Ex(guchar cValue);
	GVariant_Ex(gwchar cValue);
	GVariant_Ex(gshort nValue);
	GVariant_Ex(gushort nValue);
	GVariant_Ex(gint nValue);
	GVariant_Ex(guint nValue);
	GVariant_Ex(glong nValue);
	GVariant_Ex(gulong nValue);
	GVariant_Ex(glonglong nValue);
	GVariant_Ex(gulonglong nValue);
	GVariant_Ex(gfloat nValue);
	GVariant_Ex(gdouble nValue);
	GVariant_Ex(gdecimal nValue);
	GVariant_Ex(const GString &sValue);
	GVariant_Ex(const GObject &tValue);
	GVariant_Ex(const GObjectP &pValue);
	GVariant_Ex(const gpointer pValue);
	GVariant_Ex(const GVariant_Ex &tOther);
	~GVariant_Ex();

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

	GVariant_Ex &operator=(const GVariant_Ex &var);
	
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
BaseT GVariant_Ex::ToNumber(const guint nClassCode, const BaseT &nDefValue) const
{
	// TODO
	return BaseT();
}

#endif // _CORE_VARIANT_PRIVATE_H_