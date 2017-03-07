#pragma once

#include "gvirtualtable.h"
#include "GCore/gdynamicarray.h"
#include "GCore/gmap.h"

// 字段
class GMemoryField
{
public:
	GMemoryField(G_TABLE_FIELD_TYPE field_type, const GString &field_name);
	GMemoryField(G_TABLE_FIELD_TYPE field_type, GString &&field_name);
	GMemoryField(const GMemoryField &field);
	GMemoryField(GMemoryField &&field);

	guint8 &FieldType();
	guint8  FieldType() const;
	gsize &FieldSize();
	gsize  FieldSize() const;
	GString &FieldName();
	GString  FieldName() const;
	GString &FieldText();
	GString  FieldText() const;

	gvoid SetFieldType(G_TABLE_FIELD_TYPE field_type);
	gvoid SetFieldSize(gsize field_size);
	gvoid SetFieldName(const GString &field_name);
	gvoid SetFieldName(GString &&field_name);
	gvoid SetFieldText(const GString &field_text);
	gvoid SetFieldText(GString &&field_text);

private:
	guint8 m_nFieldType;
	gsize m_nFieldSize;
	GString m_sFieldName;
	GString m_sFieldText;
};

// 元数据
class GMemoryMeta
{
public:
	GMemoryMeta();

	GString &TableName();
	const GString &TableName() const;
	GMemoryField &FieldAt(gsize field_id);
	const GMemoryField &FieldAt(gsize field_id) const;
	GMemoryField &Field(const GString &field_name);
	const GMemoryField &Field(const GString &field_name) const;

	gvoid SetFieldCount(gsize field_count);
	gvoid SetFieldType(gsize field_id, G_TABLE_FIELD_TYPE field_type);
	gvoid SetFieldName(gsize field_id, const GString &field_name);
	gvoid SetFieldName(gsize field_id, GString &&field_name);
	gvoid SetFieldText(gsize field_id, const GString &field_text);
	gvoid SetFieldText(gsize field_id, GString &&field_text);
	gvoid SetPrimaryKey(gsize field_id);
	gvoid SetPrimaryKey(const GString &field_name);

private:
	gint m_nPrimaryKey;
	GString m_sTableName;
	GDynamicArray<GMemoryField> m_tFields;
	GMap<GString, guint8> m_tFieldName_FieldID;
};

// 连续的一块内存
class GMemoryUnit
{
public:
	GMemoryUnit(gsize unit_size, gsize row_count)
		: m_tBytes(unit_size * row_count)
	{
		
	}

	gbyte *Cursor(gsize pos)
	{
		return m_tBytes.CursorAt(pos);
	}

	const gbyte *Cursor(gsize pos) const
	{
		return m_tBytes.CursorAt(pos);
	}

private:
	GDynamicArray<gbyte> m_tBytes;
	GMemoryUnit *m_pNext;
};

class GMemoryTable
{
public:
	GMemoryTable();

private:
	GMemoryMeta *m_pMeta;
	GMemoryUnit *m_pHead;
};
