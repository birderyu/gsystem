#ifndef _CORE_DATE_TIME_H_
#define _CORE_DATE_TIME_H_

#include "gobject.h"
#include "gdatetimedefine.h"

class GDate;
class GTime;
class GVariety;

// 年(2)-月(1)-日(1)-星期几(1)-一年中的第几天(2) = 7
// 时(1)-分(1)-秒(1)-毫秒数(2) = 5
// 插入了4位无效数位，用于内存对齐
// 其中小时之前插入1位，秒数之后插入了1位，毫秒数之后插入2位，实际内存布局是：
// [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
// └───┘└─┘└─┘└─┘└───┘  └─┘└─┘└─┘      └───┘
//   年   月  日 星期 年天    时  分  秒        毫秒
class GAPI GDateTime final 
	: public GObject
{
	friend class GDate;
	friend class GTime;
	friend class GVariety;
	friend GAPI gbool operator==(const GDateTime &dt1, const GDateTime &dt2);
	friend GAPI gbool operator!=(const GDateTime &dt1, const GDateTime &dt2);
	friend GAPI gbool operator>(const GDateTime &dt1, const GDateTime &dt2);
	friend GAPI gbool operator>=(const GDateTime &dt1, const GDateTime &dt2);
	friend GAPI gbool operator<(const GDateTime &dt1, const GDateTime &dt2);
	friend GAPI gbool operator<=(const GDateTime &dt1, const GDateTime &dt2);

public:
	enum { CLASS_CODE = CLASS_CODE_DATE_TIME, };
	
public: // 静态方法
	static GDateTime Now();
	static GDateTime Parse(const GString &time);
	static gtime NowTimestamp();
	static gbool IsLeapYear(guint year);
	static gvoid DayOfMonthToDayOfYear(guint year, guint month, guint day, 
		guint &day_of_year);
	static gvoid DayOfMonthToDayOfWeek(guint year, guint month, guint day,
		guint &day_of_week);
	static gvoid DayOfYearToDayOfMonth(guint year, guint day_of_year,
		guint &month, guint &day);
	static gvoid DayOfYearToDayOfWeek(guint year, guint day_of_year,
		guint &day_of_week);

public: // 构造方法
	GDateTime();
	GDateTime(gtime timestamp);
	GDateTime(const GDate &date, const GTime &time);
	GDateTime(guint year, guint month, guint day,
		guint hour, guint minute, guint second, guint millisecond);
	GDateTime(guint year, guint day_of_year,
		guint hour, guint minute, guint second, guint millisecond);
	GDateTime(const GDateTime &datetime);
	GDateTime(GDateTime &&datetime);

public: // Getter
	guint Year() const; // guint16
	guint Month() const; // [1,12]
	guint Day() const; // [1,31], day of month
	guint DayOfYear() const; // [0,365]
	guint DayOfWeek() const; // [1,7]
	guint Hour() const; // [0,23]
	guint Minute() const; // [0,59]
	guint Second() const; // [0,59]
	guint Millisecond() const; // [0, 999]
	gtime Timestamp() const;
	GDate Date() const;
	GTime Time() const;

public: // Setter
	gbool SetDateTime(gtime timestamp);
	gvoid SetDateTime(const GDate &date, const GTime &time);
	gvoid SetDateTime(guint year, guint month, guint day,
		guint hour, guint minute, guint second, guint millisecond);
	gvoid SetDateTime(guint year, guint day_of_year,
		guint hour, guint minute, guint second, guint millisecond);
	gvoid SetDateTime(const GDateTime &datetime);
	gvoid SetDateTime(GDateTime &&datetime);
	gvoid SetDate(const GDate &date);
	gvoid SetDate(guint year, guint month, guint day);
	gvoid SetDate(guint year, guint day_of_year);
	gvoid SetTime(const GTime &time);
	gvoid SetTime(guint hour, guint minute, guint second, guint millisecond = 0);
	gvoid SetYear(guint y); // guint16
	gvoid SetMonth(guint m); // guint8
	gvoid SetMonth(const GMonth &m);
	gvoid SetDay(guint d); // guint8, day of month
	gvoid SetHour(guint h); // guint8
	gvoid SetMinute(guint mm); // guint8
	gvoid SetSecond(guint s); // guint8
	gvoid SetMillisecond(guint ms); // guint16

public: // 日期时间计算
	gint YearsTo(const GDateTime &datetime) const;
	gint YearsTo(const GDate &date) const;
	gint DaysTo(const GDateTime &datetime) const;
	gint DaysTo(const GDate &date) const;
	gint HoursTo(const GDateTime &datetime) const;
	gint MinutesTo(const GDateTime &datetime) const;
	gint SecondsTo(const GDateTime &datetime) const;
	gint64 MillisecondsTo(const GDateTime &datetime) const;
	GDateTime &AddYears(gint y);
	GDateTime &AddDays(gint d);
	GDateTime &AddHours(gint h);
	GDateTime &AddMinutes(gint mm);
	GDateTime &AddSeconds(gint s);
	GDateTime &AddMilliseconds(gint ms);

public: // Object
	GObjectP Clone() const;
	const GObject *Boxing() const;
	gbool Unboxing(const GObject *obj);
	GString ToString() const;
	GBytes ToBytes() const;
	guint ClassCode() const;
	guint HashCode() const;
	gbool Equals(const GObject *obj) const;
	gbool Serializable() const;
	template<typename ArchiveT> gbool Serialize(ArchiveT &archive) const;
	template<typename ArchiveT> gbool Deserialize(ArchiveT &archive);

public: // 符号重载
	GDateTime &operator=(const GDateTime &datetime);
	GDateTime &operator=(GDateTime &&datetime);

private: // 私有方法
	GDateTime(const gbyte *val);
	gvoid SetDayOfMonth(guint mday);
	gvoid SetDayOfYear(guint yday);
	gvoid SetDayOfWeek(guint wday);

private: // 私有成员
	gbyte m_tDateTime[G_DATE_TIME_SIZE];

private:
	static GDateTime Birderyu_Birthday();
};

template<typename ArchiveT>
GINLINE gbool GDateTime::Serialize(ArchiveT &archive) const
{
	if (!archive.Input())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	archive.Attach(m_tDateTime, G_DATE_TIME_SIZE);
	return true;
}

template<typename ArchiveT>
GINLINE gbool GDateTime::Deserialize(ArchiveT &archive)
{
	if (!archive.Output())
	{
		return false;
	}
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	archive.Detach(m_tDateTime, G_DATE_TIME_SIZE);
	return true;
}

GAPI gbool operator==(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator!=(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator>(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator>=(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator<(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator<=(const GDateTime &dt1, const GDateTime &dt2);

#endif // _CORE_DATE_TIME_H_