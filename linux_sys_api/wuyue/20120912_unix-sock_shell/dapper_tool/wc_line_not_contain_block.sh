#########################################################################
# File Name: wc_line_not_contain_block.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 19时32分38秒
#########################################################################
#!/bin/bash

filelist=`ls *.[ch]`

echo $filelist
n=0
tatol=0

for file in $filelist;
do
	n=`egrep -v ^$ $file | wc -l`
	tatol=$((tatol+n))
done
echo $tatol
