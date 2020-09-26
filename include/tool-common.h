#ifndef DBUS_TOOL_COMMON_H
#define DBUS_TOOL_COMMON_H

#include <dbus/dbus.h>

#if 0
#define VERBOSE fprintf
#else
#define VERBOSE(...) do {} while (0)
#endif

void tool_oom (const char *doing) _DBUS_GNUC_NORETURN;
dbus_bool_t tool_write_all (int fd, const void *buf, size_t size);

#endif