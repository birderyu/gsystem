#include "CsBytes.h"
#include "CsEndian.h"
#include "CsString.h"

#define CS_BYTES_DEFAULT_ADD_SIZE 512

CsBytes::CsBytes(cs_size_t nCapacity, cs_size_t nAddSize)
: m_nAddSize(nAddSize)
{
	if (nCapacity > 0)
	{
		Reserve(nCapacity);
	}
}

CsBytes::CsBytes(const CsBytes &tBytes)
: m_tBytes(tBytes.m_tBytes), m_nAddSize(CS_BYTES_DEFAULT_ADD_SIZE)
{
	
}

CsBytes::~CsBytes()
{
	
}

cs_bool CsBytes::Reserve(cs_size_t size)
{
	return m_tBytes.Reserve(size);
}

cs_bool CsBytes::Resize(cs_size_t size)
{
	return m_tBytes.Resize(size);
}

cs_void CsBytes::Clear()
{
	m_tBytes.Clear();
}

cs_void CsBytes::Dispose()
{
	m_tBytes.Dispose();
}

cs_bool CsBytes::IsEmpty() const
{
	return m_tBytes.IsEmpty();
}

cs_size_t CsBytes::Size() const
{
	return m_tBytes.Size();
}

cs_size_t CsBytes::Capacity() const
{
	return m_tBytes.Capacity();
}

cs_byte &CsBytes::GetAt(cs_size_t pos)
{
	return m_tBytes.GetAt(pos);
}

cs_byte CsBytes::GetAt(cs_size_t pos) const
{
	return m_tBytes.GetAt(pos);
}

const cs_byte *CsBytes::Head() const
{
	return m_tBytes.Head();
}

cs_byte *CsBytes::Head()
{
	return m_tBytes.Head();
}

const cs_byte *CsBytes::Tail() const
{
	return m_tBytes.Tail();
}

cs_byte *CsBytes::Tail()
{
	return m_tBytes.Tail();
}

cs_byte &CsBytes::operator[](cs_size_t pos)
{
	return m_tBytes[pos];
}

cs_byte CsBytes::operator[](cs_size_t pos) const
{
	return m_tBytes[pos];
}

CsBytes &CsBytes::operator<<(cs_bool val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_bool);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_char val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_char);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_schar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_schar);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_uchar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_uchar);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_wchar val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_wchar);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_short val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_short);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ushort val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_ushort);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_int val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_int);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_uint val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_uint);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_long val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_long);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ulong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_ulong);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_longlong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_longlong);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_ulonglong val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_ulonglong);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_float val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_float);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_double val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_double);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(cs_decimal val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t value_size = sizeof(cs_decimal);
	cs_size_t new_size = Size() + value_size;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), &val, value_size);
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator<<(const CsString &val)
{
	cs_size_t str_len = val.Size();
	if (str_len <= 0)
	{
		return *this;
	}
	else
	{
		str_len++;
	}
	cs_size_t new_size = Size() + str_len;
	if (new_size > Capacity())
	{
		if (!Reserve(new_size))
		{
			return *this;
		}
	}
	CsMemoryCopy(m_tBytes.Tail(), val.CString(), sizeof(cs_char) * (str_len + 1));
	Resize(new_size);
	return *this;
}

CsBytes &CsBytes::operator>>(cs_bool &val)
{
	cs_size_t value_size = sizeof(cs_bool);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_char &val)
{
	cs_size_t value_size = sizeof(cs_char);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_schar &val)
{
	cs_size_t value_size = sizeof(cs_schar);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_uchar &val)
{
	cs_size_t value_size = sizeof(cs_uchar);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_wchar &val)
{
	cs_size_t value_size = sizeof(cs_wchar);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_short &val)
{
	cs_size_t value_size = sizeof(cs_short);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_ushort &val)
{
	cs_size_t value_size = sizeof(cs_ushort);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_int &val)
{
	cs_size_t value_size = sizeof(cs_int);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_uint &val)
{
	cs_size_t value_size = sizeof(cs_uint);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_long &val)
{
	cs_size_t value_size = sizeof(cs_long);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_ulong &val)
{
	cs_size_t value_size = sizeof(cs_ulong);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_longlong &val)
{
	cs_size_t value_size = sizeof(cs_longlong);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_ulonglong &val)
{
	cs_size_t value_size = sizeof(cs_ulonglong);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_float &val)
{
	cs_size_t value_size = sizeof(cs_float);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_double &val)
{
	cs_size_t value_size = sizeof(cs_double);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(cs_decimal &val)
{
	cs_size_t value_size = sizeof(cs_decimal);
	cs_int new_size = Size() - value_size;
	if (new_size < 0)
	{
		return *this;
	}
	CsMemoryCopy(&val, m_tBytes.Head(), value_size);
	m_tBytes.PopFront(value_size);

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

#undef CS_BYTES_DEFAULT_ADD_SIZE