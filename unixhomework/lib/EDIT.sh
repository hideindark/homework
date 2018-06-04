#!/bin/bash
EDIT()
{
    choice=5
    while (($choice<0 || $choice>4))
    do
        clear
        centerprint 'Linux Library - ' 4 0 0 
        echo -n $(tput bold)'EDIT MENU'
        centerprint '0: ' 5 0 10
        echo -n $(tput bold)'RETURN '
        echo -n 'to the main menu'
        centerprint '1: ' 6 0 10
        echo -n $(tput bold)'ADD'
        centerprint '2: ' 7 0 10
        echo -n $(tput bold)'UPDATE STATUS'
        centerprint '3: ' 8 0 10
        echo -n $(tput bold)'DISPLAY'
        centerprint '4: ' 9 0 10
        echo -n $(tput bold)'DELETE'
        centerprint 'Enter your choice>' 10 0 0
        tput sc;echo -n '_';tput rc
        read choice
        case $choice in
            0) break
            ;;
            1) ADD
            ;;
            2) UPDATE
            ;;
            3) DISPLAY
            ;;
            4) DELETE
            ;;
            *)
            centerprint 'Wrong Input. Try again' 12 0 0
            centerprint 'Press any key to continue' 13 0 0
            read
            ;;
        esac
    done
}
ADD()
{
    while true
    do
        clear
        centerprint 'Title:  ' 4 0 0
        read title
        centerprint 'Author:  ' 5 0 0 
        read author
        centerprint 'Category:1.system 2.reference 3.textbook' 6 0 0
        read -p ', Choice:' choice;tput sc
        while (($choice<1 || $choice>3))
        do
            centerprint 'Wrong Input. Try again' 8 0 0
            centerprint 'Please enter a uesful number' 9 0 0
            tput rc
            read choice
        done
        case $choice in
            1) category='system'
            ;;
            2) category='reference'
            ;;
            3) category='textbook'
            ;;
        esac
        echo $title':'$author':'$category':in' >> library
        centerprint 'Any more to add? (Y)es or (N)o>' 10 0 6
        tput sc
        read con
        while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
        do
            centerprint 'Wrong Input,Please try again' 11 0 0
            tput rc
            read con
        done
        case $con in
            'Y' | 'y') continue
            ;;
            'N' | 'n') break
            ;;
        esac
    done
}
DELETE()
{
    while true
    do
        clear
        if test ! -s ./library
        then
            centerprint 'Dont have file or the file is empty' 4 0 0
            read
            break
        fi
        centerprint 'Enter the title>' 4 0 0
        read title
        infomation=`grep $title library`
        if test -z "$infomation"
        then
            centerprint 'Dont find , do you want try again?(Y)es or (N)o' 5 0 0
            tput sc
            read con
            while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
            do
                centerprint 'Wrong Input,Please try again' 6 0 0
                tput rc
                read con
            done
            case $con in
                'Y') continue
                ;;
                'N') break
                ;;
                'y')
                ;;
                'n') break
                ;;
            esac
        fi
        centerprint 'Linux Library - ' 7 0 6
        echo -n $(tput bold)'DLETE MODE'
        oldIFS=$IFS
        IFS=':'
        int=0
        ROW=9
        slist=('Title: ' 'Author: ' 'Category: ' 'Stauts: ' 'name: ' 'date: ')
        for item in $infomation
        do
            centerprint ${slist[${int}]}$item $ROW 0 10
            let ROW++
            let int++
        done 
        IFS=$oldIFS
        centerprint 'Delte this book?(Y)es or (No)>' 15 0 10
        tput sc
        read con
        while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
        do
            centerprint 'Wrong Input,Please try again' 16 0 0
            tput rc
            read con
        done
        case $con in
            'Y') sed -i '/'$title'/d' library 
            ;;
            'N')
            ;;
            'y')
            ;;
            'n') break
            ;;
        esac
        centerprint 'Any more to delete? (Y)es or (N)o>' 16 0 6
        tput rc
        read con
        while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
        do
            centerprint 'Wrong Input,Please try again' 16 0 0
            tput rc
            read con
        done
        case $con in
            'Y') 
            ;;
            'N') break
            ;;
            'y')
            ;;
            'n') break
            ;;
        esac
    done
}
UPDATE()
{
    while true
    do
        clear
        if test ! -s ./library
        then
            centerprint 'Dont have file or the file is empty' 4 0 0
            read
            break
        fi
        centerprint 'Enter the title>' 4 0 0
        read title
        infomation=`grep $title library`
        if test -z "$infomation" 
        then
            centerprint 'Dont find , do you want try again?(Y)es or (N)o' 5 0 0
            tput sc
            read con
            while [ $con != 'Y' &&  $con != 'N' && $con != 'y' && $con != 'n' ]
            do
                centerprint 'Wrong Input,Please try again' 6 0 0
                tput rc
                read con
            done
            case $con in
                'Y') continue
                ;;
                'N') break
                ;;
                'y')
                ;;
                'n') break
                ;;
            esac
        fi
        centerprint 'Linux Library - ' 7 0 6
        echo -n $(tput bold)'UPDATE STATUS MODE'
        oldIFS=$IFS
        IFS=':'
        int=0
        ROW=10
        slist=('Title: ' 'Author:' 'Category: ' 'Stauts: ' 'name: ' 'date: ')
        tput cup 10 0 0
        for item in $infomation
        do
            echo '                    '${slist[int]}$item
            states[int]=$item
            let ROW++
            let int++
        done 
        IFS=$oldIFS
        sed -i '/'$title'/d' library 
        case ${states[3]} in
            'in')
            centerprint 'New status: out' 15 0 0
            centerprint 'Checked out by:' 16 0 0
            read name
            time=`date -I`
            centerprint "Date: "$time 15 0 0
            newone=''
            for k in `seq 0 2`
            do
                newone=$newone${states[k]}':'
            done
            newone=$newone'out:'$name':'$time
            echo $newone >> library
            ;;
            'out')
            centerprint 'New status: in' 13 0 10
            for k in $(seq 0 2)
            do
                newone=$newone${states[k]}':'
            done
            newone=$newone'in'
            echo $newone >> library
        esac
        centerprint 'Any more to update? (Y)es or (N)0>' 16 0 10
        tput sc
        read con
        while [ $con != 'Y' && $con != 'N' && $con != 'y' && $con != 'n' ]
        do
            centerprint 'Wrong Input,Please try again' 16 0 0
            tput rc
            read con
        done
        case $con in
            'Y')
            ;;
            'N') break
            ;;
            'y')
            ;;
            'n') break
            ;;
        esac
    done   
}
DISPLAY()
{
    while true
    do
        clear
        if test ! -s ./library
        then
            centerprint 'Dont have file or the file is empty' 4 0 0
            read
            break
        fi
        centerprint 'Enter the title>' 4 0 0
        read title
        infomation=`grep $title library`
        if [ -z $infomation ]
        then
            centerprint 'Dont find , do you want try again?(Y)es or (N)o' 5 0 0
            tput sc
            read con
            while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
            do
                centerprint 'Wrong Input,Please try again' 6 0 0
                tput rc
                read con
            done
            case $con in
                'Y') continue
                ;;
                'N') break
                ;;
                'y')
                ;;
                'n') break
                ;;
            esac
        fi
        centerprint 'Linux Library - ' 7 0 6
        echo -n $(tput bold)'DISPLAY MODE'
        oldIFS=$IFS
        IFS=':'
        int=0
        ROW=9
        slist=('Title: ' 'Author:' 'Category: ' 'Stauts: ' 'name: ' 'date: ')
        tput cup 10 0 0
        for item in $infomation
        do
            echo '                    '${slist[int]}$item
            let ROW++
            let int++
        done 
        IFS=$oldIFS
        centerprint 'Any more to look for? (Y)es or (N)0>' 16 0 10
        tput sc
        read con
        while [ test $con != 'Y' &&  test $con != 'N' && test $con != 'y' && test $con != 'n' ]
        d
            centerprint 'Wrong Input,Please try again' 16 0 0
            tput rc
            read con
        done
        case $con in
            'Y')
            ;;
            'N') break
            ;;
            'y')
            ;;
            'n') break
            ;;
        esac
    done
}
