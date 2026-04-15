#include "ui/Menu.h"
#include <iostream>
#include <limits>

// Menu principal du jeu
int Menu::showMainMenu() {
    Display::clearScreen();
    Display::drawTitle();
    Display::drawSeparator();

    std::cout << Colors::BRIGHT_WHITE << Colors::BOLD;
    std::cout << "  [1] Bestiaire" << std::endl;
    std::cout << "  [2] Demarrer un combat" << std::endl;
    std::cout << "  [3] Statistiques du personnage" << std::endl;
    std::cout << "  [4] Items" << std::endl;
    std::cout << "  [5] Quitter" << std::endl;
    std::cout << Colors::RESET << std::endl;

    Display::drawSeparator();
    std::cout << Colors::CYAN << "Votre choix : " << Colors::RESET;

    return getValidInput(1, 5);
}

// Menu de fin de partie
int Menu::showEndMenu() {
    Display::drawSeparator();
    std::cout << Colors::BRIGHT_WHITE << Colors::BOLD;
    std::cout << "  [1] Rejouer" << std::endl;
    std::cout << "  [2] Quitter" << std::endl;
    std::cout << Colors::RESET << std::endl;
    Display::drawSeparator();
    std::cout << Colors::CYAN << "Votre choix : " << Colors::RESET;

    return getValidInput(1, 2);
}

// Affiche les statistiques complètes du joueur
void Menu::showStats(const Player& player) {
    Display::clearScreen();
    Display::drawBox("STATISTIQUES DU PERSONNAGE");
    std::cout << std::endl;

    std::cout << "Nom      : " << player.getName() << std::endl;
    std::cout << "HP       : " << player.getHp() << "/" << player.getMaxHp() << std::endl;
    std::cout << "Tues     : " << player.getKills() << std::endl;
    std::cout << "Epargnes : " << player.getSpared() << std::endl;
    std::cout << "Victoires: " << player.getVictories() << "/10" << std::endl;

    std::cout << std::endl;
    Display::waitForEnter();
}

// Affiche le bestiaire complet
void Menu::showBestiary(const Bestiary& bestiary) {
    Display::clearScreen();
    Display::drawBox("BESTIAIRE");
    std::cout << std::endl;
    bestiary.displayAll();
    Display::waitForEnter();
}

int Menu::getValidInput(int min, int max) {
    int choice;
    while (true) {
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << Colors::RED << "Choix invalide. Entrez un nombre entre "
            << min << " et " << max << " : " << Colors::RESET;
    }
}

// Affiche un message d'erreur en rouge
void Menu::showError(const std::string& message) {
    std::cout << Colors::RED << Colors::BOLD
        << "[ERREUR] " << message
        << Colors::RESET << std::endl;
}

// Affiche un message de succès en vert
void Menu::showSuccess(const std::string& message) {
    std::cout << Colors::GREEN << Colors::BOLD
        << "[OK] " << message
        << Colors::RESET << std::endl;
}

void Menu::showItems(Player& player) {
    Display::clearScreen();
    Display::drawBox("ITEMS");
    std::cout << std::endl;

    player.showInventory();
    std::cout << std::endl;
    std::cout << "[ -1 ] Retour" << std::endl;
    std::cout << "Choisissez un item a utiliser : ";

    int choice;
    while (!(std::cin >> choice) || choice < -1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide : ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == -1) {
        return;
    }

    player.useItem(choice);
    Display::waitForEnter();
}