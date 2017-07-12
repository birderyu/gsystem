/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file grefcounter.h
** @brief 引用计数器
** @author birderyu
** @contact https://github.com/birderyu
** @date 2015-12-31
** @version 1.0.0
**
****************************************************************************/

#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gnew.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief 引用计数器
** @template ClassT 类
**
****************************************************************************/
template <typename ClassT>
class GRefCounter 
	: public GNewT<GRefCounter<ClassT>>
{
public:
	GRefCounter(ClassT *ptr, gsize count = 1);
	GRefCounter(const GRefCounter &refCounter);
	GRefCounter(GRefCounter &&refCounter);
	~GRefCounter();

	gsize Add();
	gvoid Release();
	gsize Count() const;

	ClassT *Pointer();
	const ClassT *Pointer() const;

private:
	ClassT *m_pPointer;
	gsize m_nCount;
};

} // namespace gsystem

#include "inline/grefcounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_