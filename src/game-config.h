#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <raylib.h>
#include <cstdint>

#define RAYGUI_IMPLEMENTATION

#define INITIAL_SCREEN_WIDTH 1280
#define INITIAL_SCREEN_HEIGHT 720
#define INITIAL_MAIN_TITLE_FONT_SIZE 96
#define INITIAL_SUBHEADER_FONT_SIZE 20
#define INITIAL_HEADER_1_FONT_SIZE 64
#define INITIAL_HEADER_2_FONT_SIZE 48
#define INITIAL_HEADER_3_FONT_SIZE 36
#define INITIAL_TEXT_FONT_SIZE 20

#define INITIAL_HORIZONTAL_CLAMP_DIFFERENCE 600

#define BACKGROUND_MAIN Color{0xd1, 0xcd, 0xb7, 0xff}
#define BACKGROUND_SECONDARY Color{0xcc, 0xc8, 0xb1, 0xff}
#define BACKGROUND_TERTIARY Color{0xb4, 0xaf, 0x9a, 0xff}
#define BACKGROUND_FOURTH Color{0xda, 0xd4, 0xbb, 0xff}
#define FOREGROUND_MAIN Color{0x45, 0x41, 0x38, 0xff}

#define FLICKERING_INTERVAL 1000

#define INITIAL_BUTTON_WIDTH 190
#define INITIAL_BUTTON_HEIGHT 50

extern Font font;
extern Sound clickEffect;

extern uint8_t global_transparency;
extern bool increasing;

extern float SCREEN_WIDTH;
extern float SCREEN_HEIGHT;
extern float TITLE_FONT_SIZE;
extern float SUBHEADER_FONT_SIZE;
extern float HEADER_1_FONT_SIZE;
extern float HEADER_2_FONT_SIZE;
extern float HEADER_3_FONT_SIZE;
extern float TEXT_FONT_SIZE;
extern float HORIZONTAL_CLAMP_DIFFERENCE;
extern float HORIZONTAL_DRAW_START_DISTANCE;
extern float BUTTON_WIDTH;
extern float BUTTON_HEIGHT;

float BasedOnScreenHeight(float Original);

float BasedOnScreenWidth(float Original);

float BasedOnScreenHeightCapped(float Original, float min, float max);

float BasedOnScreenWidthCapped(float Original, float min, float max);

#endif