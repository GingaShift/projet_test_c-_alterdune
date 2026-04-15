#pragma once
#include "model/enums.h"

class EndingSystem {
public:
    // Calcule la fin selon les compteurs
    // totalMonsters = nombre total de monstres dans le jeu
    // kills         = nombre de monstres tués
    // spared        = nombre de monstres épargnés
    static EndingId calculateEnding(int totalMonsters, int kills, int spared);

    // Affiche le texte de fin correspondant
    static void displayEnding(EndingId ending);
};