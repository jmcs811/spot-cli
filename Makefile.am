bin_PROGRAMS = spot_cli
spot_cli_SOURCES = $(top_srcdir)/src/main.c \
                   $(top_srcdir)/src/dbus-print-message.c \
                   $(top_srcdir)/src/tool-common.c \
                   $(top_srcdir)/src/spotcli.c
spot_cli_LDADD = -L/usr/lib/x86_64-linux-gnu/dbus-1.0/include/ -ldbus-1
spot_cli_CPPFLAGS = -I/usr/include/dbus-1.0/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include/ -I./include