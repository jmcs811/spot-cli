#ifndef MAIN_H
#define MAIN_H

#include "config.h"
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dbus-print-message.h"

// protos
void help();
static int type_from_name (const char *arg);
static void append_arg (DBusMessageIter *iter, int type, const char *value);
void append_args(char *c, DBusMessageIter *iter);
void get_property(char *property);
void parse_response();
void show_artist();
void show_status();

#endif
