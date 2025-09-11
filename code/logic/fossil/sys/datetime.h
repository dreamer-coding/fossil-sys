/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
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
namespace fossil {

    /**
     * System namespace.
     */
    namespace sys {

        /**
         * @class DateTime
         * @brief A class that represents the current date and time.
         *
         * The DateTime class initializes an instance with the current system time.
         * It uses the fossil_sys_time_now function to set the time.
         *
         * @note This class relies on the fossil_sys_time_now function to retrieve the current time.
         *
         * @brief C++ wrapper for fossil_sys_time_datetime_t.
         */
        class DateTime {
        public:

            /**
             * @class Calendar
             * @brief C++ wrapper for fossil_sys_time_calendar_t.
             */
            DateTime() {
                fossil_sys_time_now(&dt);
            }

            /**
             * @brief Initialize the DateTime object with a specific date and time.
             *
             * @param datetime The fossil_sys_time_datetime_t structure to initialize the DateTime object with.
             */
            DateTime(const fossil_sys_time_datetime_t& datetime) : dt(datetime) {}

            /**
             * @brief Get the current date and time.
             */
            void now() {
                fossil_sys_time_now(&dt);
            }

            /**
             * @brief Format the date and time into a string.
             *
             * @param format The format string specifying the desired output format.
             * @param military_time If true, use 24-hour format; otherwise, use 12-hour format.
             * @return std::string Returns the formatted date and time as a string.
             */
            std::string format(const std::string& format, bool military_time = true) const {
                char buffer[256];
                fossil_sys_time_format(&dt, buffer, sizeof(buffer), format.c_str(), military_time);
                return std::string(buffer);
            }

            /**
             * @brief Get the DateTime object.
             *
             * @return fossil_sys_time_datetime_t Returns the DateTime object.
             */
            fossil_sys_time_datetime_t get() const {
                return dt;
            }

        private:
            fossil_sys_time_datetime_t dt;
        };

        /**
         * @class Calendar
         * @brief C++ wrapper for fossil_sys_time_calendar_t.
         */
        class Calendar {
        public:

            /**
             * @brief Initialize the Calendar object with a specific date.
             *
             * @param year The year.
             * @param month The month (1-12).
             * @param day The day of the month.
             */
            Calendar(int year, int month, int day) : cal{year, month, day, fossil_sys_time_is_leap_year(year)} {}

            /**
             * @brief Get the year.
             *
             * @return int Returns the year.
             */
            bool is_leap_year() const {
                return cal.is_leap_year;
            }

            /**
             * @brief Get the month.
             *
             * @return int Returns the month.
             */
            int days_in_month() const {
                return fossil_sys_time_days_in_month(cal.year, cal.month);
            }

            /**
             * @brief Get the day.
             *
             * @return int Returns the day.
             */
            fossil_sys_time_calendar_t get() const {
                return cal;
            }

        private:
            fossil_sys_time_calendar_t cal;
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
