# spotify-cli
A simple command line interface to control spotify


[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/spot-cli)

Useage:
```
################################################
################### SPOT-CLI ###################
################################################
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
  shell  - Enter shell mode

Shell Mode:
 Shell mode allows you to keep the spot-cli tools
 open. This means you can just type the commands with out
 having to run the binary.
To exit shell mode:
 CTRL+C or close the terminal
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
