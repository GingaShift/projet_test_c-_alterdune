#pragma once

enum class MonsterCategory {
    NORMAL,    // 2 actions ACT disponibles
    MINIBOSS,  // 3 actions ACT disponibles
    BOSS       // 4 actions ACT disponibles
};

enum class ItemType {
    HEAL       // Restaure des HP
};

enum class ActId {
    CHECK,     // Inspecte le monstre, affiche ses stats
    TALK,      // Engage la conversation
    FLIRT,     // Tente de séduire le monstre
    THREATEN,   // Intimide le monstre 
    SINGG,      // Chante pour le monstre
    JOKE,      // Raconte une blague
    SPARE,     // Propose d'épargner
    TAUNT,      // Provoque le monstre
    COMPLIMENT, // Complimente le monstre
    INSULT  // Insulte le monstre

};

enum class EndingId {
    PACIFIST,  // Zéro kill, tous épargnés
    GENOCIDE,  // Tous les monstres tués
    NEUTRAL    // Entre les deux
};