#include "CsBytes.h"
#include "CsBytes_Private.h"

CsBytes::CsBytes(const cs_size_t nBufSize)
: CsObject(new CsBytes_Private(this, nBufSize))
{

}

CsBytes::CsBytes(const CsBytes &tBytes)
: CsObject(new CsBytes_Private(this, *(CsBytes_Private*)tBytes.m_pPrivate))
{

}

cs_bool CsBytes::IsEmpty() const
{
	CS_PRIVATE(CsBytes);
	return pPrivate->IsEmpty();
}

cs_byte *CsBytes::ToCArray() const
{
	CS_PRIVATE(CsBytes);
	return pPrivate->GetBuffer();
}

CsBytes &CsBytes::operator<<(const cs_int8 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_int8>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_uint8 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_uint8>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_int16 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_int16>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_uint16 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_uint16>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_int32 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_int32>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_uint32 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_uint32>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_int64 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_int64>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_uint64 value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_uint64>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_float value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_float>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const cs_double value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<cs_double>(value);
	return *this;
}

CsBytes &CsBytes::operator<<(const CsString &value)
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator<<<CsString>(value);
	return *this;
}

const CsBytes &CsBytes::operator >> (cs_int8 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_int8>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uint8 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_uint8>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_int16 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_int16>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uint16 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_uint16>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_int32 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_int32>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uint32 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_uint32>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_int64 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_int64>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_uint64 &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_uint64>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_float &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_float>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(cs_double &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><cs_double>(value);
	return *this;
}

const CsBytes &CsBytes::operator>>(CsString &value) const
{
	CS_PRIVATE(CsBytes);
	pPrivate->operator>><CsString>(value);
	return *this;
}

