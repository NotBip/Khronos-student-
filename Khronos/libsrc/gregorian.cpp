/**	@file gregorian.cpp;
	@author Garth Santor
	@date 2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>
#include <sstream>

using namespace khronos;

// default constructor
Gregorian::Gregorian(now_t t) {
	time_t nowTime = time(NULL);
	struct tm tmNow;
	localtime_s(&tmNow, &nowTime);

	if (t == WTIMEOFDAY) {
		year_ = year_t(tmNow.tm_year) + 1900;
		month_ = month_t(tmNow.tm_mon) + 1;
		day_ = day_t(tmNow.tm_mday);
		hour_ = hour_t(tmNow.tm_hour);
		minute_ = minute_t(tmNow.tm_min);
		second_ = second_t(tmNow.tm_sec);
	}
	else if (t == NOTIMEOFDAY) {
		year_ = year_t(tmNow.tm_year) + 1900;
		month_ = month_t(tmNow.tm_mon) + 1;
		day_ = day_t(tmNow.tm_mday);
	}

}

std::string HMSToString(hour_t const& hour, minute_t const& minute, second_t const& second) {
	std::ostringstream oss; 
	hour_t tempHour{}; 
	std::string suffix{}; 

	if (hour > 12) {
		tempHour = hour - 12; 
		suffix = "pm";
	} else if (hour == 0 || hour == 12) {
		tempHour = 12;
		suffix = "pm";
	}
	else {
		tempHour = hour; 
	}

	if(hour < 12)
		suffix = "am";

		oss << tempHour << ":"; 

	if (minute < 10)
		oss << "0" << minute << ":";
	else
		oss << minute << ":";

	if (second < 10)
		oss << "0" << second;
	else
		oss << second;

	oss << " " << suffix; 

	return oss.str(); 
}

std::string Gregorian::to_string() const {
	std::ostringstream oss;
	year_t tempYear{}; 
	std::string suffix{}; 

	if (this->year() < 0) {
		suffix = " BCE";
		tempYear = -this->year() + 1;
	}
	else {
		suffix = " CE";
		tempYear = this->year(); 
	}

	oss << gregorian_day_name(day_of_week(*this)) << ", " << gregorian_month_name(this->month()) << " " << this->day() << " " << tempYear << 
		suffix << ", " << HMSToString(this->hour(), this->minute(), this->second());

	return oss.str(); 
} 

namespace khronos {

	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& months) {
		year_t y = dt.year() + months.nMonths_ / 12; 
		month_t m = dt.month() + months.nMonths_ % 12; 
		int adjustment = (m - 1) / 12 + (m - 12) / 12; 
		y += adjustment; 
		m -= adjustment * 12; 
		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y))); 

		return Gregorian(y, m, d, dt.hour(), dt.minute(), dt.second()); 
	}

	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& years){

		day_t d = dt.day(); 

		if (dt.month() == 2 and dt.day() == 29 and not is_gregorian_leapyear(dt.year() + years.nYears_))
			d = 28; 

		return Gregorian(dt.year() + years.nYears_, dt.month(), d, dt.hour(), dt.minute(), dt.second()); 
	}

}






