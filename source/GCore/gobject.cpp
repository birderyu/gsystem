#include "gobject.h"
#include "gstring.h"
#include "gbytes.h"

GObject::~GObject()
{

}

GObjectP GObject::Clone() const
{
	return GObjectP();
}

const GObject *GObject::Boxing() const
{
	return this;
}

gbool GObject::Unboxing(const GObject *)
{
	return false;
}

GString GObject::ToString() const
{
	return GString();
}

GBytes GObject::ToBytes() const
{
	return GBytes();
}

guint GObject::ClassCode() const
{
	return GObject::ClassCode();
}

guint GObject::HashCode() const
{
	return 0;
}

gbool GObject::Equals(const GObject *obj) const
{
	return this == obj;
}

gbool GObject::Serializable() const
{
	return false;
}
