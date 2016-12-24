// 流
#ifndef _CORE_STREAM_H_
#define _CORE_STREAM_H_

#include "CsGlobal.h"

class CS_API CsStream
{
public:
	virtual ~CsStream() = 0;
	virtual cs_bool Valid() const = 0;

	// 是否是抽象的
	virtual cs_bool IsAbstract() const = 0;
	// 是否是二进制，否则为文本
	virtual cs_bool IsBinary() const = 0;
	// 是否有缓冲
	virtual cs_bool HasBuffer() const = 0;
	// 是否有文件
	virtual cs_bool HasFile() const = 0;
	// 是否是输入流
	virtual cs_bool IsInput() const = 0;
	// 是否是输出流
	virtual cs_bool IsOutput() const = 0;

	//virtual cs_bool Seek() = 0;
	//virtual cs_void Rewind() = 0;
};

#endif // _CORE_STREAM_H_
