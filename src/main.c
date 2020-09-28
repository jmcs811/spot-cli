#include "main.h"

void help() {
   printf("####################\n");
   printf("##### SPOT-CLI #####\n");
   printf("####################\n");
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
   printf("\n");
}

static int
type_from_name (const char *arg)
{
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
  else
    {
      fprintf (stderr, "Unknown type \"%s\"\n", arg);
      exit (1);
    }
  return type;
}

static void
append_arg (DBusMessageIter *iter, int type, const char *value)
{
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
   printf("%p", iter);
	append_arg (iter, type2, c);
}

void get_property(char *property) {
   DBusConnection *connection;
   DBusError error;
   DBusMessage *message;
   int print_reply;
   int print_reply_literal;
   int reply_timeout;
   DBusMessageIter iter;
   int i;
   DBusBusType type = DBUS_BUS_SESSION;
   const char *dest = "org.mpris.MediaPlayer2.spotify";
   const char *name = "org.freedesktop.DBus.Properties";
   const char *path = "/org/mpris/MediaPlayer2";
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
      message = dbus_message_new_method_call (NULL,
                                                path,
                                                name,
                                                "Get");
      dbus_message_set_auto_start (message, TRUE);
   }

   if (message == NULL) {
      fprintf (stderr, "Couldn't allocate D-Bus message\n");
      exit (1);
   }

   printf("dest");
   if (dest && !dbus_message_set_destination(message, dest)) {
      fprintf (stderr, "Not enough memory\n");
      exit (1);
   }

   dbus_message_iter_init_append (message, &iter);

   append_args("org.mpris.MediaPlayer2.Player", &iter);
   append_args(property, &iter);

   
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
         print_message (reply, print_reply_literal, sec, sec);
         dbus_message_unref (reply);
      }
   }

   dbus_message_unref (message);
   dbus_connection_unref (connection);
   exit (0);
}

void parse_response() {
   
}

void show_artist() {
   printf("This is the artist\n");
   get_property("Metadata");
}

void show_status() {
   get_property("PlaybackStatus");
}

int main(int argc, char** argv) {
   char *command;
   // check the number of args
   if (argc == 2) {
      command = argv[1];
      // convert cli args to lowercase
      for (int i = 0; command[i]; i++) {
         command[i] = tolower(command[i]);
      }
      
      if (strcmp(command, "play") == 0) {
         command = "Play";
      } else if (strcmp(command, "pause") == 0) {
         command = "Pause";
      } else if (strcmp(command, "next") == 0) {
         command = "Next";
      } else if (strcmp(command, "prev") == 0) {
         command = "Previous";
      } else if (strcmp(command, "artist") == 0) {
         show_artist();
         exit(1);
      } else if (strcmp(command, "status") == 0) {
         show_status();
         exit(1);
      } else {
         help();
         exit(1);
      }
   } else {
      command = "PlayPause";
   }


   DBusConnection *connection;
   DBusError error;
   DBusMessage *message;
   int print_reply;
   int print_reply_literal;
   int reply_timeout;
   DBusMessageIter iter;
   int i;
   DBusBusType type = DBUS_BUS_SESSION;
   const char *dest = "org.mpris.MediaPlayer2.spotify";
   const char *name = "org.mpris.MediaPlayer2.Player";
   const char *path = "/org/mpris/MediaPlayer2";
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

      message = dbus_message_new_method_call (NULL,
                                                path,
                                                name,
                                                command);
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
   
   if (print_reply) {
      DBusMessage *reply;
      dbus_error_init (&error);
      reply = dbus_connection_send_with_reply_and_block (connection,
                                                         message, reply_timeout,
                                                         &error);
      if (dbus_error_is_set (&error)) {
         fprintf (stderr, "Error %s: %s\n",
         error.name,
         error.message);
         exit (1);
      }
      if (reply) {
         // print_message (reply, print_reply_literal);
         dbus_message_unref (reply);
      }
   }
   dbus_message_unref (message);
   dbus_connection_unref (connection);
   exit (0);
}