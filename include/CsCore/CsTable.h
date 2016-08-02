#ifndef _CSCORE_CSTABLE_H_
#define _CSCORE_CSTABLE_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

class CsTableField;
class CsTableFields;
class CsTableColumn;
class CsTableColumns;
class CsTableRow;
class CsTableRows;
class CsTableCell;

class CsCore_Export CsTable
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_TABLE, };
};

#endif // _CSCORE_CSDATATABLE_H_
