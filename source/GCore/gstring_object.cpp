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

guint GString::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::String);
}

GString GString::ClassName() const GNOEXCEPT
{
	return GString::ReferenceOf("gsystem::GString");
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
