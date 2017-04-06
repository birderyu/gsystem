#ifndef _CONCURRENT_ATOMIC_H_
#define _CONCURRENT_ATOMIC_H_

#include "GCore/glockguard.h"

#define G_USE_STD_ATOMIC

#ifdef G_USE_STD_ATOMIC
#include <atomic>
#include "gquicklock.h"
#else // !G_USE_STD_ATOMIC
#include "gquicklock.h"
#endif // G_USE_STD_ATOMIC

namespace gsystem { // gsystem
	namespace sync { // gsystem.sync
		namespace detail { // gsystem.sync.detail
			namespace atom { // gsystem.sync.detail.atom
				template <typename ElemT, typename LockT>
				class GAtomic_Ex;
			} // namespace gsystem.sync.detail.atom
		} // namespace gsystem.sync.detail
	} // namespace gsystem.sync
} // namespace gsystem

namespace gsystem { // gsystem
namespace sync { // gsystem.sync

// 原子操作类型
// 原子操作类型与无锁类型并非完全等价
// 通过函数IsLockFree判断当前原子操作类型是否是无锁类型
template <typename ElemT, typename LockT = GQuickLock>
class GAtomic
{
public:
	typedef typename GTypeTraits<ElemT>::ParameterType ValueType;

public:
	GAtomic();
	GAtomic(ValueType);
	GAtomic(const GAtomic<ElemT, LockT> &);

	GAtomic<ElemT, LockT> &operator=(ValueType);
	GAtomic<ElemT, LockT> &operator=(const GAtomic<ElemT, LockT> &);
	ElemT operator++();
	ElemT operator++(gint);
	ElemT operator+=(ValueType);
	ElemT operator--();
	ElemT operator--(gint);
	ElemT operator-=(ValueType);
	gbool operator==(ValueType) const;
	gbool operator!=(ValueType) const;
	gbool operator>=(ValueType) const;
	gbool operator>(ValueType) const;
	gbool operator<=(ValueType) const;
	gbool operator<(ValueType) const;
	ElemT GetValue() const;
	gvoid SetValue(ValueType);
#ifndef G_USE_STD_ATOMIC
	LockT &GetLock();
#endif // !G_USE_STD_ATOMIC

private:
#ifdef G_USE_STD_ATOMIC
	std::atomic<ElemT> m_tValue;
#else // !G_USE_STD_ATOMIC
	detail::atom::GAtomic_Ex<ElemT, LockT> m_tAtomic_Ex;
	LockT m_tLock;
#endif // G_USE_STD_ATOMIC
};

} // namespace gsystem.sync
} // namespace gsystem

#include "gatomic.inl"

#endif // _CONCURRENT_ATOMIC_H_