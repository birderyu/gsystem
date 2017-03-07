#ifndef _CORE_REGISTER_H_
#define _CORE_REGISTER_H_

#include "gglobal.h"
#include "gsingleton.h"
#include "gmutex.h"
#include "gstring.h"
#include "gunordermap.h"

G_BEGIN_NAMESPACE

class GAPI GRegister
	: public GSingleton<GRegister, GMutex>
{
public:
	gbool Register(const GString &sClassName, guint nClassCode);
	gvoid Initialize();
	
private:
	GUnorderMap<GString, guint> m_tClassName_ClassCode;
	GUnorderMap<guint, GString> m_tClassCode_ClassName;
};

G_END_NAMESPACE

#endif // _CORE_REGISTER_H_