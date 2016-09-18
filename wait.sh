pid=0
action() {
	if make ; then
		./main &
		pid=$!
	fi
}

action
inotifywait -q -m -e close_write *.cpp *.glsl | while read line; do
	echo "killing $pid"
	kill $pid
	action
done
