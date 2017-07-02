/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	grefcounter.h
** @brief	引用计数器
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gnew.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	引用计数器
**
****************************************************************************/
template <typename ClassT>
class GRefCounter 
	: public GNewT<GRefCounter<ClassT>>
{
public:
	/****************************************************************************
	**
	** @name GRefCounter
	** @brief 构造函数（constructor）
	** @param[in] count {gsize} 初始化的一个数字
	**
	** 由于GObject需要作为所有资源类的基类，因此其析构函数必须是虚拟的（virtual）。
	**
	****************************************************************************/
	GRefCounter(gsize count = 1);
	GRefCounter(const GRefCounter &refCounter);
	GRefCounter(GRefCounter &&refCounter);
	~GRefCounter();

	gsize Add();
	gsize Release();
	gsize Count() const;

private:
	ClassT *m_pPointer;
};

} // namespace gsystem

#include "inline/grefcounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_