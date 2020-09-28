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
1. Download or clone
2. run autoreconf -i
3. run ./configure
4. run make
5. run ./spot_cli

## Dependencies
- dbus
- dbus-devel
- spotify client or spotifyd (not tested, but should work)
