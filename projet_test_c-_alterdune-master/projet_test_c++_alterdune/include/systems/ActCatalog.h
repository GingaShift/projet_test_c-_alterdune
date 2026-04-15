#pragma once
#include "model/Act.h"
#include "model/enums.h"
#include <map>
#include <vector>

class ActCatalog {
public:
    ActCatalog();

    const Act& getAct(ActId id) const;

    std::vector<ActId> getAvailableActs(MonsterCategory category) const;

    void displayAvailableActs(MonsterCategory category) const;

    bool exists(ActId id) const;

private:
    std::map<ActId, Act> catalog; // Dictionnaire ActId → Act
};