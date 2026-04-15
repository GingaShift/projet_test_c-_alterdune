#pragma once
#include "model/enums.h"

class EndingSystem {
public:
    static EndingId calculateEnding(int totalMonsters, int kills, int spared);

    static void displayEnding(EndingId ending);
};