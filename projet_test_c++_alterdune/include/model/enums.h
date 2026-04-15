#pragma once

// Catégories de monstres
// Détermine le nombre d'actions ACT disponibles en combat
enum class MonsterCategory {
    NORMAL,    // 2 actions ACT disponibles
    MINIBOSS,  // 3 actions ACT disponibles
    BOSS       // 4 actions ACT disponibles
};

// Types d'items
enum class ItemType {
    HEAL       // Restaure des HP
};

// Identifiants des actions ACT disponibles en combat
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

// Identifiants des fins de partie
enum class EndingId {
    PACIFIST,  // Zéro kill, tous épargnés
    GENOCIDE,  // Tous les monstres tués
    NEUTRAL    // Entre les deux
};