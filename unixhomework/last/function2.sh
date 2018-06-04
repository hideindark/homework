#!/bin/bash
function2()#遍历搜索用户目录中最大的某一个文件，并打印该文件名及其字节数
{
    clear
    alluser=`awk -F ':' '$3>499{print $1":"$6}' /etc/passwd`
    for i in $alluser
    do
        name=`echo $i | cut -d : -f 1`
        position=`echo $i | cut -d : -f 2`
        first=`find $position -type f -print | xargs du -b | sort -nrk 1 | head -n 1 | cut -f 2`
        echo 'The biggest file: '$first
        echo 'user:'$name
    done
    read -p 'Enter any key to continue'
}