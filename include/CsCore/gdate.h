#ifndef _CORE_DATE_H_
#define _CORE_DATE_H_

#include "gobject.h"

class GAPI GDate final 
	: public GObject
{
public:
	GDate(guint y, guint m, guint d, guint dofw = 0);
	gbool SetDate(guint y, guint m, guint d, guint dofw = 0);
	guint GetYear() const;
	guint GetMonth() const;
	guint GetDay() const;
	guint GetDayOfWeek() const;
	guint GetDayOfYear() const;

	gint GetDaysTo(const GDate &) const;

	static GDate Now();

};

#endif // _CORE_DATE_H_