#ifndef _CSCORE_CSDEFINE_H_
#define _CSCORE_CSDEFINE_H_

/* 64位整型: 字面常量 */
#ifndef INT64_C
#define INT64_C(c)  c ## LL
#endif

#define	cs_true		true
#define cs_false	false

#define CS_DECL_EXPORT __declspec(dllexport)
#define CS_DECL_IMPORT __declspec(dllimport)

#ifndef NULL
#define NULL	0
#endif // !NULL

#ifndef CS_SAFE_DELETE
#define CS_SAFE_DELETE(ptr)
#endif
//{{AFX_CODEJOCK_PRIVATE
#undef CS_SAFE_DELETE
#define CS_SAFE_DELETE(ptr) \
	if (ptr) { delete ptr; ptr = NULL; }

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

#endif // _CSCORE_CSDEFINE_H_
