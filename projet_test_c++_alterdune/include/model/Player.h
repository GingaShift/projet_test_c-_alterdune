#pragma once
#include "model/Entity.h"
#include "model/Item.h"
#include <vector>

class Player : public Entity {
public:
    // Constructeur
    Player(const std::string& name, int hp, int atk, int def);

    // Implémentation obligatoire de la méthode virtuelle pure d'Entity
    void attack(Entity& target) override;

    // Redéfinition de la description pour afficher les stats du joueur
    std::string getDescription() const override;

    // Gestion de l'inventaire
    void addItem(const Item& item);
    bool useItem(int index);
    void showInventory() const;
    bool hasItems() const;

    // Getters des compteurs de fin de partie
    int getKills() const;
    int getSpared() const;
    int getGold() const;

    // Incrémenteurs
    void addKill();
    void addSpared();
    void addGold(int amount);

    // Surcharge de << pour afficher toutes les stats du joueur
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
