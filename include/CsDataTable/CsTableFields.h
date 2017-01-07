#ifndef _CORE_TABLE_FIELDS_H_
#define _CORE_TABLE_FIELDS_H_

#include "CsTableGlobal.h"

class GAPI CsTableFields
{
public:
	CsTableFields(CsDataTable &, CsSizeTypeArray *columns = NULL);
	CsTableFields(const CsTableFields &);

	CsDataTable &Table();
	const CsDataTable &Table() const;

	gsize Count() const;
	gbool Contains(const GString &) const;
	gint ColumnID(const GString &) const;

	CsTableField operator[](gsize) const;
	CsTableField operator[](const GString &) const;

	gbool Add(const CsTableField &);
	gbool Add(const GString &, CS_TABLE_FIELD_TYPE);
	gbool Remove(const CsTableField &);
	gbool Remove(const GString &);
	gbool RemoveAt(gsize);
	gbool Clear();

	CsTableFields &operator=(const CsTableFields &);
};

#endif // _CORE_TABLE_FIELDS_H_