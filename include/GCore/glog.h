#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

#include "gtextfile.h"

class GString;

class GAPI GLog
{
public:
	GLog(const GString &filename);
	gvoid Trace(const GString &msg);
	gvoid Debug(const GString &msg);
	gvoid Info(const GString &msg);
	gvoid Warn(const GString &msg);
	gvoid Error(const GString &msg);
	gvoid Fatal(const GString &msg);

private:
	GTextFile m_tLogFile;
};

#endif // _CORE_LOG_H_