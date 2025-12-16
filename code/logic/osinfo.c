#include "osinfo.h"

#include <string.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    #include <sys/utsname.h>
    #include <unistd.h>
#endif

/* ============================================================
 * Helpers
 * ============================================================ */

static void
fossil_sys_osinfo_clear(fossil_sys_osinfo_t *info)
{
    memset(info, 0, sizeof(*info));
    info->family = FOSSIL_OS_FAMILY_UNKNOWN;
    info->type   = FOSSIL_OS_TYPE_UNKNOWN;
}

/* ============================================================
 * Queries
 * ============================================================ */

bool
fossil_sys_osinfo_query(fossil_sys_osinfo_t *info)
{
    if (!info)
        return false;

    fossil_sys_osinfo_clear(info);

    /* Architecture width */
#if defined(UINTPTR_MAX) && UINTPTR_MAX > 0xFFFFFFFFu
    info->is_64bit = true;
#else
    info->is_64bit = false;
#endif

#if defined(_WIN32)

    info->family = FOSSIL_OS_FAMILY_WINDOWS;
    info->type   = FOSSIL_OS_TYPE_WINDOWS;
    info->is_embedded = false;

    OSVERSIONINFOEXA ver;
    ZeroMemory(&ver, sizeof(ver));
    ver.dwOSVersionInfoSize = sizeof(ver);

    if (GetVersionExA((OSVERSIONINFOA *)&ver)) {
        info->version_major = (uint32_t)ver.dwMajorVersion;
        info->version_minor = (uint32_t)ver.dwMinorVersion;
        info->version_patch = (uint32_t)ver.dwBuildNumber;
    }

    strncpy(info->name, "Windows", sizeof(info->name) - 1);
    strncpy(info->version_string, ver.szCSDVersion,
            sizeof(info->version_string) - 1);

    return true;

#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)

    info->family = FOSSIL_OS_FAMILY_POSIX;
    info->is_embedded = false;

    struct utsname uts;
    if (uname(&uts) != 0)
        return false;

#if defined(__APPLE__)
    info->type = FOSSIL_OS_TYPE_MACOS;
    strncpy(info->name, "macOS", sizeof(info->name) - 1);
#elif defined(__linux__)
    info->type = FOSSIL_OS_TYPE_LINUX;
    strncpy(info->name, "Linux", sizeof(info->name) - 1);
#else
    info->type = FOSSIL_OS_TYPE_BSD;
    strncpy(info->name, uts.sysname, sizeof(info->name) - 1);
#endif

    strncpy(info->version_string, uts.release,
            sizeof(info->version_string) - 1);

    /* Best-effort version parsing */
    sscanf(uts.release, "%u.%u.%u",
           &info->version_major,
           &info->version_minor,
           &info->version_patch);

    return true;

#elif defined(FOSSIL_TARGET_RTOS)

    info->family       = FOSSIL_OS_FAMILY_RTOS;
    info->type         = FOSSIL_OS_TYPE_RTOS;
    info->is_embedded  = true;

    strncpy(info->name, "RTOS", sizeof(info->name) - 1);
    strncpy(info->version_string, "unknown",
            sizeof(info->version_string) - 1);

    return true;

#else /* Bare metal */

    info->family      = FOSSIL_OS_FAMILY_BAREMETAL;
    info->type        = FOSSIL_OS_TYPE_BAREMETAL;
    info->is_embedded = true;

    strncpy(info->name, "BareMetal", sizeof(info->name) - 1);
    strncpy(info->version_string, "n/a",
            sizeof(info->version_string) - 1);

    return true;

#endif
}

/* ============================================================
 * Convenience Helpers
 * ============================================================ */

fossil_sys_os_family_t
fossil_sys_osinfo_family(void)
{
    fossil_sys_osinfo_t info;
    if (!fossil_sys_osinfo_query(&info))
        return FOSSIL_OS_FAMILY_UNKNOWN;
    return info.family;
}

fossil_sys_os_type_t
fossil_sys_osinfo_type(void)
{
    fossil_sys_osinfo_t info;
    if (!fossil_sys_osinfo_query(&info))
        return FOSSIL_OS_TYPE_UNKNOWN;
    return info.type;
}

bool
fossil_sys_osinfo_is_embedded(void)
{
    fossil_sys_osinfo_t info;
    if (!fossil_sys_osinfo_query(&info))
        return false;
    return info.is_embedded;
}

bool
fossil_sys_osinfo_is_64bit(void)
{
    fossil_sys_osinfo_t info;
    if (!fossil_sys_osinfo_query(&info))
        return false;
    return info.is_64bit;
}
