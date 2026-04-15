#include "ui/Display.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

// Affiche le texte lettre par lettre avec un délai entre chaque caractère
void Display::typewriter(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::endl;
}

// Affiche un cadre ASCII autour d'un titre
void Display::drawBox(const std::string& title) {
    int width = (int)title.length() + 4;
    std::string border(width, '=');

    std::cout << Colors::CYAN << border << Colors::RESET << std::endl;
    std::cout << Colors::CYAN << "| " << Colors::RESET;
    std::cout << Colors::BOLD << title << Colors::RESET;
    std::cout << Colors::CYAN << " |" << Colors::RESET << std::endl;
    std::cout << Colors::CYAN << border << Colors::RESET << std::endl;
}

// Affiche une barre de HP colorisée
void Display::drawHpBar(int current, int max, int barWidth) {
    // Calcule le nombre de segments remplis
    int filled = (max > 0) ? (current * barWidth / max) : 0;

    // Choisit la couleur selon le pourcentage de HP restants
    std::string color;
    float ratio = (max > 0) ? (float)current / max : 0;
    if (ratio > 0.5f)       color = Colors::GREEN;
    else if (ratio > 0.25f) color = Colors::YELLOW;
    else                    color = Colors::RED;

    std::cout << "HP ";
    std::cout << color << "[";
    for (int i = 0; i < barWidth; i++) {
        std::cout << (i < filled ? "=" : " ");
    }
    std::cout << "] " << Colors::RESET;
    std::cout << Colors::BOLD << current << "/" << max << Colors::RESET;
    std::cout << std::endl;
}

// Affiche une barre de Mercy colorisée en jaune
void Display::drawMercyBar(int current, int max, int barWidth) {
    int filled = (max > 0) ? (current * barWidth / max) : 0;

    std::cout << Colors::YELLOW << "MERCY [";
    for (int i = 0; i < barWidth; i++) {
        std::cout << (i < filled ? "#" : "-");
    }
    std::cout << "] " << current << "/" << max << Colors::RESET;
    std::cout << std::endl;
}

// Affiche le titre ASCII du jeu
void Display::drawTitle() {
    std::cout << Colors::MAGENTA << Colors::BOLD;
    std::cout << "    ___    __    ____________  ____  __  ___   ________" << std::endl;
    std::cout << "   /   |  / /   /_  __/ __/ / / / | / / __/  / ____/ /" << std::endl;
    std::cout << "  / /| | / /     / / / _// /_/ /  |/ / _/   /___ \\/ /" << std::endl;
    std::cout << " / ___ |/ /___  / / / __/ __  / /|  / /___  ___/ /_/  " << std::endl;
    std::cout << "/_/  |_/_____/ /_/ /___/_/ /_/_/ |_/_____/ /____/(_)  " << std::endl;
    std::cout << Colors::RESET << std::endl;
    std::cout << Colors::CYAN;
    std::cout << "        Interactive Systems — Un monde a epargner" << std::endl;
    std::cout << Colors::RESET << std::endl;
}

// Affiche un séparateur horizontal
void Display::drawSeparator() {
    std::cout << Colors::DIM;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << Colors::RESET;
}

// Efface la console (Windows)
void Display::clearScreen() {
    system("cls");
}

void Display::waitForEnter() {
    std::cout << Colors::DIM << "[ Appuyez sur Entree pour continuer... ]"
        << Colors::RESET << std::endl;

    // Vide TOUT le buffer d'abord
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}