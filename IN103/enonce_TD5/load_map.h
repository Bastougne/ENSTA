#ifndef __LOAD_MAP_H__
#define __LOAD_MAP_H__

#include <stdbool.h>
#include "station.h"

/** Construit un graphe à partir de la desription textuelle se trouvant
    dans le fichier dont le nom est passé en argument. */
bool load_map (char *name) ;

/** Retourne la liste chaînée de toutes les stations (noeuds) du graphe
    préalablement construit par un appel à load_map. */
struct stations_list_t* get_all_stations (void) ;

#endif
