#include "main.h"

void help() {
   printf("################################################\n");
   printf("################### SPOT-CLI ###################\n");
   printf("################################################\n");
   printf("Usage: \n");
   printf("  spot_cli [command]\n\n");
   printf("Avalilable Commands:\n");
   printf("  play, pause, next, previous, artist, status\n\n");
   printf("Command descriptions\n");
   printf("  %-6s - %-10s", "NO ARG","toggle play/pause\n");
   printf("  %-6s - %-10s", "play","starts playback\n");
   printf("  %-6s - %-10s", "pause", "pauses playback\n");
   printf("  %-6s - %-10s","next", "plays next track\n");
   printf("  %-6s - %-10s",  "prev", "plays previous track\n");
   printf("  %-6s - %-10s", "artist", "displays info about the artist\n");
   printf("  %-6s - %-10s", "status", "displays info about the playback status\n");
   printf("  %-6s - %-10s", "shell", "Enter shell mode\n");
   printf("\nShell Mode:\n");
   printf(" Shell mode allows you to keep the spot-cli tools\n");
   printf(" open. This means you can just type the commands with out\n");
   printf(" having to run the binary.\n");
   printf("To exit shell mode:\n");
   printf(" CTRL+C or close the terminal\n");
   printf("\n");
}

char* process_command(char *command) {
   char* result;
   if (strcmp(command, "play") == 0) {
      result = play_playback();
   } else if (strcmp(command, "pause") == 0) {
      result = pause_playback();
   } else if (strcmp(command, "next") == 0) {
      result = next_playback();
   } else if (strcmp(command, "prev") == 0) {
      result = prev_playback();
   } else if (strcmp(command, "artist") == 0) {
      result = show_artist();
   } else if (strcmp(command, "status") == 0) {
      result = show_status();
   } else if (strcmp(command, "toggle") == 0) {
      result = play_pause_playback();
   } else if (strcmp(command, "shell") == 0) {
      start_shell();   
   } else {
      help();
   }
   return result;
}

void start_shell() {
   char command[10];
   while (true) {
      printf("Enter a command: ");
      fgets(command, 10, stdin);
      command[strlen(command) - 1] = '\0';
      char *result = process_command(command);
      if (result != NULL) {
         printf("%s\n", result);
      }
      command[0] = '\0';
   }
}
static int
type_from_name (const char *arg) {
  int type;
  if (!strcmp (arg, "string"))
    type = DBUS_TYPE_STRING;
  else if (!strcmp (arg, "int16"))
    type = DBUS_TYPE_INT16;
  else if (!strcmp (arg, "uint16"))
    type = DBUS_TYPE_UINT16;
  else if (!strcmp (arg, "int32"))
    type = DBUS_TYPE_INT32;
  else if (!strcmp (arg, "uint32"))
    type = DBUS_TYPE_UINT32;
  else if (!strcmp (arg, "int64"))
    type = DBUS_TYPE_INT64;
  else if (!strcmp (arg, "uint64"))
    type = DBUS_TYPE_UINT64;
  else if (!strcmp (arg, "double"))
    type = DBUS_TYPE_DOUBLE;
  else if (!strcmp (arg, "byte"))
    type = DBUS_TYPE_BYTE;
  else if (!strcmp (arg, "boolean"))
    type = DBUS_TYPE_BOOLEAN;
  else if (!strcmp (arg, "objpath"))
    type = DBUS_TYPE_OBJECT_PATH;
  else {
      fprintf (stderr, "Unknown type \"%s\"\n", arg);
      exit (1);
   }
  return type;
}

static void
append_arg (DBusMessageIter *iter, int type, const char *value) {
  dbus_uint16_t uint16;
  dbus_int16_t int16;
  dbus_uint32_t uint32;
  dbus_int32_t int32;
  dbus_uint64_t uint64;
  dbus_int64_t int64;
  double d;
  unsigned char byte;
  dbus_bool_t v_BOOLEAN;
  dbus_bool_t ret;

  switch (type) {
   case DBUS_TYPE_BYTE:
   byte = strtoul (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_BYTE, &byte);
   break;

   case DBUS_TYPE_DOUBLE:
   d = strtod (value, NULL);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_DOUBLE, &d);
   break;

   case DBUS_TYPE_INT16:
   int16 = strtol (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_INT16, &int16);
   break;

   case DBUS_TYPE_UINT16:
   uint16 = strtoul (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_UINT16, &uint16);
   break;

   case DBUS_TYPE_INT32:
   int32 = strtol (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_INT32, &int32);
   break;

   case DBUS_TYPE_UINT32:
   uint32 = strtoul (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_UINT32, &uint32);
   break;

   case DBUS_TYPE_INT64:
   int64 = strtoll (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_INT64, &int64);
   break;

   case DBUS_TYPE_UINT64:
   uint64 = strtoull (value, NULL, 0);
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_UINT64, &uint64);
   break;

   case DBUS_TYPE_STRING:
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_STRING, &value);
   break;

   case DBUS_TYPE_OBJECT_PATH:
   ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_OBJECT_PATH, &value);
   break;

    case DBUS_TYPE_BOOLEAN:
      if (strcmp (value, "true") == 0) {
      v_BOOLEAN = TRUE;
      ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_BOOLEAN, &v_BOOLEAN);
	} else if (strcmp (value, "false") == 0) {
      v_BOOLEAN = FALSE;
      ret = dbus_message_iter_append_basic (iter, DBUS_TYPE_BOOLEAN, &v_BOOLEAN);
	} else {
	  fprintf (stderr, "Expected \"true\" or \"false\" instead of \"%s\"\n", value);
	  exit (1);
	}
   break;

   default:
      fprintf (stderr, "Unsupported data type %c\n", (char) type);
      exit (1);
   }
}

void append_args(char *c, DBusMessageIter *iter) {
   char *arg = "string";
   int type2;
   int secondary_type = DBUS_TYPE_INVALID;
   int container_type = DBUS_TYPE_INVALID;
   DBusMessageIter *target_iter;
   DBusMessageIter container_iter;

   type2 = type_from_name (arg);
	append_arg (iter, type2, c);
}

void send_dbus(int msg_type, char *property) {
   DBusConnection *connection;
   DBusError error;
   DBusMessage *message;
   int print_reply;
   int print_reply_literal;
   int reply_timeout;
   DBusMessageIter iter;
   int i;
   DBusBusType type = DBUS_BUS_SESSION;
   const char *dest = SPOTIFY_PLAYER;
   char* name;
   if (msg_type == 1) {
      name = DBUS_PROPERTIES;
   } else {
      name = MEDIAPLAYER_PLAYER;
   }
   const char *path = MEDIAPLAYER;
   int message_type = DBUS_MESSAGE_TYPE_METHOD_CALL;
   const char *type_str = NULL;
   const char *address = NULL;
   int session_or_system = FALSE;

   print_reply = true;
   print_reply_literal = FALSE;
   reply_timeout = -1;

   dbus_error_init(&error);
   if (address != NULL) {
      connection = dbus_connection_open (address, &error);
    
  } else {
      connection = dbus_bus_get (type, &error);
   }

   if (connection == NULL) {
      fprintf (stderr, "Failed to open connection to \"%s\" message bus: %s\n",
               (address != NULL) ? address :
                 ((type == DBUS_BUS_SYSTEM) ? "system" : "session"),
               error.message);
      dbus_error_free (&error);
      exit (1);
   }

   if (message_type == DBUS_MESSAGE_TYPE_METHOD_CALL) {
      char *last_dot;
      last_dot = strrchr (name, '.');
      if (last_dot == NULL) {
         fprintf (stderr, "Must use org.mydomain.Interface.Method notation, no dot in \"%s\"\n",
                  name);
         exit (1);
      }
      //*last_dot = '\0';
      if (msg_type == 1) {
      message = dbus_message_new_method_call (NULL,
                                                path,
                                                name,
                                                "Get");
      } else {
         message = dbus_message_new_method_call (NULL,
                                                path,
                                                name,
                                                property);
      }
      dbus_message_set_auto_start (message, TRUE);
   }

   if (message == NULL) {
      fprintf (stderr, "Couldn't allocate D-Bus message\n");
      exit (1);
   }

   if (dest && !dbus_message_set_destination(message, dest)) {
      fprintf (stderr, "Not enough memory\n");
      exit (1);
   }

   dbus_message_iter_init_append (message, &iter);

   if (msg_type == 1) {
      append_args(MEDIAPLAYER_PLAYER, &iter);
      append_args(property, &iter);
   }

   
   if (print_reply) {
      DBusMessage *reply;
      dbus_error_init (&error);
      reply = dbus_connection_send_with_reply_and_block (connection,
                                                         message, reply_timeout,
                                                         &error);
      if (dbus_error_is_set (&error)) {
         fprintf (stderr, "Error1 %s: %s\n",
         error.name,
         error.message);
         exit (1);
      }
      if (reply) {
         long sec, usec;
         if (msg_type == 1) {
            parse_response(reply);
         }
         dbus_message_unref (reply);
      }
   }

   dbus_message_unref (message);
   dbus_connection_unref (connection);
}

int check_attribute(char* response) {
   if (strcmp(response, ALBUM) == 0) {
      return 1;
   } else if (strcmp(response, ARTIST) == 0) {
      return 1;
   } else if (strcmp(response, TITLE) == 0) {
      return 1;
   } else if (strcmp(response, URL) == 0) {
      return 1;
   } else {
      return 0;
   }
}

void parse_response(DBusMessage *msg) {
   // TODO: parse the resp from show_artist/show_status
   DBusMessageIter msgIter;
   DBusMessageIter structIter;
   dbus_message_iter_init(msg, &msgIter);
   dbus_message_iter_recurse(&msgIter, &structIter);
   if (DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&structIter)) {
      char* str_response = NULL;
      dbus_message_iter_get_basic(&structIter, &str_response);
      printf("Status: %s\n", str_response);
      return;
   }

   if (DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&structIter)) {
      DBusMessageIter arrayIter;
      dbus_message_iter_recurse(&structIter, &arrayIter);
      for (int i = 0; i < 15; i++) {
         if (DBUS_TYPE_DICT_ENTRY == dbus_message_iter_get_arg_type(&arrayIter)) {
            DBusMessageIter dictIter;
            dbus_message_iter_recurse(&arrayIter, &dictIter);
            if (DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&dictIter)) {
               char* str_response = NULL;
               dbus_message_iter_get_basic(&dictIter, &str_response);
               if (check_attribute(str_response) == 0) {
                  dbus_message_iter_next(&arrayIter);
                  continue;
               }
               if (strcmp(str_response, ARTIST) == 0) {
                  str_response = "Artist";
               } else if (strcmp(str_response, URL) == 0) {
                  str_response = "URL";
               } else if (strcmp(str_response, TITLE) == 0) {
                  str_response = "Title";
               } else if (strcmp(str_response, ALBUM) == 0) {
                  str_response = "Album";
               }
               printf("%-6s -> ", str_response);
               dbus_message_iter_next(&dictIter);
               if (DBUS_TYPE_VARIANT == dbus_message_iter_get_arg_type(&dictIter)) {
                  DBusMessageIter varIter;
                  dbus_message_iter_recurse(&dictIter, &varIter);
                  if (DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&varIter)) {
                     char *test = NULL;
                     dbus_message_iter_get_basic(&varIter, &test);
                     printf("%-15s\n", test);
                  }
                  if (DBUS_TYPE_ARRAY == dbus_message_iter_get_arg_type(&varIter)) {
                     DBusMessageIter varArrayIter;
                     dbus_message_iter_recurse(&varIter, &varArrayIter);
                     if (DBUS_TYPE_STRING == dbus_message_iter_get_arg_type(&varArrayIter)) {
                        char *test = NULL;
                        dbus_message_iter_get_basic(&varArrayIter, &test);
                        printf("%-15s\n", test);
                     }
                  }
               }
            }
         }
         dbus_message_iter_next(&arrayIter);
      }
   }
}

char* play_playback() {
   send_dbus(0, "Play");
   return "Started Playback";
}

char* pause_playback() {
   send_dbus(0, "Pause");
   return "Paused Playback";
}

char* next_playback() {
   send_dbus(0, "Next");
   return "Started next track";
}

char* prev_playback() {
   send_dbus(0, "Previous");
   return "Started prev track";
}

char* play_pause_playback() {
   send_dbus(0, "PlayPause");
   return "Toggled playback";
}
char* show_artist() {
   printf("Artist Info:\n");
   send_dbus(1, "Metadata");
   return NULL;
}

char* show_status() {
   send_dbus(1, "PlaybackStatus");
   return NULL;
}