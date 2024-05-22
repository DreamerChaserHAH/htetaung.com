#pragma once

#include <game-config.h>
#include <raylib.h>
#include <functional>

class Button
{
    const char *text;
    int index;
    std::function<void(int)> onClick;
    std::function<void(int)> onHover;

    bool IsMouseHovering = false;
    bool ShouldPlaySound = true;

public:
    Button(){}
    Button(const char *text, int index, std::function<void(int)> onHover, std::function<void(int)> onClick, bool centerAlignment = true) : text(text), index(index), onHover(onHover), onClick(onClick) {}
    void DrawButton(Vector2 position, bool isSelected)
    {
        IsMouseHovering = false;

        Color ForegroundColor = FOREGROUND_MAIN;
        Color BackgroundColor = BACKGROUND_FOURTH;
        Vector2 mousePosition = GetMousePosition();

        if ((mousePosition.x >= position.x - 190/2 && mousePosition.x <= position.x + 190 - 190/2 && mousePosition.y >= position.y - 35/2 && mousePosition.y <= position.y + 35 - 35/2) || isSelected)
        {
            ForegroundColor = BACKGROUND_FOURTH;
            BackgroundColor = FOREGROUND_MAIN;
            IsMouseHovering = true;
            onClick(index);
            //if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            //    onClick(index);
            //}
        }

        DrawRectangle(position.x - 190/2, position.y - 35/2, 190, 35, BackgroundColor);
        DrawTextEx(font, text, Vector2{position.x + 25 - 190/2, position.y + 1 - 35/2}, 34, 0, ForegroundColor);
        //DrawTexture(GetNavIcon(iconType), positionX + 3, positionY + 7, ForegroundColor);
    }
    void Update(){
        if(IsMouseHovering && ShouldPlaySound){
            onHover(index);
            PlaySound(clickEffect);
            ShouldPlaySound = false;
        }

        if(!IsMouseHovering){
            ShouldPlaySound = true;
        }
    }
};