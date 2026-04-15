#pragma once
#include "model/Entity.h"
#include "model/Item.h"
#include <vector>

class Player : public Entity {
public:
    Player(const std::string& name, int hp, int atk, int def);

    void attack(Entity& target) override;

    std::string getDescription() const override;

    void addItem(const Item& item);
    bool useItem(int index);
    void showInventory() const;
    bool hasItems() const;

    int getKills() const;
    int getSpared() const;
    int getGold() const;

    void addKill();
    void addSpared();
    void addGold(int amount);

    friend std::ostream& operator<<(std::ostream& os, const Player& p);

    int getVictories() const;
    void addVictory();

private:
    std::vector<Item> inventory;  // Liste des items possédés
    int kills;                    // Nombre de monstres tués
    int spared;                   // Nombre de monstres épargnés
    int gold;                     // Or possédé
    int victories;
};
