#ifndef _EPIDEMIE_CONTEXT_HPP_
#define _EPIDEMIE_CONTEXT_HPP_
#include "interactions.hpp"
#include <cstdint>
#include <random>

namespace epidemie {
struct ContexteGlobal {
    std::size_t taux_population = 100'000; // Nombre de personnes sur terre
    std::size_t esperance_de_vie = 29'200; // Nombre de jours que vit un individu (80 ans = 365 * 80 jours )
    int deplacement_maximal = 10;
    Interactions interactions;
};
} // namespace epidemie
#endif