#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

#include "gtextfile.h"

namespace gnova { // gnova
	class GString;
} // namespace gnova

namespace gnova { // gnova
namespace log { // gnova.log

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

} // namespace gnova.log
} // namespace gnova

#endif // _CORE_LOG_H_