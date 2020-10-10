#include "main.h"

int main(int argc, char** argv) {
   char *command;
   // check the number of args
   if (argc == 2) {
      command = argv[1];
      // convert cli args to lowercase
      for (int i = 0; command[i]; i++) {
         command[i] = tolower(command[i]);
      }
      process_command(command, 0);
   } else {
      send_dbus(0, "PlayPause");
      exit(EXIT_SUCCESS);
   }
}