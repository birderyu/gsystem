#ifndef _CORE_SERIALIZABLE_H_
#define _CORE_SERIALIZABLE_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GArchive;
} // namespace gsystem

namespace gsystem { // gsystem

class GAPI GSerializable
{
public:
	virtual ~GSerializable() = 0;
	virtual guint ClassCode() const = 0;
	virtual gbool Serialize(GArchive &archive) const = 0;
	virtual gbool Deserialize(GArchive &archive) = 0;
};

} // namespace gsystem

#endif // _CORE_SERIALIZABLE_H_
