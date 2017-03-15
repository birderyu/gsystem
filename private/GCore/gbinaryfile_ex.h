#ifndef _CORE_BINARY_FILE_EX_H_
#define _CORE_BINARY_FILE_EX_H_

#include "gfile_ex.h"

namespace gsystem { // gsystem
	class GBytes;
} // namespace gsystem

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GBinaryFile_Ex
	: public GFile_Ex
{
public:
	GBinaryFile_Ex(const GString &sFileName);
	virtual ~GBinaryFile_Ex();

	gbyte Format() const;

	gbool GetByte(gbyte &);
	gbool PutByte(gbyte);

	gbool Read(gsize size, GBytes &);
	gbool ReadAll(GBytes &);
	gbool Write(const GBytes &);

protected:
	gcstring OpenMode() const;
};

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_BINARY_FILE_EX_H_