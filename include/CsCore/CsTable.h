#ifndef _CSCORE_CSTABLE_H_
#define _CSCORE_CSTABLE_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"
#include "CsVector.h"

class CsTableField;
class CsTableFields;
class CsTableColumn;
class CsTableColumns;
class CsTableRow;
class CsTableRows;
class CsTableCell;

class CsTableField
{
public:

};

class CsTableFields
{
public:
	CsTableFields();
	~CsTableFields();

private:
	CsVector<CsTableField*> m_tFields;
};

class CsCore_Export CsTableCell
{
public:
	CsTableCell();
	~CsTableCell();

	CsObject *GetValue() const;

private:
	CsObject *m_pObject;
};

class CsCore_Export CsTableRow
{

};

class CsCore_Export CsTable
{
private:
	CsTableFields m_pFields;


public:
	enum { CLASSCODE = CORE_CLASSCODE_TABLE, };
};

#endif // _CSCORE_CSDATATABLE_H_
