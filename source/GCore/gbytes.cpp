#include "gbytes.h"
#include "gbytebuffer.h"

GBytes::GBytes()
{

}

GBytes::GBytes(const gbyte *bytes, gsize size)
	: m_tBytes(bytes, size)
{

}

GBytes::GBytes(const GBytes &bytes)
	: m_tBytes(bytes.m_tBytes)
{

}

GBytes::GBytes(GBytes &&bytes)
	: m_tBytes(GMove(bytes.m_tBytes))
{

}

GBytes::GBytes(const GByteBuffer &bytes)
	: m_tBytes(bytes.m_tBytes)
{
	
}

GBytes::GBytes(GByteBuffer &&bytes)
	: m_tBytes(GMove(bytes.m_tBytes))
{
	
}

gvoid GBytes::Reserve(gsize capacity)
{
	m_tBytes.Reserve(capacity);
}

gvoid GBytes::Resize(gsize size)
{
	m_tBytes.Resize(size);
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

const gbyte &GBytes::GetAt(gsize pos) const
{
	return m_tBytes.GetAt(pos);
}

gbyte *GBytes::CursorAt(gsize pos)
{
	return m_tBytes.CursorAt(pos);
}

const gbyte *GBytes::CursorAt(gsize pos) const
{
	return m_tBytes.CursorAt(pos);
}

const gbyte *GBytes::Head() const
{
	return m_tBytes.CursorAt(0);
}

gbyte *GBytes::Head()
{
	return m_tBytes.CursorAt(0);
}

const gbyte *GBytes::Tail() const
{
	return m_tBytes.CursorAt(Size());
}

gbyte *GBytes::Tail()
{
	return m_tBytes.CursorAt(Size());
}

GBytes &GBytes::operator=(const GBytes &bytes)
{
	if (this == &bytes)
	{
		return *this;
	}
	m_tBytes = bytes.m_tBytes;
	return *this;
}

GBytes &GBytes::operator=(GBytes &&bytes)
{
	if (this == &bytes)
	{
		return *this;
	}
	m_tBytes = GForward<GBytesData>(bytes.m_tBytes);
	return *this;
}

GBytes &GBytes::operator=(const GByteBuffer &bytes)
{
	m_tBytes = bytes.m_tBytes;
	return *this;
}

GBytes &GBytes::operator=(GByteBuffer &&bytes)
{
	m_tBytes = GForward<GBytesData>(bytes.m_tBytes);
	return *this;
}

gbyte &GBytes::operator[](gsize pos)
{
	return m_tBytes[pos];
}

const gbyte &GBytes::operator[](gsize pos) const
{
	return m_tBytes[pos];
}

#undef G_BYTES_DEFAULT_ADD_SIZE