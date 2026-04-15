#pragma once
#include "ui/Display.h"
#include "ui/Colors.h"
#include "model/Player.h"
#include "systems/Bestiary.h"
#include <string>

class Menu {
public:
    // Menu principal du jeu
    // 1 = Bestiaire
    // 2 = Démarrer un combat
    // 3 = Statistiques
    // 4 = Items
    // 5 = Quitter
    static int showMainMenu();

    // Menu de fin
    // 1 = Rejouer
    // 2 = Quitter
    static int showEndMenu();

    static void showStats(const Player& player);
    static void showBestiary(const Bestiary& bestiary);
    static void showItems(Player& player);

    static int getValidInput(int min, int max);
    static void showError(const std::string& message);
    static void showSuccess(const std::string& message);
};