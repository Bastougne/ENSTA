#!/bin/bash
NBFILE=0
NBDIR=0

for ELEM in $(ls)
do
  if test -f $ELEM
  then
      NBFILE=$(expr $NBFILE + 1)
  elif test -d $ELEM
  then
      NBDIR=$(expr $NBDIR + 1)
  fi
done

echo "There are $NBFILE files"
echo "There are $NBDIR directories"