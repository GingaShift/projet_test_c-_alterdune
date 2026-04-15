#include "systems/EndingSystem.h"
#include <iostream>

// Calcule la fin de partie selon les compteurs
EndingId EndingSystem::calculateEnding(int totalMonsters, int kills, int spared) {

    // Fin Génocide : tous les monstres ont été tués
    if (kills == totalMonsters) {
        return EndingId::GENOCIDE;
    }

    // Fin Pacifiste : aucun kill ET tous les monstres épargnés
    if (kills == 0 && spared == totalMonsters) {
        return EndingId::PACIFIST;
    }

    // Fin Neutre : tout le reste
    return EndingId::NEUTRAL;
}

// Affiche le texte narratif de fin
void EndingSystem::displayEnding(EndingId ending) {
    std::cout << std::endl;
    std::cout << "==============================" << std::endl;

    switch (ending) {
    case EndingId::PACIFIST:
        std::cout << "FIN PACIFISTE" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Tu as traverse ce monde sans oter une seule vie." << std::endl;
        std::cout << "Chaque monstre rencontre repart avec un souvenir." << std::endl;
        std::cout << "Le monde sourit dans ton dos." << std::endl;
        break;

    case EndingId::GENOCIDE:
        std::cout << "FIN GENOCIDE" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Tu as tout detruit." << std::endl;
        std::cout << "Il ne reste plus rien. Pas meme le silence." << std::endl;
        std::cout << "Felicitations, j'imagine." << std::endl;
        break;

    case EndingId::NEUTRAL:
        std::cout << "FIN NEUTRE" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Tu as fait des choix. Certains bons, d'autres moins." << std::endl;
        std::cout << "Le monde continue, un peu different qu'avant." << std::endl;
        std::cout << "Peut-etre qu'une prochaine fois sera differente." << std::endl;
        break;
    }

    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
}