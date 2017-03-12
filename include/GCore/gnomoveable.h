#ifndef _CORE_NO_MOVEABLE_H_
#define _CORE_NO_MOVEABLE_H_

namespace gnova { // gnova

// the class which is immovable
class GNomovable
{
protected:
	GNomovable(GNomovable &&) = delete;
	GNomovable &operator=(GNomovable &&) = delete;
};

} // namespace gnova

#endif // _CORE_NO_MOVEABLE_H_