rshift () {
    if pgrep redshift;then
        killall -9 redshift &&
        redshift -x &&
        redshift
    else
        redshift
    fi
}

exec slstatus &
nm-applet &
xrandr --output HDMI1 --mode 1920x1080 --left-of eDP --output eDP --off &
#xrandr --output HDMI1 --off --left-of eDP --output eDP --mode 1366x768 &
#picom --config /home/tiago/.config/picom/picom.conf &
dunst &
~/.fehbg &
flameshot &
#redshift &
rshift &
caffeine &
unclutter &
#polkit &
lxsession &
greenclip daemon &
setxkbmap -layout us -variant intl &
export _JAVA_AWT_WM_NONREPARENTING=1
