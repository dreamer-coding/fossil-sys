/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_SYS_DATETIME_H
#define FOSSIL_SYS_DATETIME_H

#include <stdint.h>
#include <time.h>

// Define time units from minutes to yoctoseconds
#define FOSSIL_SYS_TIME_YOCTOSEC 1
#define FOSSIL_SYS_TIME_ZEPTOSEC 1000
#define FOSSIL_SYS_TIME_ATTOSEC  1000000
#define FOSSIL_SYS_TIME_FEMTOSEC 1000000000
#define FOSSIL_SYS_TIME_PICOSEC  1000000000000
#define FOSSIL_SYS_TIME_NANOSEC  1000000000000000
#define FOSSIL_SYS_TIME_MICROSEC 1000000000000000000
#define FOSSIL_SYS_TIME_MILLISEC 1000000000000000000000ULL
#define FOSSIL_SYS_TIME_SEC      60000000000000000000000ULL
#define FOSSIL_SYS_TIME_MIN      3600000000000000000000000ULL

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct fossil_sys_time_datetime_t
 * @brief Struct for datetime representation.
 * 
 * This structure holds the components of a date and time, including year, month, day,
 * hour, minute, second, and nanosecond.
 */
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int64_t nanosecond;
} fossil_sys_time_datetime_t;

/**
 * @struct fossil_sys_time_calendar_t
 * @brief Struct for calendar representation.
 * 
 * This structure holds information about a calendar system, including leap year status.
 */
typedef struct {
    int year;
    int month;
    int day;
    int is_leap_year;
} fossil_sys_time_calendar_t;

/**
 * @brief Get the current datetime.
 * 
 * @param dt Pointer to a fossil_sys_time_datetime_t structure to be populated with the current datetime.
 */
void fossil_sys_time_now(fossil_sys_time_datetime_t *dt);

/**
 * @brief Format datetime into a string.
 * 
 * @param dt Pointer to the fossil_sys_time_datetime_t structure to be formatted.
 * @param buffer Pointer to the buffer where the formatted string will be stored.
 * @param buffer_size Size of the buffer.
 * @param format Format string specifying the desired output format.
 * @param military_time If nonzero, uses 24-hour format; otherwise, uses 12-hour format.
 * @return int Returns the number of characters written to the buffer, excluding the null terminator.
 */
int fossil_sys_time_format(const fossil_sys_time_datetime_t *dt, char *buffer, size_t buffer_size, const char *format, int military_time);

/**
 * @brief Determine if a given year is a leap year.
 * 
 * @param year The year to check.
 * @return int Returns 1 if the year is a leap year, 0 otherwise.
 */
int fossil_sys_time_is_leap_year(int year);

/**
 * @brief Get the number of days in a given month.
 * 
 * @param year The year.
 * @param month The month (1-12).
 * @return int Returns the number of days in the specified month.
 */
int fossil_sys_time_days_in_month(int year, int month);

/**
 * @brief Add seconds to a datetime.
 *
 * Adds or subtracts a number of seconds to a datetime object.
 * The datetime will be normalized so that overflow in seconds,
 * minutes, hours, or days is properly carried forward or backward.
 *
 * @param dt Pointer to a datetime to modify.
 * @param seconds Number of seconds to add (can be negative).
 */
void fossil_sys_time_add_seconds(fossil_sys_time_datetime_t *dt, int64_t seconds);

/**
 * @brief Compute the difference between two datetimes in seconds.
 *
 * Returns the signed difference (a - b) in seconds.
 *
 * @param a Pointer to the first datetime.
 * @param b Pointer to the second datetime.
 * @return int64_t Difference in seconds (positive if a > b).
 */
int64_t fossil_sys_time_diff_seconds(const fossil_sys_time_datetime_t *a,
                                     const fossil_sys_time_datetime_t *b);

/**
 * @brief Normalize a datetime.
 *
 * Adjusts fields in a datetime object to ensure they are within
 * valid ranges (e.g., 13th month becomes January of next year).
 *
 * @param dt Pointer to a datetime to normalize.
 */
void fossil_sys_time_normalize(fossil_sys_time_datetime_t *dt);

/**
 * @brief Validate a datetime.
 *
 * Checks whether a datetime object represents a valid date and time.
 *
 * @param dt Pointer to the datetime to validate.
 * @return 1 if valid, 0 if invalid (e.g., month=13, day=32).
 */
int fossil_sys_time_validate(const fossil_sys_time_datetime_t *dt);

/**
 * @brief Convert a datetime to a Unix timestamp.
 *
 * Converts the datetime to a Unix timestamp (seconds since 1970-01-01 UTC).
 * This function assumes the datetime is in UTC.
 *
 * @param dt Pointer to the datetime.
 * @return int64_t Unix timestamp (may be negative for pre-1970 dates).
 */
int64_t fossil_sys_time_to_unix(const fossil_sys_time_datetime_t *dt);

/**
 * @brief Populate a datetime from a Unix timestamp.
 *
 * Converts a Unix timestamp (seconds since 1970-01-01 UTC)
 * into a fossil_sys_time_datetime_t structure.
 *
 * @param timestamp Unix timestamp (seconds since 1970-01-01 UTC).
 * @param dt Pointer to a datetime structure to fill.
 */
void fossil_sys_time_from_unix(int64_t timestamp, fossil_sys_time_datetime_t *dt);

/**
 * @brief Get a high-resolution monotonic timestamp.
 *
 * Returns a monotonic timestamp in nanoseconds. Unlike wall-clock
 * time, this value will never jump backward or forward due to NTP
 * adjustments. Suitable for measuring time intervals.
 *
 * @return uint64_t Monotonic timestamp in nanoseconds.
 */
uint64_t fossil_sys_time_monotonic_ns(void);

/**
 * @brief Sleep for a number of nanoseconds.
 *
 * Suspends execution for at least the specified duration.
 *
 * @param nanoseconds Number of nanoseconds to sleep.
 */
void fossil_sys_time_sleep_ns(uint64_t nanoseconds);

/**
 * @struct fossil_sys_time_span_t
 * @brief Struct representing a duration of time.
 *
 * This structure holds components of a time span, allowing precise
 * representation of durations and intervals.
 */
typedef struct {
    int64_t days;        /**< Number of days */
    int64_t hours;       /**< Number of hours */
    int64_t minutes;     /**< Number of minutes */
    int64_t seconds;     /**< Number of seconds */
    int64_t nanoseconds; /**< Number of nanoseconds */
} fossil_sys_time_span_t;

/**
 * @brief Create a time span from seconds.
 *
 * @param seconds Total number of seconds to convert into a time span.
 * @return fossil_sys_time_span_t Time span with fields populated.
 */
fossil_sys_time_span_t fossil_sys_time_span_from_seconds(int64_t seconds);

/**
 * @brief Convert a time span into seconds.
 *
 * @param span Pointer to a time span.
 * @return int64_t Total number of seconds represented by the span.
 */
int64_t fossil_sys_time_span_to_seconds(const fossil_sys_time_span_t *span);

/**
 * @brief Add a time span to a datetime.
 *
 * Adds (or subtracts, if fields are negative) the components
 * of a time span to a datetime object.
 *
 * @param dt Pointer to a datetime to modify.
 * @param span Pointer to a time span to add.
 */
void fossil_sys_time_add_span(fossil_sys_time_datetime_t *dt,
                              const fossil_sys_time_span_t *span);

#ifdef __cplusplus
}

#include <string>

/**
 * Fossil namespace.
 */
namespace fossil
{
    /**
     * @namespace fossil::sys
     * @brief Contains system-level time and date utilities.
     */
    namespace sys
    {
        /**
         * @class DateTime
         * @brief C++ wrapper for fossil_sys_time_datetime_t.
         *
         * Provides methods for manipulating and formatting date and time values.
         * Internally uses fossil_sys_time_datetime_t and related C functions.
         */
        class DateTime
        {
        public:
            /**
             * @brief Constructs a DateTime object initialized to the current system time.
             */
            DateTime() {
                fossil_sys_time_now(&dt);
            }

            /**
             * @brief Constructs a DateTime object from an existing fossil_sys_time_datetime_t.
             * @param datetime The datetime structure to initialize from.
             */
            DateTime(const fossil_sys_time_datetime_t& datetime) : dt(datetime) {}

            /**
             * @brief Updates the DateTime object to the current system time.
             */
            void now() {
                fossil_sys_time_now(&dt);
            }

            /**
             * @brief Formats the DateTime as a string.
             * @param format Format string specifying the output.
             * @param military_time If true, uses 24-hour format; otherwise, 12-hour format.
             * @return Formatted date/time string.
             */
            std::string format(const std::string& format, bool military_time = true) const {
                char buffer[256];
                fossil_sys_time_format(&dt, buffer, sizeof(buffer), format.c_str(), military_time);
                return std::string(buffer);
            }

            /**
             * @brief Gets the underlying fossil_sys_time_datetime_t structure.
             * @return The datetime structure.
             */
            fossil_sys_time_datetime_t get() const {
                return dt;
            }

            /**
             * @brief Adds seconds to the DateTime.
             * @param seconds Number of seconds to add (can be negative).
             */
            void add_seconds(int64_t seconds) {
                fossil_sys_time_add_seconds(&dt, seconds);
            }

            /**
             * @brief Computes the difference in seconds between this and another DateTime.
             * @param other The other DateTime to compare.
             * @return Difference in seconds (positive if this > other).
             */
            int64_t diff_seconds(const DateTime& other) const {
                return fossil_sys_time_diff_seconds(&dt, &other.dt);
            }

            /**
             * @brief Normalizes the DateTime fields to valid ranges.
             */
            void normalize() {
                fossil_sys_time_normalize(&dt);
            }

            /**
             * @brief Validates the DateTime fields.
             * @return True if valid, false otherwise.
             */
            bool validate() const {
                return fossil_sys_time_validate(&dt) != 0;
            }

            /**
             * @brief Converts the DateTime to a Unix timestamp.
             * @return Unix timestamp (seconds since 1970-01-01 UTC).
             */
            int64_t to_unix() const {
                return fossil_sys_time_to_unix(&dt);
            }

            /**
             * @brief Sets the DateTime from a Unix timestamp.
             * @param timestamp Unix timestamp to set from.
             */
            void from_unix(int64_t timestamp) {
                fossil_sys_time_from_unix(timestamp, &dt);
            }

            /**
             * @brief Adds a time span to the DateTime.
             * @param span The time span to add.
             */
            void add_span(const fossil_sys_time_span_t& span) {
                fossil_sys_time_add_span(&dt, &span);
            }

        private:
            fossil_sys_time_datetime_t dt; /**< Internal datetime structure. */
        };

        /**
         * @class Calendar
         * @brief C++ wrapper for fossil_sys_time_calendar_t.
         *
         * Provides methods for calendar-related queries such as leap year and days in month.
         */
        class Calendar
        {
        public:
            /**
             * @brief Constructs a Calendar object for the specified date.
             * @param year Year value.
             * @param month Month value.
             * @param day Day value.
             */
            Calendar(int year, int month, int day)
                : cal{year, month, day, fossil_sys_time_is_leap_year(year)} {}

            /**
             * @brief Checks if the calendar year is a leap year.
             * @return True if leap year, false otherwise.
             */
            bool is_leap_year() const {
                return cal.is_leap_year;
            }

            /**
             * @brief Gets the number of days in the calendar's month.
             * @return Number of days in the month.
             */
            int days_in_month() const {
                return fossil_sys_time_days_in_month(cal.year, cal.month);
            }

            /**
             * @brief Gets the underlying fossil_sys_time_calendar_t structure.
             * @return The calendar structure.
             */
            fossil_sys_time_calendar_t get() const {
                return cal;
            }

        private:
            fossil_sys_time_calendar_t cal; /**< Internal calendar structure. */
        };

        /**
         * @class TimeSpan
         * @brief C++ wrapper for fossil_sys_time_span_t.
         *
         * Represents a duration of time and provides conversion utilities.
         */
        class TimeSpan
        {
        public:
            /**
             * @brief Constructs a zero-initialized TimeSpan.
             */
            TimeSpan() : span{0, 0, 0, 0, 0} {}

            /**
             * @brief Constructs a TimeSpan from total seconds.
             * @param seconds Total seconds for the time span.
             */
            explicit TimeSpan(int64_t seconds) {
                span = fossil_sys_time_span_from_seconds(seconds);
            }

            /**
             * @brief Constructs a TimeSpan from explicit fields.
             * @param days Number of days.
             * @param hours Number of hours.
             * @param minutes Number of minutes.
             * @param seconds Number of seconds.
             * @param nanoseconds Number of nanoseconds.
             */
            TimeSpan(int64_t days, int64_t hours, int64_t minutes, int64_t seconds, int64_t nanoseconds)
                : span{days, hours, minutes, seconds, nanoseconds} {}

            /**
             * @brief Converts the TimeSpan to total seconds.
             * @return Total seconds represented by the span.
             */
            int64_t to_seconds() const {
                return fossil_sys_time_span_to_seconds(&span);
            }

            /**
             * @brief Gets the underlying fossil_sys_time_span_t structure.
             * @return The time span structure.
             */
            fossil_sys_time_span_t get() const {
                return span;
            }

        private:
            fossil_sys_time_span_t span; /**< Internal time span structure. */
        };

        /**
         * @brief Gets a high-resolution monotonic timestamp in nanoseconds.
         * @return Monotonic timestamp in nanoseconds.
         */
        inline uint64_t monotonic_ns() {
            return fossil_sys_time_monotonic_ns();
        }

        /**
         * @brief Sleeps for the specified number of nanoseconds.
         * @param nanoseconds Number of nanoseconds to sleep.
         */
        inline void sleep_ns(uint64_t nanoseconds) {
            fossil_sys_time_sleep_ns(nanoseconds);
        }
    }
}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
