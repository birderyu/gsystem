#include "gstring.h"
#include "gclasscode.h"
#include "garchive.h"

namespace gsystem { // gsystem

const GObject *GString::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

GString GString::ToString() const
{
	return GString(m_tString);
}

guint GString::ClassCode() const
{
	return static_cast<guint>(GClassCode::String);
}

gbool GString::Serialize(GArchive &archive) const
{
	archive.Attach(CString(), Size());
	return true;
}

gbool GString::Deserialize(GArchive &archive)
{
	// TODO
	return false;
}

} // namespace gsystem
