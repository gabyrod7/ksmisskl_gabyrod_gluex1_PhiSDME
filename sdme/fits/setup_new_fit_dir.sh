#!/bin/bash

if [ -z "$1" ]
then
	echo "Missing directory name. Run as:"
	echo "./setup_new_fit_dir.sh <direcotry_name>"
else
	mkdir $1
	cp ../sdme_scripts/* $1
	cd $1
	sed -i s/sdme_dir/$1/ cmd.sh
fi

