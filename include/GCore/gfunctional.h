#ifndef _CORE_FUNCTIONAL_H_
#define _CORE_FUNCTIONAL_H_

#include "gutility.h"
#include "gnocopyable.h"

namespace gsystem { // gsystem

template<typename _Fty>
class GFunction;

namespace detail { // gsystem.detail
namespace func { // gsystem.detail.func

template<typename T> GINLINE
gbool GTestCallable(const T &arg, GTrueType) noexcept
{
	return (!!arg);
}

template<typename T> GINLINE
gbool GTestCallable(const T &, GFalseType) noexcept
{
	return (true);
}

template<typename T> GINLINE
gbool GTestCallable(const T &arg) noexcept
{
	GCatBase<GIsMemberPointer<T>::value || (GIsPointer<T>::value
		&& GIsFunction<typename GRemovePointer<T>::Type>::value)> testable;
	return (GTestCallable(arg, testable));
}

template<typename T> GINLINE
gbool GTestCallable(const GFunction<T> &arg) noexcept
{
	return (!!arg);
}

const gint _num_ptrs_ = 6 + 16 / sizeof (gptr);
const gsize _space_size_ = (_num_ptrs_ - 1) * sizeof (gptr);

template<typename ImplT>
struct GIsLarge
	: GBoolConstant < _space_size_ < sizeof(ImplT)
	|| !ImplT::_Nothrow_move::value> {};

template<typename RetT, typename... ArgTs>
class GFunctionBase
	: private GNocopyable
{
public:
	virtual GFunctionBase<RetT, ArgTs...> *Copy(gptr) const = 0;
	virtual GFunctionBase<RetT, ArgTs...> *Move(gptr) = 0;
	virtual RetT DoCall(ArgTs&&...) = 0;
	virtual gvoid DeleteThis(gbool) noexcept = 0;

	virtual const type_info &TargetType() const noexcept = 0;
	const gptr Target(const type_info &info) const noexcept
	{
		return (TargetType() == info ? Get() : 0);
	}

private:
	virtual gcptr Get() const noexcept = 0;
};

template<typename CallableT, typename RetT, typename... ArgTs>
class GFunctionImpl final
	: public GFunctionBase<RetT, ArgTs...>
{
public:
	typedef GFunctionImpl<CallableT, RetT, ArgTs...> ThisType;
	typedef GFunctionBase<RetT, ArgTs...> BaseType;
	typedef GIsNothrowMoveConstructible<CallableT> NothrowMove;

	GFunctionImpl(CallableT &&callable)
		: m_tCallable(GForward<CallableT>(callable))
	{

	}

	~GFunctionImpl() noexcept
	{

	}

private:
	virtual BaseType *Copy(gptr where) const
	{
		return (Clone(where, GIsLarge<ThisType>()));
	}

	template<typename VoidT>
	BaseType *Clone(VoidT *, GTrueType) const
	{
		ThisType *ptr = GAllocate<ThisType>();
		try
		{
			GCopyConstruct<ThisType>(ptr, Callee());
		}
		catch (...)
		{
			GDeallocate<ThisType>(ptr);
			throw;
		}
		return ptr;
	}

	template<typename VoidT>
	BaseType *Clone(VoidT *where, GFalseType) const
	{
		ThisType *ptr = static_cast<ThisType *>(where);
		GCopyConstruct<ThisType>(ptr, Callee());
		return ptr;
	}

	virtual BaseType *Move(gptr where)
	{
		ThisType *ptr = static_cast<ThisType *>(where);
		GConstruct<ThisType>(ptr, GMove(Callee()));
		return ptr;
	}

	virtual RetT DoCall(ArgTs&&... args)
	{
		return (gsystem::detail::traits::GInvokeRet(
			gsystem::detail::traits::GForced<RetT>(), 
			Callee(),
			GForward<ArgTs>(args)...));
	}

	virtual const type_info &TargetType() const noexcept
	{
		return typeid(CallableT);
	}

	virtual gptr Get() const noexcept
	{
		return GAddressOf(Callee());
	}

	virtual gvoid DeleteThis(gbool deallocate) noexcept
	{
		GDestruct<ThisType>(this);
		if (deallocate)
		{
			GDeallocate<ThisType>(this);
		}
	}

	CallableT m_tCallable;

	CallableT& Callee() noexcept
	{
		return m_tCallable;
	}

	const CallableT& Callee() const noexcept
	{
		return m_tCallable;
	}
};

template<typename RetT, typename... ArgTs>
class GFunctionClass
	: public gsystem::detail::traits::GArgTypes<ArgTs...>
{
public:
	typedef RetT ResultType;
	typedef GFunctionClass<RetT, ArgTs...> ThisType;
	typedef GFunctionBase<RetT, ArgTs...> PtrType;

	GFunctionClass() noexcept
	{
		Set(GNULL);
	}

	~GFunctionClass() noexcept
	{
		Tidy();
	}

	RetT operator()(ArgTs... args) const
	{
		if (IsEmpty())
			throw "there is nothing to call.";
		return (GetImpl()->DoCall(GForward<ArgTs>(args)...));
	}

protected:
	template<typename T>
	using GResultOfInvoking = GResultOf<T(ArgTs...)>;

	template<typename T>
	using GEnableIfReturnable = GEnableIf<
		GIsConvertible<T, RetT>::value || GIsVoid<RetT>::value>;

	gbool IsEmpty() const noexcept
	{
		return (GetImpl() == GNULL);
	}

	gvoid ResetCopy(const ThisType &right)
	{
		if (!right.IsEmpty())
		{
			Set(right.GetImpl()->Copy(GetSpace()));
		}
	}

	gvoid ResetMove(ThisType && right)
	{
		if (right.IsEmpty())
		{

		}
		else if (right.IsLocal())
		{
			Set(right.GetImpl()->Move(GetSpace()));
			right.Tidy();
		}
		else
		{
			Set(right.GetImpl());
			right.Set(GNULL);
		}
	}

	template<typename T>
	gvoid Reset(T &&val)
	{
		ResetAlloc(GForward<T>(val));
	}

	template<typename T>
	gvoid ResetAlloc(T &&val)
	{
		if (!GTestCallable(val))
		{
			return;
		}

		typedef typename GDecay<FT>::Type DecayedT;
		typedef GFunctionImpl<DecayedT, RetT, ArgTs...> MyImpl;
		MyImpl *ptr = 0;

		typedef _Wrap_alloc<_Alloc> _Alimpl0;
		typedef typename _Alimpl0::template rebind<MyImpl>::other _Alimpl;
		_Alimpl _Al(_Ax);

		ResetImpl(GForward<T>(val), ptr, GIsLarge<MyImpl>());
	}

	template<typename T, typename ImplT>
	gvoid ResetImpl(T &&val, ImplT *, GTrueType)
	{
		ImplT *ptr = GAllocate<ImplT>();
		try 
		{
			GConstruct<ImplT>(ptr, GForward<T>(val));
		}
		catch (...)
		{
			GDeallocate<ImplT>(ptr);
			throw;
		}
		Set(ptr);
	}

	template<typename T, typename ImplT>
	gvoid ResetImpl(T &&val, GFalseType)
	{
		ImplT *ptr = static_cast<ImplT *>(GetSpace());
		GConstruct<ImplT>(ptr, GForward<T>(val));
		Set(ptr);
	}

	gvoid Tidy() noexcept
	{
		if (!IsEmpty())
		{
			GetImpl()->DeleteThis(!IsLocal());
			Set(GNULL);
		}
	}

	gvoid Swap(ThisType &right) noexcept
	{
		if (!IsLocal() && !right.IsLocal())
		{
			PtrType *temp = GetImpl();
			Set(right.GetImpl());
			right.Set(temp);
		}
		else
		{
			ThisType temp;
			temp.ResetMove(GMove(*this));
			ResetMove(GMove(right));
			right.ResetMove(GMove(temp));
		}
	}

	const type_info &TargetType() const noexcept
	{
		return (GetImpl() ? GetImpl()->TargetType() : typeid(gvoid));
	}

	gcptr Target(const type_info &info) const noexcept
	{
		return (GetImpl() ? GetImpl()->Target(info) : GNULL);
	}

private:
	gbool IsLocal() const noexcept
	{
		return (GetImpl() == GetSpace());
	}

	union Storage
	{
		gmaxalign m_tDummy1;
		gbyte m_tDummy2[_space_size_];
		PtrType *m_pPtrs[_num_ptrs_];
	};

	Storage m_tStorage;
	enum { _EEN_IMPL = _num_ptrs_ - 1 };
	PtrType *GetImpl() const noexcept
	{
		return (m_tStorage.m_pPtrs[_num_ptrs_ - 1]);
	}

	gvoid Set(PtrType *ptr) noexcept
	{
		m_tStorage.m_pPtrs[_num_ptrs_ - 1] = ptr;
	}

	gptr GetSpace() noexcept
	{
		return &m_tStorage;
	}

	gcptr GetSpace() const noexcept
	{
		return &m_tStorage;
	}
};

template<typename T>
struct GGetFunctionImpl
{

};

#define G_GET_FUNCTION_IMPL(CALL_OPT, X1, X2) \
	template<typename RetT, class... ArgTs> \
	struct GGetFunctionImpl<RetT CALL_OPT (ArgTs...)> \
	{ \
	typedef GFunctionClass<RetT, ArgTs...> Type; \
	};
G_NON_MEMBER_CALL(G_GET_FUNCTION_IMPL, , )
#undef G_GET_FUNCTION_IMPL

} // namespace gsystem.detail.func
} // namespace gsystem.detail

/// std::function
template<class _Fty>
class GFunction
	: public detail::func::GGetFunctionImpl<_Fty>::Type
{
private:
	typedef typename detail::func::GGetFunctionImpl<_Fty>::Type _Mybase;

public:
	typedef GFunction<_Fty> _Myt;

public:
	GFunction() noexcept
	{

	}

	GFunction(gnullptr) noexcept
	{

	}

	template<typename FT,
		typename InvResT = typename _Mybase::template GResultOfInvoking<FT &>,
		typename = typename _Mybase::template GEnableIfReturnable<InvResT> >
	GFunction(FT func)
	{
		this->Reset(GMove(func));
	}

	GFunction(const _Myt &right)
	{
		this->ResetCopy(right);
	}

	GFunction(_Myt &&right)
	{
		this->ResetMove(right);
	}

	~GFunction() noexcept
	{

	}

	_Myt &operator=(const _Myt &right)
	{
		right.Swap(*this);
		return *this;
	}

	_Myt &operator=(_Myt &&right)
	{
		if (this != &right)
		{
			this->Tidy();
			this->ResetMove(GMove(right));
		}
		return *this;
	}

	template<typename FT,
		typename InvResT = typename _Mybase::template GResultOfInvoking<FT &>,
		typename = typename _Mybase::template GEnableIfReturnable<InvResT> >
	_Myt& operator=(FT &&func)
	{
		_Myt(GForward<FT>(func)).Swap(*this);
		return *this;
	}

	_Myt& operator=(gnullptr) noexcept
	{
		this->Tidy();
		return *this;
	}
};

} // namespace gsystem

#endif // _CORE_FUNCTIONAL_H_