#ifndef _CORE_DATE_TIME_DEFINE_H_
#define _CORE_DATE_TIME_DEFINE_H_

#include "gglobal.h"

enum class GMonth
	: guint
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December,
};

enum class GDayOfMonth
	: guint
{
	Day_1 = 1,
	Day_2,
	Day_3,
	Day_4,
	Day_5,
	Day_6,
	Day_7,
	Day_8,
	Day_9,
	Day_10,
	Day_11,
	Day_12,
	Day_13,
	Day_14,
	Day_15,
	Day_16,
	Day_17,
	Day_18,
	Day_19,
	Day_20,
	Day_21,
	Day_22,
	Day_23,
	Day_24,
	Day_25,
	Day_26,
	Day_27,
	Day_28,
	Day_29,
	Day_30,
	Day_31
};

enum class GDayOfWeek
	: guint
{
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

enum class GHour
	: guint
{
	Hour_0 = 0,
	Hour_1,
	Hour_2,
	Hour_3,
	Hour_4,
	Hour_5,
	Hour_6,
	Hour_7,
	Hour_8,
	Hour_9,
	Hour_10,
	Hour_11,
	Hour_12,
	Hour_13,
	Hour_14,
	Hour_15,
	Hour_16,
	Hour_17,
	Hour_18,
	Hour_19,
	Hour_20,
	Hour_21,
	Hour_22,
	Hour_23
};

#endif // _CORE_DATE_TIME_DEFINE_H_
