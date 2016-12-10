// 表实体
#ifndef _CORE_TABLE_EX_H_
#define _CORE_TABLE_EX_H_

#include "CsGlobal.h"
#include "CsString.h"
#include "CsTableGlobal.h"

class CS_API CsVirtualTable
{
public:
	virtual ~CsVirtualTable() = 0;

public:
	// 用户权限
	virtual cs_bool CanEditStructure() const = 0;	// 是否支持编辑表结构
	virtual cs_bool CanEditData() const = 0;		// 是否支持编辑表数据
	virtual cs_bool CanRollBack() const = 0;		// 是否支持回滚

public:
	// 元信息获取
	virtual CsString GetTableName() const = 0;
	virtual cs_size_t GetFieldCount() const = 0;
	virtual CS_TABLE_FIELD_TYPE GetFieldType(cs_size_t) const = 0;
	virtual CsString GetFieldName(cs_size_t) const = 0;
	virtual CsString GetFieldText(cs_size_t) const = 0;
	virtual cs_size_t GertFieldLength() const = 0;
	virtual cs_int GetFieldID(const CsString &) const = 0;
	virtual cs_size_t GetRecordCount() const = 0;
	virtual cs_bool HasGeometry() const = 0;
	virtual cs_size_t GetGeometryFieldID() const = 0;

public:
	// 表结构编辑
	virtual cs_bool SetTableName(const CsString &) = 0;

	virtual cs_bool StartEditStructure() = 0;
	virtual cs_bool SetFieldCount(cs_size_t) = 0;
	virtual cs_bool SetFieldType(cs_size_t, CS_TABLE_FIELD_TYPE) const = 0;
	virtual cs_bool SetFieldName(cs_size_t, const CsString &) = 0;
	virtual cs_bool SetFieldAlias(cs_size_t, const CsString &) = 0;
	virtual cs_bool SertFieldLength(cs_size_t, cs_size_t) = 0;
	virtual cs_bool EndEditStructure(cs_bool) = 0;

public:
	// 数据访问
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_bool &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_char &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_schar &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_uchar &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_wchar &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col,  cs_short &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ushort &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_int &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_uint &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_long &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ulong &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_longlong &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_ulonglong &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_float &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_double &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, cs_decimal &) const = 0;
	virtual cs_bool GetValue(cs_size_t row, cs_size_t col, CsString &) const = 0;
	virtual CsVariant GetValue(cs_size_t row, cs_size_t col) const = 0;

public:
	// 数据编辑
	virtual cs_bool StartEditData() = 0;
	virtual cs_bool SetRecordCount(cs_size_t) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_bool) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_char) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_schar) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_uchar) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_wchar) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_short) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ushort) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_int) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_uint) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_long) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ulong) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_longlong) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_ulonglong) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_float) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_double) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, cs_decimal) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, const CsString &) = 0;
	virtual cs_bool SetValue(cs_size_t row, cs_size_t col, const CsVariant &) = 0;
	virtual cs_bool EndEditData(cs_bool) = 0;
};

#endif //_CORE_TABLE_EX_H_