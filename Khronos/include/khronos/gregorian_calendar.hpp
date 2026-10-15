#pragma once
/*
khronos\gregorian_calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'Gregorian calendar' declarations.
*/


#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>
#include <string>


namespace khronos {
	// LITERALS
	/* UDL - converts a Gregorian year CE to an astronomical Gregorian year. */
	inline year_t operator"" _CE(uint64_t year) {
		return static_cast<year_t> (year);
	}
	/* UDL - converts a Gregorian year BCE to an astronomical Gregorian year. */
	inline year_t operator"" _BCE(uint64_t year) {
		return -(static_cast<year_t>(year - 1));
	}

	// VALUES
	constexpr jd_t GREGORIAN_EPOCH = 1'721'425.5;



	// OPERATIONS
	/**	Leap year test for Proleptic Gregorian Calendar.
		@return 'true' if leap year, 'false' if not.
		@param year [in] Astronomical Gregorian year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
		*/
	// (𝑦𝑒𝑎𝑟 𝐦𝐨𝐝 4 = 0) 𝐚𝐧𝐝 (𝑦𝑒𝑎𝑟 𝐦𝐨𝐝 100 ≠ 0) 𝐨𝐫 (𝑦𝑒𝑎𝑟 𝐦𝐨𝐝 400 = 0)
	constexpr bool is_gregorian_leapyear(const year_t& year) {
		return ((year % 4 == 0) and (year % 100 != 0) or (year % 400 == 0));
	}


		/** Provide the number of days in the month of the Gregorian Calendar. */
	constexpr day_t gregorian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const* gregorian_month_name(month_t month) {
		return civil::month_name_long(month);
	}


	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const* gregorian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}

	// CLASSES
	// --------------------------------------------------------------------------------------
	/**	Proleptic Gregorian Calendar Date class. */
	// greg_to_jd (year, month, day)
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day);
	
	// greg_to_jd(year, month, day, hour, min, sec)
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds);



	// OPERATORS
	// ====================


} // end-of-namespace khronos