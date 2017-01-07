#ifndef _CORE_DATETIME_H_
#define _CORE_DATETIME_H_

#include "gobject.h"

class GAPI GDateTime final 
	: public GObject
{
public:
	gbool SetDate(guint y, guint m, guint d, guint dofw = 0);
	gbool SetTime(guint h, guint m, guint s, guint ms = 0);

	static GDateTime Now();

};

#endif // _CORE_DATETIME_H_