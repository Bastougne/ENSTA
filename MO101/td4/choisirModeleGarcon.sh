#! /bin/bash

NBMODELE=`ls modeles/*garcon* | wc -l`
CHOIX=$(( (RANDOM % $NBMODELE) + 1))
echo `ls modeles/*garcon-$CHOIX*`