#include "CsRegister.h"
#include "CsString.h"

cs_bool CsRegister::Register(const CsString &sClassName, cs_uint nClassCode)
{
	CsLockGuard<CsMutex> lock(m_tLock);
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

cs_void CsRegister::Initialize()
{
	Register("Object", CLASS_CODE_OBJECT);
	Register("Package", CLASS_CODE_PACKAGE);
	Register("Number", CLASS_CODE_NUMBER);
	Register("Byte", CLASS_CODE_BYTE);
	Register("Bool", CLASS_CODE_BOOLEAN);
}
