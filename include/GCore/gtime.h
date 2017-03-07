#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

#include "gobject.h"

class GDateTime;

class GAPI GTime final 
	: public GObject
{
	friend class GDateTime;

public:
	static GTime Now();
	static GTime Parse(const GString &time);

public:
	GTime();
	GTime(gtime timestamp);
	GTime(guint hour, guint minute, guint second, guint millisecond = 0);
	GTime(const GTime &time);
	GTime(GTime &&time);

public:
	guint Hour() const; // [0,23]
	guint Minute() const; // [0,59]
	guint Second() const; // [0,59]
	guint Millisecond() const; // [0, 999]
	
public:
	gbool SetTime(gtime timestamp);
	gvoid SetTime(const GTime &time);
	gvoid SetTime(GTime &&time);
	gvoid SetTime(guint hour, guint minute, guint second, guint millisecond = 0);
	gvoid SetHour(guint h); // guint8
	gvoid SetMinute(guint mm); // guint8
	gvoid SetSecond(guint s); // guint8
	gvoid SetMillisecond(guint ms); // guint16

public: // 日期时间计算
	gint HoursTo(const GTime &time) const;
	gint MinutesTo(const GTime &time) const;
	gint SecondsTo(const GTime &time) const;
	gint MillisecondsTo(const GTime &time) const;
	GTime &AddHours(gint h);
	GTime &AddMinutes(gint mm);
	GTime &AddSeconds(gint s);
	GTime &AddMilliseconds(gint ms);

public:
	GString ToString() const;

private:
	GTime(const gbyte *val);
	gbyte m_tTime[G_TIME_SIZE];
};

#endif // _CORE_TIME_H_