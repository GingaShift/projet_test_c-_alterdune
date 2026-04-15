#include "model/BestiaryEntry.h"
#include <iostream>

BestiaryEntry::BestiaryEntry(const std::string& monsterName,
    MonsterCategory category,
    int hpMax,
    int atk,
    int def,
    const std::string& result)
    : monsterName(monsterName),
    category(category),
    hpMax(hpMax),
    atk(atk),
    def(def),
    result(result) {
}

void BestiaryEntry::display() const {
    std::cout << "=== " << monsterName << " ===" << std::endl;

    std::cout << "Categorie : ";
    switch (category) {
    case MonsterCategory::NORMAL:
        std::cout << "NORMAL";
        break;
    case MonsterCategory::MINIBOSS:
        std::cout << "MINIBOSS";
        break;
    case MonsterCategory::BOSS:
        std::cout << "BOSS";
        break;
    }
    std::cout << std::endl;

    std::cout << "HP max   : " << hpMax << std::endl;
    std::cout << "ATK      : " << atk << std::endl;
    std::cout << "DEF      : " << def << std::endl;
    std::cout << "Resultat : " << result << std::endl;
}

std::string BestiaryEntry::getMonsterName() const {
    return monsterName;
}