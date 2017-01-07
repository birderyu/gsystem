#ifndef _CORE_STRING_LIST_H_
#define _CORE_STRING_LIST_H_

#include "gstringpool.h"
#include "gmap.h"

class GString;

enum G_STRING_TYPE
{
	STRING_TYPE_VALUE,
	STRING_TYPE_REFERENCE,
};

class GAPI GStringList
{
public:
	GString GetAt(gsize, G_STRING_TYPE emStrType = STRING_TYPE_VALUE) const;

	gbool Add(const GString &);
	gbool SetAt(gsize, const GString &);
	gbool RemoveAt(gsize);

	gsize Size() const;

	// 回收废弃不用的内存
	// 视情况不同，会占用一定的时间
	// 回收之后，引用型的String会失效
	gbool Collect();

private:
	GStringPool m_tPool;
	GMap<gsize, gpointer> m_t; // <下标，指针>
};

#endif // _CORE_STRING_LIST_H_