#########################################################################
# File Name: args.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 16时09分30秒
#########################################################################
#!/bin/bash


#./args.sh wang xiao dong

i=1

echo "\$0 : $0"

for item in $@;
do
	echo "\$i : $item"
	i=$(($i + 1))
done
