#########################################################################
# File Name: while.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 15时33分18秒
#########################################################################
#!/bin/bash

i=1
sum=0

read n

while [ $i -le $n ];
do
	sum=$(($sum + $i))
	i=$(($i + 1))


done

echo "$sum"
