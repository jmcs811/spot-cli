#include "main.h"

void help() {
   printf("################################################\n");
   printf("################### SPOT-CLI ###################\n");
   printf("################################################\n");
   printf("status - displays info about the playback status");
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
         play_playback();
         exit(EXIT_SUCCESS);
      } else if (strcmp(command, "pause") == 0) {
         pause_playback();
         exit(EXIT_SUCCESS);
      } else if (strcmp(command, "next") == 0) {
         next_playback();
         exit(EXIT_SUCCESS);
      } else if (strcmp(command, "prev") == 0) {
         prev_playback();
         exit(EXIT_SUCCESS);
      } else if (strcmp(command, "artist") == 0) {
         show_artist();
         exit(EXIT_SUCCESS);
      } else if (strcmp(command, "status") == 0) {
         show_status();
         exit(EXIT_SUCCESS);
      } else {
         help();
         exit(EXIT_SUCCESS);
      }
   } else {
      send_dbus(0, "PlayPause");
      exit(EXIT_SUCCESS);
   }
}