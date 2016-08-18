#ifndef _CORE_DEFINE_H_
#define _CORE_DEFINE_H_

#if defined(_MSC_VER)
#	define CS_DECL_EXPORT __declspec(dllexport)
#	define CS_DECL_IMPORT __declspec(dllimport)
#endif // _MSC_VER

#ifndef NULL
#	define NULL	0
#endif // !NULL

/*
#if !defined(CXX_11) || __cplusplus < 201103
#	define nullptr NULL
#	define override
#	define constexpr
#	define final
#endif // for C++11
*/

#define CS_DECLARE_PUBLIC(Class) \
	Class *const m_pPublic; \
	inline Class* GetPublic() { return static_cast<Class *>(m_pPublic); } \
	inline const Class* GetPublic() const { return static_cast<const Class *>(m_pPublic); } \
	friend class Class;

#define CS_DECLARE_PRIVATE(Class) \
	Class##_Private *const m_pPrivate; \
	inline Class##_Private* GetPrivate() { return reinterpret_cast<Class##_Private *>(m_pPrivate); } \
	inline const Class##_Private* GetPrivate() const { return reinterpret_cast<const Class##_Private *>(m_pPrivate); } \
	friend class Class##_Private;

#define CS_PUBLIC(Class) Class *const pPublic = (Class*)GetPublic()
#define CS_PRIVATE(Class) Class##_Private *const pPrivate = (Class##_Private*)GetPrivate()

# define CS_BEGIN_NAMESPACE namespace CSYSTEM {
# define CS_END_NAMESPACE }

#  ifdef __cplusplus
#    define CS_DECL_NOTHROW  throw()
#  endif

#  if defined (CS_CORE_BUILD_DLL)
#    define CS_CORE_EXPORT CS_DECL_EXPORT
#  else 
#    define CS_CORE_EXPORT CS_DECL_IMPORT
#  endif 

//inline void cs_noop(void) {}
//CS_CORE_EXPORT void cs_assert(const char *assertion, const char *file, int line) CS_DECL_NOTHROW;

#if defined(_DEBUG)
#	include <assert.h>  
#	define CS_ASSERT(e) assert(e)
#else
#	define CS_ASSERT(e) do { } while ((false) && (e))
#endif // 

#endif // _CORE_DEFINE_H_
