// 字节缓冲
// 与字节数组GByteBuffer不同的是，GByteBuffer会按照数据增长步长，预先分配内存

#ifndef _CORE_BUFFER_H_
#define _CORE_BUFFER_H_

#include "gobject.h"
#include "gstructure.h"
#include "gseries.h"

class GBytes;

#define G_BYTES_DEFAULT_CAPACITY 1024
#define G_BYTES_DEFAULT_ADD_SIZE 512

class GAPI GByteBuffer final
	: public GListT<GByteBuffer>
	, public GObject
{
	friend class GBytes;

public:
	GByteBuffer(gsize capacity = G_BYTES_DEFAULT_CAPACITY,
		gsize add_size = G_BYTES_DEFAULT_ADD_SIZE);
	GByteBuffer(const GByteBuffer &tBytes);
	~GByteBuffer();

	gvoid Reserve(gsize);
	gvoid Resize(gsize);
	gvoid Clear();
	gvoid Dispose();

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;
	
	const gbyte *Head() const;
	gbyte *Head();
	const gbyte *Tail() const;
	gbyte *Tail();

	gbyte &operator[](gsize);
	const gbyte &operator[](gsize) const;

	/*
	/// 写入二进制字节流
	GByteBuffer &operator<<(gbool);
	GByteBuffer &operator<<(gchar);
	GByteBuffer &operator<<(gschar);
	GByteBuffer &operator<<(guchar);
	GByteBuffer &operator<<(gwchar);
	GByteBuffer &operator<<(gshort);
	GByteBuffer &operator<<(gushort);
	GByteBuffer &operator<<(gint);
	GByteBuffer &operator<<(guint);
	GByteBuffer &operator<<(glong);
	GByteBuffer &operator<<(gulong);
	GByteBuffer &operator<<(glonglong);
	GByteBuffer &operator<<(gulonglong);
	GByteBuffer &operator<<(gfloat);
	GByteBuffer &operator<<(gdouble);
	GByteBuffer &operator<<(gdecimal);
	GByteBuffer &operator<<(const GString &);

	/// 从二进制字节流中写出
	GByteBuffer &operator >> (gbool &);
	GByteBuffer &operator >> (gchar &);
	GByteBuffer &operator >> (gschar &);
	GByteBuffer &operator >> (guchar &);
	GByteBuffer &operator >> (gwchar &);
	GByteBuffer &operator >> (gshort &);
	GByteBuffer &operator >> (gushort &);
	GByteBuffer &operator >> (gint &);
	GByteBuffer &operator >> (guint &);
	GByteBuffer &operator >> (glong &);
	GByteBuffer &operator >> (gulong &);
	GByteBuffer &operator >> (glonglong &);
	GByteBuffer &operator >> (gulonglong &);
	GByteBuffer &operator >> (gfloat &);
	GByteBuffer &operator >> (gdouble &);
	GByteBuffer &operator >> (gdecimal &);
	*/

private:
	GBytesData m_tBytes;
	gsize m_nAddSize;
};

#undef G_BYTES_DEFAULT_ADD_SIZE
#undef G_BYTES_DEFAULT_CAPACITY

#endif // _CORE_BUFFER_H_