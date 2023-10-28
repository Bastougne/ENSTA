#include "contexte.hpp"
#include "graphisme/src/SDL2/sdl2.hpp"
#include "individu.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <ostream>
#include <random>

void majStatistique( epidemie::Grille &grille, std::vector<epidemie::Individu> const &individus ) {
    for ( auto &statistique : grille.getStatistiques() ) {
        statistique.nombre_contaminant_grippe_et_contamine_par_agent = 0;
        statistique.nombre_contaminant_seulement_contamine_par_agent = 0;
        statistique.nombre_contaminant_seulement_grippe = 0;
    }
    auto [largeur, hauteur] = grille.dimension();
    auto &statistiques = grille.getStatistiques();
    for ( auto const &personne : individus ) {
        auto pos = personne.position();

        std::size_t index = pos.x + pos.y * largeur;
        if ( personne.aGrippeContagieuse() ) {
            if ( personne.aAgentPathogeneContagieux() ) {
                statistiques[index].nombre_contaminant_grippe_et_contamine_par_agent += 1;
            } else {
                statistiques[index].nombre_contaminant_seulement_grippe += 1;
            }
        } else {
            if ( personne.aAgentPathogeneContagieux() ) {
                statistiques[index].nombre_contaminant_seulement_contamine_par_agent += 1;
            }
        }
    }
}

void afficheSimulation( sdl2::window &ecran, epidemie::Grille const &grille, std::size_t jour ) {
    auto [largeur_ecran, hauteur_ecran] = ecran.dimensions();
    auto [largeur_grille, hauteur_grille] = grille.dimension();
    auto const &statistiques = grille.getStatistiques();
    sdl2::font fonte_texte( "./graphisme/src/data/Lato-Thin.ttf", 18 );
    ecran.cls( { 0x00, 0x00, 0x00 } );
    // Affichage de la grille :
    std::uint16_t stepX = largeur_ecran / largeur_grille;
    unsigned short stepY = ( hauteur_ecran - 50 ) / hauteur_grille;
    double factor = 255. / 15.;

    for ( unsigned short i = 0; i < largeur_grille; ++i ) {
        for ( unsigned short j = 0; j < hauteur_grille; ++j ) {
            auto const &stat = statistiques[i + j * largeur_grille];
            int valueGrippe =
                stat.nombre_contaminant_grippe_et_contamine_par_agent + stat.nombre_contaminant_seulement_grippe;
            int valueAgent = stat.nombre_contaminant_grippe_et_contamine_par_agent +
                             stat.nombre_contaminant_seulement_contamine_par_agent;
            std::uint16_t origx = i * stepX;
            std::uint16_t origy = j * stepY;
            std::uint8_t red = valueGrippe > 0 ? 127 + std::uint8_t( std::min( 128., 0.5 * factor * valueGrippe ) ) : 0;
            std::uint8_t green = std::uint8_t( std::min( 255., factor * valueAgent ) );
            std::uint8_t blue = std::uint8_t( std::min( 255., factor * valueAgent ) );
            ecran << sdl2::rectangle( { origx, origy }, { stepX, stepY }, { red, green, blue }, true );
        }
    }

    ecran << sdl2::texte( "Carte population grippee", fonte_texte, ecran, { 0xFF, 0xFF, 0xFF, 0xFF } )
                 .at( largeur_ecran / 2, hauteur_ecran - 20 );
    ecran << sdl2::texte( std::string( "Jour : " ) + std::to_string( jour ), fonte_texte, ecran,
                          { 0xFF, 0xFF, 0xFF, 0xFF } )
                 .at( 0, hauteur_ecran - 20 );
    ecran << sdl2::flush;
}

void simulation( bool affiche, MPI_Comm globComm, int rank ) {

    constexpr const unsigned int largeur_ecran = 1280, hauteur_ecran = static_cast<int>( largeur_ecran / 1.25 );
    sdl2::window ecran( "Simulation epidemie de grippe", { largeur_ecran, hauteur_ecran } );

    unsigned int graine_aleatoire = 1;
    std::uniform_real_distribution<double> porteur_pathogene( 0., 1. );

    epidemie::ContexteGlobal contexte;
    // contexte.deplacement_maximal = 1; <= Si on veut moins de brassage
    contexte.taux_population = 400'000;
    // contexte.taux_population = 1'000;
    contexte.interactions.beta = 60.;
    std::vector<epidemie::Individu> population;
    population.reserve( contexte.taux_population );
    epidemie::Grille grille{ contexte.taux_population };

    auto [largeur_grille, hauteur_grille] = grille.dimension();
    // L'agent pathogene n'evolue pas et reste donc constant...
    epidemie::AgentPathogene agent( graine_aleatoire++ );
    // Initialisation de la population initiale :
    for ( std::size_t i = 0; i < contexte.taux_population; ++i ) {
        std::default_random_engine motor( 100 * ( i + 1 ) );
        population.emplace_back( graine_aleatoire++, contexte.esperance_de_vie, contexte.deplacement_maximal );
        population.back().setPosition( largeur_grille, hauteur_grille );
        if ( porteur_pathogene( motor ) < 0.2 ) {
            population.back().estContamine( agent );
        }
    }

    MPI_Status status;
    int flag = 0;

    std::size_t jours_ecoules = 0;
    int jour_apparition_grippe = 0;
    int nombre_immunises_grippe = ( contexte.taux_population * 23 ) / 100;
    sdl2::event_queue queue;

    bool quitting = false;
    // bool quit;

    std::ofstream output( "Courbe.dat" );
    output << "# jours_ecoules \t nombreTotalContaminesGrippe \t nombreTotalContaminesAgentPathogene() \t "
              "dureeSimulation \t dureeAffichage \n";

    epidemie::Grippe grippe( 0 );

    auto debut = std::chrono::system_clock::now(), fin = debut;
    double dureeSimulation, dureeAffichage;

    std::cout << "Debut boucle epidemie" << std::endl << std::flush;

    // MPI_Reduce( &quitting, &quit, 1, MPI_C_BOOL, MPI_LOR, 0, globComm );
    // quitting = quit;
    while ( !quitting ) {

        debut = std::chrono::system_clock::now();
        if ( rank == 1 ) { // ce processus s'occupe de la simulation
            auto events = queue.pull_events();
            for ( const auto &e : events ) {
                if ( e->kind_of_event() == sdl2::event::quit )
                    quitting = true;
            }
            if ( jours_ecoules % 365 == 0 ) // Si le premier Octobre (debut de l'annee pour l'epidemie ;-) )
            {
                grippe = epidemie::Grippe( jours_ecoules / 365 );
                jour_apparition_grippe = grippe.dateCalculImportationGrippe();
                grippe.calculNouveauTauxTransmission();
                // 23% des gens sont immunises. On prend les 23% premiers
                for ( int ipersonne = 0; ipersonne < nombre_immunises_grippe; ++ipersonne ) {
                    population[ipersonne].devientImmuniseGrippe();
                }
                for ( int ipersonne = nombre_immunises_grippe; ipersonne < int( contexte.taux_population );
                      ++ipersonne ) {
                    population[ipersonne].redevientSensibleGrippe();
                }
            }
            if ( jours_ecoules % 365 == std::size_t( jour_apparition_grippe ) ) {
                for ( int ipersonne = nombre_immunises_grippe; ipersonne < nombre_immunises_grippe + 25; ++ipersonne ) {
                    population[ipersonne].estContamine( grippe );
                }
            }
            // Mise a jour des statistiques pour les cases de la grille :
            majStatistique( grille, population );
            // On parcout la population pour voir qui est contamine et qui ne l'est pas, d'abord pour la grippe puis
            // pour l'agent pathogene
            std::size_t compteur_grippe = 0, compteur_agent = 0, mouru = 0;
            for ( auto &personne : population ) {
                if ( personne.testContaminationGrippe( grille, contexte.interactions, grippe, agent ) ) {
                    compteur_grippe++;
                    personne.estContamine( grippe );
                }
                if ( personne.testContaminationAgent( grille, agent ) ) {
                    compteur_agent++;
                    personne.estContamine( agent );
                }
                // On verifie si il n'y a pas de personne qui veillissent de veillesse et on genere une nouvelle
                // personne si c'est le cas.
                if ( personne.doitMourir() ) {
                    mouru++;
                    unsigned nouvelle_graine = jours_ecoules + personne.position().x * personne.position().y;
                    personne =
                        epidemie::Individu( nouvelle_graine, contexte.esperance_de_vie, contexte.deplacement_maximal );
                    personne.setPosition( largeur_grille, hauteur_grille );
                }
                personne.veillirDUnJour();
                personne.seDeplace( grille );
            }
            fin = std::chrono::system_clock::now();
            dureeSimulation = (double)std::chrono::duration_cast<std::chrono::milliseconds>( fin - debut ).count();

            flag = 0;
            MPI_Iprobe( 0, 0, globComm, &flag, &status );
            if ( flag ) { // si le processus 0 est pret a afficher
                MPI_Send( &dureeSimulation, 1, MPI_DOUBLE, 0, 0, globComm );
                MPI_Send( grille.getStatistiques().data(), 3 * largeur_grille * hauteur_grille, MPI_INT, 0, 1,
                          globComm );
            }

        } else if ( rank == 0 ) { // ce processus s'occupe de l'affichage
            int pret = 1;
            MPI_Send( &pret, 1, MPI_INT, 1, 0, globComm );
            MPI_Recv( &dureeSimulation, 1, MPI_DOUBLE, 1, 0, globComm, &status );
            MPI_Recv( grille.getStatistiques().data(), 3 * largeur_grille * hauteur_grille, MPI_INT, 1, 1, globComm,
                      &status );

            //#############################################################################################################
            //##    Affichage des resultats pour le temps  actuel
            //#############################################################################################################
            if ( affiche ) {
                afficheSimulation( ecran, grille, jours_ecoules );
            }
            fin = std::chrono::system_clock::now();
            dureeAffichage = (double)std::chrono::duration_cast<std::chrono::milliseconds>( fin - debut ).count();

            /*std::cout << jours_ecoules << "\t" << grille.nombreTotalContaminesGrippe() << "\t"
                      << grille.nombreTotalContaminesAgentPathogene() << std::endl;*/

            output << jours_ecoules << "\t\t" << grille.nombreTotalContaminesGrippe() << "\t\t"
                   << grille.nombreTotalContaminesAgentPathogene() << "\t\t" << dureeSimulation << "\t\t"
                   << dureeAffichage << std::endl;
        }
        jours_ecoules += 1;

    } // Fin boucle temporelle
    output.close();
}

int main( int argc, char *argv[] ) {
    int numtasks, rank;

    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; // Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    // parse command-line
    bool affiche = true;
    for ( int i = 0; i < argc; i++ ) {
        std::cout << i << " " << argv[i] << "\n";
        if ( std::string( "-nw" ) == argv[i] )
            affiche = false;
    }

    sdl2::init( argc, argv );
    { simulation( affiche, globComm, rank ); }
    sdl2::finalize();

    MPI_Finalize();
    return EXIT_SUCCESS;
}
