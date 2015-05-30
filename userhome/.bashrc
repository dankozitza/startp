#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin

alias ls='ls --color=auto'
alias sc='systemctl'
alias cpueat="while true; do date; ps auxf | awk '{if(\$8==\"D\") print $0;}\'; sleep 1; done"
alias save_vms="echo 'shutting down running vms'; VBoxManage list runningvms | sed -r 's/\"//' | sed -r 's/\".*$//' | xargs -i VBoxManage controlvm '{}' savestate"

function off {

	save_vms
	sleep 1

	echo
	echo "running vms:"
	echo
	if ps -ef | grep -v "grep" | grep "startvm"
	then
		echo
		echo "there are still vms running"
		
	else
		echo "no vms running, shutting down"
		echo
		su -c 'shutdown'
	fi

	# alias offon="save_vms; reboot"
}

alias check="echo $UID"

#PS1='[\u@\h \W]\$ '
