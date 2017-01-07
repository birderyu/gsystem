/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonArray.h
** @brief	Json数组类型的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonArray
**
** Json数组在方括号中书写：
** 数组可包含多个对象：
** {
**	"employees":[
**		{ "firstName":"John", "lastName" : "Doe" },
** 		{ "firstName":"Anna", "lastName" : "Smith" },
** 		{ "firstName":"Peter", "lastName" : "Jones" }
**	]
** }
** 在上面的例子中，对象 "employees" 是包含三个对象的数组，每个对象
** 代表一条关于某人（有姓和名）的记录。
**
****************************************************************************/

#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "CsList.h"

class CsJsonValue;

class CS_API CsJsonArray
{
public:
	CsJsonArray();
	CsJsonArray(const CsString &);
	CsJsonArray(const CsJsonArray &);

	cs_bool Parse(const CsString &jsonStr, cs_size_t cursor = 0, CsString *s_error = NULL);

private:
	CsList<CsJsonValue*> m_tList;
};

#endif // _CORE_JSON_ARRAY_H_