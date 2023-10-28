#! /bin/bash

MODELE=$1
PRENOM=$2
TAILLE=$3
POIDS=$4
DATE=`date -d $5 "+%d %B %Y"`

sed -e "s/<PRENOM>/$PRENOM/" -e "s/<TAILLE>/$TAILLE/" -e "s/<POIDS>/$POIDS/"  -e "s/<DATE>/$DATE/" $MODELE