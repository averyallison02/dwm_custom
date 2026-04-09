# dwm will not start until the shell returns from running this script.
# note that you should still background any processes which should run at the same time as others.

# update changing information
while true; do
    DATE="$( date +'%a %b %d %Y %I:%M %p' )"
    BATTERY="$( cat /sys/class/power_supply/BAT1/capacity )%"
    xsetroot -name " $DATE -$BATTERY- "
    sleep 1s
done &

# start compositor
picom &

# set desktop background
feh --bg-fill "$HOME/backgrounds/torrent.jpg"
