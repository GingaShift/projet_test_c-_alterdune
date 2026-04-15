#pragma once
#include "model/Player.h"
#include "model/Monster.h"
#include "systems/ActCatalog.h"

enum class CombatResult {
    VICTORY,    // Le monstre est mort
    SPARE,      // Le monstre a été épargné
    DEFEAT,     // Le joueur est mort
    FLEE        // Le joueur a fui
};

class CombatSystem {
public:
    CombatSystem(ActCatalog& catalog);

    CombatResult startCombat(Player& player, Monster& monster);

private:
    ActCatalog& catalog;  // Référence au catalogue d'actions

    bool playerTurn(Player& player, Monster& monster);

    bool monsterTurn(Player& player, Monster& monster);

    void handleFight(Player& player, Monster& monster);
    void handleAct(Player& player, Monster& monster);
    void handleItem(Player& player, Monster& monster);
    bool handleMercy(Player& player, Monster& monster);

    void displayStatus(const Player& player, const Monster& monster) const;
    void displayMenu() const;
};