#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

#include "gtextfile.h"

namespace gsystem { // gsystem
	class GString;
} // namespace gsystem

namespace gsystem { // gsystem
namespace log { // gsystem.log

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

} // namespace gsystem.log
} // namespace gsystem

#endif // _CORE_LOG_H_