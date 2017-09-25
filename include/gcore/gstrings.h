#ifndef _CORE_STRINGS_H_
#define _CORE_STRINGS_H_

#include "gstring.h"

namespace gsystem {

class GStrings
{
public:
	/****************************************************************************
	**
	** @name ToString
	** @brief 静态方法，转换成字符串
	** @template T 数据类型
	** @param [in] obj {const T &} 对象
	** @return {GString} 字符串
	**
	****************************************************************************/
	template <typename T>
	static GString ToString(const T &obj) GEXCEPT(false);

	static GString8 ToString8(const GString16 &str) GEXCEPT(false);
	static GString8 ToString8(const GString32 &str) GEXCEPT(false);
	static GString16 ToString16(const GString8 &str) GEXCEPT(false);
	static GString16 ToString16(const GString32 &str) GEXCEPT(false);
	static GString32 ToString32(const GString8 &str) GEXCEPT(false);
	static GString32 ToString32(const GString16 &str) GEXCEPT(false);

};

} // namespace gsystem

#endif // _CORE_STRING_H_
