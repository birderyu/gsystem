// ���ɼ̳е���ģ��
#ifndef _CORE_FINAL_H_
#define _CORE_FINAL_H_

#ifdef WIN32  
template<typename TDerive, typename TProvider>
class GFinalBase
{
	friend TDerive;
	friend TProvider;
private:
	GFinalBase() {}
	~GFinalBase() {}
};
#else  
template <typename T>
class CsFinalIdentity
{
public:
	typedef T me;
};

template<typename TDerive, typename TProvider>
class GFinalBase
{
	friend class CsFinalIdentity<TDerive>::me;
	friend class CsFinalIdentity<TProvider>::me;
private:
	GFinalBase() {}
	~GFinalBase() {}
};
#endif 

template<typename TFinalClass>
class GFinal 
	: virtual public GFinalBase<TFinalClass, GFinal<TFinalClass> >
{
public:
	GFinal() {}
	~GFinal() {}
};

#endif // _CORE_FINAL_H_