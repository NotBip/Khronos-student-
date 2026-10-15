/**	@file Jd.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <sstream>

using namespace khronos;

	Jd::Jd(now_t t) : jd_(0) {
		time_t nowTime = time(NULL); 
		struct tm tmNow; 
		localtime_s(&tmNow, &nowTime);

		if(t == WTIMEOFDAY)
			jd_ = gregorian_to_jd(
				year_t(tmNow.tm_year) + 1900,
				month_t(tmNow.tm_mon) + 1,
				day_t(tmNow.tm_mday), 
				hour_t(tmNow.tm_hour),
				minute_t(tmNow.tm_min), 
				second_t(tmNow.tm_sec)
			); 
		else 
			jd_ = gregorian_to_jd(
				year_t(tmNow.tm_year) + 1900,
				month_t(tmNow.tm_mon) + 1,
				day_t(tmNow.tm_mday)
			);
	}




	std::string Jd::to_string() const {
		std::ostringstream oss;

		oss << jd_; 
		return oss.str();
	}

