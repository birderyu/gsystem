#ifndef _CORE_MEMORY_POOL_INLINE_
#define _CORE_MEMORY_POOL_INLINE_

// ¶ÔÆë³¤¶È
#define G_MEMORYPOOL_ALIGNMENT 8

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace mempool { // gsystem.detail.mempool

template<gsize SIZE>
struct GAligment
{
	static const gsize value = (SIZE + (G_MEMORYPOOL_ALIGNMENT - 1)) & ~(G_MEMORYPOOL_ALIGNMENT - 1);
};

template<>
struct GAligment<1>
{
	static const gsize value = sizeof(guint16);
};

template<>
struct GAligment<2>
{
	static const gsize value = sizeof(guint16);
};

template<>
struct GAligment<3>
{
	static const gsize value = sizeof(guint32);
};

template<>
struct GAligment<4>
{
	static const gsize value = sizeof(guint32);
};

} // namespace gsystem.detail.mempool
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

template<gsize UNIT_SIZE, guint16 INIT_SIZE, guint16 GROW_SIZE>
const gsize GMemoryPool<UNIT_SIZE, INIT_SIZE, GROW_SIZE>::m_nUnitSize
	= detail::mempool::GAligment<UNIT_SIZE>::value;

} // namespace gsystem

#undef G_MEMORYPOOL_ALIGNMENT

#endif // _CORE_MEMORY_POOL_INLINE_
