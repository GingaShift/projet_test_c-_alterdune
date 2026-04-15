#pragma once
#include "model/enums.h"
#include <string>

class Player;

class Item {
public:
    Item(const std::string& name, ItemType type, int value, int quantity = 1);

    void use(Player& player) const;

    std::string getName() const;
    ItemType getType() const;
    int getValue() const;
    int getQuantity() const;

    void addQuantity(int amount);
    void removeOne();

private:
    std::string name;
    ItemType type;
    int value;
    int quantity;
};