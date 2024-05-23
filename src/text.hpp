#ifndef TEXT_HPP
#define TEXT_HPP

#include <game-config.h>
#include <raylib.h>

void DrawHeader(const char *text, Vector2 position, int fontSize, bool centralalignment = true);

void DrawNormalText(const char *text, Vector2 position, int fontSize, bool centeralignment = false);

void DrawFlickingText(const char *text, Vector2 position, int fontSize);
#endif