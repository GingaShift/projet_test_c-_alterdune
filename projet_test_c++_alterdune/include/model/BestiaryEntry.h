#pragma once
#include "model/enums.h"
#include <string>

class BestiaryEntry {
public:
    BestiaryEntry(const std::string& monsterName,
        MonsterCategory category,
        int hpMax,
        int atk,
        int def,
        const std::string& result);

    void display() const;

    std::string getMonsterName() const;

private:
    std::string monsterName;
    MonsterCategory category;
    int hpMax;
    int atk;
    int def;
    std::string result; // "Tue" ou "Epargne"
};