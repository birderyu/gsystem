#ifndef _CORE_SYNCHRONOUS_LOG_H_
#define _CORE_SYNCHRONOUS_LOG_H_

#include "gglobal.h"
#include "gnocopyable.h"

namespace gnova {
namespace log {

class GAPI GSynchronousLog
	: private GNocopyable
{
public:
	GSynchronousLog();
	~GSynchronousLog();

	gvoid Append(const GString &msg, gsize size);
	gvoid Flush();
};

}
}

#endif // _CORE_SYNCHRONOUS_LOG_H_
