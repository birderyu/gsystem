#ifndef _CORE_STRING_BUFFER_H_
#define _CORE_STRING_BUFFER_H_

#include "gobject.h"
#include "gstructure.h"
#include "gvector.h"
#include "gstring.h"

#define G_STRING_BUFFER_DEFAULT_CAPACITY 2048
#define G_STRING_BUFFER_DEFAULT_ADD_SIZE 512

class GAPI GStringBuffer
	: public GListT<GStringBuffer>
	, public GObject
{
public:
	GStringBuffer(gsize capacity = G_STRING_BUFFER_DEFAULT_CAPACITY,
		gsize add_size = G_STRING_BUFFER_DEFAULT_ADD_SIZE);
	GStringBuffer(const GString &);
	GStringBuffer(const GStringBuffer &);
	~GStringBuffer();

	gbool Reserve(gsize);
	gvoid Clear();
	gvoid Dispose();

	GStringBuffer &Append(gchar);
	GStringBuffer &Append(gcstring);
	GStringBuffer &Append(const GString &);

private:
	GVector<gchar> m_tBlock;
};

#undef G_STRING_BUFFER_DEFAULT_ADD_SIZE
#undef G_STRING_BUFFER_DEFAULT_CAPACITY

#endif // _CORE_STRING_BUFFER_H_