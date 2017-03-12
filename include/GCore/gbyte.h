#ifndef _CORE_BYTE_H_
#define _CORE_BYTE_H_

#include "gpackage.h"

namespace gnova {

class GAPI GByte 
	: public GPackage<gbyte>
{
public:
	enum { CLASS_CODE = CLASS_CODE_BYTE, };

public:
	GByte(gbyte val = 0);
	GByte(const GByte &);

	guint ClassCode() const;
};

}

#endif // _CORE_BYTE_H_