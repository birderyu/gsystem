#ifndef _CORE_ATOMI_INLINE_
#define _CORE_ATOMI_INLINE_

#ifdef G_SYSTEM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>
#endif // G_SYSTEM_WINDOWS

template<typename T> 
GINLINE gbool GAtom::CompareAndSwap(T *target, T comperand, T exchange)
{
#ifdef G_SYSTEM_WINDOWS
	InterlockedCompareExchange(target, exchange, comperand);
	return target == exchange;
#else // !G_SYSTEM_WINDOWS
	return __sync_bool_compare_and_swap(target, comperand, exchange);
#endif // G_SYSTEM_WINDOWS
}

template<typename T> 
GINLINE T GAtom::ValuedCompareAndSwap(T *target, T comperand, T exchange)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedCompareExchange(target, exchange, comperand);
#else // !G_SYSTEM_WINDOWS
	return __sync_val_compare_and_swap(target, comperand, exchange);
#endif // G_SYSTEM_WINDOWS
}

template<typename T>
GINLINE T GAtom::IncrementAndFetch(T *var)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedIncrement(var); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_add_and_fetch(var, 1); // NOLINT
#endif // G_SYSTEM_WINDOWS
}

template<typename T> 
GINLINE T GAtom::DecrementAndFetch(T *var)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedDecrement(var); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_fetch_and_sub(var, 1); // NOLINT
#endif // G_SYSTEM_WINDOWS
}

template<typename T> 
GINLINE T GAtom::FetchAndIncrement(T *var)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedExchangeAdd(var, 1); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_add_and_fetch(var, 1); // NOLINT
#endif // G_SYSTEM_WINDOWS
}

template<typename T>
GINLINE T GAtom::FetchAndDecrement(T *var)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedExchangeSubtract(var, 1); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_sub_and_fetch(var, 1); // NOLINT
#endif // G_SYSTEM_WINDOWS
}

template<typename T> 
GINLINE T GAtom::FetchAndAdd(T *target, T value)
{
#ifdef WIN32
	return ::InterlockedExchangeAdd(target, value); // NOLINT
#else
	return __sync_fetch_and_add(target, value);  // NOLINT
#endif
}

template<typename T> 
GINLINE T GAtom::FetchAndSubtract(T *target, T value)
{
#ifdef WIN32
	return ::InterlockedExchangeSubtract(target, value); // NOLINT
#else
	return __sync_fetch_and_sub(target, value);  // NOLINT
#endif
}

template<typename T> 
GINLINE T GAtom::Exchange(T *target, T value)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedExchange(target, value); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_lock_test_and_set(target, value);  // NOLINT
#endif // G_SYSTEM_WINDOWS
}

template<typename T> 
GINLINE T GAtom::SetValue(T *target, T value)
{
#ifdef G_SYSTEM_WINDOWS
	::InterlockedExchange(target, value); // NOLINT
#else // !G_SYSTEM_WINDOWS
	__sync_lock_test_and_set(target, value);  // NOLINT
#endif // G_SYSTEM_WINDOWS
	return value;
}

template<typename T> 
GINLINE T GAtom::GetValue(T *var)
{
#ifdef G_SYSTEM_WINDOWS
	return ::InterlockedExchangeAdd(var, 0); // NOLINT
#else // !G_SYSTEM_WINDOWS
	return __sync_fetch_and_add(var, 0);  // NOLINT
#endif // G_SYSTEM_WINDOWS
}

#endif // _CORE_ATOMI_INLINE_
