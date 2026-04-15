#pragma once
#include "ui/Colors.h"
#include "model/Player.h"
#include "model/Monster.h"
#include <string>

class Display {
public:
    static void typewriter(const std::string& text, int delayMs = 30);

    static void drawBox(const std::string& title);

    static void drawHpBar(int current, int max, int barWidth = 20);

    static void drawMercyBar(int current, int max, int barWidth = 20);

    static void drawTitle();

    static void drawSeparator();

    static void clearScreen();

    static void waitForEnter();
};