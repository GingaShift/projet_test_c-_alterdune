#include "model/Item.h"
#include "model/Player.h"
#include <iostream>

Item::Item(const std::string& name, ItemType type, int value, int quantity)
    : name(name), type(type), value(value), quantity(quantity) {
}

void Item::use(Player& player) const {
    if (type == ItemType::HEAL) {
        player.heal(value);
        std::cout << "Vous utilisez " << name
            << " et recuperez " << value << " HP !" << std::endl;
    }
}

std::string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
int Item::getValue() const { return value; }
int Item::getQuantity() const { return quantity; }

void Item::addQuantity(int amount) {
    quantity += amount;
}

void Item::removeOne() {
    if (quantity > 0) {
        quantity--;
    }
}