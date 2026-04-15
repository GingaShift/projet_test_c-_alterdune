#include "systems/CombatSystem.h"
#include "systems/RandomManager.h"
#include <iostream>
#include <limits>

CombatSystem::CombatSystem(ActCatalog& catalog) : catalog(catalog) {}

// Boucle de combat principale
CombatResult CombatSystem::startCombat(Player& player, Monster& monster) {
    std::cout << std::endl;
    std::cout << "*** " << monster.getName() << " apparait ! ***" << std::endl;
    std::cout << std::endl;

    while (true) {
        // Affiche l'état actuel
        displayStatus(player, monster);

        // Tour du joueur
        bool combatContinue = playerTurn(player, monster);
        if (!combatContinue) {
            // Vérifie la raison de l'arrêt
            if (!monster.isAlive()) {
                std::cout << monster.getName() << " est vaincu !" << std::endl;
                return CombatResult::VICTORY;
            }
            if (monster.isSpared()) {
                std::cout << monster.getName() << " s'en va paisiblement." << std::endl;
                return CombatResult::SPARE;
            }
            // Fuite
            return CombatResult::FLEE;
        }

        // Tour du monstre
        combatContinue = monsterTurn(player, monster);
        if (!combatContinue) {
            std::cout << "Vous etes vaincu..." << std::endl;
            return CombatResult::DEFEAT;
        }
    }
}

// Tour du joueur : choisit une action
bool CombatSystem::playerTurn(Player& player, Monster& monster) {
    displayMenu();

    int choice = 0;
    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide. Entrez 1, 2, 3 ou 4 : ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        handleFight(player, monster);
        // Vérifie si le monstre est mort après l'attaque
        if (!monster.isAlive()) return false;
        break;
    case 2:
        handleAct(player, monster);
        break;
    case 3:
        handleItem(player, monster);
        break;
    case 4:
        return handleMercy(player, monster);
    }
    return true;
}

// Tour du monstre : attaque le joueur
bool CombatSystem::monsterTurn(Player& player, Monster& monster) {
    std::cout << std::endl;
    monster.attack(player);
    if (!player.isAlive()) return false;
    return true;
}

// Action FIGHT : le joueur attaque le monstre
void CombatSystem::handleFight(Player& player, Monster& monster) {
    std::cout << std::endl;
    player.attack(monster);
}

// Action ACT : le joueur effectue une action spéciale
void CombatSystem::handleAct(Player& player, Monster& monster) {
    std::cout << std::endl;
    std::cout << "--- ACT ---" << std::endl;

    // Récupère les actions disponibles selon la catégorie du monstre
    std::vector<ActId> availableActs = monster.getAvailableActs();

    // Affiche les actions numérotées
    for (int i = 0; i < (int)availableActs.size(); i++) {
        const Act& act = catalog.getAct(availableActs[i]);
        std::cout << "[" << i + 1 << "] " << act.getDescription() << std::endl;
    }
    std::cout << "[0] Retour" << std::endl;

    int choice = -1;
    while (!(std::cin >> choice) || choice < 0 || choice >(int)availableActs.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide : ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) return;

    // Applique l'effet de l'action sur la jauge mercy
    const Act& chosen = catalog.getAct(availableActs[choice - 1]);
    monster.addMercy(chosen.getMercyImpact());

    std::cout << monster.getName() << " reagit." << std::endl;
    std::cout << "Mercy : " << monster.getMercy()
        << "/" << monster.getMercyThreshold() << std::endl;
}

// Action ITEM : utilise un item de l'inventaire
void CombatSystem::handleItem(Player& player, Monster& monster) {
    std::cout << std::endl;
    std::cout << "--- INVENTAIRE ---" << std::endl;
    player.showInventory();

    if (player.getHp() == player.getMaxHp()) {
        std::cout << "Inventaire vide ou HP deja au maximum." << std::endl;
        return;
    }

    int choice = -1;
    std::cout << "Choisissez un item (ou -1 pour annuler) : ";
    while (!(std::cin >> choice) || choice < -1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide : ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == -1) return;
    player.useItem(choice);
}

// Action MERCY : épargne le monstre si la jauge est suffisante
bool CombatSystem::handleMercy(Player& player, Monster& monster) {
    std::cout << std::endl;
    if (monster.canBeSpared()) {
        monster.setSpared(true);
        std::cout << "Vous epargnez " << monster.getName() << " !" << std::endl;
        return false;  // Combat terminé
    }
    else {
        std::cout << "La jauge Mercy est insuffisante ("
            << monster.getMercy() << "/"
            << monster.getMercyThreshold() << ")." << std::endl;
        std::cout << "Continuez a utiliser ACT pour augmenter la jauge." << std::endl;
        return true;   // Combat continue
    }
}

// Affiche l'état du joueur et du monstre
void CombatSystem::displayStatus(const Player& player, const Monster& monster) const {
    std::cout << "------------------------------" << std::endl;
    std::cout << monster.getDescription() << std::endl;
    std::cout << player.getDescription() << std::endl;
    std::cout << "------------------------------" << std::endl;
}

// Affiche le menu principal du combat
void CombatSystem::displayMenu() const {
    std::cout << std::endl;
    std::cout << "[1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY" << std::endl;
    std::cout << "Votre choix : ";
}