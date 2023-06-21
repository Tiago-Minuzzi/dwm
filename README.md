# My build of suckless dwm

dwm (dynamic window manager) is an extremely fast, small, and dynamic window manager for X.

This build is using dwm version 6.4, and is meant to be run on Arch Linux.

## Installation

Clone this repo to `$HOME/.dwm`, enter the directory and run the script `install.sh`.

Edit `config.mk` to match your local setup (dwm is installed into
the `/usr/local` namespace by default).

**Dependencies**

- git
- go
- yay
- base-devel

## Packages

- alacritty
- brightnessctl
- dmenu
- feh
- libxft
- nm-applet
- playerctl
- polkit (any)
- ranger
- rofi-greenclip
- scrot
- slstatus
- st
- sxhkd
- ttf-font-awesome
- ttf-jetbrains-mono
- ttf-joypixels
- ueberzug
- unclutter
- xorg-xkill
- xorg-server
- xorg-setxkbmap
- xorg-xinit
- xorg-xrandr

## Patches

- dwm-actualfullscreen-20211013-cb3f58a
- dwm-autostart-20210120-cb3f58a
- dwm-noborderfloatingfix-6.2
- dwm-pertag-20200914-61bb8b2
- dwm-restartsig-20180523-6.2
- dwm-systray-6.4
- dwm-vanitygaps-20200610-f09418b

**OBS**: for the autostart patch to work, the `autostart.sh` file must be in any of the following location -> `$XDG_DATA_HOME/dwm`, `$HOME/.local/share/dwm`, and `$HOME/.dwm` 

## Scripts

- copyToClip
- displayConnect
- dwmDisplay
- getVol
- weather.sh

