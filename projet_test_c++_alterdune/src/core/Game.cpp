#include "core/Game.h"
#include "systems/CsvLoader.h"
#include "systems/RandomManager.h"
#include "model/Item.h"
#include "ui/Colors.h"
#include <iostream>
#include <stdexcept>

// Constructeur : initialise le système de combat avec le catalogue
Game::Game() : combatSystem(actCatalog) {}

// Point d'entrée principal
void Game::run() {
    init();

    if (!player) {
        Menu::showError("Le jeu n'a pas pu etre initialise.");
        return;
    }

    gameLoop();

    Display::drawBox("A bientot !");
    std::cout << std::endl;
}

// Initialise une nouvelle partie
void Game::init() {
    state.reset();

    // Charge les monstres depuis le CSV
    try {
        bestiary.load("data/monsters.csv");
        Menu::showSuccess("Monstres charges : " +
            std::to_string(bestiary.getMonsterCount()));
    }
    catch (const std::exception& e) {
        Menu::showError(e.what());
        return;
    }

    // Demande le nom du joueur
    askPlayerName();

    // Crée le joueur
    player = std::make_unique<Player>(state.playerName, 100, 20, 10);

    // Donne quelques items de départ
    try {
        auto rows = CsvLoader::load("data/items.csv");

        for (int i = 0; i < (int)rows.size(); i++) {
            std::string name = rows[i].at("name");
            int value = std::stoi(rows[i].at("value"));
            int quantity = std::stoi(rows[i].at("quantity"));

            player->addItem(Item(name, ItemType::HEAL, value, quantity));
        }

        Menu::showSuccess("Items de depart ajoutes !");
    }
    catch (const std::exception& e) {
        Menu::showError(e.what());
    }
}

void Game::askPlayerName() {
    Display::clearScreen();
    Display::drawBox("NOUVELLE PARTIE");
    std::cout << std::endl;
    Display::typewriter("Quel est ton nom, petit humain ?");
    std::cout << Colors::CYAN << "> " << Colors::RESET;
    std::getline(std::cin, state.playerName);

    if (state.playerName.empty()) {
        state.playerName = "Frisk";
    }

    std::cout << std::endl;
    Display::typewriter("Ah... " + state.playerName + ". Quel joli nom.");
    Display::waitForEnter();
}

// Boucle principale : enchaîne les combats
void Game::gameLoop() {
    if (!player) {
        Menu::showError("Erreur d'initialisation !");
        return;
    }

    while (state.isRunning) {
        if (state.isGameOver()) {
            triggerEnding();
            break;
        }

        int choice = Menu::showMainMenu();

        switch (choice) {
        case 1:
            Menu::showBestiary(bestiary);
            break;

        case 2:
            runRandomCombat();
            if (state.isRunning && !state.isGameOver()) {
                showInterlude();
            }
            break;

        case 3:
            Menu::showStats(*player);
            break;

        case 4:
            Menu::showItems(*player);
            break;

        case 5:
            state.isRunning = false;
            break;
        }
    }
}

// Lance un combat contre un monstre aléatoire
void Game::runRandomCombat() {
    // Choisit un monstre aléatoire dans le bestiaire
    int index = RandomManager::getInstance().getInt(
        0, bestiary.getMonsterCount() - 1
    );

    // Récupère le nom du monstre via le bestiaire
    // On recharge pour obtenir le nom à l'index
    std::string monsterName = bestiary.getMonsterNameAt(index);

    // Crée le monstre
    std::unique_ptr<Monster> monster;
    try {
        monster = bestiary.createMonster(monsterName);
    }
    catch (const std::exception& e) {
        Menu::showError(e.what());
        return;
    }

    // Enregistre la rencontre dans le bestiaire
    

    // Lance le combat
    CombatResult result = combatSystem.startCombat(*player, *monster);

    // Gère le résultat
    handleCombatResult(result, *monster);
}

void Game::handleCombatResult(CombatResult result, const Monster& monster) {
    switch (result) {
    case CombatResult::VICTORY:
        state.kills++;
        state.victories++;
        player->addKill();
        player->addVictory();
        bestiary.registerKill(monster);
        Display::typewriter("Tu as vaincu " + monster.getName() + ".");
        break;

    case CombatResult::SPARE:
        state.spared++;
        state.victories++;
        player->addSpared();
        player->addVictory();
        bestiary.registerSpare(monster);
        Display::typewriter("Tu as epargne " + monster.getName() + ".");
        break;

    case CombatResult::DEFEAT:
        Display::typewriter("Tu t'es effondre...");
        Display::typewriter("Mais quelqu'un croit encore en toi.");
        player = std::make_unique<Player>(state.playerName, 100, 20, 10);
        break;

    case CombatResult::FLEE:
        Display::typewriter("Tu t'es enfui !");
        break;
    }

    state.updateRoute();
}

// Affiche l'écran entre deux combats
void Game::showInterlude() {
    Display::drawSeparator();
    std::cout << std::endl;

    // Affiche les stats actuelles
    std::cout << Colors::CYAN << "[ " << state.playerName << " ] ";
    Display::drawHpBar(player->getHp(), player->getMaxHp());
    std::cout << Colors::YELLOW << "Victoires : "
        << state.victories << "/10"
        << Colors::RESET << std::endl;
    std::cout << std::endl;

    Display::waitForEnter();
}

// Déclenche la fin de partie
void Game::triggerEnding() {
    EndingId ending = EndingSystem::calculateEnding(
        state.victories,
        state.kills,
        state.spared
    );

    EndingSystem::displayEnding(ending);
    Menu::showStats(*player);

    // Menu de fin
    int choice = Menu::showEndMenu();
    if (choice == 1) {
        // Rejouer
        state.reset();
        run();
    }
}