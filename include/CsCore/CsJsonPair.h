/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonPair.h
** @brief	Json名称/值对类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonPair
**
** Json数据的书写格式是：名称/值对。
** 名称/值对包括字段名称（在双引号中），后面写一个冒号，然后是值：
**	"firstName" : "John"
**
****************************************************************************/

#ifndef _CORE_JSON_PAIR_H_
#define _CORE_JSON_PAIR_H_

#include "CsString.h"
#include "CsJsonValue.h"

class CsJsonPair
{
private:
	CsString m_sKey;
	CsJsonValue *m_pValue;
};

#endif // _CORE_JSON_PAIR_H_