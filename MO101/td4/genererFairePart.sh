#! /bin/bash

cat naissances.txt | while read LINE; do
    GENRE=`echo $LINE | cut -d";" -f 1`
    PRENOM=`echo $LINE | cut -d";" -f 2`
    TAILLE=`echo $LINE | cut -d";" -f 3`
    POIDS=`echo $LINE | cut -d";" -f 4`
    DATE=`echo $LINE | cut -d";" -f 5`

    if [ $GENRE == 'Fille' ]; then
    bash creerFairePart.sh `bash choisirModeleFille.sh` $PRENOM $TAILLE $POIDS $DATE > faire-part/$PRENOM-$DATE.txt
    else
    bash creerFairePart.sh `bash choisirModeleGarcon.sh` $PRENOM $TAILLE $POIDS $DATE > faire-part/$PRENOM-$DATE.txt
    fi
done