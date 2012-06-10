/*
 * @file timer.h
 *
 * A timer class to measure elapsed time
 *
 *  Created on: May 9, 2011
 *      Author: dhlin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_TIMER_H
#define BCSLIB_TIMER_H

#include <bcslib/base/config.h>
#include <bcslib/base/basic_defs.h>

#if BCS_PLATFORM_INTERFACE == BCS_POSIX_INTERFACE
#include <sys/time.h>
#endif

namespace bcs
{
	enum time_units
	{
		SECONDS,
		MILLI_SECONDS,
		MICRO_SECONDS
	};


#if BCS_PLATFORM_INTERFACE == BCS_WINDOWS_INTERFACE

	// TODO: implement the timer for windows platform
#error The timer for windows platform is yet to be implemented.

#elif BCS_PLATFORM_INTERFACE == BCS_POSIX_INTERFACE

	/**
	 * A performance timer
	 */
	class timer
	{
	public:
		explicit timer(bool start_it = false)
		{
			reset();

			if (start_it)
			{
				start();
			}
		}

		void start()
		{
			m_elapsed_usecs = 0;
			resume();
		}


		void reset()
		{
			m_is_on = false;
			m_elapsed_usecs = 0;
			m_last_resume.tv_sec = 0;
			m_last_resume.tv_usec = 0;
		}

		void resume()
		{
			m_is_on = true;
			::gettimeofday(&m_last_resume, BCS_NULL);
		}

		void pause()
		{
			m_elapsed_usecs += last_elapsed();
			m_is_on = false;
		}

		double elapsed( time_units unit = SECONDS ) const
		{
			double e = static_cast<double>(m_is_on ? last_elapsed() + m_elapsed_usecs : m_elapsed_usecs);

			if (unit == SECONDS)
			{
				return e * 1.0e-6;
			}
			else if (unit == MILLI_SECONDS)
			{
				return e * 1.0e-3;
			}
			else
			{
				return e;
			}
		}

	private:
		BCS_ENSURE_INLINE int64_t last_elapsed() const
		{
			::timeval ct;
			::gettimeofday(&ct, BCS_NULL);
			return static_cast<int64_t>(ct.tv_sec - m_last_resume.tv_sec) * 1000000
					+ (ct.tv_usec - m_last_resume.tv_usec);
		}

	private:
		bool m_is_on;
		int64_t m_elapsed_usecs;
		::timeval m_last_resume;

	}; // end class performance timer

#endif

}

#endif
