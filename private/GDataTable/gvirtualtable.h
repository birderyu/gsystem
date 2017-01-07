// 虚拟表实例
#ifndef _CORE_TABLE_EX_H_
#define _CORE_TABLE_EX_H_

#include "GCore/gglobal.h"
#include "GCore/gstring.h"
#include "gtableglobal.h"

class GAPI GVirtualTable
{
public:
	virtual ~GVirtualTable() = 0;

public:
	// 用户权限
	virtual gbool CanEditStructure() const = 0;	// 是否支持编辑表结构
	virtual gbool CanEditData() const = 0;		// 是否支持编辑表数据
	virtual gbool CanRollBack() const = 0;		// 是否支持回滚

public:
	// 元信息获取
	virtual GString GetTableName() const = 0;
	virtual gsize GetFieldCount() const = 0;
	virtual G_TABLE_FIELD_TYPE GetFieldType(gsize) const = 0;
	virtual GString GetFieldName(gsize) const = 0;
	virtual GString GetFieldText(gsize) const = 0;
	virtual gsize GertFieldLength() const = 0;
	virtual gint GetFieldID(const GString &) const = 0;
	virtual gsize GetRecordCount() const = 0;
	virtual gbool HasGeometry() const = 0;
	virtual gsize GetGeometryFieldID() const = 0;

public:
	// 表结构编辑
	virtual gbool SetTableName(const GString &) = 0;

	virtual gbool StartEditStructure() = 0;
	virtual gbool SetFieldCount(gsize) = 0;
	virtual gbool SetFieldType(gsize, G_TABLE_FIELD_TYPE) const = 0;
	virtual gbool SetFieldName(gsize, const GString &) = 0;
	virtual gbool SetFieldAlias(gsize, const GString &) = 0;
	virtual gbool SertFieldLength(gsize, gsize) = 0;
	virtual gbool EndEditStructure(gbool) = 0;

public:
	// 数据访问
	virtual gbool GetValue(gsize row, gsize col, gbool &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gschar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, guchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gwchar &) const = 0;
	virtual gbool GetValue(gsize row, gsize col,  gshort &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gushort &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gint &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, guint &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, glong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gulong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, glonglong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gulonglong &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gfloat &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gdouble &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, gdecimal &) const = 0;
	virtual gbool GetValue(gsize row, gsize col, GString &) const = 0;
	virtual GVariant GetValue(gsize row, gsize col) const = 0;

public:
	// 数据编辑
	virtual gbool StartEditData() = 0;
	virtual gbool SetRecordCount(gsize) = 0;
	virtual gbool SetValue(gsize row, gsize col, gbool) = 0;
	virtual gbool SetValue(gsize row, gsize col, gchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gschar) = 0;
	virtual gbool SetValue(gsize row, gsize col, guchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gwchar) = 0;
	virtual gbool SetValue(gsize row, gsize col, gshort) = 0;
	virtual gbool SetValue(gsize row, gsize col, gushort) = 0;
	virtual gbool SetValue(gsize row, gsize col, gint) = 0;
	virtual gbool SetValue(gsize row, gsize col, guint) = 0;
	virtual gbool SetValue(gsize row, gsize col, glong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gulong) = 0;
	virtual gbool SetValue(gsize row, gsize col, glonglong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gulonglong) = 0;
	virtual gbool SetValue(gsize row, gsize col, gfloat) = 0;
	virtual gbool SetValue(gsize row, gsize col, gdouble) = 0;
	virtual gbool SetValue(gsize row, gsize col, gdecimal) = 0;
	virtual gbool SetValue(gsize row, gsize col, const GString &) = 0;
	virtual gbool SetValue(gsize row, gsize col, const GVariant &) = 0;
	virtual gbool EndEditData(gbool) = 0;
};

#endif //_CORE_TABLE_EX_H_