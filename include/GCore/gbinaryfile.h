#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gnova { // gnova
	class GBytes;
	namespace extra { // gnova.extra
		class GBinaryFile_Ex;
	} // namespace gnova.extra
} // namespace gnova

namespace gnova { // gnova

class GAPI GBinaryFile
	: public GFile
{
public:
	GBinaryFile(const GString &sFileName);

	gbool Read(gsize size, GBytes &);
	gbool ReadAll(GBytes &);
	gbool Write(const GBytes &);

protected:
	GBinaryFile(extra::GBinaryFile_Ex *);
};

} // namespace gnova

#endif // _CORE_BINARY_FILE_H_