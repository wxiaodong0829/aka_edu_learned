#########################################################################
# File Name: modify_prefix.sh
# Author: wxiaodong
# mail  : wxiaodong0829@163.com
# 自由  谐作   创造   沟通
# Created Time: 2012年09月12日 星期三 17时49分30秒
#########################################################################
#!/bin/bash
# ./add_str_at_file.sh dong
i=0
selfname=""
rmtoname=""
if [ $# = "0" -o $# = "1" ];
then
	echo "useage: ./add_str_at_file.sh --help"
	if [ $# = "1" ];
	then
		if [ $1 = "--help" ];
		then
			echo "./modify_prefix.sh -[ar] dong"
			echo "		-a add \"dong\" is the prefix of your wish"
			echo "		-r rm  \"dong\" is the prefix of your wish"
		fi
	fi
else
		selfname=`echo $0 | sed 's/.\///'`

		if [ $1 = "-a" ];
		then	# 添加 前缀 
			for file in `ls`;
			do
				name=$2_$file
				if [ $file != $selfname ];
				then
					mv $file $name
					echo $name
				fi
			done
		elif [ $1 = "-r" ];  # 删除 前缀 
		then
			for file in `ls`;
			do
				rmtoname=`echo $file | sed "s/$2_//"`
				if [ $file != $rmtoname ];
				then
					mv $file $rmtoname
				fi

			done
		fi
fi
