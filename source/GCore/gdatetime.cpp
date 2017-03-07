#include "gdatetime.h"
#include "gbytes.h"
#include "gstring.h"
#include "gdate.h"
#include "gtime.h"

#ifdef G_SYSTEM_WINDOWS 
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>
#include <time.h>
#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

#define G_DATA_TIME_FIRST_YEAR			1900
#define G_DATA_TIME_OFFSET_DATE			0
#define G_DATA_TIME_OFFSET_TIME			8
#define G_DATA_TIME_OFFSET_YEAR			(G_DATA_TIME_OFFSET_DATE + 0)
#define G_DATA_TIME_OFFSET_MONTH		(G_DATA_TIME_OFFSET_DATE + 2)
#define G_DATA_TIME_OFFSET_DAY			(G_DATA_TIME_OFFSET_DATE + 3)
#define G_DATA_TIME_OFFSET_DAY_OF_YEAR	(G_DATA_TIME_OFFSET_DATE + 4)
#define G_DATA_TIME_OFFSET_DAY_OF_WEEK	(G_DATA_TIME_OFFSET_DATE + 6)
#define G_DATA_TIME_OFFSET_HOUR			(G_DATA_TIME_OFFSET_TIME + 0)
#define G_DATA_TIME_OFFSET_MINUTE		(G_DATA_TIME_OFFSET_TIME + 1)
#define G_DATA_TIME_OFFSET_SECOND		(G_DATA_TIME_OFFSET_TIME + 2)
#define G_DATA_TIME_OFFSET_MILLISECOND	(G_DATA_TIME_OFFSET_TIME + 4)
#define G_DATA_TIME_SIZE_YEAR			2
#define G_DATA_TIME_SIZE_MONTH			1
#define G_DATA_TIME_SIZE_DAY			1
#define G_DATA_TIME_SIZE_DAY_OF_YEAR	2
#define G_DATA_TIME_SIZE_DAY_OF_WEEK	1
#define G_DATA_TIME_SIZE_HOUR			1
#define G_DATA_TIME_SIZE_MINUTE			1
#define G_DATA_TIME_SIZE_SECOND			1
#define G_DATA_TIME_SIZE_MILLISECOND	2

GDateTime GDateTime::Now()
{
	GDateTime dt;

#ifdef G_SYSTEM_WINDOWS

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);

	guint day_of_year = 0;
	GDateTime::DayOfMonthToDayOfYear(st.wYear, st.wMonth, st.wDay, day_of_year);

	dt.SetYear(st.wYear);
	dt.SetMonth(st.wMonth);
	dt.SetDayOfMonth(st.wDay);
	dt.SetDayOfWeek(st.wDayOfWeek);
	dt.SetDayOfYear(day_of_year);
	dt.SetHour(st.wHour);
	dt.SetMinute(st.wMinute);
	dt.SetSecond(st.wSecond);
	dt.SetMillisecond(st.wMilliseconds);

#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

	return dt;
}

GDateTime GDateTime::Parse(const GString &time)
{
	// TODO
	return GDateTime();
}

gtime GDateTime::NowTimestamp()
{
	gtime t;
	return ::time(&t);
}

gbool GDateTime::IsLeapYear(guint year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

gvoid GDateTime::DayOfMonthToDayOfYear(guint year, guint month, guint day,
	guint &day_of_year)
{
	//计算某月以前月份的天数
	switch (month) {
	case 1: day_of_year = 0; break;
	case 2: day_of_year = 31; break;
	case 3: day_of_year = 59; break;
	case 4: day_of_year = 90; break;
	case 5: day_of_year = 120; break;
	case 6: day_of_year = 151; break;
	case 7: day_of_year = 181; break;
	case 8: day_of_year = 212; break;
	case 9: day_of_year = 243; break;
	case 10: day_of_year = 273; break;
	case 11: day_of_year = 304; break;
	case 12: day_of_year = 334; break;
	default:
		throw("month error! month must in [1, 12].");
		break;
	}

	//月份天数加上这个月的日数
	day_of_year = day_of_year + day;

	if (GDateTime::IsLeapYear(year))
	{
		if (month > 2)
		{
			++day_of_year;
		}
	}

	// 日期的计算从0开始
	--day_of_year;
}

gvoid GDateTime::DayOfMonthToDayOfWeek(guint year, guint month, guint day,
	guint &day_of_week)
{
	if (month == 1 || month == 2)
	{
		month += 12;
		year--;
	}
	day_of_week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	++day_of_week;
}

gvoid GDateTime::DayOfYearToDayOfMonth(guint year, guint day_of_year,
	guint &month, guint &day)
{
	if (day_of_year <= 31)
	{
		month = 1;
		day = day_of_year + 1;
		return;
	}

	if (GDateTime::IsLeapYear(year))
	{
		// 闰年
		if (day_of_year < 31 + 29)
		{
			month = 2;
			day = day_of_year - 31 + 1;
		}
		else if (day_of_year < 31 + 29 + 31)
		{
			month = 3;
			day = day_of_year - (31 + 29) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30)
		{
			month = 4;
			day = day_of_year - (31 + 29 + 31) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31)
		{
			month = 5;
			day = day_of_year - (31 + 29 + 31 + 30) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30)
		{
			month = 6;
			day = day_of_year - (31 + 29 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31)
		{
			month = 7;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 ) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31)
		{
			month = 8;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30)
		{
			month = 9;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31)
		{
			month = 10;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30)
		{
			month = 11;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31)
		{
			month = 12;
			day = day_of_year - (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30) + 1;
		}
		else
		{
			throw("day_of_year error! must in [1, 365] this year.");
		}
	}
	else
	{
		// 非闰年
		// 闰年
		if (day_of_year < 31 + 28)
		{
			month = 2;
			day = day_of_year - 31 + 1;
		}
		else if (day_of_year < 31 + 28 + 31)
		{
			month = 3;
			day = day_of_year - (31 + 28) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30)
		{
			month = 4;
			day = day_of_year - (31 + 28 + 31) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31)
		{
			month = 5;
			day = day_of_year - (31 + 28 + 31 + 30) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30)
		{
			month = 6;
			day = day_of_year - (31 + 28 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31)
		{
			month = 7;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31)
		{
			month = 8;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30)
		{
			month = 9;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31)
		{
			month = 10;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30)
		{
			month = 11;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31) + 1;
		}
		else if (day_of_year < 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31)
		{
			month = 12;
			day = day_of_year - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30) + 1;
		}
		else
		{
			throw("day_of_year error! must in [1, 365] this year.");
		}
	}
	
}

gvoid GDateTime::DayOfYearToDayOfWeek(guint year, guint day_of_year, guint &day_of_week)
{
	guint month = 0, day = 0;
	DayOfYearToDayOfMonth(year, day_of_year, month, day);
	DayOfMonthToDayOfWeek(year, month, day, day_of_week);
}

GDateTime::GDateTime()
{
	GMemSet(m_tDateTime, 0, G_DATE_TIME_SIZE);
}

GDateTime::GDateTime(gtime timestamp)
{
	GMemSet(m_tDateTime, 0, G_DATE_TIME_SIZE);
	SetDateTime(timestamp);
}

GDateTime::GDateTime(const gbyte *val)
{
	GMemCopy(m_tDateTime, val, G_DATE_TIME_SIZE);
}

GDateTime::GDateTime(const GDate &date, const GTime &time)
{
	SetDateTime(date, time);
}

GDateTime::GDateTime(guint year, guint month, guint day,
	guint hour, guint minute, guint second, guint millisecond)
{
	SetDateTime(year, month, day, hour, minute, second, millisecond);
}

GDateTime::GDateTime(guint year, guint day_of_year,
	guint hour, guint minute, guint second, guint millisecond)
{
	SetDateTime(year, day_of_year, hour, minute, second, millisecond);
}

GDateTime::GDateTime(const GDateTime &datetime)
{
	SetDateTime(datetime);
}

GDateTime::GDateTime(GDateTime &&datetime)
{
	SetDateTime(GForward<GDateTime>(datetime));
}

guint GDateTime::Year() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_YEAR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_YEAR, &val);
	return val;
}

guint GDateTime::Month() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_MONTH>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_MONTH, &val);
	return val;
}

guint GDateTime::Day() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_DAY>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_DAY, &val);
	return val;
}

guint GDateTime::DayOfYear() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_DAY_OF_YEAR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_DAY_OF_YEAR, &val);
	return val;
}

guint GDateTime::DayOfWeek() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_DAY_OF_WEEK>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_DAY_OF_WEEK, &val);
	return val;
}

guint GDateTime::Hour() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_HOUR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_HOUR, &val);
	return val;
}

guint GDateTime::Minute() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_MINUTE>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_MINUTE, &val);
	return val;
}

guint GDateTime::Second() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_SECOND>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_SECOND, &val);
	return val;
}

guint GDateTime::Millisecond() const
{
	GIntegerForSize<G_DATA_TIME_SIZE_MILLISECOND>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDateTime + G_DATA_TIME_OFFSET_MILLISECOND, &val);
	return val;
}

gtime GDateTime::Timestamp() const
{
	struct tm t = { 0 };
	t.tm_year = Year() - G_DATA_TIME_FIRST_YEAR;
	t.tm_mon = Month() - 1;
	t.tm_mday = Day();
	t.tm_hour = Hour();
	t.tm_min = Minute();
	t.tm_sec = Second();
	return ::mktime(&t);
}

GDate GDateTime::Date() const
{
	return GDate(m_tDateTime + G_DATA_TIME_OFFSET_DATE);
}

GTime GDateTime::Time() const
{
	return GTime(m_tDateTime + G_DATA_TIME_OFFSET_TIME);
}

gbool GDateTime::SetDateTime(gtime timestamp)
{
	struct tm t = { 0 };
	if (0 != localtime_s(&t, &timestamp))
	{
		return false;
	}

	guint wday = t.tm_wday;
	if (wday == 0)
	{
		wday = 7;
	}

	SetYear(t.tm_year + G_DATA_TIME_FIRST_YEAR);
	SetMonth(t.tm_mon + 1);
	SetDayOfMonth(t.tm_mday);
	SetDayOfWeek(wday);
	SetDayOfYear(t.tm_yday + 1);
	SetHour(t.tm_hour);
	SetMinute(t.tm_min);
	SetSecond(t.tm_sec);
	SetMillisecond(0);

	return true;
}

gvoid GDateTime::SetDateTime(const GDate &date, const GTime &time)
{
	SetDate(date);
	SetTime(time);
}

gvoid GDateTime::SetDateTime(guint year, guint month, guint day,
	guint hour, guint minute, guint second, guint millisecond)
{
	SetDate(year, month, day);
	SetTime(hour, minute, second, millisecond);
}

gvoid GDateTime::SetDateTime(guint year, guint day_of_year,
	guint hour, guint minute, guint second, guint millisecond)
{
	SetDate(year, day_of_year);
	SetTime(hour, minute, second, millisecond);
}

gvoid GDateTime::SetDateTime(const GDateTime &datetime)
{
	GMemCopy(m_tDateTime, datetime.m_tDateTime, G_DATE_TIME_SIZE);
}

gvoid GDateTime::SetDateTime(GDateTime &&datetime)
{
	GMemCopy(m_tDateTime, datetime.m_tDateTime, G_DATE_TIME_SIZE);
}

gvoid GDateTime::SetDate(const GDate &date)
{
	GMemCopy(m_tDateTime + G_DATA_TIME_OFFSET_DATE, date.m_tDate, G_DATE_SIZE);
}

gvoid GDateTime::SetDate(guint year, guint month, guint day)
{
	guint day_of_year = 0, day_of_week = 0;
	GDateTime::DayOfMonthToDayOfYear(year, month, day,
		day_of_year);
	GDateTime::DayOfMonthToDayOfWeek(year, month, day,
		day_of_week);

	SetYear(year);
	SetMonth(month);
	SetDayOfMonth(day);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDateTime::SetDate(guint year, guint day_of_year)
{
	guint month = 0, day = 0, day_of_week = 0;
	GDateTime::DayOfYearToDayOfMonth(year, day_of_year,
		month, day);
	GDateTime::DayOfMonthToDayOfWeek(year, month, day,
		day_of_week);

	SetYear(year);
	SetMonth(month);
	SetDayOfMonth(day);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDateTime::SetTime(const GTime &time)
{
	GMemCopy(m_tDateTime + G_DATA_TIME_OFFSET_TIME, time.m_tTime, G_TIME_SIZE);
}

gvoid GDateTime::SetTime(guint hour, guint minute, guint second, guint millisecond)
{
	SetHour(hour);
	SetMinute(minute);
	SetSecond(second);
	SetMillisecond(millisecond);
}

gvoid GDateTime::SetYear(guint y)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_YEAR>::Unsigned;
	Type val = y;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_YEAR);
}

gvoid GDateTime::SetMonth(guint m)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_MONTH>::Unsigned;
	Type val = m;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_MONTH);
}

gvoid GDateTime::SetMonth(const GMonth &m)
{
	SetMonth(static_cast<guint>(m));
}

gvoid GDateTime::SetDay(guint d)
{
	guint year = Year();
	guint month = Month();
	guint day_of_year = 0, day_of_week = 0;
	GDateTime::DayOfMonthToDayOfYear(year, month, d, day_of_year);
	GDateTime::DayOfMonthToDayOfWeek(year, month, d, day_of_week);

	SetDayOfMonth(d);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDateTime::SetDayOfMonth(guint mday)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_DAY>::Unsigned;
	Type val = mday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_DAY);
}

gvoid GDateTime::SetDayOfYear(guint yday)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_DAY_OF_YEAR>::Unsigned;
	Type val = yday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_DAY_OF_YEAR);
}

gvoid GDateTime::SetDayOfWeek(guint wday)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_DAY_OF_WEEK>::Unsigned;
	Type val = wday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_DAY_OF_WEEK);
}

gvoid GDateTime::SetHour(guint h)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_HOUR>::Unsigned;
	Type val = h;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_HOUR);
}

gvoid GDateTime::SetMinute(guint mm)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_MINUTE>::Unsigned;
	Type val = mm;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_MINUTE);
}

gvoid GDateTime::SetSecond(guint s)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_SECOND>::Unsigned;
	Type val = s;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_SECOND);
}

gvoid GDateTime::SetMillisecond(guint ms)
{
	using Type = GIntegerForSize<G_DATA_TIME_SIZE_MILLISECOND>::Unsigned;
	Type val = ms;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDateTime + G_DATA_TIME_OFFSET_MILLISECOND);
}

gint GDateTime::YearsTo(const GDateTime &datetime) const
{
	gint that_year = datetime.Year();
	gint this_year = Year();
	return that_year - this_year;
}

gint GDateTime::YearsTo(const GDate &date) const
{
	gint that_year = date.Year();
	gint this_year = Year();
	return that_year - this_year;
}

gint GDateTime::DaysTo(const GDateTime &datetime) const
{
	gint that_year = datetime.Year();
	gint this_year = Year();
	gint that_day_of_year = datetime.DayOfYear();
	gint this_day_of_year = DayOfYear();

	if (that_year == this_year)
	{
		return that_day_of_year - this_day_of_year;
	}
	else if (that_year > this_year)
	{
		gint days_to = 0;

		guint days_in_a_year = 365;
		if (GDateTime::IsLeapYear(this_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - this_day_of_year - 1);

		while (++this_year < that_year)
		{
			if (GDateTime::IsLeapYear(this_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
			days_to += days_in_a_year;
		}

		days_to += (that_day_of_year + 1);

		return days_to;
	}
	else
	{
		gint days_to = 0;

		guint days_in_a_year = 365;
		if (GDateTime::IsLeapYear(that_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - that_day_of_year - 1);

		while (++that_year < this_year)
		{
			if (GDateTime::IsLeapYear(that_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
			days_to += days_in_a_year;
		}

		days_to += (this_day_of_year + 1);

		return 0 - days_to;
	}
}

gint GDateTime::DaysTo(const GDate &date) const
{
	gint that_year = date.Year();
	gint this_year = Year();
	gint that_day_of_year = date.DayOfYear();
	gint this_day_of_year = DayOfYear();

	if (that_year == this_year)
	{
		return that_day_of_year - this_day_of_year;
	}
	else if (that_year > this_year)
	{
		gint days_to = 0;

		guint days_in_a_year = 365;
		if (GDateTime::IsLeapYear(this_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - this_day_of_year - 1);

		while (++this_year < that_year)
		{
			if (GDateTime::IsLeapYear(this_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
			days_to += days_in_a_year;
		}

		days_to += (that_day_of_year + 1);

		return days_to;
	}
	else
	{
		gint days_to = 0;

		guint days_in_a_year = 365;
		if (GDateTime::IsLeapYear(that_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - that_day_of_year - 1);

		while (++that_year < this_year)
		{
			if (GDateTime::IsLeapYear(that_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
			days_to += days_in_a_year;
		}

		days_to += (this_day_of_year + 1);

		return 0 - days_to;
	}
}

gint GDateTime::HoursTo(const GDateTime &datetime) const
{
	gint hours_to = DaysTo(datetime) * 24;
	hours_to -= Hour();
	hours_to += datetime.Hour();
	return hours_to;
}

gint GDateTime::MinutesTo(const GDateTime &datetime) const
{
	gint minutes_to = HoursTo(datetime) * 60;
	minutes_to -= Minute();
	minutes_to += datetime.Minute();
	return minutes_to;
}

gint GDateTime::SecondsTo(const GDateTime &datetime) const
{
	gint seconds_to = MinutesTo(datetime) * 60;
	seconds_to -= Second();
	seconds_to += datetime.Second();
	return seconds_to;
}

gint64 GDateTime::MillisecondsTo(const GDateTime &datetime) const
{
	gint milliseconds_to = SecondsTo(datetime) * 1000;
	milliseconds_to -= Millisecond();
	milliseconds_to += datetime.Millisecond();
	return milliseconds_to;
}

GDateTime &GDateTime::AddYears(gint y)
{
	if (y == 0)
	{
		return *this;
	}
	guint old_year = Year();
	guint new_year = old_year + y;

	guint new_month = Month();
	guint new_day_of_month = Day();

	if (!GDateTime::IsLeapYear(new_year))
	{
		// 新的年份是平年，则可能出现2月29日的错误
		if (new_month == 2 && new_day_of_month == 29)
		{
			// 2月29日，对于当前年份是非法的，改为3月1日
			new_month = 3;
			new_day_of_month = 1;

			SetMonth(new_month);
			SetDayOfMonth(new_day_of_month);
		}
	}

	guint new_day_of_year = 0, new_day_of_week = 0;
	GDateTime::DayOfMonthToDayOfYear(new_year, new_month, new_day_of_month, new_day_of_year);
	GDateTime::DayOfMonthToDayOfWeek(new_year, new_month, new_day_of_month, new_day_of_week);

	SetYear(new_year);
	SetDayOfYear(new_day_of_year);
	SetDayOfWeek(new_day_of_week);
	
	return *this;
}

GDateTime &GDateTime::AddDays(gint d)
{
	if (d == 0)
	{
		return *this;
	}
	guint new_year = Year();
	gint old_day_of_year = DayOfYear();
	gint new_day_of_year = old_day_of_year + d;

	guint days_in_a_year = 365;
	if (GDateTime::IsLeapYear(new_year))
	{
		days_in_a_year = 366;
	}

	while (new_day_of_year / days_in_a_year)
	{
		if (new_day_of_year > 0)
		{
			new_day_of_year = new_day_of_year - days_in_a_year;
			++new_year;
			if (GDateTime::IsLeapYear(new_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
		}
		else
		{
			--new_year;
			if (GDateTime::IsLeapYear(new_year))
			{
				days_in_a_year = 366;
			}
			else
			{
				days_in_a_year = 365;
			}
			new_day_of_year = new_day_of_year + days_in_a_year;
		}
	}

	guint new_month = 0, new_day_of_month = 0, new_day_of_week = 0;
	GDateTime::DayOfYearToDayOfMonth(new_year, new_day_of_year, new_month, new_day_of_month);
	GDateTime::DayOfMonthToDayOfWeek(new_year, new_month, new_day_of_month, new_day_of_week);

	SetYear(new_year);
	SetMonth(new_month);
	SetDayOfMonth(new_day_of_month);
	SetDayOfYear(new_day_of_year);
	SetDayOfWeek(new_day_of_week);
	return *this;
}

GDateTime &GDateTime::AddHours(gint h)
{
	if (h == 0)
	{
		return *this;
	}
	
	gint new_hour = Hour() + h;
	gint add_days = 0;
	guint hours_in_a_day = 24;
	while (new_hour / hours_in_a_day)
	{
		if (new_hour > 0)
		{
			new_hour = new_hour - hours_in_a_day;
			++add_days;
		}
		else
		{
			new_hour = new_hour + hours_in_a_day;
			--add_days;
		}
	}

	AddDays(add_days).SetHour(new_hour);
	return *this;
}

GDateTime &GDateTime::AddMinutes(gint mm)
{
	if (mm == 0)
	{
		return *this;
	}

	gint new_minute = Minute() + mm;
	gint add_hours = 0;
	guint minutes_in_an_hour = 60;
	while (new_minute / minutes_in_an_hour)
	{
		if (new_minute > 0)
		{
			new_minute = new_minute - minutes_in_an_hour;
			++add_hours;
		}
		else
		{
			new_minute = new_minute + minutes_in_an_hour;
			--add_hours;
		}
	}

	AddHours(add_hours).SetMinute(new_minute);
	return *this;
}

GDateTime &GDateTime::AddSeconds(gint s)
{
	if (s == 0)
	{
		return *this;
	}

	gint new_second = Second() + s;
	gint add_minutes = 0;
	guint seconds_in_a_minute = 60;
	while (new_second / seconds_in_a_minute)
	{
		if (new_second > 0)
		{
			new_second = new_second - seconds_in_a_minute;
			++add_minutes;
		}
		else
		{
			new_second = new_second + seconds_in_a_minute;
			--add_minutes;
		}
	}

	AddMinutes(add_minutes).SetSecond(new_second);
	return *this;
}

GDateTime &GDateTime::AddMilliseconds(gint ms)
{
	if (ms == 0)
	{
		return *this;
	}

	gint new_millisecond = Millisecond() + ms;
	gint add_seconds = 0;
	guint milliseconds_in_a_second = 1000;
	while (new_millisecond / milliseconds_in_a_second)
	{
		if (new_millisecond > 0)
		{
			new_millisecond = new_millisecond - milliseconds_in_a_second;
			++add_seconds;
		}
		else
		{
			new_millisecond = new_millisecond + milliseconds_in_a_second;
			--add_seconds;
		}
	}

	AddSeconds(add_seconds).SetMillisecond(new_millisecond);
	return *this;
}

GObjectP GDateTime::Clone() const
{
	return GObjectP(new GDateTime(*this));
}

const GObject *GDateTime::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

gbool GDateTime::Unboxing(const GObject *obj)
{
	const GDateTime *dt = dynamic_cast<const GDateTime *>(obj);
	if (GNULL == dt)
	{
		return false;
	}
	*this = (*dt);
	return true;
}

GString GDateTime::ToString() const
{
	// 1991-02-28 20:40 00:000
	GString str;
	str.Reserve(23);
	str.Append(GString::Number(Year()));
	str.Append("-");
	str.Append(GString::Number(Month()));
	str.Append("-");
	str.Append(GString::Number(Day()));
	str.Append(" ");
	str.Append(GString::Number(Hour()));
	str.Append(":");
	str.Append(GString::Number(Minute()));
	str.Append(" ");
	str.Append(GString::Number(Second()));
	str.Append(":");
	str.Append(GString::Number(Millisecond()));
	return str;
}

GBytes GDateTime::ToBytes() const
{
	return GBytes(m_tDateTime, G_DATE_TIME_SIZE);
}

guint GDateTime::ClassCode() const
{
	return GDateTime::CLASS_CODE;
}

guint GDateTime::HashCode() const
{
	gtime timestamp = Timestamp();
	return timestamp << 10 + Millisecond(); // * 1024
}

gbool GDateTime::Equals(const GObject *obj) const
{
	const GDateTime *dt = dynamic_cast<const GDateTime *>(obj);
	if (GNULL == dt)
	{
		return false;
	}
	return *this == *dt;
}

gbool GDateTime::Serializable() const
{
	return true;
}

GDateTime &GDateTime::operator=(const GDateTime &datetime)
{
	if (this == &datetime)
	{
		return *this;
	}
	SetDateTime(datetime);
	return *this;
}

GDateTime &GDateTime::operator=(GDateTime &&datetime)
{
	if (this == &datetime)
	{
		return *this;
	}
	SetDateTime(GForward<GDateTime>(datetime));
	return *this;
}

GDateTime GDateTime::Birderyu_Birthday()
{
	// my birthday
	return GDateTime(1991, 2, 28, 20, 40, 0, 0);
}

gbool operator==(const GDateTime &dt1, const GDateTime &dt2)
{
	return dt1.Year() == dt2.Year() &&
		dt1.Month() == dt2.Month() &&
		dt1.Day() == dt2.Day() &&
		dt1.Hour() == dt2.Hour() &&
		dt1.Minute() == dt2.Minute() &&
		dt1.Second() == dt2.Second() &&
		dt1.Millisecond() == dt2.Millisecond();
}

gbool operator!=(const GDateTime &dt1, const GDateTime &dt2)
{
	return !(dt1 == dt2);
}

gbool operator>(const GDateTime &dt1, const GDateTime &dt2)
{
	guint y1 = dt1.Year(), y2 = dt2.Year();
	if (y1 > y2)
	{
		return true;
	}
	else if (y1 < y2)
	{
		return false;
	}
	else
	{
		guint m1 = dt1.Month(), m2 = dt2.Month();
		if (m1 > m2)
		{
			return true;
		}
		else if (m1 < m2)
		{
			return false;
		}
		else
		{
			guint d1 = dt1.Day(), d2 = dt2.Day();
			if (d1 > d2)
			{
				return true;
			}
			else if (d1 < d2)
			{
				return false;
			}
			else
			{
				guint h1 = dt1.Hour(), h2 = dt2.Hour();
				if (h1 > h2)
				{
					return true;
				}
				else if (h1 < h2)
				{
					return false;
				}
				else
				{
					guint mm1 = dt1.Minute(), mm2 = dt2.Minute();
					if (mm1 > mm2)
					{
						return true;
					}
					else if (mm1 < mm2)
					{
						return false;
					}
					else
					{
						guint s1 = dt1.Second(), s2 = dt2.Second();
						if (s1 > s2)
						{
							return true;
						}
						else if (s1 < s2)
						{
							return false;
						}
						else
						{
							guint ms1 = dt1.Millisecond(), ms2 = dt2.Millisecond();
							if (ms1 > ms2)
							{
								return true;
							}
							else if (ms1 < ms2)
							{
								return false;
							}
							else
							{
								// 完全相等
								return false;
							}
						}
					}
				}
			}
		}
	}
}

gbool operator>=(const GDateTime &dt1, const GDateTime &dt2)
{
	return !(dt1 < dt2);
}

gbool operator<(const GDateTime &dt1, const GDateTime &dt2)
{
	guint y1 = dt1.Year(), y2 = dt2.Year();
	if (y1 < y2)
	{
		return true;
	}
	else if (y1 > y2)
	{
		return false;
	}
	else
	{
		guint m1 = dt1.Month(), m2 = dt2.Month();
		if (m1 < m2)
		{
			return true;
		}
		else if (m1 > m2)
		{
			return false;
		}
		else
		{
			guint d1 = dt1.Day(), d2 = dt2.Day();
			if (d1 < d2)
			{
				return true;
			}
			else if (d1 > d2)
			{
				return false;
			}
			else
			{
				guint h1 = dt1.Hour(), h2 = dt2.Hour();
				if (h1 < h2)
				{
					return true;
				}
				else if (h1 > h2)
				{
					return false;
				}
				else
				{
					guint mm1 = dt1.Minute(), mm2 = dt2.Minute();
					if (mm1 < mm2)
					{
						return true;
					}
					else if (mm1 > mm2)
					{
						return false;
					}
					else
					{
						guint s1 = dt1.Second(), s2 = dt2.Second();
						if (s1 < s2)
						{
							return true;
						}
						else if (s1 > s2)
						{
							return false;
						}
						else
						{
							guint ms1 = dt1.Millisecond(), ms2 = dt2.Millisecond();
							if (ms1 < ms2)
							{
								return true;
							}
							else if (ms1 > ms2)
							{
								return false;
							}
							else
							{
								// 完全相等
								return false;
							}
						}
					}
				}
			}
		}
	}
}

gbool operator<=(const GDateTime &dt1, const GDateTime &dt2)
{
	return !(dt1 > dt2);
}

#undef G_DATA_TIME_SIZE_MILLISECOND	
#undef G_DATA_TIME_SIZE_SECOND			
#undef G_DATA_TIME_SIZE_MINUTE			
#undef G_DATA_TIME_SIZE_HOUR			
#undef G_DATA_TIME_SIZE_DAY_OF_WEEK	
#undef G_DATA_TIME_SIZE_DAY_OF_YEAR	
#undef G_DATA_TIME_SIZE_DAY			
#undef G_DATA_TIME_SIZE_MONTH			
#undef G_DATA_TIME_SIZE_YEAR						
#undef G_DATA_TIME_OFFSET_MILLISECOND
#undef G_DATA_TIME_OFFSET_SECOND		
#undef G_DATA_TIME_OFFSET_MINUTE		
#undef G_DATA_TIME_OFFSET_HOUR			
#undef G_DATA_TIME_OFFSET_DAY_OF_WEEK
#undef G_DATA_TIME_OFFSET_DAY_OF_YEAR
#undef G_DATA_TIME_OFFSET_DAY
#undef G_DATA_TIME_OFFSET_MONTH
#undef G_DATA_TIME_OFFSET_YEAR
#undef G_DATA_TIME_OFFSET_TIME
#undef G_DATA_TIME_OFFSET_DATE
#undef G_DATA_TIME_FIRST_YEAR