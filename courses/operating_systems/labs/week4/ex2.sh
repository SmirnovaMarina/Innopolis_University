#!/bin/bash
#Explanation of the result:
#process ex2.exe runs in backgroung
#ex2.sh will run ex2.exe and pstree for building 3 trees
#
./ex2.exe &
for i in 1 2 3
do
	pstree -h -p
done
