#!/bin/bash
function4()#查询某个用户是否在线
{
    clear
    echo 'Who is you want to check:'
    read name
    result=`who | cut -d : -f 1 |grep $name`
    case $? in
        0) echo $name' is online'
        ;;
        1) echo $name'dont online'
        ;;
    esac
    read -p 'Enter any key to continue'
}