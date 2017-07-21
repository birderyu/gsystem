#ifndef _CORE_TABLE_FIELD_H_
#define _CORE_TABLE_FIELD_H_

#include "gtableglobal.h"

template<typename TableT>
class GTableField
{
public:
	GTableField(GDataTable &, gsize column);
	GTableField(const GTableField<TableT> &);
	GTableField(GTableField<TableT> &&);

	gsize FieldID() const;
	GString FieldName() const;
};

#endif // _CORE_TABLE_FIELD_H_