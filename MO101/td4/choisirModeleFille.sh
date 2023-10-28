#! /bin/bash

NBMODELE=`ls modeles/*fille* | wc -l`
CHOIX=$(( (RANDOM % $NBMODELE) + 1))
echo `ls modeles/*fille-$CHOIX*`