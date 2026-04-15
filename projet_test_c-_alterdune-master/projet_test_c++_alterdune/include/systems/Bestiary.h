#pragma once
#include "model/Monster.h"
#include "model/BestiaryEntry.h"
#include <vector>
#include <memory>
#include <string>

class Bestiary {
public:
    Bestiary();

    void load(const std::string& filepath);

    std::unique_ptr<Monster> createMonster(const std::string& name) const;

    void registerKill(const Monster& monster);
    void registerSpare(const Monster& monster);

    void displayAll() const;

    int getMonsterCount() const;
    std::string getMonsterNameAt(int index) const;

private:
    struct MonsterData {
        std::string name;
        int hp;
        int atk;
        int def;
        MonsterCategory category;
        int mercyThreshold;
        std::vector<ActId> acts;
        std::vector<ActId> availableActs;
    };

    std::vector<MonsterData> monstersData;
    std::vector<BestiaryEntry> entries;

    MonsterCategory parseCategory(const std::string& str) const;
};