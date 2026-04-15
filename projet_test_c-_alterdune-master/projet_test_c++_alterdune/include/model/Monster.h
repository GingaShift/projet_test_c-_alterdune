#pragma once
#include "model/Entity.h"
#include "model/enums.h"
#include <vector>
#include <string>

class Monster : public Entity {
public:
    Monster(const std::string& name,
        int hp,
        int atk,
        int def,
        MonsterCategory category,
        int mercyThreshold,
        const std::vector<ActId>& availableActs);

    void attack(Entity& target) override;
    std::string getDescription() const override;

    void addMercy(int amount);
    bool canBeSpared() const;

    void setSleeping(bool state);
    void setSpared(bool state);
    bool isSleeping() const;
    bool isSpared() const;

    int getActCount() const;
    MonsterCategory getCategory() const;
    int getMercy() const;
    int getMercyThreshold() const;
    std::vector<ActId> getActs() const;
    std::vector<ActId> getAvailableActs() const;

private:
    MonsterCategory category;
    int mercy;
    int mercyThreshold;
    bool sleeping;
    bool spared;
    std::vector<ActId> acts;
    std::vector<ActId> availableActs;
};