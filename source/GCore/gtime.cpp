#include "gtime.h"
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

#define G_TIME_OFFSET_HOUR			0
#define G_TIME_OFFSET_MINUTE		1
#define G_TIME_OFFSET_SECOND		2
#define G_TIME_OFFSET_MILLISECOND	4
#define G_TIME_SIZE_HOUR			1
#define G_TIME_SIZE_MINUTE			1
#define G_TIME_SIZE_SECOND			1
#define G_TIME_SIZE_MILLISECOND		2

GTime GTime::Now()
{
	GTime t;

#ifdef G_SYSTEM_WINDOWS

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	t.SetHour(st.wHour);
	t.SetMinute(st.wMinute);
	t.SetSecond(st.wSecond);
	t.SetMillisecond(st.wMilliseconds);

#else // !G_SYSTEM_WINDOWS

#endif // G_SYSTEM_WINDOWS

	return t;
}

GTime GTime::Parse(const GString &time)
{
	// TODO
	return GTime();
}

GTime::GTime()
{
	GMemSet(m_tTime, 0, G_TIME_SIZE);
}

GTime::GTime(gtime timestamp)
{
	GMemSet(m_tTime, 0, G_TIME_SIZE);
	SetTime(timestamp);
}

GTime::GTime(guint hour, guint minute, guint second, guint millisecond)
{
	SetTime(hour, minute, second, millisecond);
}

GTime::GTime(const GTime &time)
{
	SetTime(time);
}

GTime::GTime(GTime &&time)
{
	SetTime(GForward<GTime>(time));
}

GTime::GTime(const gbyte *val)
{
	GMemCopy(m_tTime, val, G_TIME_SIZE);
}

guint GTime::Hour() const
{
	GIntegerForSize<G_TIME_SIZE_HOUR>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tTime + G_TIME_OFFSET_HOUR, &val);
	return val;
}

guint GTime::Minute() const
{
	GIntegerForSize<G_TIME_SIZE_MINUTE>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tTime + G_TIME_OFFSET_MINUTE, &val);
	return val;
}

guint GTime::Second() const
{
	GIntegerForSize<G_TIME_SIZE_SECOND>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tTime + G_TIME_OFFSET_SECOND, &val);
	return val;
}

guint GTime::Millisecond() const
{
	GIntegerForSize<G_TIME_SIZE_MILLISECOND>::Unsigned val = 0;
	GBytes::BytesToArithmetic(m_tTime + G_TIME_OFFSET_MILLISECOND, &val);
	return val;
}

gbool GTime::SetTime(gtime timestamp)
{
	struct tm t = { 0 };
	if (0 != localtime_s(&t, &timestamp))
	{
		return false;
	}

	SetHour(t.tm_hour);
	SetMinute(t.tm_min);
	SetSecond(t.tm_sec);
	SetMillisecond(0);

	return true;
}

gvoid GTime::SetTime(const GTime &time)
{
	GMemCopy(m_tTime, time.m_tTime, G_TIME_SIZE);
}

gvoid GTime::SetTime(GTime &&time)
{
	GMemCopy(m_tTime, time.m_tTime, G_TIME_SIZE);
}

gvoid GTime::SetTime(guint hour, guint minute, guint second, guint millisecond)
{
	SetHour(hour);
	SetMinute(minute);
	SetSecond(second);
	SetMillisecond(millisecond);
}

gvoid GTime::SetHour(guint h)
{
	using Type = GIntegerForSize<G_TIME_SIZE_HOUR>::Unsigned;
	Type val = h;
	GBytes::ArithmeticToBytes<Type>(&val, m_tTime + G_TIME_OFFSET_HOUR);
}

gvoid GTime::SetMinute(guint mm)
{
	using Type = GIntegerForSize<G_TIME_SIZE_MINUTE>::Unsigned;
	Type val = mm;
	GBytes::ArithmeticToBytes<Type>(&val, m_tTime + G_TIME_OFFSET_MINUTE);
}

gvoid GTime::SetSecond(guint s)
{
	using Type = GIntegerForSize<G_TIME_SIZE_SECOND>::Unsigned;
	Type val = s;
	GBytes::ArithmeticToBytes<Type>(&val, m_tTime + G_TIME_OFFSET_SECOND);
}

gvoid GTime::SetMillisecond(guint ms)
{
	using Type = GIntegerForSize<G_TIME_SIZE_MILLISECOND>::Unsigned;
	Type val = ms;
	GBytes::ArithmeticToBytes<Type>(&val, m_tTime + G_TIME_OFFSET_MILLISECOND);
}

gint GTime::HoursTo(const GTime &time) const
{
	gint that_hour = time.Hour();
	gint this_hour = Hour();
	return that_hour - this_hour;
}

gint GTime::MinutesTo(const GTime &time) const
{
	gint minutes_to = HoursTo(time) * 60;
	minutes_to -= Minute();
	minutes_to += time.Minute();
	return minutes_to;
}

gint GTime::SecondsTo(const GTime &time) const
{
	gint seconds_to = MinutesTo(time) * 60;
	seconds_to -= Second();
	seconds_to += time.Second();
	return seconds_to;
}

gint GTime::MillisecondsTo(const GTime &time) const
{
	gint milliseconds_to = SecondsTo(time) * 1000;
	milliseconds_to -= Millisecond();
	milliseconds_to += time.Millisecond();
	return milliseconds_to;
}

GTime &GTime::AddHours(gint h)
{
	if (h == 0)
	{
		return *this;
	}

	gint new_hour = Hour() + h;
	guint hours_in_a_day = 24;
	while (new_hour / hours_in_a_day)
	{
		if (new_hour > 0)
		{
			new_hour = new_hour - hours_in_a_day;
		}
		else
		{
			new_hour = new_hour + hours_in_a_day;
		}
	}

	SetHour(new_hour);
	return *this;
}

GTime &GTime::AddMinutes(gint mm)
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

GTime &GTime::AddSeconds(gint s)
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

GTime &GTime::AddMilliseconds(gint ms)
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

GString GTime::ToString() const
{
	// 20:40 00:000
	GString str;
	str.Reserve(12);
	str.Append(GString::Number(Hour()));
	str.Append(":");
	str.Append(GString::Number(Minute()));
	str.Append(" ");
	str.Append(GString::Number(Second()));
	str.Append(":");
	str.Append(GString::Number(Millisecond()));
	return str;
}

#undef G_TIME_SIZE_MILLISECOND	
#undef G_TIME_SIZE_SECOND			
#undef G_TIME_SIZE_MINUTE			
#undef G_TIME_SIZE_HOUR					
#undef G_TIME_OFFSET_MILLISECOND
#undef G_TIME_OFFSET_SECOND		
#undef G_TIME_OFFSET_MINUTE		
#undef G_TIME_OFFSET_HOUR