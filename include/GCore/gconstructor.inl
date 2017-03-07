#ifndef _CORE_CONSTRUCTOR_INLINE_
#define _CORE_CONSTRUCTOR_INLINE_

namespace GNova {
	namespace Constructor {
		namespace Private {

			template <typename ClassT>
			GINLINE gvoid _GDefaultConstruct(ClassT *ptr, GTrueType)
			{
				// 没有默认的构造函数，不调用
			}

			template <typename ClassT>
			GINLINE gvoid _GDefaultConstruct(ClassT *ptr, GFalseType)
			{
				// 有默认的构造函数，调用默认的构造函数
				new(ptr)ClassT();
			}

			template <typename ClassT>
			GINLINE gvoid __GCopyConstruct(ClassT *ptr, const ClassT &copyable, GTrueType)
			{
				// 基本类型由于编译器的优化，调用等号操作效率较高
				*ptr = copyable;
			}

			template <typename ClassT>
			GINLINE gvoid __GCopyConstruct(ClassT *ptr, const ClassT &copyable, GFalseType)
			{
				// 非基本类型调用内存拷贝
				GMemCopy(ptr, &copyable);
			}

			template <typename ClassT>
			GINLINE gvoid _GCopyConstruct(ClassT *ptr, const ClassT &copyable, GTrueType)
			{
				// 没有拷贝构造函数，此时分两种情况考虑（基本类型认为没有拷贝构造函数）
				__GCopyConstruct(ptr, copyable,
					GTypeTraits<ClassT>::Arithmetic());
			}

			template <typename ClassT>
			GINLINE gvoid _GCopyConstruct(ClassT *ptr, const ClassT &copyable, GFalseType)
			{
				// 有拷贝构造函数，调用拷贝构造函数
				new(ptr)ClassT(copyable);
			}

			template <typename ClassT>
			GINLINE gvoid __GMoveConstruct(ClassT *ptr, ClassT &&moveable, GTrueType)
			{
				// 基本类型由于编译器的优化，调用等号操作效率较高
				*ptr = moveable;
			}

			template <typename ClassT>
			GINLINE gvoid __GMoveConstruct(ClassT *ptr, ClassT &&moveable, GFalseType)
			{
				// 非基本类型调用内存拷贝
				GMemCopy(ptr, &moveable);
			}

			template <typename ClassT>
			GINLINE gvoid _GMoveConstruct(ClassT *ptr, ClassT &&moveable, GTrueType)
			{
				// 没有移动构造函数，此时分两种情况考虑（基本类型认为没有移动构造函数）
				__GMoveConstruct(ptr, GForward<ClassT>(moveable),
					GTypeTraits<ClassT>::Arithmetic());
			}

			template <typename ClassT>
			GINLINE gvoid _GMoveConstruct(ClassT *ptr, ClassT &&moveable, GFalseType)
			{
				// 有移动构造函数，调用移动构造函数，可能会退化为拷贝构造函数
				new(ptr)ClassT(GForward<ClassT>(moveable));
			}

			template <typename ClassT>
			GINLINE gvoid _GDestruct(ClassT *ptr, GTrueType)
			{

			}

			template <typename ClassT>
			GINLINE gvoid _GDestruct(ClassT *ptr, GFalseType)
			{
				ptr->~ClassT();
			}

		}
	}
}

template <typename ClassT> 
GINLINE gvoid GConstruct(ClassT *ptr)
{
	GDefaultConstruct(ptr);
}

template <typename ClassT>
GINLINE gvoid GConstruct(ClassT *ptr, const ClassT &copyable)
{
	GCopyConstruct(ptr, copyable);
}

template <typename ClassT>
GINLINE gvoid GConstruct(ClassT *ptr, ClassT &&moveable)
{
	GMoveConstruct(ptr, GForward<ClassT>(moveable));
}

template <typename ClassT>
GINLINE gvoid GDestruct(ClassT *ptr)
{
	GNova::Constructor::Private::_GDestruct(ptr,
		GTypeTraits<ClassT>::TrivialDestructible());
}

template <typename ClassT> 
GINLINE gvoid GDefaultConstruct(ClassT *ptr)
{
	static_assert(GIsDefaultConstructible<ClassT>::value,
		"this type has not a default constructor.");
	GNova::Constructor::Private::_GDefaultConstruct(ptr,
		GTypeTraits<ClassT>::TrivialDefaultConstructible());
}

template <typename ClassT> 
GINLINE gvoid GCopyConstruct(ClassT *ptr, const ClassT &copyable)
{
	static_assert(GIsCopyConstructible<ClassT>::value,
		"this type has not a copy constructor.");
	GNova::Constructor::Private::_GCopyConstruct(ptr, copyable,
		GTypeTraits<ClassT>::TrivialCopyConstructible());
}

template <typename ClassT> 
GINLINE gvoid GMoveConstruct(ClassT *ptr, ClassT &&moveable)
{
	static_assert(GIsMoveConstructible<ClassT>::value,
		"this type has not a move constructor.");
	GNova::Constructor::Private::_GMoveConstruct<ClassT>(ptr, GForward<ClassT>(moveable),
		GTypeTraits<ClassT>::TrivialMoveConstructible());
}

#endif // _CORE_CONSTRUCTOR_INLINE_