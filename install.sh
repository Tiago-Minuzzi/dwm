#!/usr/bin/env bash

HELPER=yay

pacman -S --needed alacritty brightnessctl dmenu feh playerctl polkit-kde-agent ranger  slstatus sxhkd ttf-font-awesome ttf-jetbrains-mono ttf-joypixels ueberzug unclutter xcb-util-image xorg-setxkbmap

if command -v $HELPER > /dev/null;then
    $HELPER -S --needed rofi-greenclip
else
    echo "${HELPER} is not installed"
    exit 1
fi
