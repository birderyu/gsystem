#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	class GBytes;
	namespace detail { // gsystem.detail
		class GBinaryFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** gbinaryfile.h
**
** @class		GBinaryFile
** @brief		二进制文件
**
** GBinaryFile用于打开、创建、编辑一个二进制文件，它是文件类GFile的一个派生。
**
** @see GFile
**
****************************************************************************/
class GAPI GBinaryFile
	: public GFile
{
public:
	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		GBinaryFile
	** @brief		构造函数（constructor）
	** @param[in]	filename {const GString &} 文件名
	**
	****************************************************************************/
	GBinaryFile(const GString &filename);

	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		Read
	** @brief		读取二进制文件，并将其存入一个字节数组
	** @param[in]	size {gsize} 读取的尺寸，单位字节
	** @param[out]	bytes {GBytes &} 字节数组
	** @return		{gbool} 若读取失败，则返回false
	** @see			GBytes
	**
	****************************************************************************/
	gbool Read(gsize size, GBytes &bytes);

	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		ReadAll
	** @brief		读取二进制文件的全部内容，并将其存入一个字节数组
	** @param[out]	bytes {GBytes &} 字节数组
	** @return		{gbool} 若读取失败，则返回false
	** @see			GBytes
	**
	****************************************************************************/
	gbool ReadAll(GBytes &bytes);

	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		Write
	** @brief		将字节数组中的内容写入文件
	** @param[out]	bytes {const GBytes &} 字节数组
	** @return		{gbool} 若写入失败，则返回false
	** @see			GBytes
	**
	** 写入的方式取决于打开文件的方式（mode {OPEN_MODE}）
	**
	****************************************************************************/
	gbool Write(const GBytes &bytes);

protected:
	GBinaryFile(detail::GBinaryFile_Ex *);
};

} // namespace gsystem

#endif // _CORE_BINARY_FILE_H_