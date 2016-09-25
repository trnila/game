#!/bin/bash
wrapper=

if [ ! -z "$SSH_CONNECTION" ]; then
	wrapper=vglrun
fi

pid=0
action() {
	if make ; then
		$wrapper ./main &
		pid=$!
	fi
}

action
inotifywait -q -m -e close_write *.cpp *.h *.glsl | while read line; do
	echo "killing $pid"
	kill $pid
	action
done
