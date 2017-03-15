#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	namespace detail { // gsystem.detail
		class GTextFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

class GAPI GTextFile 
	: public GFile
{
public:
	GTextFile(const GString &filename);

	gbool Read(gsize size, GString &content);
	gbool ReadAll(GString &content);
	gbool Write(const GString &content);

protected:
	GTextFile(detail::GTextFile_Ex *);
};

} // namespace gsystem

#endif // _CORE_TEXT_FILE_H_