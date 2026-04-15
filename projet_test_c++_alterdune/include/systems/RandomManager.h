#pragma once
#include <random>

class RandomManager {
public:
    // Retourne l'instance unique (Singleton)
    static RandomManager& getInstance();

    // Retourne un entier aléatoire entre min et max inclus
    int getInt(int min, int max);

    // Retourne un flottant aléatoire entre 0.0 et 1.0
    float getFloat();

    // Empêche la copie et l'assignation (règle du Singleton)
    RandomManager(const RandomManager&) = delete;
    RandomManager& operator=(const RandomManager&) = delete;

private:
    // Constructeur privé : on ne peut pas créer d'instance depuis l'extérieur
    RandomManager();

    std::mt19937 engine;  // Le moteur Mersenne Twister
};
