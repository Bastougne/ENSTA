#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct guerrier {
    char *nom;
    float pv;
    int pa;
    float tg;
};

void afficher_guerrier( struct guerrier P ) {
    printf( "Le guerrier %s a %.2f points de vie\n", P.nom, P.pv );
};

void attaque( struct guerrier *Pjoueur, struct guerrier *Padversaire ) {
    printf( "%s attaque %s\n", Pjoueur->nom, Padversaire->nom );
    Padversaire->pv = Padversaire->pv - Pjoueur->pa;
};

void bouclier( struct guerrier *Pjoueur ) {
    printf( "%s lève son bouclier\n", Pjoueur->nom );
    Pjoueur->pv = Pjoueur->pv + Pjoueur->tg * ( 100 - Pjoueur->pv );
};

void main() {
    struct guerrier P1 = { "Aragorn", 100, 20, 0.6 };
    struct guerrier P2 = { "Boromir", 100, 30, 0.4 };
    afficher_guerrier( P1 );
    afficher_guerrier( P2 );
    struct guerrier *Pjoueur = &P1;
    struct guerrier *Padversaire = &P2;
    struct guerrier *tempo;
    char touche;
    struct guerrier *gagnant = 0;
    int tours = 0;
    float regen;
    srand( time( 0 ) );
    while ( gagnant == 0 ) {
        printf( "%s va-t-il attaquer %s (a) ou lever son bouclier (b) ?    ->", Pjoueur->nom, Padversaire->nom );
        scanf( " %c", &touche );
        if ( touche == 'a' ) {
            attaque( Pjoueur, Padversaire );
        } else if ( touche == 'b' ) {
            bouclier( Pjoueur );
        };
        regen = rand() % 11 - 5;
        if ( regen > 0 ) {
            printf( "%s se soigne\n", Padversaire->nom );
            Padversaire->pv = Padversaire->pv + regen;
        } else {
            printf( "%s se blesse\n", Padversaire->nom );
            Padversaire->pv = Padversaire->pv + regen;
        };
        afficher_guerrier( *Pjoueur );
        afficher_guerrier( *Padversaire );
        if ( Padversaire->pv <= 0 ) {
            gagnant = Pjoueur;
        };
        tempo = Pjoueur;
        Pjoueur = Padversaire;
        Padversaire = tempo;
        tours = tours + 1;
        printf( "\n" );
    };
    printf( "%s a gagné en %i tours !\n", gagnant->nom, tours );
};