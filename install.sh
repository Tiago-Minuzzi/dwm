#!/usr/bin/env bash

HELPER=yay

echo "=============================================================="
echo "|| By running this script you're allowing SUDO privilegies! ||"
echo "=============================================================="

sudo pacman -S --needed alacritty brightnessctl feh libxft playerctl polkit-kde-agent ranger sxhkd ttf-font-awesome ttf-jetbrains-mono ttf-joypixels ueberzug unclutter xcb-util-image xorg-setxkbmap

if command -v $HELPER > /dev/null;then
    $HELPER -S --needed rofi-greenclip
else
    echo "${HELPER} is not installed"
    exit 1
fi

echo "### Cloning dmenu and slstatus"
git clone --depth 1 https://github.com/Tiago-Minuzzi/dmenu $HOME/.config/dmenu
git clone --depth 1 https://github.com/Tiago-Minuzzi/slstatus $HOME/.config/slstatus
