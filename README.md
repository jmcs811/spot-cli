# spotify-cli
A simple command line interface to control spotify

Useage:
```
####################
##### SPOT-CLI #####
####################
Usage: 
  spot_cli [command]

Avalilable Commands:
  play, pause, next, previous, artist, status

Command descriptions
  NO ARG - toggle play/pause
  play   - starts playback
  pause  - pauses playback
  next   - plays next track
  prev   - plays previous track
  artist - displays info about the artist
  status - displays info about the playback status
```

## Installation
1. Download tar from releases
2. Install the spotify client
3. Install dbus and dbus-devel
4. Locate the dbus include and library dir (/usr/lib64/dbus-1.0/include/ & /usr/lib64/dbus-1.0/include/) 
5. run ./configure
6. run make
7. Optional: make install (will install in /usr/local/bin by default)
8. run ./spot_cli

## Dependencies
- dbus
- dbus-devel
- spotify client or spotifyd (not tested, but should work)
