#ifndef _CORE_SERIALIZE_H_
#define _CORE_SERIALIZE_H_

#include "gglobal.h"

/// Serializeº¯Êý
template<typename ArchiveT, typename DataT>
struct GSerializeF
	: public GBinaryF<ArchiveT, DataT, gbool>
{
	gbool operator()(ArchiveT &archive, const DataT &v) const
	{
		return v.Serialize(archive);
	}
};

/// Deserializeº¯Êý
template<typename ArchiveT, typename DataT>
struct GDeserializeF
	: public GBinaryF<ArchiveT, DataT, gbool>
{
	gbool operator()(ArchiveT &archive, DataT &v) const
	{
		return v.Deserialize(archive);
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gbool>
{
	gbool operator()(ArchiveT &archive, const gbool &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gchar>
{
	gbool operator()(ArchiveT &archive, const gchar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gschar>
{
	gbool operator()(ArchiveT &archive, const gschar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, guchar>
{
	gbool operator()(ArchiveT &archive, const guchar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gwchar>
{
	gbool operator()(ArchiveT &archive, const gwchar &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gshort>
{
	gbool operator()(ArchiveT &archive, const gshort &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gushort>
{
	gbool operator()(ArchiveT &archive, const gushort &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gint>
{
	gbool operator()(ArchiveT &archive, const gint &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, guint>
{
	gbool operator()(ArchiveT &archive, const guint &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, glong>
{
	gbool operator()(ArchiveT &archive, const glong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gulong>
{
	gbool operator()(ArchiveT &archive, const gulong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, glonglong>
{
	gbool operator()(ArchiveT &archive, const glonglong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gulonglong>
{
	gbool operator()(ArchiveT &archive, const gulonglong &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gfloat>
{
	gbool operator()(ArchiveT &archive, const gfloat &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gdouble>
{
	gbool operator()(ArchiveT &archive, const gdouble &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT>
struct GSerializeF<ArchiveT, gdecimal>
{
	gbool operator()(ArchiveT &archive, const gdecimal &v) const
	{
		archive << v;
		return true;
	}
};

template<typename ArchiveT, typename DataT>
struct GSerializeF<ArchiveT, DataT*>
{
	gbool operator()(ArchiveT &archive, const DataT *pv) const
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
struct GDeserializeF<ArchiveT, gbool>
{
	gbool operator()(ArchiveT &archive, gbool &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gchar>
{
	gbool operator()(ArchiveT &archive, gchar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gschar>
{
	gbool operator()(ArchiveT &archive, gschar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, guchar>
{
	gbool operator()(ArchiveT &archive, guchar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gwchar>
{
	gbool operator()(ArchiveT &archive, gwchar &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gshort>
{
	gbool operator()(ArchiveT &archive, gshort &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gushort>
{
	gbool operator()(ArchiveT &archive, gushort &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gint>
{
	gbool operator()(ArchiveT &archive, gint &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, guint>
{
	gbool operator()(ArchiveT &archive, guint &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, glong>
{
	gbool operator()(ArchiveT &archive, glong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gulong>
{
	gbool operator()(ArchiveT &archive, gulong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, glonglong>
{
	gbool operator()(ArchiveT &archive, glonglong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gulonglong>
{
	gbool operator()(ArchiveT &archive, gulonglong &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gfloat>
{
	gbool operator()(ArchiveT &archive, gfloat &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gdouble>
{
	gbool operator()(ArchiveT &archive, gdouble &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT>
struct GDeserializeF<ArchiveT, gdecimal>
{
	gbool operator()(ArchiveT &archive, gdecimal &v) const
	{
		archive >> v;
		return true;
	}
};

template<typename ArchiveT, typename DataT>
struct GDeserializeF<ArchiveT, DataT*>
{
	gbool operator()(ArchiveT &archive, DataT *&pv) const
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