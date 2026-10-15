#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/


#include <khronos/def.hpp>
#include <iostream>


namespace khronos {
	// LITERALS
	/* UDL - converts an 'AM' hour to 'military' hour. */
	inline hour_t operator"" _am(uint64_t time) {
		if (time == 12)
			return 0; 

		return static_cast<hour_t> (time);
	}



	/* UDL - converts an 'PM' hour to 'military' hour. */
	inline hour_t operator"" _pm(uint64_t time) {
		if (time == 12)
			return static_cast<hour_t> (time);

		return static_cast<hour_t> (time + 12);
	}

	/* Seconds per day. */
	constexpr second_t SECONDS_PER_DAY = 86'400; 


	/* H:M:S.S to time-of-day [0.0..1.0) */
	constexpr tod_t tod(const hour_t& hours, const minute_t& minutes, const second_t& seconds) {
		return ((hours * 60 + minutes) * 60 + seconds) / SECONDS_PER_DAY;
	}


	/**	Convert Time-of-day (TOD) to hours, minutes, seconds.  Civil days run from midnight to midnight.
		@param tod [in] a time-of-day [0..1)
		@param hours [out] 0-23
		@param minutes [out] 0-59
		@param seconds [out] [0.0..60.0)
	*/
	inline void tod_to_HMS(const tod_t& tod, hour_t& hours, minute_t& minutes, second_t& seconds) {
		int seconds_in_a_day = static_cast<int> (floor(tod * SECONDS_PER_DAY + 0.5));

		seconds = static_cast<second_t> (seconds_in_a_day % 60); 
		hours = static_cast<hour_t> (seconds_in_a_day / (60 * 60));
		minutes = static_cast<minute_t> (seconds_in_a_day / 60) % 60;
	}

} // end-of-namespace khronos
