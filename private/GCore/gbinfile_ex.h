#ifndef _CORE_BINARY_FILE_EX_H_
#define _CORE_BINARY_FILE_EX_H_

#include "gfile_ex.h"

namespace gsystem { // gsystem
	class GBytes;
} // namespace gsystem

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

class GBinFile_Ex
	: public GFile_Ex
{
public:
	GBinFile_Ex(const GString &sFileName);
	virtual ~GBinFile_Ex();

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