#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	class GBytes;
	namespace detail { // gsystem.detail
		class GBinaryFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

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

} // namespace gsystem

#endif // _CORE_BINARY_FILE_H_