/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gmutex.h
** @brief	改文件包含了互斥锁类的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/
#ifndef _CORE_MUTEX_H_
#define _CORE_MUTEX_H_

#include "glock.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief 互斥锁的定义
** 
** 互斥锁（mutex）属于内核对象，它能够确保线程拥有对单个资源的互斥访问权。需要注意的是，在
** Windows下，互斥锁是可递归的（可重入的，reentrant），而pthread_mutex_t默认是非递归
** 的（不可重入的，non-reentrant）。
**
****************************************************************************/
class GAPI GMutex final 
	: public GLock
{
public:
	GMutex();
	GMutex(gbool reentrant); // TODO，默认非递归？
	~GMutex();
	gvoid Lock();
	gbool Trylock();
	gvoid Unlock();

private:
	gbool Initialize();
	gvoid Release();

#ifdef G_SYSTEM_WINDOWS
	gptr m_pHandle;
#endif // G_SYSTEM_WINDOWS
};

} // namespace gsystem

#endif // _CORE_MUTEX_H_
