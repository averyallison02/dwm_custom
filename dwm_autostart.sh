# dwm will not start until the shell returns from running this script.
# note that you should still background any processes which should run at the same time as others.

while true; do
    xsetroot -name "$( date +"%a %b %d %Y %I:%M %p" )"
    sleep "$(expr 60 - $( date +"%S" ) )s"
done &
