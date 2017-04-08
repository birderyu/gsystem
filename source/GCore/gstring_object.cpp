#include "gstring.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

const GObject *GString::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

guint GString::ClassCode() const
{
	return static_cast<guint>(GClassCode::String);
}

GString GString::ToString() const
{
	return GString(m_tString);
}

} // namespace gsystem
