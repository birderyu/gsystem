/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gbinfile.h
** @brief 二进制文件
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	class GBytes;
	namespace detail { // gsystem.detail
		class GBinFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 二进制文件
**
** 二进制文件类用于打开、创建、编辑一个二进制文件，它是文件类（GFile）的一个派生。
**
********************************************************************************/
class GAPI GBinFile final
	: public GFile
{
public:
	/****************************************************************************
	**
	** @name GBinFile
	** @brief 构造函数（constructor）
	** @param [in] filename {const GString &} 文件全名，包含文件路径、文件名和文件后缀名
	**
	****************************************************************************/
	GBinFile(const GString &filename);

	/****************************************************************************
	**
	** @name Read
	** @brief 读取二进制文件的部分内容，并将其存入一个字节串
	** @param [in] size {gsize} 读取的字节数
	** @param [out] bytes {GBytes &} 字节串
	** @return {gbool} 若读取成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Read(gsize size, GBytes &bytes);

	/****************************************************************************
	**
	** @name ReadAll
	** @brief 读取二进制文件的全部内容，并将其存入一个字节串
	** @param [out] bytes {GBytes &} 字节串
	** @return {gbool} 若读取成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool ReadAll(GBytes &bytes);

	/****************************************************************************
	**
	** @name Write
	** @brief 将字节串中的内容写入文件
	** @param [in] bytes {const GBytes &} 字节串
	** @return {gbool} 若写入成功，则返回true，否则返回false
	**
	** 写入的方式取决于打开文件的模式
	**
	****************************************************************************/
	gbool Write(const GBytes &bytes);

protected:
	/****************************************************************************
	**
	** @name GBinFile
	** @brief 构造函数（constructor）
	** @param [in] file {detail::GBinFile_Ex *} 二进制文件私有实现体
	**
	****************************************************************************/
	GBinFile(detail::GBinFile_Ex *file);
};

} // namespace gsystem

#endif // _CORE_BINARY_FILE_H_