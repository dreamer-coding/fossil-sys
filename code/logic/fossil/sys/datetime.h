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
#define FOSSIL_SYS_TIME_HOUR  (60 * FOSSIL_SYS_TIME_MIN)
#define FOSSIL_SYS_TIME_DAY   (24 * FOSSIL_SYS_TIME_HOUR)
#define FOSSIL_SYS_TIME_WEEK  (7 * FOSSIL_SYS_TIME_DAY)

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
 * @brief Format datetime into a string using a named format.
 *
 * @param dt Pointer to the fossil_sys_time_datetime_t structure.
 * @param buffer Output buffer.
 * @param buffer_size Size of output buffer.
 * @param format_id String ID of the format (NULL or "human" for default).
 * @return int Number of characters written, excluding null terminator, or -1 on error.
 */
int fossil_sys_time_format(
    const fossil_sys_time_datetime_t *dt,
    char *buffer,
    size_t buffer_size,
    const char *format_id
);

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

typedef enum {
    FOSSIL_SYS_SEASON_WINTER,
    FOSSIL_SYS_SEASON_SPRING,
    FOSSIL_SYS_SEASON_SUMMER,
    FOSSIL_SYS_SEASON_AUTUMN,
    FOSSIL_SYS_SEASON_UNKNOWN
} fossil_sys_season_t;

/**
 * @brief Get the season for a given datetime.
 *
 * @param dt Pointer to a datetime.
 * @param northern_hemisphere If nonzero, uses Northern Hemisphere seasons; otherwise, Southern Hemisphere.
 * @return fossil_sys_season_t The season.
 */
fossil_sys_season_t fossil_sys_time_get_season(const fossil_sys_time_datetime_t *dt, int northern_hemisphere);

typedef struct {
    int month;
    int day;
    const char *name;
} fossil_sys_holiday_fixed_t;

typedef enum {
    FOSSIL_SYS_HOLIDAY_NONE = 0,      // Not a holiday
    FOSSIL_SYS_HOLIDAY_NEW_YEAR,      // January 1
    FOSSIL_SYS_HOLIDAY_ML_KING_DAY,   // Third Monday in January
    FOSSIL_SYS_HOLIDAY_VALENTINES,    // February 14
    FOSSIL_SYS_HOLIDAY_PRESIDENTS_DAY,// Third Monday in February
    FOSSIL_SYS_HOLIDAY_ST_PATRICKS,   // March 17
    FOSSIL_SYS_HOLIDAY_EASTER,        // Variable date
    FOSSIL_SYS_HOLIDAY_MEMORIAL_DAY,  // Last Monday in May
    FOSSIL_SYS_HOLIDAY_INDEPENDENCE,  // July 4
    FOSSIL_SYS_HOLIDAY_LABOR_DAY,     // First Monday in September
    FOSSIL_SYS_HOLIDAY_HALLOWEEN,     // October 31
    FOSSIL_SYS_HOLIDAY_VETERANS_DAY,  // November 11
    FOSSIL_SYS_HOLIDAY_THANKSGIVING,  // Fourth Thursday in November
    FOSSIL_SYS_HOLIDAY_CHRISTMAS,     // December 25
    FOSSIL_SYS_HOLIDAY_BLACK_FRIDAY,  // Day after Thanksgiving
    FOSSIL_SYS_HOLIDAY_SUPER_BOWL,    // First Sunday in February (optional fun)
    FOSSIL_SYS_HOLIDAY_MOTHERS_DAY,   // Second Sunday in May
    FOSSIL_SYS_HOLIDAY_FATHERS_DAY,   // Third Sunday in June
} fossil_sys_holiday_id_t;

/**
 * @brief Check if a given date is a fixed holiday.
 *
 * @param dt Pointer to a datetime.
 * @return fossil_sys_holiday_id_t ID of holiday, or FOSSIL_SYS_HOLIDAY_NONE if none.
 */
fossil_sys_holiday_id_t fossil_sys_time_get_holiday(const fossil_sys_time_datetime_t *dt);

/**
 * @brief Returns true if the date is a weekend.
 */
int fossil_sys_time_is_weekend(const fossil_sys_time_datetime_t *dt);

/**
 * @brief Returns the quarter (1-4) of the year.
 */
int fossil_sys_time_get_quarter(const fossil_sys_time_datetime_t *dt);

/**
 * @brief Format a datetime using human-aware "smart" rules.
 *
 * Automatically selects an appropriate display format based on the
 * relationship between the given datetime and a reference time.
 *
 * Examples:
 *  - Same day:        "3:45 PM"
 *  - Yesterday:       "Yesterday at 3:45 PM"
 *  - Same week:       "Tuesday at 3:45 PM"
 *  - Same year:       "Jan 31"
 *  - Different year:  "Jan 31, 2026"
 *
 * @param dt Pointer to the datetime to format.
 * @param now Pointer to the reference datetime (typically current time).
 * @param buffer Output buffer for the formatted string.
 * @param buffer_size Size of the output buffer in bytes.
 * @return int Number of characters written (excluding null terminator),
 *             or -1 on error.
 */
int fossil_sys_time_format_smart(
    const fossil_sys_time_datetime_t *dt,
    const fossil_sys_time_datetime_t *now,
    char *buffer,
    size_t buffer_size
);

/**
 * @brief Format a datetime as a human-friendly relative time string.
 *
 * Produces natural relative descriptions such as "just now",
 * "5 minutes ago", "today at 3:45 PM", or "Tuesday at 6:00 PM",
 * based on the difference between the target datetime and a
 * reference time.
 *
 * This function is deterministic and does not perform locale
 * or timezone inference.
 *
 * @param target Pointer to the datetime being described.
 * @param now Pointer to the reference datetime (typically current time).
 * @param buffer Output buffer for the formatted string.
 * @param buffer_size Size of the output buffer in bytes.
 * @return int Number of characters written (excluding null terminator),
 *             or -1 on error.
 */
int fossil_sys_time_format_relative(
    const fossil_sys_time_datetime_t *target,
    const fossil_sys_time_datetime_t *now,
    char *buffer,
    size_t buffer_size
);

/**
 * @brief Evaluate whether a datetime matches a search expression.
 *
 * Supports comparisons, semantic keywords, and named time formats.
 *
 * @param dt Pointer to the datetime being tested.
 * @param now Pointer to reference datetime (typically current time).
 * @param query Search expression string.
 * @return int 1 if the datetime matches the query, 0 if not, -1 on error.
 */
int fossil_sys_time_search(
    const fossil_sys_time_datetime_t *dt,
    const fossil_sys_time_datetime_t *now,
    const char *query
);

#ifdef __cplusplus
}

#include <string>

namespace fossil {

namespace sys {

/**
 * @class TimeSpan
 * @brief Represents a duration of time, providing conversions between
 *        seconds and structured components (days, hours, minutes, etc.).
 * 
 * This class is a thin wrapper over the C struct fossil_sys_time_span_t.
 * It provides convenience methods for creating, converting, and manipulating
 * time spans in a C++-friendly way.
 */
class TimeSpan {
public:
    /// Underlying C representation of the time span
    fossil_sys_time_span_t span{};

    /// Default constructor: zero-initialized duration
    TimeSpan() = default;

    /**
     * @brief Construct a TimeSpan from a total number of seconds.
     * 
     * @param seconds Total number of seconds to represent.
     */
    explicit TimeSpan(int64_t seconds) {
        span = fossil_sys_time_span_from_seconds(seconds);
    }

    /**
     * @brief Factory method to create a TimeSpan from seconds.
     * 
     * @param seconds Total seconds.
     * @return TimeSpan instance representing the specified duration.
     */
    static TimeSpan from_seconds(int64_t seconds) {
        return TimeSpan(seconds);
    }

    /**
     * @brief Convert the time span to total seconds.
     * 
     * @return int64_t Total number of seconds represented by this span.
     */
    int64_t to_seconds() const {
        return fossil_sys_time_span_to_seconds(&span);
    }
};

/**
 * @class DateTime
 * @brief Represents a specific point in time, including year, month, day, hour, minute, second, and nanosecond.
 * 
 * DateTime wraps the fossil_sys_time_datetime_t C struct and exposes
 * validation, arithmetic, formatting, and semantic operations in a
 * C++-friendly interface.
 */
class DateTime {
public:
    /// Underlying C representation of the datetime
    fossil_sys_time_datetime_t dt{};

    /// Default constructor: uninitialized datetime (all fields zero)
    DateTime() = default;

    /**
     * @brief Construct a DateTime from an existing C struct.
     * 
     * @param value A fossil_sys_time_datetime_t value to wrap.
     */
    explicit DateTime(const fossil_sys_time_datetime_t& value)
        : dt(value) {}

    /* ---------- factories ---------- */

    /**
     * @brief Get the current local datetime.
     * 
     * @return DateTime representing the current system time.
     */
    static DateTime now() {
        DateTime t;
        fossil_sys_time_now(&t.dt);
        return t;
    }

    /**
     * @brief Create a DateTime from a Unix timestamp.
     * 
     * Converts a timestamp (seconds since 1970-01-01 UTC) into a DateTime.
     * 
     * @param timestamp Unix timestamp in seconds.
     * @return DateTime representing the specified timestamp.
     */
    static DateTime from_unix(int64_t timestamp) {
        DateTime t;
        fossil_sys_time_from_unix(timestamp, &t.dt);
        return t;
    }

    /* ---------- validation ---------- */

    /**
     * @brief Check whether the datetime represents a valid date and time.
     * 
     * @return true if valid, false otherwise (e.g., month=13, day=32)
     */
    bool is_valid() const {
        return fossil_sys_time_validate(&dt) != 0;
    }

    /**
     * @brief Determine if the date falls on a weekend.
     * 
     * @return true if Saturday or Sunday, false otherwise
     */
    bool is_weekend() const {
        return fossil_sys_time_is_weekend(&dt) != 0;
    }

    /**
     * @brief Get the quarter of the year (1-4).
     * 
     * @return int Quarter number (1 = Jan-Mar, ..., 4 = Oct-Dec)
     */
    int quarter() const {
        return fossil_sys_time_get_quarter(&dt);
    }

    /**
     * @brief Check if the year of this DateTime is a leap year.
     * 
     * @return true if leap year, false otherwise
     */
    bool is_leap_year() const {
        return fossil_sys_time_is_leap_year(dt.year) != 0;
    }

    /* ---------- arithmetic ---------- */

    /**
     * @brief Add or subtract seconds from the datetime.
     * 
     * Automatically normalizes overflow/underflow across minutes, hours, and days.
     * 
     * @param seconds Number of seconds to add (can be negative)
     */
    void add_seconds(int64_t seconds) {
        fossil_sys_time_add_seconds(&dt, seconds);
    }

    /**
     * @brief Add a TimeSpan to this DateTime.
     * 
     * Adds all components of the TimeSpan (days, hours, minutes, seconds, nanoseconds)
     * and normalizes the result.
     * 
     * @param span TimeSpan to add (can contain negative values)
     */
    void add_span(const TimeSpan& span) {
        fossil_sys_time_add_span(&dt, &span.span);
    }

    /**
     * @brief Compute the difference in seconds between this DateTime and another.
     * 
     * @param other Another DateTime to compare with
     * @return int64_t Difference in seconds (positive if this > other)
     */
    int64_t diff_seconds(const DateTime& other) const {
        return fossil_sys_time_diff_seconds(&dt, &other.dt);
    }

    /* ---------- conversion ---------- */

    /**
     * @brief Convert the datetime to a Unix timestamp.
     * 
     * @return int64_t Seconds since 1970-01-01 UTC
     */
    int64_t to_unix() const {
        return fossil_sys_time_to_unix(&dt);
    }

    /**
     * @brief Normalize the datetime fields to ensure valid ranges.
     * 
     * Example: 13th month becomes January of next year, 61 seconds carry over to minutes, etc.
     */
    void normalize() {
        fossil_sys_time_normalize(&dt);
    }

    /* ---------- formatting ---------- */

    /**
     * @brief Format the DateTime as a string using a named format.
     * 
     * @param format_id Format identifier (e.g., "human", "iso", "military")
     * @return std::string Formatted datetime, empty string on error
     */
    std::string format(const std::string& format_id = "human") const {
        char buf[128];
        int n = fossil_sys_time_format(
            &dt,
            buf,
            sizeof(buf),
            format_id.empty() ? nullptr : format_id.c_str()
        );
        return n >= 0 ? std::string(buf, n) : std::string{};
    }

    /**
     * @brief Format the DateTime using human-aware smart rules.
     * 
     * Chooses an appropriate display format relative to `now`.
     * Examples:
     * - Same day: "3:45 PM"
     * - Yesterday: "Yesterday at 3:45 PM"
     * - Same week: "Tuesday at 3:45 PM"
     * - Same year: "Jan 31"
     * - Different year: "Jan 31, 2026"
     * 
     * @param now Reference DateTime for relative calculations
     * @return std::string Smart-formatted datetime string
     */
    std::string format_smart(const DateTime& now) const {
        char buf[128];
        int n = fossil_sys_time_format_smart(
            &dt,
            &now.dt,
            buf,
            sizeof(buf)
        );
        return n >= 0 ? std::string(buf, n) : std::string{};
    }

    /**
     * @brief Format the DateTime as a human-friendly relative string.
     * 
     * Examples: "just now", "5 minutes ago", "today at 3:45 PM", "Tuesday at 6:00 PM"
     * 
     * @param now Reference DateTime
     * @return std::string Relative time string
     */
    std::string format_relative(const DateTime& now) const {
        char buf[128];
        int n = fossil_sys_time_format_relative(
            &dt,
            &now.dt,
            buf,
            sizeof(buf)
        );
        return n >= 0 ? std::string(buf, n) : std::string{};
    }

    /* ---------- semantics ---------- */

    /**
     * @brief Determine the season of the year.
     * 
     * @param northern_hemisphere true to use Northern Hemisphere conventions, false for Southern
     * @return fossil_sys_season_t Enum representing the season
     */
    fossil_sys_season_t season(bool northern_hemisphere = true) const {
        return fossil_sys_time_get_season(&dt, northern_hemisphere ? 1 : 0);
    }

    /**
     * @brief Get the holiday ID for the datetime, if any.
     * 
     * @return fossil_sys_holiday_id_t ID of the holiday, or FOSSIL_SYS_HOLIDAY_NONE
     */
    fossil_sys_holiday_id_t holiday() const {
        return fossil_sys_time_get_holiday(&dt);
    }

    /* ---------- search ---------- */

    /**
     * @brief Determine if the datetime matches a search query.
     * 
     * Supports operators, keywords, and named formats.
     * 
     * @param now Reference DateTime for relative evaluations
     * @param query Search expression string (e.g., "today", "> 2026-01-01")
     * @return true if the DateTime matches the search query
     */
    bool matches(const DateTime& now, const std::string& query) const {
        int r = fossil_sys_time_search(&dt, &now.dt, query.c_str());
        return r > 0;
    }
};

/**
 * @class Calendar
 * @brief Represents calendar-related information for a specific date.
 * 
 * Wraps fossil_sys_time_calendar_t, exposing leap year checks and days-in-month queries.
 */
class Calendar {
public:
    fossil_sys_time_calendar_t cal{};

    /// Default constructor: zero-initialized calendar
    Calendar() = default;

    /**
     * @brief Construct a Calendar for a specific date.
     * 
     * @param year Year
     * @param month Month (1-12)
     * @param day Day (1-31)
     */
    Calendar(int year, int month, int day) {
        cal.year = year;
        cal.month = month;
        cal.day = day;
        cal.is_leap_year = fossil_sys_time_is_leap_year(year);
    }

    /**
     * @brief Check if the year is a leap year.
     * 
     * @return true if leap year, false otherwise
     */
    bool is_leap_year() const {
        return cal.is_leap_year != 0;
    }

    /**
     * @brief Get the number of days in the month of this calendar date.
     * 
     * @return int Number of days in the month
     */
    int days_in_month() const {
        return fossil_sys_time_days_in_month(cal.year, cal.month);
    }
};

} // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
