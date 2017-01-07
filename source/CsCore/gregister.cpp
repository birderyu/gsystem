#include "gregister.h"
#include "gstring.h"

gbool GRegister::Register(const GString &sClassName, guint nClassCode)
{
	GLockGuard<GMutex> lock(m_tLock);
	/*
	if (!m_tClassName_ClassCode.Contains(sClassName) &&
		!m_tClassCode_ClassName.Contains(nClassCode))
	{
		m_tClassName_ClassCode.Insert(sClassName, nClassCode);
		m_tClassCode_ClassName.Insert(nClassCode, sClassName);
		return true;
	}
	*/
	return false;
}

gvoid GRegister::Initialize()
{
	Register("Object", CLASS_CODE_OBJECT);
	Register("Package", CLASS_CODE_PACKAGE);
	Register("Number", CLASS_CODE_NUMBER);
	Register("Byte", CLASS_CODE_BYTE);
	Register("Bool", CLASS_CODE_BOOLEAN);
}
