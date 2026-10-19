#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/


#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/julian_day.hpp>

namespace khronos {
	
	constexpr float JULIAN_EPOCH = 1'721'423.5; 

	

	constexpr bool is_julian_leapyear(year_t y) {
		return (y % 4 == 0);
	}

	constexpr day_t julian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}

	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const* julian_month_name(month_t month) {
		return civil::month_name_long(month);
	}


	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const* julian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}

	constexpr jdn_t julian_to_jdn(year_t const& year, month_t const& month, day_t const& day) {
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;

		return static_cast<jdn_t>(day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083.5);
	}

	constexpr jd_t julian_to_jd(year_t const& year, month_t const& month, day_t const& day, hour_t const& hour = 0, minute_t const& minute = 0, second_t const& second = 0) {
		jdn_t jdn = julian_to_jdn(year, month, day); 
		tod_t timeOfDay = tod(hour, minute, second); 

		return static_cast<jd_t>(jdn + timeOfDay); 
	}



}