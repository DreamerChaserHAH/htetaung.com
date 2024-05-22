#ifndef TEXT_HTPP
#define TEXT_HPP

#include <game-config.h>
#include <raylib.h>

void DrawHeader(const char *text, Vector2 position, int fontSize);

void DrawNormalText(const char *text, Vector2 position, int fontSize, bool centeralignment);

void DrawFlickingText(const char *text, Vector2 position, int fontSize);
#endif