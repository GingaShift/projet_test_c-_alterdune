#include "systems/RandomManager.h"
#include <random>

// Constructeur privé : initialise le moteur avec une graine aléatoire
RandomManager::RandomManager() {
    std::random_device rd;   // Source d'entropie matérielle
    engine = std::mt19937(rd()); // Initialise le moteur avec cette graine
}

// Retourne l'unique instance de la classe
RandomManager& RandomManager::getInstance() {
    static RandomManager instance; // Créée une seule fois, détruite à la fin
    return instance;
}

// Génère un entier entre min et max inclus
int RandomManager::getInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

// Génère un flottant entre 0.0 et 1.0
float RandomManager::getFloat() {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(engine);
}