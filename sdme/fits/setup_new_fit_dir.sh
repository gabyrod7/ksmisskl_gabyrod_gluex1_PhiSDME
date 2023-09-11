#!/bin/bash

if [ -z "$2" ]
then
	echo "Missing directory name or run period. Run as:"
	echo "./setup_new_fit_dir.sh <direcotry_name> <run_period>"
else
	mkdir $1
	cp ../sdme_scripts/* $1
	cd $1
	sed -i s/sdme_dir/$1 cmd.sh
	sed -i s/DATA/$2/g divideData.pl
	sed -i s/DATA/$2/g fitsdme.py
fi

