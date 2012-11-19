#########################################################################
# File Name: rm_non_block_line.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 19时46分35秒
#########################################################################
#!/bin/bash

if [ $# = "0" ];
then
	echo "usage: ./shell.sh filename"
else
	newfile=""
	for file in $@;
	do
		`egrep -v ^$ $file > $$`
		rm $file
		mv $$ $file
	done
fi
