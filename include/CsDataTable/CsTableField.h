#ifndef _CORE_TABLE_FIELD_H_
#define _CORE_TABLE_FIELD_H_

#include "CsTableGlobal.h"

class GAPI CsTableField
{
public:
	CsTableField(CsDataTable &, gsize column);
	CsTableField(const CsTableField &);

	gsize FieldID() const;
	GString FieldName() const;
};

#endif // _CORE_TABLE_FIELD_H_