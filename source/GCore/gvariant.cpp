#include "gvariant.h"
#include "gvariant_ex.h"

GVariant::GVariant()
: m_pVariant_Ex(new GVariant_Ex())
{

}

GVariant::GVariant(gbool bValue)
: m_pVariant_Ex(new GVariant_Ex(bValue))
{

}

GVariant::GVariant(gchar cValue)
: m_pVariant_Ex(new GVariant_Ex(cValue))
{

}

GVariant::GVariant(guchar cValue)
: m_pVariant_Ex(new GVariant_Ex(cValue))
{

}

GVariant::GVariant(gwchar cValue)
: m_pVariant_Ex(new GVariant_Ex(cValue))
{

}

GVariant::GVariant(gshort nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gushort nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gint nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(guint nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(glong nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gulong nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(glonglong nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gulonglong nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gfloat nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gdouble nValue)
: m_pVariant_Ex(new GVariant_Ex(nValue))
{

}

GVariant::GVariant(gcstring sValue)
: m_pVariant_Ex(new GVariant_Ex(GString(sValue)))
{

}

GVariant::GVariant(const GString &sValue)
: m_pVariant_Ex(new GVariant_Ex(sValue))
{

}

GVariant::GVariant(const GObject &tValue)
: m_pVariant_Ex(new GVariant_Ex(tValue))
{

}

GVariant::GVariant(const gpointer pValue)
: m_pVariant_Ex(new GVariant_Ex(pValue))
{

}

GVariant::GVariant(const GVariant &tOther)
: m_pVariant_Ex(new GVariant_Ex(*tOther.m_pVariant_Ex))
{

}

GVariant::~GVariant()
{
	if (m_pVariant_Ex)
	{
		delete m_pVariant_Ex;
	}
}

G_VARIANT_TYPE GVariant::GetVariantType() const
{
	return m_pVariant_Ex->GetVariantType();
}

gpointer GVariant::GetPoiter() const
{
	return m_pVariant_Ex->GetPoiter();
}

gvoid GVariant::SetPoiter(const gpointer pValue)
{
	m_pVariant_Ex->SetPoiter(pValue);
}

gvoid GVariant::SetValue(const gbool bValue)
{
	m_pVariant_Ex->SetValue(bValue);
}

gvoid GVariant::SetValue(const gchar cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

gvoid GVariant::SetValue(const guchar cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

gvoid GVariant::SetValue(const gwchar cValue)
{
	m_pVariant_Ex->SetValue(cValue);
}

gvoid GVariant::SetValue(const gshort nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gushort nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gint nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const guint nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const glong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gulong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const glonglong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gulonglong nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gfloat nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(const gdouble nValue)
{
	m_pVariant_Ex->SetValue(nValue);
}

gvoid GVariant::SetValue(gcstring sValue)
{
	m_pVariant_Ex->SetValue(GString(sValue));
}

gvoid GVariant::SetValue(const GString &sValue)
{
	m_pVariant_Ex->SetValue(sValue);
}

gvoid GVariant::SetValue(const GObject &tValue)
{
	m_pVariant_Ex->SetValue(tValue);
}

gbool GVariant::ToBool(const gbool def) const
{
	return m_pVariant_Ex->ToBool(def);
}

gchar GVariant::ToChar(const gchar def) const
{
	return m_pVariant_Ex->ToChar(def);
}

guchar GVariant::ToUChar(const guchar def) const
{
	return m_pVariant_Ex->ToUChar(def);
}

gwchar GVariant::ToWChar(const gwchar def) const
{
	return m_pVariant_Ex->ToWChar(def);
}

gsmall GVariant::ToSmall(const gsmall def) const
{
	return m_pVariant_Ex->ToSmall(def);
}

gusmall GVariant::ToUSmall(const gusmall def) const
{
	return m_pVariant_Ex->ToUSmall(def);
}

gshort GVariant::ToShort(const gshort def) const
{
	return m_pVariant_Ex->ToShort(def);
}

gushort GVariant::ToUShort(const gushort def) const
{
	return m_pVariant_Ex->ToUShort(def);
}

gint GVariant::ToInt(const gint def) const
{
	return m_pVariant_Ex->ToInt(def);
}

guint GVariant::ToUInt(const guint def) const
{
	return m_pVariant_Ex->ToUInt(def);
}

glong GVariant::ToLong(const glong def) const
{
	return m_pVariant_Ex->ToLong(def);
}

gulong GVariant::ToULong(const gulong def) const
{
	return m_pVariant_Ex->ToULong(def);
}

glonglong GVariant::ToLongLong(const glonglong def) const
{
	return m_pVariant_Ex->ToLongLong(def);
}

gulonglong GVariant::ToULongLong(const gulonglong def) const
{
	return m_pVariant_Ex->ToULongLong(def);
}

gfloat GVariant::ToFloat(const gfloat def) const
{
	return m_pVariant_Ex->ToFloat(def);
}

gdouble GVariant::ToDouble(const gdouble def) const
{
	return m_pVariant_Ex->ToDouble(def);
}

GString GVariant::ToString(const GString &def) const
{
	return m_pVariant_Ex->ToString(def);
}

GObject *GVariant::ToObject() const
{
	return m_pVariant_Ex->ToObject();
}

gbyte GVariant::ToByte(const gbyte &def) const
{
	return ToUChar(def);
}

gint8 GVariant::ToInt8(const gint8 &def) const
{
	return ToSmall(def);
}

guint8 GVariant::ToUInt8(const guint8 &def) const
{
	return ToUSmall(def);
}

gint16 GVariant::ToInt16(const gint16 &def) const
{
	return ToShort(def);
}

guint16 GVariant::ToUInt16(const guint16 &def) const
{
	return ToUShort(def);
}

gint32 GVariant::ToInt32(const gint32 &def) const
{
	return ToInt(def);
}

guint32 GVariant::ToUInt32(const guint32 &def) const
{
	return ToUInt(def);
}

gint64 GVariant::ToInt64(const gint64 &def) const
{
	return ToLongLong(def);
}

guint64 GVariant::ToUInt64(const guint64 &def) const
{
	return ToULongLong(def);
}

gsize GVariant::ToSizeType(const gsize &def) const
{
	return ToUInt(def);
}

gbool GVariant::IsValid() const
{
	return m_pVariant_Ex->IsValid();
}

GVariant &GVariant::operator = (const GVariant &var)
{
	m_pVariant_Ex->operator=(*var.m_pVariant_Ex);
	return *this;
}