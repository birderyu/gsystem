#include "gmemorytable.h"

GMemoryField::GMemoryField(G_TABLE_FIELD_TYPE field_type, const GString &field_name)
	: m_nFieldType(field_type), m_sFieldName(field_name)
{

}

GMemoryField::GMemoryField(G_TABLE_FIELD_TYPE field_type, GString &&field_name)
	: m_nFieldType(field_type), m_sFieldName(GForward<GString>(field_name))
{

}

GMemoryField::GMemoryField(const GMemoryField &field)
	: m_nFieldType(field.m_nFieldType)
	, m_nFieldSize(field.m_nFieldSize)
	, m_sFieldName(field.m_sFieldName)
	, m_sFieldText(field.m_sFieldText)
{

}

GMemoryField::GMemoryField(GMemoryField &&field)
	: m_nFieldType(field.m_nFieldType)
	, m_nFieldSize(field.m_nFieldSize)
	, m_sFieldName(GMove(field.m_sFieldName))
	, m_sFieldText(GMove(field.m_sFieldText))
{

}