#pragma once
#include <random>

class RandomManager {
public:
    static RandomManager& getInstance();

    int getInt(int min, int max);

    float getFloat();

    RandomManager(const RandomManager&) = delete;
    RandomManager& operator=(const RandomManager&) = delete;

private:
    RandomManager();

    std::mt19937 engine;  // Le moteur Mersenne Twister
};
