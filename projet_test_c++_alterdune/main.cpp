#include "core/Game.h"
#include <iostream>

int main() {
    // Active les couleurs ANSI dans la console Windows
    system("chcp 65001 > nul");

    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}