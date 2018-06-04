#!/bin/bash
function3()#查询特定用户目录下所有的C++源程序
{
    clear
    allusr=`awk -F ':' '$3>499{print $1":"$6}' /etc/passwd`
    echo 'allusr have :' 
    for i in $allusr
    do
        name=`echo $i | cut -d : -f 1`
        echo $name
    done
    echo 'Who you want to find'
    tput sc
    read name
    result=`echo $allusr | grep $name`
    while (($?==127))
    do
        echo 'Dont find the user, please try again' 
        tput rc
        read name
        result=`echo $allusr | grep $name`
    done
    position=`cat /etc/passwd | grep $name | cut -d : -f 6`
    echo 'Find result:'
    find $position -name "*.cpp " -o -name "*.hpp" -print
    read -p 'Enter any key to continue'
}