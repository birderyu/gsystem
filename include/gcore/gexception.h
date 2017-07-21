#ifndef _CORE_EXCEPTION_H_
#define _CORE_EXCEPTION_H_

#include "gstring.h"
#include "gsharedptr.h"
#include "gserializable.h"

namespace gsystem {
	class GException;
	typedef GSharedPtr<GException> GExceptionPtr;
}

namespace gsystem {

class GAPI GException
	: virtual public GSerializable
{
public:
	virtual ~GException() GNOEXCEPT = 0;

public:
	virtual gvoid Raise() = 0;
	const GString &ExceptionMessage() const GNOEXCEPT;
	const GString &Details() const GNOEXCEPT;
	const GString &StackTrace() const GNOEXCEPT;
	gvoid AddStackTraceInfo(const GString &methodName,
		gsize lineNumber, const GString &fileName) GNOEXCEPT;
	gvoid AddStackTraceInfo(const GString &methodName, const GString &methodParams,
		gsize lineNumber, const GString &fileName) GNOEXCEPT;
	typedef GString(*LocaleCallbackFunc)();
	static gvoid RegisterLocaleCallback(LocaleCallbackFunc func);

public:
	guint ClassCode() const GNOEXCEPT;
	GString ClassName() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

protected:
	GException() GNOEXCEPT;

	/****************************************************************************
	**
	** @brief 构造异常对象
	** @param [in] methodName {const GString &} 异常抛出方法名
	** @param [in] lineNumber {gsize} 异常抛出行号
	** @param [in] fileName {const GString &} 异常抛出文件
	** @param [in] whatArguments {const GStringList *} 什么异常
	** @param [in] whyMessageId {const GString &} 异常为什么产生的信息ID
	** @param [in] whyArguments {const GStringList *} 异常为什么产生的相关参数
	**
	****************************************************************************/
	GException(const GString &methodName, gsize lineNumber,
		const GString &fileName, const GStringList *whatArguments,
		const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT;

	virtual GString FormatWhatMessage(const GStringList &arguments) GNOEXCEPT = 0;
	virtual GString FormatWhyMessage(const GStringList &arguments) GNOEXCEPT = 0;
	virtual GString FormatDetails() GNOEXCEPT = 0;
	virtual GString FormatStackTrace() GNOEXCEPT = 0;

protected:
	/// 引起异常的函数名集合
	GStringList m_tMethodNames;

	/// 引起异常的函数参数名集合
	GStringList m_tMethodParams;

	/// 引起异常的行数集合
	GStringList m_tLineNumbers;

	/// 引起异常的文件名集合
	GStringList m_tFileNames;

	/// 描述异常是什么的参数集合
	GStringList m_tWhatArguments;

	/// 描述为什么出现异常的消息ID标示符
	GString m_sWhyMessageId;

	/// 描述为什么出现异常的参数集合
	GStringList m_tWhyArguments;

	/// 局部消息
	GString m_sMessage;

	/// 局部细节
	GString m_sDetails;

	/// 局部堆栈信息
	GString m_sStackTrace;

private:
	static LocaleCallbackFunc smLocaleCallbackFunc;

	/// \brief 获取默认的本地化语言
	/// \return 默认的本地化语言
	GString GetLocale() GNOEXCEPT;
};

} // namespace gsystem

#endif // _CORE_EXCEPTION_H_
