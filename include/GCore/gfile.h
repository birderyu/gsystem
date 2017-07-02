/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gfile.h
** @brief	该文件包含了文件类的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-12-31
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "gglobal.h"

namespace gsystem { // gsystem
	namespace detail { // gsystem.detail
		class GFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	文件类
**
** GFile表示一个文件，是一个抽象类，它的具体功能取决于它的两个实现：文本文件（GTextFile）和
** 二进制文件（GBinFile）。GFile本身不支持缓存，若需要构建一个文件缓存，可以使用相应的文件流。
**
****************************************************************************/
class GAPI GFile
{
public:
	/****************************************************************************
	**
	** @name		OPEN_MODE
	** @brief		文件的打开模式
	**
	****************************************************************************/
	enum OPEN_MODE
	{
		NO_OPEN = 0x0000,						/// 不打开
		ONLY_READ = 0x0001,						/// 只读模式
		ONLY_WIRTE = 0x0002,					/// 只写模式
		READ_WIRTE = ONLY_READ | ONLY_WIRTE,	/// 读写模式
		APPEND = 0x0004,						/// 在尾部添加
	};

	enum FILE_FORMAT
	{
		BINARY_FILE,	/// 二进制文件
		TEXT_FILE		/// 文本文件
	};

	enum SEEK_MODE
	{
		SEEK_MODE_START		= 0,
		SEEK_MODE_CURRENT	= 1,
		SEEK_MODE_END		= 2,
	};

public:
	virtual ~GFile() = 0;

	FILE_FORMAT Format() const;

	gbool Valid() const;
	gbool EndOfFile() const;	

	const GString &FileName() const;
	GString &FileName();
	gvoid SetFileName(const GString &);

	gbool Open(OPEN_MODE mode);
	gvoid Close();

	gbool Seek(glong offset, SEEK_MODE);
	glong Tell() const; // 负值则表示获取位置失败
	gvoid Rewind();

	// 获取文件的大小，单位，字节
	gsize Size() const;

protected:
	GFile(detail::GFile_Ex *);
	detail::GFile_Ex *m_pFileEx;
};

} // namespace gsystem

#endif _CORE_FILE_H_