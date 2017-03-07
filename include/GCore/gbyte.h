#ifndef _CORE_BYTE_H_
#define _CORE_BYTE_H_

#include "gpackage.h"

G_BEGIN_NAMESPACE

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

G_END_NAMESPACE

#endif // _CORE_BYTE_H_