# dwm will not start until the shell returns from running this script.
# note that you should still background any processes which should run at the same time as others.

# update clock when necessary
while true; do
    DATE="$( date +'%a %b %d %Y %I:%M %p' )"
    xsetroot -name " $DATE "
    sleep "$(expr 60 - $( date +"%S" ) )s"
done &

# start compositor
picom &

# set desktop background
feh --bg-fill "$HOME/backgrounds/torrent.jpg"
