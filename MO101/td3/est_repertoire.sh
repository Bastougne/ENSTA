#! /bin/bash

if [ $# -gt 0 ]
then
	if [ -d $1 ]
	then
		echo $1 : est un dossier
	fi
fi