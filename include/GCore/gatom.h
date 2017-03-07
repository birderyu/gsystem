// 整型的简单原子操作
#ifndef _CORE_ATOM_H_
#define _CORE_ATOM_H_

#include "gglobal.h"

/// 原子操作
/// 仅支持guint、gulong、gulonglong以及与之等价类型（如guint32、guint64）的原子操作
class GAtom
{
public:
	/// CAS操作（compare-and-swap）
	/// 将target的值与comperand比较，若相等，则将target的值替换为exchange，否则不做操作
	/// 若操作成功，则返回true，否则返回false
	/// 
	/// 由于windows下没有提供返回布尔类型的cas函数，因此在windows下其实是先调用了ValuedCompareAndSwap，再比较结果
	/// 效率上相比ValuedCompareAndSwap略有下降
	template<typename T> static gbool CompareAndSwap(T *target, T comperand, T exchange);

	/// 返回值的CAS操作（valued compare-and-swap）
	/// 将target的值与comperand比较，若相等，则将target的值替换为exchange，否则不做操作
	/// 返回target之前的值
	template<typename T> static T ValuedCompareAndSwap(T *target, T comperand, T exchange);

	/// 原子自增操作，返回新值，相当于++*var
	template<typename T> static T IncrementAndFetch(T *target);

	/// 原子自减操作，返回新值，相当于--*var
	template<typename T> static T DecrementAndFetch(T *target);

	/// 原子自增操作，返回旧值，相当于*var++
	template<typename T> static T FetchAndIncrement(T *target);

	/// 原子自减操作，返回旧值，相当于*var--
	template<typename T> static T FetchAndDecrement(T *target);

	/// FAA操作（fetch-and-add）
	/// 增加一个值到target，返回原本的值
	template<typename T> static T FetchAndAdd(T *target, T value);

	/// FAS操作（fetch-and-subtract）
	/// 从target减去一个值，返回原本的值
	template<typename T> static T FetchAndSubtract(T *target, T value);

	/// 交换值，返回旧值
	template<typename T> static T Exchange(T *target, T value);

	/// 设置值，返回新值
	/// 
	/// 由于没有提供返回新值的原子交换操作，SetValue其实是使用Exchange来实现的，因此推荐使用Exchange
	template<typename T> static T SetValue(T *target, T value);

	/// 获取值
	template<typename T> static T GetValue(T *target);
};

#include "gatom.inl"

#endif // _CORE_ATOM_H_