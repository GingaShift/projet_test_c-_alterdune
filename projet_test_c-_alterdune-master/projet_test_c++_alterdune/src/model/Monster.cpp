#include "model/Monster.h"
#include "systems/RandomManager.h"
#include <iostream>

Monster::Monster(const std::string& name,
    int hp,
    int atk,
    int def,
    MonsterCategory category,
    int mercyThreshold,
    const std::vector<ActId>& availableActs)
    : Entity(name, hp, atk, def),
    category(category),
    mercy(0),
    mercyThreshold(mercyThreshold),
    sleeping(false),
    spared(false),
    availableActs(availableActs) {
}

void Monster::attack(Entity& target) {
    if (sleeping) {
        std::cout << name << " dort profondement et n'attaque pas." << std::endl;
        return;
    }

    int degats = RandomManager::getInstance().getInt(0, target.getMaxHp());
    target.takeDamage(degats);

    std::cout << name << " attaque " << target.getName()
        << " et inflige " << degats << " degats !" << std::endl;
}

std::string Monster::getDescription() const {
    std::string desc = name + " [HP: " + std::to_string(hp)
        + "/" + std::to_string(maxHp)
        + " | Mercy: " + std::to_string(mercy)
        + "/" + std::to_string(mercyThreshold) + "]";
    if (sleeping) desc += " (endormi)";
    if (spared) desc += " (epargne)";
    return desc;
}

void Monster::addMercy(int amount) {
    mercy += amount;
    if (mercy > mercyThreshold) mercy = mercyThreshold;
    if (mercy < 0) mercy = 0;
}

bool Monster::canBeSpared() const {
    return mercy >= mercyThreshold;
}

void Monster::setSleeping(bool state) { sleeping = state; }
void Monster::setSpared(bool state) { spared = state; }
bool Monster::isSleeping() const { return sleeping; }
bool Monster::isSpared() const { return spared; }

int Monster::getActCount() const {
    return (int)acts.size();
}

MonsterCategory Monster::getCategory() const { return category; }
int Monster::getMercy() const { return mercy; }
int Monster::getMercyThreshold() const { return mercyThreshold; }

std::vector<ActId> Monster::getActs() const {
    return acts;
}

std::vector<ActId> Monster::getAvailableActs() const {
    return availableActs;
}