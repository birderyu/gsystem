#ifndef _CORE_TABLE_FIELDS_H_
#define _CORE_TABLE_FIELDS_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableFields
{
public:
	GTableFields(GDataTable &, GSizeArray *columns = GNULL);
	GTableFields(const GTableFields<TableT> &);
	GTableFields(GTableFields<TableT> &&);

	GDataTable &Table();
	const GDataTable &Table() const;

	gsize Count() const;
	gbool Contains(const GString &) const;
	gint ColumnID(const GString &) const;

	GTableField operator[](gsize) const;
	GTableField operator[](const GString &) const;

	gbool Add(const GTableField &);
	gbool Add(const GString &, G_TABLE_FIELD_TYPE);
	gbool Remove(const GTableField &);
	gbool Remove(const GString &);
	gbool RemoveAt(gsize);
	gbool Clear();

	GTableFields &operator=(const GTableFields &);
};

#endif // _CORE_TABLE_FIELDS_H_