#ifndef _CORE_DEFINE_H_
#define _CORE_DEFINE_H_

#if defined(_MSC_VER)
#	define CS_DECL_EXPORT __declspec(dllexport)
#	define CS_DECL_IMPORT __declspec(dllimport)
#endif // _MSC_VER

#ifndef NULL
#	define NULL	0
#endif // !NULL

//#if __cplusplus >= 201103L
#	define CS_CPP_11
//#endif

#ifndef CS_CPP_11
#	define nullptr NULL
#	define override
#	define constexpr
#	define final
#endif // for C++11

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

#define CS_BEGIN_NAMESPACE namespace CSuperNova {
#define CS_END_NAMESPACE }

#ifdef __cplusplus
#	define CS_DECLARE_NOTHROW  throw()
#endif

#  if defined (CS_CORE_BUILD_DLL)
#    define CSYSTEM_EXPORT CS_DECL_EXPORT
#  else 
#    define CSYSTEM_EXPORT CS_DECL_IMPORT
#  endif 

#define CS_API CSYSTEM_EXPORT

#if defined(_DEBUG)
#	include <assert.h>  
#	define CS_ASSERT(e) assert(e)
#else
#	define CS_ASSERT(e) do { } while ((false) && (e))
#endif // 

#define CS_DECLARE_OPERATOR_NEW_DELETE \
public: \
	static cs_pointer operator new(cs_size_t) \
		throw(std::bad_alloc); \
	static cs_void operator delete (cs_pointer);

#define CS_IMPLEMENT_OPERATOR_NEW_DELETE(Class, Lock) \
	CsMemoryPool m_gMemoryPool = CsMemoryPool(sizeof(##Class)); \
	Lock m_gLock; \
	cs_pointer Class##::operator new(cs_size_t size) \
	{ \
		CsAutoLock<##Lock> tLock(m_gLock); \
		cs_pointer pBuf = m_gMemoryPool.Alloc(); \
		if (!pBuf) \
		{ \
			throw std::bad_alloc(); \
		} \
		return pBuf; \
	} \
	cs_void Class##::operator delete(cs_pointer pFree) \
	{ \
		if (pFree == NULL) \
		{ \
			return; \
		} \
		CsAutoLock<##Lock> tLock(m_gLock); \
		m_gMemoryPool.Free(pFree); \
	} \

#define CS_IMPLEMENT_OPERATOR_NEW_DELETE_NO_SAFE(Class) \
	CsMemoryPool m_gMemoryPool = CsMemoryPool(sizeof(##Class)); \
	cs_pointer Class##::operator new(cs_size_t size) \
	{ \
		cs_pointer pBuf = m_gMemoryPool.Alloc(); \
		if (!pBuf) \
		{ \
			throw std::bad_alloc(); \
		} \
		return pBuf; \
	} \
	cs_void Class##::operator delete(cs_pointer pFree) \
	{ \
		if (pFree == NULL) \
		{ \
			return; \
		} \
		m_gMemoryPool.Free(pFree); \
	} \

#if defined (i386) || defined (__i386__) || defined (_M_IX86) || \
	defined (vax) || defined (__alpha) || defined (__LITTLE_ENDIAN__) || \
	defined (ARM) || defined (_M_IA64) || defined (_M_AMD64) || \
	defined (__amd64) || \
	((defined (__ia64__) || defined (__ia64)) && !defined (__hpux))
#	define CS_LITTLE_ENDIAN 0x0123
#	define CS_BYTE_ORDER CS_LITTLE_ENDIAN
#else
#	define CS_BIG_ENDIAN 0x3210
#	define CS_BYTE_ORDER CS_BIG_ENDIAN
#endif

#define CS_POINTER_ADDRESS_SIZE	4

#define CS_INT32_MAX 0x7fffffff
#define CS_INT64_MAX 0x7fffffffffffffffLL

#ifdef __cplusplus__
extern "C"{
#endif

#ifdef __cplusplus__
}
#endif

#endif // _CORE_DEFINE_H_
