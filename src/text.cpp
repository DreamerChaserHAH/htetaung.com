#include <text.hpp>

void DrawHeader(const char *text, Vector2 position, int fontSize, bool centeralignment)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x + static_cast<int>(10 * (fontSize/96.0)) - (centeralignment? textSize.x / 2 : 0), position.y + static_cast<int>(10 * (fontSize/96.0)) - (centeralignment? textSize.y / 2 : 0)}, fontSize, 0, BACKGROUND_TERTIARY);
    DrawTextEx(font, text, Vector2{position.x - (centeralignment? textSize.x / 2: 0), position.y - (centeralignment? textSize.y / 2 : 0)}, fontSize, 0, FOREGROUND_MAIN);
}

void DrawNormalText(const char *text, Vector2 position, int fontSize, bool centeralignment)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x + (centeralignment? -textSize.x / 2: 0), position.y - (centeralignment? textSize.y / 2: 0)}, fontSize, 0, FOREGROUND_MAIN);
}

void DrawFlickingText(const char *text, Vector2 position, int fontSize)
{

    global_transparency += (increasing) ? global_transparency++ : global_transparency--;

    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x - textSize.x / 2, position.y - textSize.y / 2}, fontSize, 0, Color{FOREGROUND_MAIN.r, FOREGROUND_MAIN.g, FOREGROUND_MAIN.b, global_transparency});
}