#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

#include "gobject.h"

class GString;

class GAPI GTime final 
	: public GObject
{
public:
	GTime(guint h, guint m, guint s, guint ms = 0);

	gbool SetTime(guint h, guint m, guint s, guint ms = 0);

	guint GetHour() const;
	guint GetMinute() const;
	guint GetSecond() const;
	guint GetMilliSecond() const;

	gint GetSecsTo(const GTime &) const;
	gint GetMSecsTo(const GTime &) const;

	static GTime Now();
};

#endif // _CORE_TIME_H_