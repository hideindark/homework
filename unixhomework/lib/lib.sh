#!/bin/bash
. ./EDIT.sh
. ./REPORT.sh
centerprint()
{
    STR=$1
    ROW=$2
    bold=$3
    offset=$4
    COLS=`tput cols`
    LEN=`echo $STR|wc -c`
    HOLD_COL=`expr $COLS - $LEN`
    NEW_COL=`expr $HOLD_COL / 2`
    OFFSET_COL=`expr $NEW_COL + $offset`
    tput cup $ROW $OFFSET_COL
    if test $bold -eq 0
    then
        echo -n $STR
    else
        echo -n $(tput bold)$STR
    fi
}
title()
{
    while true
    do
        clear
        centerprint "Linux Library Mnanger" 4 1 0
        centerprint "This is the Linux Library application" 8 0 0
        centerprint "Please enter any key to continue..." 9 0 0
        read 
        choice=3
        while (($choice<0 || $choice>2))
        do
            clear
            centerprint "Linux Library - " 4 0 0
            echo -n $(tput bold)"MAIN MENU"
            centerprint '0:' 5 0 10
            echo -n $(tput bold)"EXIT "
            echo -n "this program"
            centerprint '1:' 6 0 10
            echo -n $(tput bold)"EDIT "
            echo -n 'Menu'
            centerprint '2:' 7 0 10
            echo -n $(tput bold)"REPORTS "
            echo -n 'Menu'
            centerprint 'Enter your choice >' 8 0 0
            tput sc;echo -n '_';tput rc
            read choice
            case $choice in
                1) EDIT
                ;;
                2) 
                REPORTS
                EDIT
                ;;
                0) exit 0
                ;;
                *)
                centerprint 'Wrong Input. Try again' 10 0 0
                centerprint 'Press any key to continue' 11 0 0
                read
                ;;
            esac
        done
    done
}
title
