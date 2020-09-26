#include "config.h"
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void help() {
   printf("####################\n");
   printf("##### SPOT-CLI #####\n");
   printf("####################\n");
   printf("Usage: \n");
   printf("  spot_cli [command]\n\n");
   printf("Avalilable Commands:\n");
   printf("  play, pause, next, previous\n");
}

void show_artist() {
   printf("This is the artist\n");
   // DBusBusType type = DBUS_BUS_SESSION;
   // DBusConnection  *connection;
   // DBusError error;
   // DBusMessage *msg;
   // DBusMessageIter args;
   // DBusPendingCall *pending;
   // int message_type = DBUS_MESSAGE_TYPE_METHOD_CALL;
   // char *client = "spotify";

   // dbus_error_init(&error);
   // connection = dbus_bus_get(type, &error);
   // if (connection == NULL) {
   //    fprintf(stderr, "Failed to open connection");
   //    dbus_error_free(&error);
   //    exit(1);
   // }

   // msg = dbus_message_new_method_call(NULL,
   //                                    "/org/mpris/MediaPlayer2",
   //                                    "/org/mpris/MediaPlayer2",
   //                                    "");

   // if (NULL == msg) { 
   //    fprintf(stderr, "Message Null\n");
   //    exit(1);
   // }

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
      if (last_dot == NULL)
         {
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
         // print_message (reply, print_reply_literal);
         dbus_message_unref (reply);
      }
   }
   dbus_message_unref (message);
   dbus_connection_unref (connection);
   exit (0);

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
      if (last_dot == NULL)
         {
            fprintf (stderr, "Must use org.mydomain.Interface.Method notation, no dot in \"%s\"\n",
                     name);
            exit (1);
         }
      //*last_dot = '\0';
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