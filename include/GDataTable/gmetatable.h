#pragma once

#include "gtableglobal.h"

class GVirtualMeta;

class GMetaTable
{
public:
	GString &TableName();
	const GString &TableName() const;
	GString &TableText();
	const GString &TableText() const;

	gvoid SetTableName(const GString &tablename);
	gvoid SetTableName(GString &&tablename);
	gvoid SetTableText(const GString &tabletext);
	gvoid SetTableText(GString &&tabletext);
	gvoid SetFieldCount(gsize count);
	gvoid SetFieldNameAt(gsize fieldid, const GString &fieldname);
	gvoid SetFieldTextAt(gsize fieldid, const GString &fieldtext);
	gvoid SetFieldType(gsize fieldid, G_TABLE_FIELD_TYPE type);

private:
	GVirtualMeta *m_pVirtualMeta;
};