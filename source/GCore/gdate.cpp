#include "gdate.h"
#include "gdatetime.h"
#include "gbytes.h"
#include "gstring.h"

#ifdef G_SYSTEM_WINDOWS 
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#include <windows.h>
#include <time.h>
#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

#define G_DATA_FIRST_YEAR			1900
#define G_DATA_OFFSET_YEAR			0
#define G_DATA_OFFSET_MONTH			2
#define G_DATA_OFFSET_DAY			3
#define G_DATA_OFFSET_DAY_OF_YEAR	4
#define G_DATA_OFFSET_DAY_OF_WEEK	6
#define G_DATA_SIZE_YEAR			2
#define G_DATA_SIZE_MONTH			1
#define G_DATA_SIZE_DAY				1
#define G_DATA_SIZE_DAY_OF_YEAR		2
#define G_DATA_SIZE_DAY_OF_WEEK		1

GDate GDate::Now()
{
	return GDate(::time(GNULL));
}

GDate GDate::Parse(const GString &time)
{
	// TODO
	return GDate();
}

gbool GDate::IsLeapYear(guint year)
{
	return GDateTime::IsLeapYear(year);
}

gvoid GDate::DayOfMonthToDayOfYear(guint year, guint month, guint day, guint &day_of_year)
{
	GDateTime::DayOfMonthToDayOfYear(year, month, day, day_of_year);
}

gvoid GDate::DayOfMonthToDayOfWeek(guint year, guint month, guint day, guint &day_of_week)
{
	GDateTime::DayOfMonthToDayOfWeek(year, month, day, day_of_week);
}

gvoid GDate::DayOfYearToDayOfMonth(guint year, guint day_of_year, guint &month, guint &day)
{
	GDateTime::DayOfYearToDayOfMonth(year, day_of_year, month, day);
}

gvoid GDate::DayOfYearToDayOfWeek(guint year, guint day_of_year, guint &day_of_week)
{
	GDateTime::DayOfYearToDayOfWeek(year, day_of_year, day_of_week);
}

GDate::GDate()
{
	GMemSet(m_tDate, 0, G_DATE_SIZE);
}

GDate::GDate(gtime timestamp)
{
	GMemSet(m_tDate, 0, G_DATE_SIZE);
	SetDate(timestamp);
}

GDate::GDate(guint year, guint month, guint day)
{
	SetDate(year, month, day);
}

GDate::GDate(guint year, guint day_of_year)
{
	SetDate(year, day_of_year);
}

GDate::GDate(const GDate &date)
{
	SetDate(date);
}

GDate::GDate(GDate &&date)
{
	SetDate(GForward<GDate>(date));
}

GDate::GDate(const gbyte *val)
{
	GMemCopy(m_tDate, val, G_DATE_SIZE);
}

guint GDate::Year() const
{
	GIntegerForSize<G_DATA_SIZE_YEAR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDate + G_DATA_OFFSET_YEAR, &val);
	return val;
}

guint GDate::Month() const
{
	GIntegerForSize<G_DATA_SIZE_MONTH>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDate + G_DATA_OFFSET_MONTH, &val);
	return val;
}

guint GDate::Day() const
{
	GIntegerForSize<G_DATA_SIZE_DAY>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDate + G_DATA_OFFSET_DAY, &val);
	return val;
}

guint GDate::DayOfYear() const
{
	GIntegerForSize<G_DATA_SIZE_DAY_OF_YEAR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDate + G_DATA_OFFSET_DAY_OF_YEAR, &val);
	return val;
}

guint GDate::DayOfWeek() const
{
	GIntegerForSize<G_DATA_SIZE_DAY_OF_WEEK>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tDate + G_DATA_OFFSET_DAY_OF_WEEK, &val);
	return val;
}

gbool GDate::SetDate(gtime timestamp)
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

	SetYear(t.tm_year + G_DATA_FIRST_YEAR);
	SetMonth(t.tm_mon + 1);
	SetDayOfMonth(t.tm_mday);
	SetDayOfWeek(wday);
	SetDayOfYear(t.tm_yday + 1);

	return true;
}

gvoid GDate::SetDate(const GDate &date)
{
	GMemCopy(m_tDate, date.m_tDate, G_DATE_SIZE);
}

gvoid GDate::SetDate(GDate &&date)
{
	GMemCopy(m_tDate, date.m_tDate, G_DATE_SIZE);
}

gvoid GDate::SetDate(guint year, guint month, guint day)
{
	guint day_of_year = 0, day_of_week = 0;
	GDate::DayOfMonthToDayOfYear(year, month, day,
		day_of_year);
	GDate::DayOfMonthToDayOfWeek(year, month, day,
		day_of_week);

	SetYear(year);
	SetMonth(month);
	SetDayOfMonth(day);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDate::SetDate(guint year, guint day_of_year)
{
	guint month = 0, day = 0, day_of_week = 0;
	GDate::DayOfYearToDayOfMonth(year, day_of_year,
		month, day);
	GDate::DayOfMonthToDayOfWeek(year, month, day,
		day_of_week);

	SetYear(year);
	SetMonth(month);
	SetDayOfMonth(day);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDate::SetYear(guint y)
{
	using Type = GIntegerForSize<G_DATA_SIZE_YEAR>::Unsigned;
	Type val = y;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDate + G_DATA_OFFSET_YEAR);
}

gvoid GDate::SetMonth(guint m)
{
	using Type = GIntegerForSize<G_DATA_SIZE_MONTH>::Unsigned;
	Type val = m;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDate + G_DATA_OFFSET_MONTH);
}

gvoid GDate::SetMonth(const GMonth &m)
{
	SetMonth(static_cast<guint>(m));
}

gvoid GDate::SetDay(guint d)
{
	guint year = Year();
	guint month = Month();
	guint day_of_year = 0, day_of_week = 0;
	GDate::DayOfMonthToDayOfYear(year, month, d, day_of_year);
	GDate::DayOfMonthToDayOfWeek(year, month, d, day_of_week);

	SetDayOfMonth(d);
	SetDayOfYear(day_of_year);
	SetDayOfWeek(day_of_week);
}

gvoid GDate::SetDayOfMonth(guint mday)
{
	using Type = GIntegerForSize<G_DATA_SIZE_DAY>::Unsigned;
	Type val = mday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDate + G_DATA_OFFSET_DAY);
}

gvoid GDate::SetDayOfYear(guint yday)
{
	using Type = GIntegerForSize<G_DATA_SIZE_DAY_OF_YEAR>::Unsigned;
	Type val = yday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDate + G_DATA_OFFSET_DAY_OF_YEAR);
}

gvoid GDate::SetDayOfWeek(guint wday)
{
	using Type = GIntegerForSize<G_DATA_SIZE_DAY_OF_WEEK>::Unsigned;
	Type val = wday;
	GBytes::ArithmeticToBytes<Type>(&val, m_tDate + G_DATA_OFFSET_DAY_OF_WEEK);
}

guint GDate::YearsTo(const GDateTime &datetime) const
{
	gint that_year = datetime.Year();
	gint this_year = Year();
	return that_year - this_year;
}

guint GDate::YearsTo(const GDate &date) const
{
	gint that_year = date.Year();
	gint this_year = Year();
	return that_year - this_year;
}

guint GDate::DaysTo(const GDateTime &datetime) const
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
		if (GDate::IsLeapYear(this_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - this_day_of_year - 1);

		while (++this_year < that_year)
		{
			if (GDate::IsLeapYear(this_year))
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
		if (GDate::IsLeapYear(that_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - that_day_of_year - 1);

		while (++that_year < this_year)
		{
			if (GDate::IsLeapYear(that_year))
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

guint GDate::DaysTo(const GDate &date) const
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
		if (GDate::IsLeapYear(this_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - this_day_of_year - 1);

		while (++this_year < that_year)
		{
			if (GDate::IsLeapYear(this_year))
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
		if (GDate::IsLeapYear(that_year))
		{
			days_in_a_year = 366;
		}
		days_to += (days_in_a_year - that_day_of_year - 1);

		while (++that_year < this_year)
		{
			if (GDate::IsLeapYear(that_year))
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

GDate &GDate::AddYears(gint y)
{
	if (y == 0)
	{
		return *this;
	}
	guint old_year = Year();
	guint new_year = old_year + y;

	guint new_month = Month();
	guint new_day_of_month = Day();

	if (!GDate::IsLeapYear(new_year))
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
	GDate::DayOfMonthToDayOfYear(new_year, new_month, new_day_of_month, new_day_of_year);
	GDate::DayOfMonthToDayOfWeek(new_year, new_month, new_day_of_month, new_day_of_week);

	SetYear(new_year);
	SetDayOfYear(new_day_of_year);
	SetDayOfWeek(new_day_of_week);

	return *this;
}

GDate &GDate::AddDays(gint d)
{
	if (d == 0)
	{
		return *this;
	}
	guint new_year = Year();
	gint old_day_of_year = DayOfYear();
	gint new_day_of_year = old_day_of_year + d;

	guint days_in_a_year = 365;
	if (GDate::IsLeapYear(new_year))
	{
		days_in_a_year = 366;
	}

	while (new_day_of_year / days_in_a_year)
	{
		if (new_day_of_year > 0)
		{
			new_day_of_year = new_day_of_year - days_in_a_year;
			++new_year;
			if (GDate::IsLeapYear(new_year))
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
			if (GDate::IsLeapYear(new_year))
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
	GDate::DayOfYearToDayOfMonth(new_year, new_day_of_year, new_month, new_day_of_month);
	GDate::DayOfMonthToDayOfWeek(new_year, new_month, new_day_of_month, new_day_of_week);

	SetYear(new_year);
	SetMonth(new_month);
	SetDayOfMonth(new_day_of_month);
	SetDayOfYear(new_day_of_year);
	SetDayOfWeek(new_day_of_week);
	return *this;
}

GString GDate::ToString() const
{
	// 1991-02-28
	GString str;
	str.Reserve(10);
	str.Append(GString::Number(Year()));
	str.Append("-");
	str.Append(GString::Number(Month()));
	str.Append("-");
	str.Append(GString::Number(Day()));
	return str;
}

#undef G_DATA_SIZE_DAY_OF_WEEK		
#undef G_DATA_SIZE_DAY_OF_YEAR	
#undef G_DATA_SIZE_DAY	
#undef G_DATA_SIZE_MONTH	
#undef G_DATA_SIZE_YEAR	
#undef G_DATA_OFFSET_DAY_OF_WEEK
#undef G_DATA_OFFSET_DAY_OF_YEAR	
#undef G_DATA_OFFSET_DAY	
#undef G_DATA_OFFSET_MONTH	
#undef G_DATA_OFFSET_YEAR	
#undef G_DATA_FIRST_YEAR