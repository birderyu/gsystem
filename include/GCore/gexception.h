#ifndef _CORE_EXCEPTION_H_
#define _CORE_EXCEPTION_H_

#include "gserializable.h"

namespace gsystem {
	class GString;
}

namespace gsystem {

class GAPI GException
	: virtual public GSerializable
{
public:
	virtual ~GException() = 0;

public:
	GString ExceptionMessage() const;
	GString Details() const;
	GString StackTrace() const;

protected:
	/// \brief 构造异常对象
	/// \param [in] methodName 异常抛出方法名
	/// \param [in] lineNumber 异常抛出行号
	/// \param [in] fileName 异常抛出文件
	/// \param [in] whatArguments 什么异常
	/// \param [in] whyMessageId 异常为什么产生的信息ID
	/// \param [in] whyArguments 异常为什么产生的相关参数
	GException(const GString &methodName, gsize lineNumber,
		const GString &fileName, WStringArray* whatArguments,
		CREFWSTRING whyMessageId, WStringArray* whyArguments) GNOEXCEPT;
};

} // namespace gsystem

#endif // _CORE_EXCEPTION_H_
