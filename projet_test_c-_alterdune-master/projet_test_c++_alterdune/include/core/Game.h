#pragma once
#include "core/GameState.h"
#include "model/Player.h"
#include "systems/Bestiary.h"
#include "systems/ActCatalog.h"
#include "systems/CombatSystem.h"
#include "systems/EndingSystem.h"
#include "ui/Menu.h"
#include "ui/Display.h"
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    GameState           state;
    ActCatalog          actCatalog;
    Bestiary            bestiary;
    CombatSystem        combatSystem;
    std::unique_ptr<Player> player;

    void init();

    void askPlayerName();

    void gameLoop();

    void runRandomCombat();

    void handleCombatResult(CombatResult result, const Monster& monster);

    void triggerEnding();

    void showInterlude();
};