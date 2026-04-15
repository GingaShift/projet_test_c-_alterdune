#include "model/Player.h"
#include "systems/RandomManager.h"
#include <iostream>

// Constructeur : initialise Entity + les compteurs propres au joueur
Player::Player(const std::string& name, int hp, int atk, int def)
    : Entity(name, hp, atk, def), kills(0), spared(0), gold(0), victories(0) {
}

// Le joueur attaque une cible
// Formule : dégâts = nombre aléatoire entre 0 et maxHp du défenseur
void Player::attack(Entity& target) {
    int degats = RandomManager::getInstance().getInt(0, target.getMaxHp());
    target.takeDamage(degats);

    std::cout << name << " attaque " << target.getName()
        << " et inflige " << degats << " degats !" << std::endl;
}

// Description enrichie du joueur
std::string Player::getDescription() const {
    return name + " [HP: " + std::to_string(hp) + "/" + std::to_string(maxHp)
        + " | Kills: " + std::to_string(kills)
        + " | Epargnes: " + std::to_string(spared) + "]";
}

// Ajoute un item à l'inventaire
void Player::addItem(const Item& item) {
    for (auto& existing : inventory) {
        if (existing.getName() == item.getName() &&
            existing.getType() == item.getType() &&
            existing.getValue() == item.getValue()) {
            existing.addQuantity(item.getQuantity());
            return;
        }
    }

    inventory.push_back(item);
}

// Utilise l'item à l'index donné, retourne false si index invalide
bool Player::useItem(int index) {
    if (index < 0 || index >= (int)inventory.size()) {
        std::cout << "Item invalide." << std::endl;
        return false;
    }

    inventory[index].use(*this);
    inventory[index].removeOne();

    if (inventory[index].getQuantity() <= 0) {
        inventory.erase(inventory.begin() + index);
    }

    return true;
}

// Affiche tous les items de l'inventaire
void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Inventaire vide." << std::endl;
        return;
    }

    for (int i = 0; i < (int)inventory.size(); i++) {
        std::cout << "[" << i << "] "
            << inventory[i].getName()
            << " x" << inventory[i].getQuantity()
            << " -> soigne " << inventory[i].getValue()
            << " HP" << std::endl;
    }
}

bool Player::hasItems() const {
    return !inventory.empty();
}

// Getters
int Player::getKills() const { return kills; }
int Player::getSpared() const { return spared; }
int Player::getGold() const { return gold; }
int Player::getVictories() const { return victories; }


// Incrémenteurs
void Player::addKill() { kills++; }
void Player::addSpared() { spared++; }
void Player::addGold(int amount) { gold += amount; }
void Player::addVictory() { victories++; }

// Affichage complet des stats du joueur
std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "=== " << p.name << " ===" << std::endl;
    os << "HP     : " << p.hp << "/" << p.maxHp << std::endl;
    os << "ATK    : " << p.atk << std::endl;
    os << "DEF    : " << p.def << std::endl;
    os << "Or     : " << p.gold << std::endl;
    os << "Kills  : " << p.kills << std::endl;
    os << "Epargnes: " << p.spared << std::endl;
    return os;
}