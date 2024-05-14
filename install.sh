#!/usr/bin/env bash

HELPER=yay

echo "=============================================================="
echo "|| By running this script you're allowing SUDO privilegies! ||"
echo "=============================================================="

sudo pacman -S --needed blueman bluez brightnessctl feh libxft lxseesion-gtk3 playerctl network-manager-applet ranger scrot sxhkd ttf-font-awesome ttf-jetbrains-mono ttf-joypixels unclutter w3m xorg-xkill xorg-server xorg-setxkbmap xorg-xinit xorg-xrandr j4-dmenu-desktop && \

echo "### Building dwm ###"
sudo make clean install && \

if command -v $HELPER > /dev/null;then
    $HELPER -S --needed rofi-greenclip
else
    echo "${HELPER} is not installed"
    exit 1
fi

echo -e "### Cloning dmenu, slstatus and st \n###"
git clone --depth 1 https://github.com/Tiago-Minuzzi/dmenu $HOME/.config/dmenu && cd $HOME/.config/dmenu && sudo make clean install && \
git clone --depth 1 https://github.com/Tiago-Minuzzi/slstatus $HOME/.config/slstatus && cd $HOME/.config/slstatus && sudo make clean install && \
git clone --depth 1 https://github.com/Tiago-Minuzzi/st $HOME/.config/st && cd $HOME/.config/st && sudo make clean install && \
cd && echo "You may need to restart dwm to run slstatus"

