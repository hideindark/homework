#!/bin/bash
. ./function1.sh
. ./function2.sh
. ./function3.sh
. ./function4.sh
. ./function5.sh
title()
{
    while true
    do
        clear
        echo '0.quit'
        echo '1.who ust max'
        echo '2.which file biggest'
        echo '3.someone all c++ resource file'
        echo '4.who is online'
        echo '5.FTP and apache2 check'
        echo 'Make your choice'
        tput sc;
        read choice
        case $choice in
            0) break
            ;;
            1) function1
            ;;
            2) function2
            ;;
            3) function3
            ;;
            4) function4
            ;;
            5) function5
            ;;
            *) echo 'Wrong answer, please try again';read
            ;;
        esac
    done
}
title