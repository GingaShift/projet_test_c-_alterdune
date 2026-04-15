#pragma once
#include <string>
#include <iostream>

class Entity {
public:
    Entity(const std::string& name, int hp, int atk, int def);

    virtual ~Entity() = default;

    virtual void attack(Entity& target) = 0;

    virtual std::string getDescription() const;

    void takeDamage(int amount);

    void heal(int amount);

    bool isAlive() const;

    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAtk() const;
    int getDef() const;

    friend std::ostream& operator<<(std::ostream& os, const Entity& e);

protected:
    std::string name;
    int hp;
    int maxHp;
    int atk;
    int def;
};
