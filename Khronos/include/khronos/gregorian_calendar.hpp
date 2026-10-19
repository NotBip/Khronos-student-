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

	constexpr char const* gregorian_day_name(day_t day) {
		return civil::day_name(day); 
	}

	// greg_to_jd (year, month, day)
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day);

	// greg_to_jd(year, month, day, hour, min, sec)
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds);



	// CLASSES
	// --------------------------------------------------------------------------------------
	/**	Proleptic Gregorian Calendar Date class. */

	class Gregorian {
		year_t year_ = 1;
		month_t month_ = 1;
		day_t day_ = 1;
		hour_t hour_ = 0; 
		minute_t minute_ = 0; 
		second_t second_ = 0; 


	public:
		Gregorian(now_t now = WTIMEOFDAY);

		constexpr Gregorian(year_t y, month_t m, day_t d) : year_(y), month_(m), day_(d) {}
		constexpr Gregorian(year_t y, month_t m, day_t d, hour_t h, minute_t min, second_t s) : year_(y), month_(m), day_(d), hour_(h), minute_(min), second_(s) {}

		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		void from_jd(jd_t jd) { jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return gregorian_to_jd(year_, month_, day_, hour_, minute_, second_); }

		Gregorian(Jd const& jd) { from_jd(jd.jd()); }

		operator Jd() const { return Jd(to_jd()); }

		Gregorian& operator = (Jd const& jd) { from_jd(jd.jd()); return *this; }

		std::string to_string() const;

	private: 
		Gregorian operator + (detail::packaged_month_real const&); 
		Gregorian operator - (detail::packaged_month_real const&);
		Gregorian operator + (detail::packaged_year_real const&);
		Gregorian operator - (detail::packaged_year_real const&);
	};

	inline civil_weekday_codes_long day_of_week(Jd jd) {
		return static_cast<civil_weekday_codes_long> (utility::mod(jd.jd() + 0.5, 7));
	}



	constexpr jdn_t gregorian_to_jdn_int(Gregorian const& g) {
		long long a = (14 - g.month()) / 12;
		long long y = g.year() + 4800 - a;
		long long m = g.month() + 12 * a - 3;
		return static_cast<jdn_t> (g.day() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045.5);
	}

	constexpr jdn_t operator - (Gregorian const& lhs, Gregorian const& rhs) {
		return (gregorian_to_jdn_int(lhs) - gregorian_to_jdn_int(rhs));
	}


	// Gregorian + month
	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& months);
	
	// Gregorian - month
	inline Gregorian operator - (Gregorian const& dt, detail::packaged_month_integer const& months) {
		return dt + detail::packaged_month_integer(-months.nMonths_);
	}

	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& years);

	// Gregorian - month
	inline Gregorian operator - (Gregorian const& dt, detail::packaged_year_integer const& years) { 
		return dt + detail::packaged_year_integer(-years.nYears_);
	}

	inline std::ostream& operator << (std::ostream& os, Gregorian const& g) {
		os << g.to_string(); 

		return os; 
	}

	// Element functions
	constexpr year_t year(Gregorian const& g) { return g.year(); }
	constexpr month_t month(Gregorian const& g) { return g.month(); }
	constexpr day_t day(Gregorian const& g) { return g.day(); }
	constexpr hour_t hour(Gregorian const& g) { return g.hour(); }
	constexpr minute_t minute(Gregorian const& g) { return g.minute(); }
	constexpr second_t second(Gregorian const& g) { return g.second(); }
}; // end-of-namespace khronos