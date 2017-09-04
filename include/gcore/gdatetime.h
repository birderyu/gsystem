/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gdatetime.h
** @brief 日期时间类
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_DATE_TIME_H_
#define _CORE_DATE_TIME_H_

#include "gobject.h"
#include "gserializable.h"
#include "gdtdef.h"

namespace gsystem { // gsystem
	class GDate;
	class GTime;
	class GVariety;
} // namespace gsystem

namespace gsystem { // gsystem

// 年(2)-月(1)-日(1)-星期几(1)-一年中的第几天(2) = 7
// 时(1)-分(1)-秒(1)-毫秒数(2) = 5
// 插入了4位无效数位，用于内存对齐
// 其中小时之前插入1位，秒数之后插入了1位，毫秒数之后插入2位，实际内存布局是：
// [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
// └───┘└─┘└─┘└─┘└───┘  └─┘└─┘└─┘      └───┘
//   年   月  日 星期 年天    时  分  秒        毫秒

/********************************************************************************
**
** @brief 日期时间类
** 
** 日期时间类封装了日期和时间的相关方法
**
********************************************************************************/
class GAPI GDateTime final 
	: virtual public GObject
	, virtual public GSerializable
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
	/****************************************************************************
	**
	** @name Now
	** @brief 静态方法，获取当前时刻的日期时间
	** @return {GDateTime} 日期时间
	**
	****************************************************************************/
	static GDateTime Now();

	/****************************************************************************
	**
	** @name Parse
	** @brief 静态方法，解析字符串获取日期时间
	** @param [in] time {const GString &} 以字符串表示的日期时间
	** @return {GDateTime} 日期时间
	**
	****************************************************************************/
	static GDateTime Parse(const GString &time);

	/****************************************************************************
	**
	** @name Now
	** @brief 静态方法，获取当前时刻的时间戳
	** @return {gtime} 时间戳
	**
	****************************************************************************/
	static gtime NowTimestamp();

	/****************************************************************************
	**
	** @name IsLeapYear
	** @brief 静态方法，判断年份是否为闰年
	** @param [in] year {guint} 年份
	** @return {gbool} 若是闰年，则返回true，否则返回false
	**
	****************************************************************************/
	static gbool IsLeapYear(guint year);

	/****************************************************************************
	**
	** @name DayOfMonthToDayOfYear
	** @brief 静态方法，给出某一年中某一月份的一天，求出该天是当前年份的第几天
	** @param [in] year {guint} 年份，从1开始计数，如数字1991表示公元1991年
	** @param [in] month {guint} 月份，从1开始计数，如数字2表示2月
	** @param [in] day {guint} 天，从1开始计数，如数字28表示28号
	** @param [out] day_of_year {guint &} 当前年份的第几天，从0开始计数，如数字58表示第59天
	**
	****************************************************************************/
	static gvoid DayOfMonthToDayOfYear(guint year, guint month, guint day, 
		guint &day_of_year);

	/****************************************************************************
	**
	** @name DayOfMonthToDayOfWeek
	** @brief 静态方法，给出某一年中某一月份的一天，求出该天是当前星期的第几天
	** @param [in] year {guint} 年份，从1开始计数，如数字1991表示公元1991年
	** @param [in] month {guint} 月份，从1开始计数，如数字2表示2月
	** @param [in] day {guint} 天，从1开始计数，如数字28表示28号
	** @param [out] day_of_week {guint &} 当前星期的第几天，从1开始计数，如数字4表示周四
	**
	****************************************************************************/
	static gvoid DayOfMonthToDayOfWeek(guint year, guint month, guint day,
		guint &day_of_week);

	/****************************************************************************
	**
	** @name DayOfYearToDayOfMonth
	** @brief 静态方法，给出某一年中第几天，求出该天是当前年份哪一个月的哪一天
	** @param [in] year {guint} 年份，从1开始计数，如数字1991表示公元1991年
	** @param [in] day_of_year {guint &} 当前年份的第几天，从0开始计数，如数字58表示第59天
	** @param [out] month {guint} 月份，从1开始计数，如数字2表示2月
	** @param [out] day {guint} 天，从1开始计数，如数字28表示28号
	**
	****************************************************************************/
	static gvoid DayOfYearToDayOfMonth(guint year, guint day_of_year,
		guint &month, guint &day);

	/****************************************************************************
	**
	** @name DayOfYearToDayOfWeek
	** @brief 静态方法，给出某一年中第几天，求出该天是当前星期的第几天
	** @param [in] year {guint} 年份，从1开始计数，如数字1991表示公元1991年
	** @param [in] day_of_year {guint &} 当前年份的第几天，从0开始计数，如数字58表示第59天
	** @param [out] day_of_week {guint &} 当前星期的第几天，从1开始计数，如数字4表示周四
	**
	****************************************************************************/
	static gvoid DayOfYearToDayOfWeek(guint year, guint day_of_year,
		guint &day_of_week);

public:
	/****************************************************************************
	**
	** @name GDateTime
	** @brief 构造函数（constructor）
	**
	** 构造一个空的日期
	**
	****************************************************************************/
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
	GObjectPtr Clone() const;
	const GObject *Boxing() const;
	gbool Unboxing(const GObject *obj);
	GString ToString() const;
	GBytes ToBytes() const;
	guint HashCode() const;
	gbool Equals(const GObject *obj) const;

	guint ClassCode() const GNOEXCEPT;
	GString ClassName() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

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

GAPI gbool operator==(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator!=(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator>(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator>=(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator<(const GDateTime &dt1, const GDateTime &dt2);
GAPI gbool operator<=(const GDateTime &dt1, const GDateTime &dt2);

} // namespace gsystem

#endif // _CORE_DATE_TIME_H_