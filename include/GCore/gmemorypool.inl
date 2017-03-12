#ifndef _CORE_MEMORY_POOL_INLINE_
#define _CORE_MEMORY_POOL_INLINE_

// ¶ÔÆë³¤¶È
#define G_MEMORYPOOL_ALIGNMENT 8

namespace gnova { // gnova
namespace extra { // gnova.extra
namespace mempool { // gnova.extra.mempool

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

} // namespace gnova.extra.mempool
} // namespace gnova.extra
} // namespace gnova

namespace gnova { // gnova

template<gsize UNIT_SIZE, guint16 INIT_SIZE, guint16 GROW_SIZE>
const gsize GMemoryPool<UNIT_SIZE, INIT_SIZE, GROW_SIZE>::m_nUnitSize
	= extra::mempool::GAligment<UNIT_SIZE>::value;

} // namespace gnova

#undef G_MEMORYPOOL_ALIGNMENT

#endif // _CORE_MEMORY_POOL_INLINE_
