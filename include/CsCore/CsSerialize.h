#ifndef _CORE_SERIALIZE_H_
#define _CORE_SERIALIZE_H_

#include "CsGlobal.h"

/// Serializeº¯Êý
template<typename ArchiveT, typename DataT>
struct CsSerializeF
	: public CsBinaryF<ArchiveT, DataT, cs_bool>
{
	cs_bool operator()(ArchiveT &archive, const DataT &v) const
	{
		return v.Serialize(archive);
	}
};

/// Deserializeº¯Êý
template<typename ArchiveT, typename DataT>
struct CsDeserializeF
	: public CsBinaryF<ArchiveT, DataT, cs_bool>
{
	cs_bool operator()(ArchiveT &archive, DataT &v) const
	{
		return v.Deserialize(archive);
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_bool>
{
	cs_bool operator()(ArchiveT &archive, const cs_bool &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_char>
{
	cs_bool operator()(ArchiveT &archive, const cs_char &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_schar>
{
	cs_bool operator()(ArchiveT &archive, const cs_schar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_uchar>
{
	cs_bool operator()(ArchiveT &archive, const cs_uchar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_wchar>
{
	cs_bool operator()(ArchiveT &archive, const cs_wchar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_short>
{
	cs_bool operator()(ArchiveT &archive, const cs_short &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_ushort>
{
	cs_bool operator()(ArchiveT &archive, const cs_ushort &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_int>
{
	cs_bool operator()(ArchiveT &archive, const cs_int &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_uint>
{
	cs_bool operator()(ArchiveT &archive, const cs_uint &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_long>
{
	cs_bool operator()(ArchiveT &archive, const cs_long &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_ulong>
{
	cs_bool operator()(ArchiveT &archive, const cs_ulong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_longlong>
{
	cs_bool operator()(ArchiveT &archive, const cs_longlong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_ulonglong>
{
	cs_bool operator()(ArchiveT &archive, const cs_ulonglong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_float>
{
	cs_bool operator()(ArchiveT &archive, const cs_float &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_double>
{
	cs_bool operator()(ArchiveT &archive, const cs_double &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct CsSerializeF<ArchiveT, cs_decimal>
{
	cs_bool operator()(ArchiveT &archive, const cs_decimal &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT, typename DataT>
struct CsSerializeF<ArchiveT, DataT*>
{
	cs_bool operator()(ArchiveT &archive, const DataT *pv) const
	{
		if (!pv)
		{
			return false;
		}
		//archive << *pv;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_bool>
{
	cs_bool operator()(ArchiveT &archive, cs_bool &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_char>
{
	cs_bool operator()(ArchiveT &archive, cs_char &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_schar>
{
	cs_bool operator()(ArchiveT &archive, cs_schar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_uchar>
{
	cs_bool operator()(ArchiveT &archive, cs_uchar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_wchar>
{
	cs_bool operator()(ArchiveT &archive, cs_wchar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_short>
{
	cs_bool operator()(ArchiveT &archive, cs_short &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_ushort>
{
	cs_bool operator()(ArchiveT &archive, cs_ushort &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_int>
{
	cs_bool operator()(ArchiveT &archive, cs_int &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_uint>
{
	cs_bool operator()(ArchiveT &archive, cs_uint &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_long>
{
	cs_bool operator()(ArchiveT &archive, cs_long &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_ulong>
{
	cs_bool operator()(ArchiveT &archive, cs_ulong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_longlong>
{
	cs_bool operator()(ArchiveT &archive, cs_longlong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_ulonglong>
{
	cs_bool operator()(ArchiveT &archive, cs_ulonglong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_float>
{
	cs_bool operator()(ArchiveT &archive, cs_float &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_double>
{
	cs_bool operator()(ArchiveT &archive, cs_double &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct CsDeserializeF<ArchiveT, cs_decimal>
{
	cs_bool operator()(ArchiveT &archive, cs_decimal &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT, typename DataT>
struct CsDeserializeF<ArchiveT, DataT*>
{
	cs_bool operator()(ArchiveT &archive, DataT *&pv) const
	{
		if (!pv)
		{
			return false;
		}
		//archive >> *pv;
		return true;
	}
};

#endif // _CORE_SERIALIZE_H_