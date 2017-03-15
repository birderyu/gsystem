#ifndef _CORE_NO_MOVEABLE_H_
#define _CORE_NO_MOVEABLE_H_

namespace gsystem { // gsystem

// the class which is immovable
class GNomovable
{
protected:
	GNomovable(GNomovable &&) = delete;
	GNomovable &operator=(GNomovable &&) = delete;
};

} // namespace gsystem

#endif // _CORE_NO_MOVEABLE_H_