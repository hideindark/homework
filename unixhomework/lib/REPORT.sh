#!/bin/bash
REPORTS()
{
    choice=4
    while (($choice<0 || $choice>3))
    do
        clear
        centerprint 'Linux Library - ' 4 0 0
        echo -n $(tput bold)'REPORTS MENU'
        centerprint '0: ' 5 0 10
        echo -n $(tput bold)' TITLES'
        centerprint '1: Sorted by ' 6 0 10
        echo -n $(tput bold)' TITLE'
        centerprint '2: Sorted by ' 7 0 10
        echo -n $(tput bold)' AUTHOR'
        centerprint '3: Sorted by ' 8 0 10
        echo -n $(tput bold)' CATEGORY'
        centerprint 'Enter your choice>' 9 0 0
        #tput sc;echo -n '_';tput rc
        read choice
        case $choice in
            0) break
            ;;
            1) sort1 1
            ;;
            2) sort1 2
            ;;
            3) sort1 3
            ;;
            *)
                centerprint 'Wrong Input. Try again' 11 0 0
                centerprint 'Press any key to continue' 12 0 0
                read
        esac
    done
}
sort1()
{
    clear
    if test -s ./library
    then
        case $1 in
        1) sort -k 1 -t : library -o temp
        ;;
        2) sort  -k 2 -t : library -o temp
        ;;
        3) sort -k 3 -t : library -o temp
        ;;
        *) echo 'falid'
        ;;
        esac
        slist=('Title: ' 'Author:' 'Category: ' 'Stauts: ' 'Checked out by: ' 'date: ')
        for line in `cat temp `
        do
            oldIFS=$IFS
            IFS=':'
            int=0
            for item in $line
            do
                echo ${slist[int]}$item >> Ptemp
                let int++
            done
            IFS=$oldIFS
        done
        more -c -10 Ptemp
    else
        centerprint 'Dont have file or the file is empty' 4 0 0
        read
    fi

}
