/// 数据表

#ifndef _CORE_DATA_TABLE_H_
#define _CORE_DATA_TABLE_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

enum CS_FIELD_TYPE
{
	FIELD_TYPE_ILLEGAL = -1,
};

class CsField
{
public:
	CsField(const CsString &sFieldName, CS_FIELD_TYPE emFieldType);
	const CsString &GetFieldName() const;
	FIELD_TYPE_ILLEGAL GetFieldType() const;
};

class CsFields
{
public:
	CsFields();
	~CsFields();
	cs_bool Add(const CsField&);
	cs_size_t Count() const;
	const CsField &operator[](cs_size_t) const;
	CsField &operator[](cs_size_t);
	const CsField &operator[](const CsString&) const;
	CsField &operator[](const CsString&);
};

class CsRecord
{
public:
	CsRecord(CsTable *pTable, const cs_long nRow);
};

class CS_CORE_EXPORT CsTable
{
public:
	CsTable();
	CsTable(const CsFields &sFields);
	cs_bool SetFields(const CsFields &sFields);
	const CsFields &GetFields() const;

	/// 预分配行数
	cs_bool Resize(const cs_size_t row) const;


	cs_size_t GetColumnCount() const;
	cs_size_t GetRowCount() const;

	CsVariant &GetValue(const cs_size_t row, const cs_size_t col);
	cs_bool SetValue(const cs_size_t row, const cs_size_t col, const CsVariant &val);

public:
	enum { CLASSCODE = CORE_CLASSCODE_TABLE, };
};

#endif // _CSCORE_CSDATATABLE_H_
