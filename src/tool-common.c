#include "tool-common.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef DBUS_WIN
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

void
tool_oom (const char *doing)
{
  fprintf (stderr, "OOM while %s\n", doing);
  exit (1);
}

#ifdef DBUS_WIN
typedef int WriteResult;
#define write(fd, buf, len) _write(fd, buf, len)
#else
typedef ssize_t WriteResult;
#endif

dbus_bool_t
tool_write_all (int fd,
    const void *buf,
    size_t size)
{
  const char *p = buf;
  size_t bytes_written = 0;

  while (size > bytes_written)
    {
      WriteResult res = write (fd, p, size - bytes_written);

      if (res < 0)
        {
          if (errno == EINTR)
            continue;
          else
            return FALSE;
        }
      else
        {
          size_t this_time = (size_t) res;
          p += this_time;
          bytes_written += this_time;
        }
    }

  return TRUE;
}