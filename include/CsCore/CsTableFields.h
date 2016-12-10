#ifndef _CORE_TABLE_FIELDS_H_
#define _CORE_TABLE_FIELDS_H_

#include "CsTableGlobal.h"

class CS_API CsTableFields
{
public:
	CsTableFields(CsDataTable &, CsIntArray *columns = NULL);
	CsTableFields(const CsTableFields &);

	CsDataTable &Table();
	const CsDataTable &Table() const;

	cs_size_t Count() const;
	cs_bool Contains(const CsString &) const;
	cs_int ColumnID(const CsString &) const;

	CsTableField operator[](cs_size_t) const;
	CsTableField operator[](const CsString &) const;

	cs_bool Add(const CsTableField &);
	cs_bool Add(const CsString &, CS_TABLE_FIELD_TYPE);
	cs_bool Remove(const CsTableField &);
	cs_bool Remove(const CsString &);
	cs_bool RemoveAt(cs_size_t);
	cs_bool Clear();

	CsTableFields &operator=(const CsTableFields &);
};

#endif // _CORE_TABLE_FIELDS_H_