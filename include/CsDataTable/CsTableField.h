#ifndef _CORE_TABLE_FIELD_H_
#define _CORE_TABLE_FIELD_H_

#include "CsTableGlobal.h"

class CS_API CsTableField
{
public:
	CsTableField(CsDataTable &, cs_size_t column);
	CsTableField(const CsTableField &);

	cs_size_t FieldID() const;
	CsString FieldName() const;
};

#endif // _CORE_TABLE_FIELD_H_