#include "gbytes.h"
#include "gendian.h"
#include "gstring.h"

#define CS_BYTES_DEFAULT_ADD_SIZE 512

GBytes::GBytes(gsize nCapacity, gsize nAddSize)
: m_nAddSize(nAddSize)
{
	if (nCapacity > 0)
	{
		Reserve(nCapacity);
	}
}

GBytes::GBytes(const GBytes &tBytes)
: m_tBytes(tBytes.m_tBytes), m_nAddSize(CS_BYTES_DEFAULT_ADD_SIZE)
{
	
}

GBytes::~GBytes()
{
	
}

gbool GBytes::Reserve(gsize size)
{
	return m_tBytes.Reserve(size);
}

gbool GBytes::Resize(gsize size)
{
	return m_tBytes.Resize(size);
}

gvoid GBytes::Clear()
{
	m_tBytes.Clear();
}

gvoid GBytes::Dispose()
{
	m_tBytes.Dispose();
}

gbool GBytes::IsEmpty() const
{
	return m_tBytes.IsEmpty();
}

gsize GBytes::Size() const
{
	return m_tBytes.Size();
}

gsize GBytes::Capacity() const
{
	return m_tBytes.Capacity();
}

gbyte &GBytes::GetAt(gsize pos)
{
	return m_tBytes.GetAt(pos);
}

gbyte GBytes::GetAt(gsize pos) const
{
	return m_tBytes.GetAt(pos);
}

const gbyte *GBytes::Head() const
{
	return m_tBytes.Head();
}

gbyte *GBytes::Head()
{
	return m_tBytes.Head();
}

const gbyte *GBytes::Tail() const
{
	return m_tBytes.Tail();
}

gbyte *GBytes::Tail()
{
	return m_tBytes.Tail();
}

gbyte &GBytes::operator[](gsize pos)
{
	return m_tBytes[pos];
}

gbyte GBytes::operator[](gsize pos) const
{
	return m_tBytes[pos];
}

GBytes &GBytes::operator<<(gbool val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gchar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gschar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(guchar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gwchar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gshort val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gushort val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gint val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(guint val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(glong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gulong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(glonglong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gulonglong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gfloat val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gdouble val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(gdecimal val)
{
#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

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

GBytes &GBytes::operator<<(const GString &val)
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

GBytes &GBytes::operator>>(gbool &val)
{
	gsize value_size = sizeof(gbool);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gchar &val)
{
	gsize value_size = sizeof(gchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gschar &val)
{
	gsize value_size = sizeof(gschar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(guchar &val)
{
	gsize value_size = sizeof(guchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gwchar &val)
{
	gsize value_size = sizeof(gwchar);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gshort &val)
{
	gsize value_size = sizeof(gshort);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gushort &val)
{
	gsize value_size = sizeof(gushort);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gint &val)
{
	gsize value_size = sizeof(gint);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(guint &val)
{
	gsize value_size = sizeof(guint);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(glong &val)
{
	gsize value_size = sizeof(glong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gulong &val)
{
	gsize value_size = sizeof(gulong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(glonglong &val)
{
	gsize value_size = sizeof(glonglong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gulonglong &val)
{
	gsize value_size = sizeof(gulonglong);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gfloat &val)
{
	gsize value_size = sizeof(gfloat);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gdouble &val)
{
	gsize value_size = sizeof(gdouble);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

GBytes &GBytes::operator>>(gdecimal &val)
{
	gsize value_size = sizeof(gdecimal);
	gint new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	GMemCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = GEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

#undef CS_BYTES_DEFAULT_ADD_SIZE