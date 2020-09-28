#ifndef MAIN_H
#define MAIN_H

//#include "config.h"
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dbus-print-message.h"

#define ALBUM "xesam:album"
#define ARTIST "xesam:artist"
#define TITLE "xesam:title"
#define URL "xesam:url"

// protos
void help();
static int type_from_name (const char *arg);
static void append_arg (DBusMessageIter *iter, int type, const char *value);
void append_args(char *c, DBusMessageIter *iter);
void send_dbus(int msg_type, char *property);
void get_property(char *property);
void parse_response();
void play_playback();
void pause_playback();
void next_playback();
void prev_playback();
void play_pause_playback();
void show_artist();
void show_status();

#endif
