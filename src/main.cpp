#include <chrono>

#include <game-config.h>
#include <raygui.h>
#include <yorha.h>
#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;
#endif

enum Screen: uint8_t{
    HOME,
    ABOUT,
    PROJECTS,
    SKILLS,
    CONTACT
};

Font font;
Texture NavIcons[5];
Music BackgroundMusic;
Sound ClickEffect;

const std::chrono::milliseconds interval(FLICKERING_INTERVAL);
auto lastChangedTime = std::chrono::steady_clock::now();
uint8_t global_transparency;
bool increasing;
bool IsMouseHovering = false;
bool ShouldPlayMouseHover = true;
Screen currentScreen = HOME;

Texture &GetNavIcon(Screen type)
{
    return NavIcons[type];
}

void DrawHeader(const char *text, Vector2 position, int fontSize)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x + 10 - textSize.x / 2, position.y + 10 - textSize.y / 2}, fontSize, 0, BACKGROUND_TERTIARY);
    DrawTextEx(font, text, Vector2{position.x - textSize.x / 2, position.y - textSize.y / 2}, fontSize, 0, FOREGROUND_MAIN);
}

void DrawNormalText(const char *text, Vector2 position, int fontSize)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x - textSize.x / 2, position.y - textSize.y / 2}, fontSize, 0, FOREGROUND_MAIN);
}

void DrawFlickingText(const char *text, Vector2 position, int fontSize)
{

    global_transparency += (increasing) ? global_transparency++ : global_transparency--;

    Vector2 textSize = MeasureTextEx(font, text, fontSize, 0);
    DrawTextEx(font, text, Vector2{position.x - textSize.x / 2, position.y - textSize.y / 2}, fontSize, 0, Color{FOREGROUND_MAIN.r, FOREGROUND_MAIN.g, FOREGROUND_MAIN.b, global_transparency});
}

void DrawBackground()
{
    ClearBackground(BACKGROUND_MAIN);
    for (int i = 0; i < SCREEN_WIDTH; i += 6)
    {
        DrawLine(i, 0, i, SCREEN_HEIGHT, BACKGROUND_SECONDARY);
    }
    for (int i = 0; i < SCREEN_HEIGHT; i += 6)
    {
        DrawLine(0, i, SCREEN_WIDTH, i, BACKGROUND_SECONDARY);
    }
}

void DrawNavLines()
{
    DrawLine(0, 60, SCREEN_WIDTH, 60, FOREGROUND_MAIN);
    DrawLine(0, 61, SCREEN_WIDTH, 61, FOREGROUND_MAIN);
    DrawLine(0, SCREEN_HEIGHT - 60, SCREEN_WIDTH, SCREEN_HEIGHT - 60, FOREGROUND_MAIN);
    DrawLine(0, SCREEN_HEIGHT - 61, SCREEN_WIDTH, SCREEN_HEIGHT - 61, FOREGROUND_MAIN);
}

void DrawNavButton(float positionX, float positionY, int iconId, const char *text, Screen iconType)
{
    Color ForegroundColor = FOREGROUND_MAIN;
    Color BackgroundColor = BACKGROUND_TERTIARY;
    Vector2 mousePosition = GetMousePosition();

    if ((mousePosition.x >= positionX && mousePosition.x <= positionX + 190 && mousePosition.y >= positionY && mousePosition.y <= positionY + 35))
    {
            ForegroundColor = BACKGROUND_TERTIARY;
            BackgroundColor = FOREGROUND_MAIN;
            IsMouseHovering = true;
    }

    if(iconType == currentScreen){
        ForegroundColor = BACKGROUND_TERTIARY;
        BackgroundColor = FOREGROUND_MAIN;
        DrawRectangle(positionX, positionY, 190, 50, BackgroundColor);
    }

    DrawRectangle(positionX, positionY, 190, 35, BackgroundColor);
    DrawTextEx(font, text, Vector2{positionX + 25, positionY + 1}, 34, 0, ForegroundColor);
    DrawTexture(GetNavIcon(iconType), positionX + 3, positionY + 7, ForegroundColor);
}

void DrawNavBar()
{
    DrawNavButton(140, 10, 185, "HOME", HOME);
    DrawNavButton(350, 10, 186, "ABOUT", ABOUT);
    DrawNavButton(560, 10, 178, "PROJECTS", PROJECTS);
    DrawNavButton(770, 10, 149, "SKILLS", SKILLS);
    DrawNavButton(980, 10, 191, "CONTACT", CONTACT);
    DrawNavLines();
    DrawNormalText("Copyrighted 2024 by HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30}, 15);
}

void UpdateTransparency()
{
    auto currentTime = std::chrono::steady_clock::now();
    if (currentTime - lastChangedTime > interval)
    {
        if (global_transparency <= 30)
        {
            increasing = true;
        }

        if (global_transparency >= 215)
        {
            increasing = false;
        }

        (increasing) ? global_transparency += 10 : global_transparency += 10;
        lastChangedTime = currentTime;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portfolio");
    InitAudioDevice();

    #ifdef __EMSCRIPTEN__
        emscripten::val::global("window").call<void>("resizeCanvas");
    #endif

    GuiLoadStyleYorha();

    font = LoadFontEx("resources/font.ttf", 72, 0, 0);

    NavIcons[0] = LoadTexture("resources/sprites/home.png");
    NavIcons[1] = LoadTexture("resources/sprites/about.png");
    NavIcons[2] = LoadTexture("resources/sprites/projects.png");
    NavIcons[3] = LoadTexture("resources/sprites/skills.png");
    NavIcons[4] = LoadTexture("resources/sprites/contact.png");
    
    BackgroundMusic = LoadMusicStream("resources/bg.mp3");
    ClickEffect = LoadSound("resources/click.wav");

    PlayMusicStream(BackgroundMusic);

    GenTextureMipmaps(&font.texture);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        IsMouseHovering = false;

        BeginDrawing();
        DrawBackground();
        DrawNavBar();

        DrawHeader("HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 96);
        DrawNormalText("DARE TO MAKE A NEW WAY", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50}, 16);
        DrawFlickingText("Use your arrows keys or mouse button switch between menus", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 250}, 16);

        // DrawTextEx(font, "HTET AUNG HLAING", Vector2(SCREEN_WIDTH/2 + 10, SCREEN_HEIGHT/2 + 10), 96, 0, BACKGROUND_TERTIARY);
        // DrawTextEx(font, "HTET AUNG HLAING", Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 96, 0, FOREGROUND_MAIN);
        EndDrawing();

        UpdateTransparency();
        UpdateMusicStream(BackgroundMusic);
        if(IsMouseHovering && ShouldPlayMouseHover){
            PlaySound(ClickEffect);
            ShouldPlayMouseHover = false;
        }

        if(!IsMouseHovering){
            ShouldPlayMouseHover = true;
        }
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}