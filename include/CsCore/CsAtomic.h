#ifndef _CORE_ATOMIC_H_
#define _CORE_ATOMIC_H_

#include "CsLockGuard.h"

//#define CS_USE_STD_ATOMIC

#ifdef CS_USE_STD_ATOMIC
#include <atomic>
#include "CsMutex.h"
#else
#include "CsMutex.h"
#endif

template <typename ElemT, typename LockT>
class CsAtomic_Ex;

// 原子类型
template <typename ElemT, typename LockT = CsMutex>
class CsAtomic
{
public:
	typedef typename CsTraits<ElemT>::ParameterType ValueType;

public:
	CsAtomic();
	CsAtomic(ValueType);
	CsAtomic(const CsAtomic<ElemT, LockT> &);

	CsAtomic<ElemT, LockT> &operator=(ValueType);
	CsAtomic<ElemT, LockT> &operator=(const CsAtomic<ElemT, LockT> &);
	ElemT operator++();
	ElemT operator++(cs_int);
	ElemT operator+=(ValueType);
	ElemT operator--();
	ElemT operator--(cs_int);
	ElemT operator-=(ValueType);
	cs_bool operator==(ValueType) const;
	cs_bool operator!=(ValueType) const;
	cs_bool operator>=(ValueType) const;
	cs_bool operator>(ValueType) const;
	cs_bool operator<=(ValueType) const;
	cs_bool operator<(ValueType) const;
	ElemT GetValue() const;
	cs_void SetValue(ValueType);
#ifndef CS_USE_STD_ATOMIC
	LockT &GetLock();
#endif // !CS_USE_STD_ATOMIC

private:
#ifdef CS_USE_STD_ATOMIC
	std::atomic<ElemT> m_tValue;
#else
	CsAtomic_Ex<ElemT, LockT> m_tAtomic_Ex;
	LockT m_tLock;
#endif
};

// 原子类型实现类
template <typename ElemT, typename LockT>
class CsAtomic_Ex
{
public:
	typedef typename CsTraits<ElemT>::ParameterType ValueType;

public:
	CsAtomic_Ex(LockT &);
	CsAtomic_Ex(LockT &, ValueType);
	CsAtomic_Ex(const CsAtomic_Ex<ElemT, LockT>&);

	CsAtomic_Ex<ElemT, LockT> &operator=(ValueType);
	CsAtomic_Ex<ElemT, LockT> &operator=(const CsAtomic_Ex<ElemT, LockT> &);
	ElemT operator++();
	ElemT operator++(cs_int);
	ElemT operator+=(ValueType);
	ElemT operator--();
	ElemT operator--(cs_int);
	ElemT operator-=(ValueType);
	cs_bool operator==(ValueType) const;
	cs_bool operator!=(ValueType) const;
	cs_bool operator>=(ValueType) const;
	cs_bool operator>(ValueType) const;
	cs_bool operator<=(ValueType) const;
	cs_bool operator<(ValueType) const;
	ElemT GetValue() const;
	cs_void SetValue(ValueType);
	LockT &GetLock();

private:
	LockT &m_rLock;
	ElemT m_tValue;
};

#include "CsAtomic.inl"

#endif // _CORE_ATOMIC_H_