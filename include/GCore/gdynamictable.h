/// 动态表，动态表的行数是非固定的，可以任意扩展
#ifndef _CORE_DYNAMIC_TABLE_H_
#define _CORE_DYNAMIC_TABLE_H_

#include "gobject.h"
#include "gvector.h"

namespace GNova {
	namespace DynamicTable {
		namespace Private {

			template <gsize N, typename ...TS>
			struct GTypeAt
			{
				typedef typename GTupleAt<N, GTuple<TS...> >::ValueType Type;
			};

			template <typename ...TS>
			struct GTypesStoreSize
			{
				static constexpr gsize size = GTypesTraits<TS...>::total_size;
			};

			template <typename T, typename ...TS>
			struct GTypesCursor
			{
				static constexpr gsize id = GTypeExist<T, TS...>::id - 1;
				static constexpr gsize cursor = sizeof(GTypeAt<id, TS...>::Type);
			};

		}
	}
}

template<typename ...TS>
class GDynamicTableRow
{
public:
	GDynamicTableRow()
	{

	}

public:
	//constexpr static gsize m_type_cursor[] = { 1, 2, 3 };
	//constexpr static gsize m_type_cursor[] = { GTypeExist<TS, TS...>::id... };
	constexpr static gsize m_type_cursor[] = { GNova::DynamicTable::Private::GTypesCursor<TS, TS...>::cursor... };
};

template<typename ...TS>
class GDynamicTable
	: virtual public GObject
{
public:
	typedef GDynamicTableRow<TS...> RowType;

public:
	template<typename T>
	T GetValue(gsize row, gsize column) const;

private:
	//GVector<RowType> m_tTable;
};

#endif // _CORE_DYNAMIC_TABLE_H_
