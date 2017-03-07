#ifndef _CORE_DATE_H_
#define _CORE_DATE_H_

#include "gobject.h"
#include "gdatetimedefine.h"

class GDateTime;

class GAPI GDate final 
	: public GObject
{
	friend class GDateTime;

public:
	static GDate Now();
	static GDate Parse(const GString &time);
	static gbool IsLeapYear(guint year);
	static gvoid DayOfMonthToDayOfYear(guint year, guint month, guint day,
		guint &day_of_year);
	static gvoid DayOfMonthToDayOfWeek(guint year, guint month, guint day,
		guint &day_of_week);
	static gvoid DayOfYearToDayOfMonth(guint year, guint day_of_year,
		guint &month, guint &day);
	static gvoid DayOfYearToDayOfWeek(guint year, guint day_of_year,
		guint &day_of_week);

public:
	GDate();
	GDate(gtime timestamp);
	GDate(guint year, guint month, guint day);
	GDate(guint year, guint day_of_year);
	GDate(const GDate &date);
	GDate(GDate &&date);

public:
	guint Year() const; // guint16
	guint Month() const; // [1,12]
	guint Day() const; // [1,31], day of month
	guint DayOfYear() const; // [0,365]
	guint DayOfWeek() const; // [1,7]

public:
	gbool SetDate(gtime timestamp);
	gvoid SetDate(const GDate &date);
	gvoid SetDate(GDate &&date);
	gvoid SetDate(guint year, guint month, guint day);
	gvoid SetDate(guint year, guint day_of_year);
	gvoid SetYear(guint y); // guint16
	gvoid SetMonth(guint m); // guint8
	gvoid SetMonth(const GMonth &m);
	gvoid SetDay(guint d); // guint8, day of month

public:
	guint YearsTo(const GDateTime &datetime) const;
	guint YearsTo(const GDate &date) const;
	guint DaysTo(const GDateTime &datetime) const;
	guint DaysTo(const GDate &date) const;
	GDate &AddYears(gint y);
	GDate &AddDays(gint d);

public:
	GString ToString() const;

private:
	GDate(const gbyte *val);
	gvoid SetDayOfMonth(guint mday);
	gvoid SetDayOfWeek(guint wday);
	gvoid SetDayOfYear(guint yday);

private:
	gbyte m_tDate[G_DATE_SIZE];
};

#endif // _CORE_DATE_H_