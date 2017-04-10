#include "gbytebuffer.h"
#include "gendian.h"
#include "gstring.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

GByteBuffer::GByteBuffer(gsize capacity)
	: m_tBytes(capacity)
{

}

GByteBuffer::GByteBuffer(const GByteBuffer &tBytes)
	: m_tBytes(tBytes.m_tBytes)
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

gvoid GByteBuffer::Destroy()
{
	m_tBytes.Destroy();
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

guint GByteBuffer::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::ByteBuffer);
}

gbool GByteBuffer::Serialize(GArchive &archive) const
{
	return m_tBytes.Serialize(archive);
}

gbool GByteBuffer::Deserialize(GArchive &archive)
{
	return m_tBytes.Deserialize(archive);
}

} // namespace gsystem