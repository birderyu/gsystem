// 不可继承的类模板
#ifndef _CORE_FINAL_H_
#define _CORE_FINAL_H_

#ifdef WIN32  
template<typename TDerive, typename TProvider>
class CsFinalBase
{
	friend TDerive;
	friend TProvider;
private:
	CsFinalBase() {}
	~CsFinalBase() {}
};
#else  
template <typename T>
class CsFinalIdentity
{
public:
	typedef T me;
};

template<typename TDerive, typename TProvider>
class CsFinalBase
{
	friend class CsFinalIdentity<TDerive>::me;
	friend class CsFinalIdentity<TProvider>::me;
private:
	CsFinalBase() {}
	~CsFinalBase() {}
};
#endif 

template<typename TFinalClass>
class CsFinal 
	: virtual public CsFinalBase<TFinalClass, CsFinal<TFinalClass> >
{
public:
	CsFinal() {}
	~CsFinal() {}
};

#endif // _CORE_FINAL_H_