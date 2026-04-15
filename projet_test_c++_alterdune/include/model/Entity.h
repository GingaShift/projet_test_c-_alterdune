#pragma once
#include <string>
#include <iostream>

class Entity {
public:
    // Constructeur
    Entity(const std::string& name, int hp, int atk, int def);

    // Destructeur virtuel : indispensable quand on utilise l'héritage
    virtual ~Entity() = default;

    // Méthode virtuelle pure : chaque enfant DOIT l'implémenter
    virtual void attack(Entity& target) = 0;

    // Méthode virtuelle : peut être redéfinie par les enfants
    virtual std::string getDescription() const;

    // Applique des dégâts à l'entité
    void takeDamage(int amount);

    void heal(int amount);

    // Vérifie si l'entité est encore en vie
    bool isAlive() const;

    // Getters
    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAtk() const;
    int getDef() const;

    // Surcharge de l'opérateur << pour afficher les stats
    friend std::ostream& operator<<(std::ostream& os, const Entity& e);

protected:
    // Attributs accessibles par les classes filles (Player, Monster)
    std::string name;
    int hp;
    int maxHp;
    int atk;
    int def;
};
