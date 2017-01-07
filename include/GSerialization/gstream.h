// 流
#ifndef _CORE_STREAM_H_
#define _CORE_STREAM_H_

#include "GCore/gglobal.h"

class GAPI GStream
{
public:
	virtual ~GStream() = 0;
	virtual gbool Valid() const = 0;

	// 是否是抽象的
	virtual gbool IsAbstract() const = 0;
	// 是否是二进制，否则为文本
	virtual gbool IsBinary() const = 0;
	// 是否有缓冲
	virtual gbool HasBuffer() const = 0;
	// 是否有文件
	virtual gbool HasFile() const = 0;
	// 是否是输入流
	virtual gbool IsInput() const = 0;
	// 是否是输出流
	virtual gbool IsOutput() const = 0;
};

#endif // _CORE_STREAM_H_
