#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "gfile.h"

namespace gnova { // gnova
	namespace detail { // gnova.detail
		class GTextFile_Ex;
	} // namespace gnova.detail
} // namespace gnova

namespace gnova { // gnova

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

} // namespace gnova

#endif // _CORE_TEXT_FILE_H_