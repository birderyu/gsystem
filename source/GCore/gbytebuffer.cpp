#include "gbytebuffer.h"
#include "gendian.h"
#include "gstring.h"

#define G_BYTES_DEFAULT_ADD_SIZE 512

GByteBuffer::GByteBuffer(gsize capacity, gsize add_size)
	: m_nAddSize(add_size)
{
	if (m_nAddSize <= 0)
	{
		m_nAddSize = G_BYTES_DEFAULT_ADD_SIZE;
	}
	if (capacity > 0)
	{
		Reserve(capacity);
	}
}

GByteBuffer::GByteBuffer(const GByteBuffer &tBytes)
	: m_tBytes(tBytes.m_tBytes), m_nAddSize(G_BYTES_DEFAULT_ADD_SIZE)
{

}

GByteBuffer::~GByteBuffer()
{

}

gvoid GByteBuffer::Reserve(gsize capacity)
{
	m_tBytes.Reserve(capacity);
}

gvoid GByteBuffer::Resize(gsize size)
{
	m_tBytes.Resize(size);
}

gvoid GByteBuffer::Clear()
{
	m_tBytes.Clear();
}

gvoid GByteBuffer::Dispose()
{
	m_tBytes.Dispose();
}

gbool GByteBuffer::IsEmpty() const
{
	return m_tBytes.IsEmpty();
}

gsize GByteBuffer::Size() const
{
	return m_tBytes.Size();
}

gsize GByteBuffer::Capacity() const
{
	return m_tBytes.Capacity();
}

gbyte &GByteBuffer::GetAt(gsize pos)
{
	return m_tBytes.GetAt(pos);
}

const gbyte &GByteBuffer::GetAt(gsize pos) const
{
	return m_tBytes.GetAt(pos);
}

const gbyte *GByteBuffer::Head() const
{
	return m_tBytes.CursorAt(0);
}

gbyte *GByteBuffer::Head()
{
	return m_tBytes.CursorAt(0);
}

const gbyte *GByteBuffer::Tail() const
{
	return m_tBytes.CursorAt(Size());
}

gbyte *GByteBuffer::Tail()
{
	return m_tBytes.CursorAt(Size());
}

gbyte &GByteBuffer::operator[](gsize pos)
{
	return m_tBytes[pos];
}

const gbyte &GByteBuffer::operator[](gsize pos) const
{
	return m_tBytes[pos];
}

/*
GByteBuffer &GByteBuffer::operator<<(gbool val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gbool);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gchar val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gchar);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gschar val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gschar);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(guchar val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(guchar);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gwchar val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gwchar);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gshort val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gshort);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gushort val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gushort);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gint val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gint);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(guint val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(guint);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(glong val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(glong);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gulong val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gulong);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(glonglong val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(glonglong);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gulonglong val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gulonglong);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gfloat val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gfloat);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gdouble val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gdouble);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(gdecimal val)
{
#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN

	gsize value_size = sizeof(gdecimal);
	gsize new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator<<(const GString &val)
{
	gsize str_len = val.Size();
	if (str_len <= 0)
	{
		return *this;
	}
	else
	{
		str_len++;
	}
	gsize new_size = Size() + str_len;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	GMemCopy(m_tBytes.Tail(), val.CString(), sizeof(gchar) * (str_len + 1));
	Resize(new_size);
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gbool &val)
{
	gsize value_size = sizeof(gbool);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gchar &val)
{
	gsize value_size = sizeof(gchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gschar &val)
{
	gsize value_size = sizeof(gschar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (guchar &val)
{
	gsize value_size = sizeof(guchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gwchar &val)
{
	gsize value_size = sizeof(gwchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gshort &val)
{
	gsize value_size = sizeof(gshort);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gushort &val)
{
	gsize value_size = sizeof(gushort);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gint &val)
{
	gsize value_size = sizeof(gint);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (guint &val)
{
	gsize value_size = sizeof(guint);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (glong &val)
{
	gsize value_size = sizeof(glong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gulong &val)
{
	gsize value_size = sizeof(gulong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (glonglong &val)
{
	gsize value_size = sizeof(glonglong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gulonglong &val)
{
	gsize value_size = sizeof(gulonglong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gfloat &val)
{
	gsize value_size = sizeof(gfloat);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gdouble &val)
{
	gsize value_size = sizeof(gdouble);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}

GByteBuffer &GByteBuffer::operator >> (gdecimal &val)
{
	gsize value_size = sizeof(gdecimal);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef G_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // G_LITTLE_ENDIAN
	return *this;
}
*/

#undef G_BYTES_DEFAULT_ADD_SIZE