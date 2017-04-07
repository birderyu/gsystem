#ifndef _CORE_SERIALIZABLE_H_
#define _CORE_SERIALIZABLE_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GArchive;
} // namespace gsystem

namespace gsystem { // gsystem

class GSerializable
{
public:
	virtual guint ClassCode() const { return 0; }
	virtual gbool Serialize(GArchive &archive) const { return false; }
	virtual gbool Deserialize(GArchive &archive) { return false; }
};

} // namespace gsystem

#endif // _CORE_SERIALIZABLE_H_
