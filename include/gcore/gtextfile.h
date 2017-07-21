/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gtextfile.h
** @brief 文本文件
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	namespace detail { // gsystem.detail
		class GTextFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 文本文件
**
** 文本文件类用于打开、创建、编辑一个文本文件，它是文件类（GFile）的一个派生。
**
********************************************************************************/
class GAPI GTextFile final
	: public GFile
{
public:
	/****************************************************************************
	**
	** @name GTextFile
	** @brief 构造函数（constructor）
	** @param [in] filename {const GString &} 文件全名，包含文件路径、文件名和文件后缀名
	**
	****************************************************************************/
	GTextFile(const GString &filename);

	/****************************************************************************
	**
	** @name Read
	** @brief 读取文本文件的部分内容，并将其存入一个字符串
	** @param [in] size {gsize} 读取的字符数
	** @param [out] content {GString &} 字符串
	** @return {gbool} 若读取成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Read(gsize size, GString &content);

	/****************************************************************************
	**
	** @name ReadAll
	** @brief 读取文本文件的全部内容，并将其存入一个字符串
	** @param [out] content {GString &} 字符串
	** @return {gbool} 若读取成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool ReadAll(GString &content);

	/****************************************************************************
	**
	** @name Write
	** @brief 将字符串中的内容写入文件
	** @param [in] content {const GString &} 字符串
	** @return {gbool} 若写入成功，则返回true，否则返回false
	**
	** 写入的方式取决于打开文件的模式
	**
	****************************************************************************/
	gbool Write(const GString &content);

protected:
	/****************************************************************************
	**
	** @name GTextFile
	** @brief 构造函数（constructor）
	** @param [in] file {detail::GTextFile_Ex *} 文本文件私有实现体
	**
	****************************************************************************/
	GTextFile(detail::GTextFile_Ex *file);
};

} // namespace gsystem

#endif // _CORE_TEXT_FILE_H_