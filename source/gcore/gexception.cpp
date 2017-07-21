#include "gexception.h"
#include "gexceptdef.h"
#include "gclasscode.h"

namespace gsystem {

GException::GException() GNOEXCEPT
{

}

GException::GException(
	const GString &methodName, 
	gsize lineNumber, 
	const GString &fileName, 
	const GStringList *whatArguments, 
	const GString &whyMessageId,
	const GStringList *whyArguments) GNOEXCEPT
	: m_sWhyMessageId(whyMessageId)
{
	AddStackTraceInfo(methodName, lineNumber, fileName);
	if (GNULL != whatArguments && !(whatArguments->IsEmpty()))
	{
		for (gsize i = 0; i < whatArguments->Size(); ++i)
		{
			m_tWhatArguments.Add(whatArguments->GetAt(i));
		}
	}
	if (GNULL != whyArguments && !(whyArguments->IsEmpty()))
	{
		for (gsize i = 0; i < whyArguments->Size(); ++i)
		{
			m_tWhyArguments.Add(whyArguments->GetAt(i));
		}
	}
}

GException::~GException() GNOEXCEPT
{

}

const GString &GException::ExceptionMessage() const GNOEXCEPT
{
	/*
	if (m_sMessage.IsEmpty())
	{
		m_sMessage = FormatWhatMessage(m_tWhatArguments);
		if (!m_sWhyMessageId.IsEmpty())
		{
			m_sMessage += "\n";
			m_sMessage += FormatWhyMessage(m_tWhyArguments);
		}
	}
	*/
	return m_sMessage;
}

const GString &GException::Details() const GNOEXCEPT
{
	/*
	if (m_sDetails.IsEmpty())
	{
		m_sDetails = ExceptionMessage();
		m_sDetails += "\n";
		m_sDetails += FormatDetails();
		m_sDetails += "\n";
		m_sDetails += FormatStackTrace();
	}
	*/
	return m_sDetails;
}

const GString &GException::StackTrace() const GNOEXCEPT
{
	/*
	if (m_sStackTrace.IsEmpty())
	{
		m_sStackTrace = FormatStackTrace();
	}
	*/
	return m_sStackTrace;
}

gvoid GException::AddStackTraceInfo(const GString &methodName, gsize lineNumber, const GString &fileName) GNOEXCEPT
{
	AddStackTraceInfo(methodName, "", lineNumber, fileName);
}

gvoid GException::AddStackTraceInfo(const GString &methodName, const GString &methodParams, gsize lineNumber, const GString &fileName) GNOEXCEPT
{
	gsize stackSize = m_tMethodNames.Size();
	if (stackSize > 0)
	{
		if (methodName != m_tMethodNames[stackSize - 1])
		{
			m_tMethodNames.Add(methodName);
			m_tMethodParams.Add(methodParams);
			m_tLineNumbers.Add(lineNumber);
			m_tFileNames.Add(fileName);
		}
	}
	else
	{
		m_tMethodNames.Add(methodName);
		m_tMethodParams.Add(methodParams);
		m_tLineNumbers.Add(lineNumber);
		m_tFileNames.Add(fileName);
	}
}

guint GException::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::Exception);
}

GString GException::ClassName() const GNOEXCEPT
{
	return GString::ReferenceOf("gsystem::GException");
}

gbool GException::Serialize(GArchive &archive) const
{
	m_tMethodNames.Serialize(archive);
	m_tMethodParams.Serialize(archive);
	m_tLineNumbers.Serialize(archive);
	m_tFileNames.Serialize(archive);
	m_tWhatArguments.Serialize(archive);
	m_sWhyMessageId.Serialize(archive);
	m_tWhyArguments.Serialize(archive);
	m_sMessage.Serialize(archive);
	m_sDetails.Serialize(archive);
	m_sStackTrace.Serialize(archive);
	return true;
}

gbool GException::Deserialize(GArchive &archive)
{
	m_tMethodNames.Deserialize(archive);
	m_tMethodParams.Deserialize(archive);
	m_tLineNumbers.Deserialize(archive);
	m_tFileNames.Deserialize(archive);
	m_tWhatArguments.Deserialize(archive);
	m_sWhyMessageId.Deserialize(archive);
	m_tWhyArguments.Deserialize(archive);
	m_sMessage.Deserialize(archive);
	m_sDetails.Deserialize(archive);
	m_sStackTrace.Deserialize(archive);
	return true;
}

}