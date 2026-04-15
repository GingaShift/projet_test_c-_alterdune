#pragma once
#include "model/Player.h"
#include "model/Monster.h"
#include "systems/ActCatalog.h"

// Résultat possible d'un combat
enum class CombatResult {
    VICTORY,    // Le monstre est mort
    SPARE,      // Le monstre a été épargné
    DEFEAT,     // Le joueur est mort
    FLEE        // Le joueur a fui
};

class CombatSystem {
public:
    // Constructeur
    CombatSystem(ActCatalog& catalog);

    // Lance un combat complet entre le joueur et un monstre
    CombatResult startCombat(Player& player, Monster& monster);

private:
    ActCatalog& catalog;  // Référence au catalogue d'actions

    // --- Tours ---
    // Tour du joueur : retourne true si le combat continue
    bool playerTurn(Player& player, Monster& monster);

    // Tour du monstre : retourne true si le combat continue
    bool monsterTurn(Player& player, Monster& monster);

    // --- Actions du joueur ---
    void handleFight(Player& player, Monster& monster);
    void handleAct(Player& player, Monster& monster);
    void handleItem(Player& player, Monster& monster);
    bool handleMercy(Player& player, Monster& monster);

    // --- Affichage ---
    void displayStatus(const Player& player, const Monster& monster) const;
    void displayMenu() const;
};