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

	class Jd {
		jd_t jd_;

	public:
		Jd(now_t now = WTIMEOFDAY);

		constexpr Jd(jd_t jd) : jd_(jd) {}

		constexpr jd_t jd() const { return jd_; }

		std::string to_string() const; 
	};

	constexpr jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }

	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string(); 
	}

	constexpr bool operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }
}; // end-of-namespace khronos

