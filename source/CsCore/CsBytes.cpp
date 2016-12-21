#include "CsBytes.h"
#include "CsEndian.h"
#include "CsString.h"

#define CS_BYTES_DEFAULT_ADD_SIZE 512

CsBytes::CsBytes(cs_size_t nCapacity, cs_size_t nAddSize)
: m_nHeadCursor(CS_LIST_NULL_POS)
, m_nTailCursor(CS_LIST_NULL_POS)
, m_nAddSize(nAddSize)
{
	if (nCapacity > 0)
	{
		Reserve(nCapacity);
	}
}

CsBytes::CsBytes(const CsBytes &tBytes)
: m_nHeadCursor(CS_LIST_NULL_POS)
, m_nTailCursor(CS_LIST_NULL_POS)
, m_nAddSize(CS_BYTES_DEFAULT_ADD_SIZE)
{
	cs_size_t size = tBytes.Size();
	if (size <= 0)
	{
		return;
	}
	m_tBlock.CreateFrom(tBytes.m_tBlock, tBytes.m_nHeadCursor, size);
	m_nHeadCursor = 0;
	m_nTailCursor = size;
}

CsBytes::~CsBytes()
{
	Dispose();
}

cs_bool CsBytes::Reserve(cs_size_t size)
{
	cs_size_t capacity = Capacity();
	if (size <= capacity)
	{
		// 无需扩容
		return true;
	}
	if (size - capacity < m_nAddSize)
	{
		// 按照扩容步长进行扩容
		size = capacity + m_nAddSize;
	}
	cs_size_t bytes_size = Size();
	if (!m_tBlock.Resize(size, m_nHeadCursor, bytes_size))
	{
		return false;
	}
	m_nHeadCursor = 0;
	m_nTailCursor = bytes_size;
	return true;
}

cs_void CsBytes::Clear()
{
	m_nHeadCursor = m_nTailCursor = CS_LIST_NULL_POS;
}

cs_void CsBytes::Dispose()
{
	if (!m_tBlock.Resize(0))
	{
		return;
	}
	m_nHeadCursor = m_nTailCursor = CS_LIST_NULL_POS;
}

cs_bool CsBytes::Valid() const
{
	return m_tBlock.Valid()
		&& m_nHeadCursor != CS_LIST_NULL_POS
		&& m_nTailCursor != CS_LIST_NULL_POS
		&& m_nTailCursor >= m_nHeadCursor
		&& m_nTailCursor <= m_tBlock.Size();
}

cs_bool CsBytes::IsEmpty() const
{
	return Size() == 0;
}

cs_size_t CsBytes::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTailCursor - m_nHeadCursor;
}

cs_size_t CsBytes::Capacity() const
{
	cs_size_t nMemSize = m_tBlock.Size();
	if (m_nHeadCursor == CS_LIST_NULL_POS || nMemSize <= m_nHeadCursor)
	{
		return 0;
	}
	return nMemSize - m_nHeadCursor;
}

cs_byte &CsBytes::GetAt(cs_size_t pos)
{
	CS_ASSERT(m_nHeadCursor != NULL_POS);
	return m_tBlock.GetAt(m_nHeadCursor + pos);
}

cs_byte CsBytes::GetAt(cs_size_t pos) const
{
	CS_ASSERT(m_nHeadCursor != NULL_POS);
	return m_tBlock.GetAt(m_nHeadCursor + pos);
}

cs_byte &CsBytes::operator[](cs_size_t pos)
{
	CS_ASSERT(m_nHeadCursor != NULL_POS);
	return m_tBlock[m_nHeadCursor + pos];
}

cs_byte CsBytes::operator[](cs_size_t pos) const
{
	CS_ASSERT(m_nHeadCursor != NULL_POS);
	return m_tBlock[m_nHeadCursor + pos];
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), &val, value_size);
	m_nTailCursor += value_size;
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
	CsMemoryCopy(Tail(), val.CString(), str_len);
	m_nTailCursor += str_len;
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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

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
	CsMemoryCopy(&val, Head(), value_size);
	m_nHeadCursor += value_size;

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return *this;
}

CsBytes &CsBytes::operator>>(CsString &val)
{
	// TODO
	return *this;
}

cs_byte *CsBytes::Head() const
{
	if (!Valid())
	{
		return NULL;
	}
	return (cs_byte *)m_tBlock.Cursor(m_nHeadCursor);
}

cs_byte *CsBytes::Tail() const
{
	if (!Valid())
	{
		return NULL;
	}
	return (cs_byte *)m_tBlock.Cursor(m_nTailCursor);
}

#undef CS_BYTES_DEFAULT_ADD_SIZE