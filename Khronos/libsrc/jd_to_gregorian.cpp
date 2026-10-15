/*
khronos\jdn_to_gregorian.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'gregorian::from_jdn' implementation.
*/

#include <khronos/gregorian_calendar.hpp>

namespace khronos {
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");

		jd = floor(jd - 0.5) + 0.5;
		long long a = static_cast<long long>(jd + 0.5) + 32044;
		long long b = (4 * a + 3) / 146097;
		long long c = a - b * 146097 / 4;
		long long d = (4 * c + 3) / 1461;
		long long e = c - 1461 * d / 4;
		long long m = (5 * e + 2) / 153;
		day = static_cast<day_t>(e - (153 * m + 2) / 5 + 1);
		month = static_cast<month_t>(m + 3 - 12 * (m / 10));
		year = b * 100 + d - 4800 + m / 10;
	}

	namespace detail {
		tod_t jd_to_tod(jd_t jd) {
			return (jd + 0.5) - floor(jd + 0.5);
		}
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& seconds) {
		jd_to_gregorian(jd, year, month, day);
		tod_to_HMS(detail::jd_to_tod(jd), hour, minute, seconds);
	}


}