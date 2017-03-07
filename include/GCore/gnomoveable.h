#ifndef _CORE_NO_MOVEABLE_H_
#define _CORE_NO_MOVEABLE_H_

// the class which is immovable
class GNomovable
{
protected:
	GNomovable(GNomovable &&) = delete;
	GNomovable &operator=(GNomovable &&) = delete;
};

#endif // _CORE_NO_MOVEABLE_H_