#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <raylib.h>
#include <cstdint>

#define RAYGUI_IMPLEMENTATION

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define BACKGROUND_MAIN Color{0xd1, 0xcd, 0xb7, 0xff}
#define BACKGROUND_SECONDARY Color{0xcc, 0xc8, 0xb1, 0xff}
#define BACKGROUND_TERTIARY Color{0xb4, 0xaf, 0x9a, 0xff}
#define BACKGROUND_FOURTH Color{0xda, 0xd4, 0xbb, 0xff}
#define FOREGROUND_MAIN Color{0x45, 0x41, 0x38, 0xff}

#define FLICKERING_INTERVAL 1000

#define BUTTON_HEIGHT 35

extern Font font;
extern Sound clickEffect;

extern uint8_t global_transparency;
extern bool increasing;

#endif