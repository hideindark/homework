#!/bin/bash
function5()
{
    while true
    do
        clear
        echo 'What you want to do，make your choice'
        echo '0.back to Title'
        echo '1.Show the FTP service status'
        echo '2.Start ftp service'
        echo '3.stop ftp service'
        echo '4.Show the apache2 service status'
        echo '5.Start apache service'
        echo '6.Stop apache service'
        read choice;tput sc
        if (($choice<0 || $choice>6))
        then
            echo 'Wrong choice, Please try again'
            echo 'Press any button to Continue'
            read
            continue
        else
            case $choice in
            0) break;;
            1) service vsftpd status;;
            2) service vsftpd start;;
            3) service vsftpd stop;;
            4) systemctl status apache2.service;;
            5) sudo /etc/init.d/apache2 start;;
            6) sudo /etc/init.d/apache2 stop;;
            esac
        fi
    done
}