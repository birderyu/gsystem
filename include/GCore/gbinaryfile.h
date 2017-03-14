#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gnova { // gnova
	class GBytes;
	namespace detail { // gnova.detail
		class GBinaryFile_Ex;
	} // namespace gnova.detail
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
	GBinaryFile(detail::GBinaryFile_Ex *);
};

} // namespace gnova

#endif // _CORE_BINARY_FILE_H_