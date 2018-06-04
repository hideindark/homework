#!/bin/bash
function1()#统计用户的磁盘占用情况，打印占用磁盘空间最大的用户名
{
    clear
    alluser=`awk -F ':' '$3>499{print $1":"$6}' /etc/passwd`
    for i in $alluser
    do
        name=`echo $i | cut -d : -f 1`
        position=`echo $i | cut -d : -f 2`
        total=`find $position -user $name -type f -print | xargs du -h -b | awk 'BEGIN{sum=0}{sum+=$1}END{print sum}'`
        echo $total' '$name >> lib
    done
    sort -nrk 1 lib
    biggest=`sort -nrk 1 lib | head -n 1`
    rm lib
    read -p 'The biggest is '$biggest        
}