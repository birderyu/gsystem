#ifndef _CORE_ATOMIC_H_
#define _CORE_ATOMIC_H_

#include "glockguard.h"

#define G_USE_STD_ATOMIC

#ifdef G_USE_STD_ATOMIC
#include <atomic>
#include "gquicklock.h"
#else // !G_USE_STD_ATOMIC
#include "gquicklock.h"
#endif // G_USE_STD_ATOMIC

template <typename ElemT, typename LockT>
class GAtomic_Ex;

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
	GAtomic_Ex<ElemT, LockT> m_tAtomic_Ex;
	LockT m_tLock;
#endif // G_USE_STD_ATOMIC
};

// 原子类型实现类
template <typename ElemT, typename LockT>
class GAtomic_Ex
{
public:
	typedef typename GTypeTraits<ElemT>::ParameterType ValueType;

public:
	GAtomic_Ex(LockT &);
	GAtomic_Ex(LockT &, ValueType);
	GAtomic_Ex(const GAtomic_Ex<ElemT, LockT>&);

	GAtomic_Ex<ElemT, LockT> &operator=(ValueType);
	GAtomic_Ex<ElemT, LockT> &operator=(const GAtomic_Ex<ElemT, LockT> &);
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
	LockT &GetLock();

private:
	LockT &m_rLock;
	ElemT m_tValue;
};

#include "gatomic.inl"

#endif // _CORE_ATOMIC_H_