#pragma once
/*	julian_day.hpp

	Khronos library Julian Day class declaration.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.25
	Repaced relational operators with <=>

Version 2016.09.30
	Added: Phase List

Version 2015.09.21
	Initial Release


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <cmath>
#include <string>
#include <ostream>

#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>



namespace khronos {
	// TYPES
	// --------------------------------------------------------------------------------------
	using jd_t = long double;		// with the fractions of a day.
	using jdn_t = long long;		// without the fraction of a day.

	// jd_to_gregorian(jd, year, month, day)
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);

	// jd_to_gregorian(year, month, day, hour, min, sec)
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& seconds);

	inline jdn_t jd_to_jdn(const jd_t& jd) {
		return static_cast<jdn_t> (floor(jd + 0.5));
	}

	class Jd {
		jd_t jd_;

	public:
		Jd(now_t now = WTIMEOFDAY);

		constexpr Jd(jd_t jd) : jd_(jd) {}

		constexpr jd_t jd() const { return jd_; }

		std::string to_string() const;
	};

	namespace detail {
		struct packaged_day {
			day_t nDays_;
			constexpr packaged_day(day_t d) : nDays_(d) {}
		};

		struct packaged_week {
			day_t nWeeks_;
			constexpr packaged_week(day_t w) : nWeeks_(w) {}
		};
	};
	constexpr jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }
	constexpr jd_t operator + (Jd const& lhs, Jd const& rhs) { return lhs.jd() + rhs.jd(); }

	constexpr detail::packaged_day days(day_t d) { return detail::packaged_day(d); }
	constexpr Jd operator + (Jd const& jdn, detail::packaged_day days) { return Jd(jdn.jd() + days.nDays_); }
	constexpr Jd operator - (Jd const& jdn, detail::packaged_day days) { return Jd(jdn.jd() - days.nDays_); }

	constexpr detail::packaged_week weeks(day_t w) { return detail::packaged_week(w); }
	constexpr Jd operator + (Jd const& jdn, detail::packaged_week days) { return Jd(jdn.jd() + days.nWeeks_ * 7); }
	constexpr Jd operator - (Jd const& jdn, detail::packaged_week days) { return Jd(jdn.jd() - days.nWeeks_ * 7); }

	namespace detail {
		struct packaged_year_integer {
			year_t nYears_;
			constexpr packaged_year_integer(year_t y) : nYears_(y) {}
		};
		/** Year as real number wrapper. */
		struct packaged_year_real {
			double nYears_;
			constexpr packaged_year_real(double y) : nYears_(y) {}
		};
	};

	/** Wrap a double literal into a real year package. */
	constexpr detail::packaged_year_real years(double y) { return detail::packaged_year_real(y); }

	/** Wrap a float literal into a real year package. */
	constexpr detail::packaged_year_real years(float y) { return detail::packaged_year_real(y); }

	/** Wrap all other literals into an integer year package (if possible). */
	template<typename T> constexpr detail::packaged_year_integer years(T y) { return detail::packaged_year_integer(static_cast<year_t>(y)); }

	constexpr Jd operator + (Jd const& lhs, detail::packaged_year_real years) {
		return Jd(lhs.jd() + EARTH_ORBITAL_PERIOD_DAYS * years.nYears_);
	}

	constexpr Jd operator - (Jd const& lhs, detail::packaged_year_real years) {
		return Jd(lhs.jd() - EARTH_ORBITAL_PERIOD_DAYS * years.nYears_);
	}

	namespace detail {
		struct packaged_month_integer {
			month_t nMonths_;
			constexpr packaged_month_integer(month_t m) : nMonths_(m) {}
		};
		struct packaged_month_real {
			double nMonths_;
			constexpr packaged_month_real(double m) : nMonths_(m) {}
		};
	}

	constexpr detail::packaged_month_real months(double m) { return detail::packaged_month_real(m); }
	constexpr detail::packaged_month_real months(float m) { return detail::packaged_month_real(m); }
	template <typename T> constexpr detail::packaged_month_integer months(T m) { return detail::packaged_month_integer(static_cast<month_t>(m)); }

	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}

	constexpr bool operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }
	constexpr bool operator < (Jd const& lhs, Jd const& rhs) { return lhs.jd() < rhs.jd(); }
	constexpr bool operator <= (Jd const& lhs, Jd const& rhs) { return lhs.jd() <= rhs.jd(); }
	constexpr bool operator >= (Jd const& lhs, Jd const& rhs) { return lhs.jd() >= rhs.jd(); }
	constexpr bool operator > (Jd const& lhs, Jd const& rhs) { return lhs.jd() > rhs.jd(); }


}; // end-of-namespace khronos

