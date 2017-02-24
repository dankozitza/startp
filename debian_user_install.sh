#!/bin/bash

USER_NAME=$1

### install init.d scripts ###
#
echo "\n!--- installing init.d scripts ---!\n"
sleep 2
ln init.d/mount_media /etc/init.d/mount_media
chmod 755 /etc/init.d/mount_media
update-rc.d mount_media defaults

ln init.d/mount_backup /etc/init.d/mount_backup
chmod 755 /etc/init.d/mount_backup
update-rc.d mount_backup defaults
#
###

USER_HOME="/home/$USER_NAME/"
if [[ "$USER_NAME" == "root" ]]; then
	USER_HOME="/$USER_NAME/"
	echo "set user home to $USER_HOME"
fi

### set git name and email ###
#
#git config --system user.name "Dan Kozitza"
#git config --system user.email "dankoz@gmx.us"
#git config --system color.diff always
#git config --system color.status true
#
###

### root+program configuration ###
#
#find userhome/ -maxdepth 1 -mindepth 1 -exec cp -r {} ~ \;
#find usr/ -maxdepth 1 -mindepth 1 -exec cp -r {} /usr/ \;
#find etc/ -maxdepth 1 -mindepth 1 -exec cp -r {} /etc/ \;
#
###

### network setup ***
#
#ip addr
#
#echo "\n!--- configure network.service ---!\n"
#sleep 5
#
#vim network.service
#
#cp extra/network.service /etc/systemd/system/
#
#systemctl daemon-reload
#systemctl start network.service
#
#echo "\n!--- if ping fails network setup failed! ---!\n"
#sleep 2
#
#ping google.com
#
###

### virtualbox guest setup ###
#
#apt-get -q install virtualbox-guest-modules
#apt-get -q install virtualbox-guest-utils
#
#modprobe -a vboxguest vboxsf vboxvideo
#cp extra/virtualboxguest.conf /etc/modules-load.d/
#cp extra/mount_vboxshared.service /etc/systemd/system/
#systemd start mount_vboxshared.service
#
#systemctl daemon-reload
#systemctl enable vboxservice
#
###

#### program download+installation ***
##
##echo "\n!--- Now going to install a few programs ---!\n"
##sleep 2
##
#apt-get -q install vim
#apt-get -q install wget
#apt-get -q install rsnapshot
##apt-get -q install openbox
##apt-get -q install xorg
##apt-get -q install xorg-xinit
##apt-get -q install xfce4-terminal
##apt-get -q install xfce4
##apt-get -q install arandr
##apt-get -q install git
##apt-get -q install go
#apt-get -q install mpc
#apt-get -q install ncmpcpp
##apt-get -q install alsa-utils
#apt-get -q install htop
##apt-get -q install surf
#apt-get -q install dwb
##apt-get -q install gst-plugins-good
##apt-get -q install dmenu
#apt-get -q install figlet
##apt-get -q install flashplugin
##apt-get -q install transmission-gtk
#apt-get -q install scrot
##apt-get -q install gimp
##apt-get -q install epdfview
#apt-get -q install tor
##
####

### user setup ###
#
#echo "\n!--- Now going to set up user $USER_NAME ---!\n"
#sleep 2
#
#useradd -m -s /bin/bash $USER_NAME
#passwd $USER_NAME
#
###

### user+program configuration ***
#
echo "\n!--- Now going to configure programs ---!\n"
sleep 2

# copy config files
# for all of them
#find userhome/ -maxdepth 1 -mindepth 1 -exec cp -r {} $USER_HOME \;

#cp userhome/.bashrc "$USER_HOME.bashrc"
cp -r userhome/.irssi "$USER_HOME.irssi"
cp userhome/.vimrc "$USER_HOME.vimrc"

#openbox --reconfigure

#mkdir -p $USER_HOME/go/src/github.com/dankozitza
#mkdir $USER_HOME/go/pkg

# make sure user owns all their files
#chown -R $USER_NAME $USER_HOME
#
###

echo "\n!--- Done ---!\n"

### virtualbox host setup ###
#
#apt-get -q install virtualbox
#apt-get -q install qt4
#apt-get -q install virtualbox-guest-iso
#
#depmod -a
#modprobe vboxdrv
#modprobe vboxpci
#cp extra/virtualboxhost.conf /etc/modules-load.d/
#
###
