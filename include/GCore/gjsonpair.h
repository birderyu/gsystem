/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gjsonpair.h
** @brief	Json名称/值对类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonPair
**
** Json数据的书写格式是：名称/值对。
** 名称/值对包括字段名称（在双引号中），后面写一个冒号，然后是值：
**	"firstName" : "John"
**
****************************************************************************/

#ifndef _CORE_JSON_PAIR_H_
#define _CORE_JSON_PAIR_H_

#include "gstring.h"
#include "gjsonvalue.h"

G_BEGIN_NAMESPACE
class GJsonParserMessage;
G_END_NAMESPACE

G_BEGIN_NAMESPACE

class GAPI GJsonPair
	: public GObject
{
public:
	GJsonPair();
	~GJsonPair();

	gbool Valid() const;

	GString &Key();
	const GString &Key() const;
	GJsonValue *Value();
	const GJsonValue *Value() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);
	
private:
	gvoid Dispose();
	GString m_sKey;
	GJsonValue *m_pValue;
};

G_END_NAMESPACE

#endif // _CORE_JSON_PAIR_H_