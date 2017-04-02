#ifndef _CORE_FUNCTIONAL_H_
#define _CORE_FUNCTIONAL_H_

#include "gutility.h"
#include "gnocopyable.h"
#include <functional>

namespace gsystem { // gsystem

template<typename FunT>
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

template<gint N>
struct GPlaceholder
{
};

template<typename T>
struct GIsPlaceholder
	: GIntegralConstant<gint, 0>
{
};

template<gint N>
struct GIsPlaceholder<GPlaceholder<N> >
	: GIntegralConstant<gint, N>
{
};

template<typename T>
struct GIsPlaceholder<const T>
	: GIsPlaceholder<T>
{
};

template<typename T>
struct GIsPlaceholder<volatile T>
	: GIsPlaceholder<T>
{
};

template<typename T>
struct GIsPlaceholder<const volatile T>
	: GIsPlaceholder<T>
{
};

template<typename RetT, typename FunT, typename... ArgTs>
class GBinder;

template<typename T>
struct GIsBindExpression
	: GFalseType {};

template<typename RetT, typename FunT, typename... ArgTs>
struct GIsBindExpression<GBinder<RetT, FunT, ArgTs...> >
	: GTrueType {};

template<typename T>
struct GIsBindExpression<const T>
	: GIsBindExpression<T>
{
};

template<typename T>
struct GIsBindExpression<volatile T>
	: GIsBindExpression<T>
{
};

template<typename T>
struct GIsBindExpression<const volatile T>
	: GIsBindExpression<T>
{
};

/*
template<typename T,
	gbool = gsystem::detail::traits::GUnrefwrap<T>::is_refwrap,
	gbool = GIsBindExpression<T>::value,
	gint = GIsPlaceholder<T>::value>
struct GSelectFixer;

template<typename T>
struct GSelectFixer<T, true, false, 0>
{
	template<typename UntupleT>
	static T::Type &Fix(T &tid, UntupleT &&)
	{
		return tid.Get();
	}
};

template<typename T>
struct GSelectFixer<T, false, true, 0>
{
	template<class UntupleT, gsize... _Jx>
	static auto Apply(T &tid, UntupleT &&u, GIntegerSequence<gsize, J...>)
		-> decltype(tid(GTupleGet<J>(Move(u))...))
	{
		return (tid(GTupleGet<J>(Move(u))...));
	}

	template<class UntupleT>
	static auto Fix(T &tid, UntupleT&& u)
		-> decltype(Apply(tid, Move(u),
			GMakeIntegerSequence<gsize, tuple_size<UntupleT>::value>()))
	{	// call a nested bind expression
		return (_Apply(tid, _STD move(u),
			make_integer_sequence<size_t, tuple_size<UntupleT>::value>()));
	}
};

template<typename T>
struct GSelectFixer<T, false, false, 0>
{	// identity fixer
	template<class UntupleT>
	static T& _Fix(T& _Tid, UntupleT&&)
	{	// pass a bound argument as an lvalue (important!)
		return (_Tid);
	}
};

template<typename T, gint J>
struct GSelectFixer<T, false, false, J>
{	// placeholder fixer
	static_assert(J > 0, "invalid is_placeholder value");

	template<class UntupleT>
	static auto _Fix(T& _Tid, UntupleT&& _Ut)
		-> decltype(_STD get<J - 1>(_STD move(_Ut)))
	{	// choose the Jth unbound argument (1-based indexing)
		return (_STD get<J - 1>(_STD move(_Ut)));
	}
};
*/

} // namespace gsystem.detail.func
} // namespace gsystem.detail

template<class FunT>
class GFunction
	: public detail::func::GGetFunctionImpl<FunT>::Type
{
private:
	typedef typename detail::func::GGetFunctionImpl<FunT>::Type BaseType;

public:
	typedef GFunction<FunT> ThisType;

public:
	GFunction() noexcept
	{

	}

	GFunction(gnullptr) noexcept
	{

	}

	template<typename FT,
		typename InvResT = typename BaseType::template GResultOfInvoking<FT &>,
		typename = typename BaseType::template GEnableIfReturnable<InvResT> >
		GFunction(FT func)
	{
		this->Reset(GMove(func));
	}

	GFunction(const ThisType &right)
	{
		this->ResetCopy(right);
	}

	GFunction(ThisType &&right)
	{
		this->ResetMove(right);
	}

	~GFunction() noexcept
	{

	}

	ThisType &operator=(const ThisType &right)
	{
		right.Swap(*this);
		return *this;
	}

	ThisType &operator=(ThisType &&right)
	{
		if (this != &right)
		{
			this->Tidy();
			this->ResetMove(GMove(right));
		}
		return *this;
	}

	template<typename FT,
		typename InvResT = typename BaseType::template GResultOfInvoking<FT &>,
		typename = typename BaseType::template GEnableIfReturnable<InvResT> >
		ThisType& operator=(FT &&func)
	{
		ThisType(GForward<FT>(func)).Swap(*this);
		return *this;
	}

	ThisType& operator=(gnullptr) noexcept
	{
		this->Tidy();
		return *this;
	}

	gvoid Swap(ThisType &right) noexcept
	{
		BaseType::Swap(right);
	}

	explicit operator bool() const noexcept
	{
		return (!IsEmpty());
	}

	const type_info &TargetType() const noexcept
	{
		return BaseType::TargetType();
	}

	template<typename FT>
	FT *Target() noexcept
	{
		return (static_cast<FT *>(const_cast<gptr>(
			BaseType::Target(typeid(FT)))));
	}

	template<typename FT>
	const FT *Target() const noexcept
	{
		return (static_cast<const FT *>(BaseType::Target(typeid(FT))));
	}
};

template<typename FunT> GINLINE
gvoid Swap(GFunction<FunT> &left, GFunction<FunT> &right) noexcept
{
	left.Swap(right);
}

template<typename FunT> GINLINE
gbool operator==(const GFunction<FunT> &func, gnullptr) noexcept
{
	return !func;
}

template<typename FunT> GINLINE
gbool operator==(gnullptr, const GFunction<FunT> &func) noexcept
{
	return !func;
}

template<typename FunT> GINLINE
gbool operator!=(const GFunction<FunT> &func, gnullptr) noexcept
{
	return !!func;
}

template<typename FunT> GINLINE
gbool operator!=(gnullptr, const GFunction<FunT> &func) noexcept
{
	return !!func;
}

} // namespace gsystem

#endif // _CORE_FUNCTIONAL_H_