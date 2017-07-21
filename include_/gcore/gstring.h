#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "gstring8.h"

namespace gsystem {

GString8 GToString8(const GString8 &str);
GString8 GToString8(const GString16 &str);
GString8 GToString8(const GString32 &str);

}

#endif // _CORE_STRING_H_