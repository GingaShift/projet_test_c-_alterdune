#include "model/Entity.h"

// Constructeur : initialise tous les attributs
Entity::Entity(const std::string& name, int hp, int atk, int def)
    : name(name), hp(hp), maxHp(hp), atk(atk), def(def) {
}

// Applique les dégâts en s'assurant que les HP ne descendent pas sous 0
void Entity::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Entity::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}

// Retourne true si l'entité a encore des HP
bool Entity::isAlive() const {
    return hp > 0;
}

// Getters
std::string Entity::getName() const { return name; }
int Entity::getHp() const { return hp; }
int Entity::getMaxHp() const { return maxHp; }
int Entity::getAtk() const { return atk; }
int Entity::getDef() const { return def; }

// Description par défaut (peut être redéfinie par les enfants)
std::string Entity::getDescription() const {
    return name + " [HP: " + std::to_string(hp) + "/" + std::to_string(maxHp) + "]";
}

// Affiche les stats de l'entité dans la console
std::ostream& operator<<(std::ostream& os, const Entity& e) {
    os << "=== " << e.name << " ===" << std::endl;
    os << "HP  : " << e.hp << "/" << e.maxHp << std::endl;
    os << "ATK : " << e.atk << std::endl;
    os << "DEF : " << e.def << std::endl;
    return os;
}