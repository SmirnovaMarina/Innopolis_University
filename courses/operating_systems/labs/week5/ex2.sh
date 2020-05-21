#!/bin/sh
if test ! -f read_from.txt
then
	echo 0 > read_from.txt
fi
if ln read_from.txt read_from.txt.lock
then	
	for i in $(seq 1 50)
	do
		last=`tail -1 read_from.txt`
		last=$((last+1))
		echo $last >> read_from.txt
	done
	rm read_from.txt.lock
fi
