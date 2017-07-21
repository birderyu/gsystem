/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gmutex.h
** @brief 互斥锁类
** @author birderyu
** @contact https://github.com/birderyu
** @date 2015-12-31
** @version 0.9.0
**
********************************************************************************/

#ifndef _CORE_MUTEX_H_
#define _CORE_MUTEX_H_

#include "glock.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 互斥锁
** 
** 互斥锁（mutex）属于内核对象，它能够确保线程拥有对单个资源的互斥访问权。
**
********************************************************************************/
class GAPI GMutex final 
	: public GLock
{
public:
	/****************************************************************************
	**
	** @name GMutex
	** @brief 构造函数（constructor）
	** @param [in] reentrant {gbool} 是否可重入，默认可重入
	**
	** 可重入的互斥锁，又称可递归的互斥锁。需要注意的是，在Windows下，互斥锁是可递归的（可重入
	** 的，reentrant），而pthread_mutex_t默认是非递归的（不可重入的，non-reentrant）。
	**
	****************************************************************************/
	GMutex(gbool reentrant = true);

	/****************************************************************************
	**
	** @name ~GMutex
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	~GMutex();
	gvoid Lock();
	gbool Trylock();
	gvoid Unlock();

private:
	gbool Initialize(gbool reentrant);
	gvoid Release();

#ifdef G_SYSTEM_WINDOWS
	gptr m_pHandle;
#endif // G_SYSTEM_WINDOWS
};

} // namespace gsystem

#endif // _CORE_MUTEX_H_
