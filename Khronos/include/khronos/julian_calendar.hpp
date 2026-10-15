#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/calendar.hpp>

namespace khronos {
	// jd_to_gregorian(jd, year, month, day)
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);

	// jd_to_gregorian(year, month, day, hour, min, sec)
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& seconds);

	inline jdn_t jd_to_jdn(const jd_t& jd) {
		return static_cast<jdn_t> (floor(jd + 0.5));
	}

}