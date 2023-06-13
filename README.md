# My build of suckless dwm

dwm (dynamic window manager) is an extremely fast, small, and dynamic window manager for X.

This build is using dwm version 6.4.

## Packages

- alacritty
- brightnessctl
- dmenu
- feh
- playerctl
- polkit (any)
- ranger
- rofi-greenclip
- slstatus
- sxhkd
- ttf-font-awesome
- ttf-jetbrains-mono
- ttf-joypixels
- ueberzug
- unclutter
- xcb-util-image
- xorg-setxkbmap

## Patches

- dwm-actualfullscreen-20211013-cb3f58a
- dwm-autostart-20210120-cb3f58a
- dwm-noborderfloatingfix-6.2
- dwm-pertag-20200914-61bb8b2
- dwm-restartsig-20180523-6.2
- dwm-systray-6.4
- dwm-vanitygaps-20200610-f09418b

## Scripts

- copyToClip
- displayConnect
- dwmDisplay
- getVol
- weather.sh

## Installation
------------
Edit `config.mk` to match your local setup (dwm is installed into
the `/usr/local` namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install
