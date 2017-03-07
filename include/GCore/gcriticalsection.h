/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gcriticalsection.h
** @brief	基础对象类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-22
** @version	1.0
**
****************************************************************************/
#ifndef _CORE_CRITICAL_SECTION_H_
#define _CORE_CRITICAL_SECTION_H_

#include "glock.h"

#define G_CRITICAL_SECTION_HANELD_SIZE G_POINTER_ADDRESS_SIZE*8

/****************************************************************************
**
** gobject.h
**
** @class		GCriticalSection
** @brief		临界区
** @module		GCore
**
** 临界区也称关键代码段，其优点是速度较快，这是因为它的工作位于用户态，因此开销小于互斥量，
** 为了提高性能，如果临界区已经被其它线程持有时，它可以先原地自旋，当自旋一定次数后还不能
** 获取关键代码段，此时线程才转入内核方式，进入等待状态。
** 默认情况下不启用自旋功能，若要启用，应在构造函数中指定启用并指定自旋次数。
**
****************************************************************************/
class GAPI GCriticalSection final 
	: public GLock
{
public:
	GCriticalSection();
	GCriticalSection(gbool spin, gsize spin_count);
	~GCriticalSection();
	gvoid Lock();
	gvoid Unlock();

private:
	gvoid Initialize(gbool spin, gsize spin_count);
	gvoid Release();

private:
#ifdef G_SYSTEM_WINDOWS
	gbyte m_pHandle[G_CRITICAL_SECTION_HANELD_SIZE];
#endif // G_SYSTEM_WINDOWS
};

#undef G_CRITICAL_SECTION_HANELD_SIZE

#endif // _CORE_CRITICAL_SECTION_H_