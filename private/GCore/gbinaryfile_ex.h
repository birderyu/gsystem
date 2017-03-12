#ifndef _CORE_BINARY_FILE_EX_H_
#define _CORE_BINARY_FILE_EX_H_

#include "gfile_ex.h"

namespace gnova {
	class GBytes;
}

namespace gnova {
namespace extra {

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

}
}

#endif // _CORE_BINARY_FILE_EX_H_