#pragma once
#include "ui/Colors.h"
#include "model/Player.h"
#include "model/Monster.h"
#include <string>

class Display {
public:
    // Affiche du texte lettre par lettre (effet typewriter)
    static void typewriter(const std::string& text, int delayMs = 30);

    // Affiche un cadre ASCII autour d'un titre
    static void drawBox(const std::string& title);

    // Affiche une barre de HP colorisée
    // Ex: [========  ] 80/100
    static void drawHpBar(int current, int max, int barWidth = 20);

    // Affiche une barre de Mercy colorisée
    static void drawMercyBar(int current, int max, int barWidth = 20);

    // Affiche le titre du jeu au démarrage
    static void drawTitle();

    // Affiche un séparateur horizontal
    static void drawSeparator();

    // Efface la console
    static void clearScreen();

    // Pause : attend que le joueur appuie sur Entrée
    static void waitForEnter();
};