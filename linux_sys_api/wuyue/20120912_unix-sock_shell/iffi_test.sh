#########################################################################
# File Name: iffi_test.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 15时26分49秒
#########################################################################
#!/bin/bash

read n

if [ $n -gt 100 ]
then
	echo "great"
elif [ $n -eq 100 ]
then
	echo "equal"
else
	echo "less"
fi
