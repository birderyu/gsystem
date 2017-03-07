#ifndef _CORE_NO_COPYABLE_H_
#define _CORE_NO_COPYABLE_H_

// the class which cannot copy
class GNocopyable
{
protected:
	GNocopyable() = default;
	~GNocopyable() = default;
	GNocopyable(const GNocopyable &) = delete;
	GNocopyable &operator=(const GNocopyable &) = delete;
};

#endif // _CORE_NO_COPYABLE_H_