/// 二进制字节流
#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "gobject.h"
#include "gstructure.h"
#include "gvector.h"

#define G_BYTES_DEFAULT_CAPACITY 1024
#define G_BYTES_DEFAULT_ADD_SIZE 512

class GAPI GBytes final
	: public GListT<GBytes>
	, public GObject
{
public:
	GBytes(gsize nCapacity = G_BYTES_DEFAULT_CAPACITY,
		gsize nAddSize = G_BYTES_DEFAULT_ADD_SIZE);
	GBytes(const GBytes &tBytes);
	~GBytes();

	gbool Reserve(gsize);
	gbool Resize(gsize);
	gvoid Clear();
	gvoid Dispose();

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbyte &GetAt(gsize);
	gbyte  GetAt(gsize) const;
	gbyte &operator[](gsize);
	gbyte  operator[](gsize) const;

	const gbyte *Head() const;
	gbyte *Head();
	const gbyte *Tail() const;
	gbyte *Tail();

	/// 写入二进制字节流
	GBytes &operator<<(gbool);
	GBytes &operator<<(gchar);
	GBytes &operator<<(gschar);
	GBytes &operator<<(guchar);
	GBytes &operator<<(gwchar);
	GBytes &operator<<(gshort);
	GBytes &operator<<(gushort);
	GBytes &operator<<(gint);
	GBytes &operator<<(guint);
	GBytes &operator<<(glong);
	GBytes &operator<<(gulong);
	GBytes &operator<<(glonglong);
	GBytes &operator<<(gulonglong);
	GBytes &operator<<(gfloat);
	GBytes &operator<<(gdouble);
	GBytes &operator<<(gdecimal);
	GBytes &operator<<(const GString &);

	/// 从二进制字节流中写出
	GBytes &operator>>(gbool &);
	GBytes &operator>>(gchar &);
	GBytes &operator>>(gschar &);
	GBytes &operator>>(guchar &);
	GBytes &operator>>(gwchar &);
	GBytes &operator>>(gshort &);
	GBytes &operator>>(gushort &);
	GBytes &operator>>(gint &);
	GBytes &operator>>(guint &);
	GBytes &operator>>(glong &);
	GBytes &operator>>(gulong &);
	GBytes &operator>>(glonglong &);
	GBytes &operator>>(gulonglong &);
	GBytes &operator>>(gfloat &);
	GBytes &operator>>(gdouble &);
	GBytes &operator>>(gdecimal &);

private:
	// 每次增长时的步长单元
	gsize m_nAddSize;
	GVector<gbyte> m_tBytes;
};

#undef G_BYTES_DEFAULT_ADD_SIZE
#undef G_BYTES_DEFAULT_CAPACITY

#endif // _CORE_BYTES_H_