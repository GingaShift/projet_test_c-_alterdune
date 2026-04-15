#include "systems/Bestiary.h"
#include "systems/CsvLoader.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
Bestiary::Bestiary() {}

// Charge les monstres depuis le CSV
void Bestiary::load(const std::string& filepath) {
    std::vector<CsvRow> rows = CsvLoader::load(filepath);

    monstersData.clear();
    entries.clear();

    for (const auto& row : rows) {
        MonsterData data;

        data.name = row.at("name");
        data.hp = std::stoi(row.at("hp"));
        data.atk = std::stoi(row.at("atk"));
        data.def = std::stoi(row.at("def"));
        data.category = parseCategory(row.at("category"));
        data.mercyThreshold = std::stoi(row.at("mercyThreshold"));

        std::vector<std::string> actFields = {
            row.at("act1"),
            row.at("act2"),
            row.at("act3"),
            row.at("act4")};

        for (const auto& actStr : actFields) {
            if (actStr == "-") continue;

            if (actStr == "CHECK") data.availableActs.push_back(ActId::CHECK);
            else if (actStr == "TALK") data.availableActs.push_back(ActId::TALK);
            else if (actStr == "FLIRT") data.availableActs.push_back(ActId::FLIRT);
            else if (actStr == "THREATEN") data.availableActs.push_back(ActId::THREATEN);
            else if (actStr == "SINGG") data.availableActs.push_back(ActId::SINGG);
            else if (actStr == "JOKE") data.availableActs.push_back(ActId::JOKE);
            else if (actStr == "SPARE") data.availableActs.push_back(ActId::SPARE);
            else if (actStr == "TAUNT") data.availableActs.push_back(ActId::TAUNT);
            else if (actStr == "COMPLIMENT") data.availableActs.push_back(ActId::COMPLIMENT);
            else if (actStr == "INSULT") data.availableActs.push_back(ActId::INSULT);
            else {
                throw std::runtime_error("Act inconnu dans monsters.csv : " + actStr);
            }
        }

        monstersData.push_back(data);
    }
}

// Crée une instance de Monster prête pour le combat
std::unique_ptr<Monster> Bestiary::createMonster(const std::string& name) const {
    for (const auto& data : monstersData) {
        if (data.name == name) {
            auto monster = std::make_unique<Monster>(
                data.name,
                data.hp,
                data.atk,
                data.def,
                data.category,
                data.mercyThreshold,
                data.acts,
                data.availableActs
            );
            return monster;
        }
    }
    throw std::runtime_error("Monstre introuvable : " + name);
}


// Affiche tout le bestiaire
void Bestiary::displayAll() const {
    std::cout << "=== BESTIAIRE ===" << std::endl;
    for (const auto& entry : entries) {
        entry.display();
        std::cout << std::endl;
    }
}

// Retourne le nombre de monstres chargés
int Bestiary::getMonsterCount() const {
    return (int)monstersData.size();
}

// Convertit une string en MonsterCategory
MonsterCategory Bestiary::parseCategory(const std::string& str) const {
    if (str == "NORMAL")   return MonsterCategory::NORMAL;
    if (str == "MINIBOSS") return MonsterCategory::MINIBOSS;
    if (str == "BOSS")     return MonsterCategory::BOSS;
    throw std::runtime_error("Categorie inconnue : " + str);
}

void Bestiary::registerKill(const Monster& monster) {
    entries.emplace_back(
        monster.getName(),
        monster.getCategory(),
        monster.getMaxHp(),
        monster.getAtk(),
        monster.getDef(),
        "Tue"
    );
}

void Bestiary::registerSpare(const Monster& monster) {
    entries.emplace_back(
        monster.getName(),
        monster.getCategory(),
        monster.getMaxHp(),
        monster.getAtk(),
        monster.getDef(),
        "Epargne"
    );
}

std::string Bestiary::getMonsterNameAt(int index) const {
    if (index < 0 || index >= (int)monstersData.size()) {
        throw std::runtime_error("Index de monstre invalide.");
    }
    return monstersData[index].name;
}