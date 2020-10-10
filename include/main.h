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

#define ALBUM "xesam:album"
#define ARTIST "xesam:artist"
#define TITLE "xesam:title"
#define URL "xesam:url"
#define SPOTIFY_PLAYER "org.mpris.MediaPlayer2.spotify"
#define DBUS_PROPERTIES "org.freedesktop.DBus.Properties"
#define MEDIAPLAYER_PLAYER "org.mpris.MediaPlayer2.Player"
#define MEDIAPLAYER "/org/mpris/MediaPlayer2"

// protos
char* help();
char* process_command(char *command, int inShell);
void start_shell();
static int type_from_name (const char *arg);
static void append_arg (DBusMessageIter *iter, int type, const char *value);
void append_args(char *c, DBusMessageIter *iter);
void send_dbus(int msg_type, char *property);
void get_property(char *property);
void parse_response();
char* play_playback();
char* pause_playback();
char* next_playback();
char* prev_playback();
char* play_pause_playback();
char* show_artist();
char* show_status();

#endif
