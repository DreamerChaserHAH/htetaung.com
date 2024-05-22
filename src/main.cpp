#include <chrono>
#include <iostream>

#include <raygui.h>
#include <raylib.h>

#include <game-config.h>
#include <projects.hpp>
#include <text.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;
#endif

using std::cout, std::endl;

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
Sound clickEffect;

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
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                currentScreen = iconType;
            }
    }

    if(iconType == currentScreen){
        ForegroundColor = BACKGROUND_TERTIARY;
        BackgroundColor = FOREGROUND_MAIN;
        DrawRectangle(positionX, positionY, 190, 50, BackgroundColor);
    }

    DrawRectangle(positionX, positionY, 190, BUTTON_HEIGHT, BackgroundColor);
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
    DrawNormalText("Copyrighted 2024 by HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30}, 15, true);
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

void DrawHomeScreen(){
    DrawFlickingText("I am looking to fill an backend internship role in 2025 June", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250}, 20);
    DrawNormalText("ASPIRING ENTREPRENEUR/DEVELOPER", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50}, 18, true);
    DrawHeader("HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 96);
    DrawNormalText("DARE TO MAKE A NEW WAY", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50}, 18, true);
    DrawFlickingText("Use your arrows keys or mouse button switch between menus", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 250}, 16);
}

void DrawAboutScreen(){
    DrawHeader("HTET AUNG HLAING", Vector2{335, 130}, 64);
    DrawNormalText("Age : 21; MBTI : ENTP; TimeZone: GMT+8;", Vector2{335, 155}, 16, true);

    DrawNormalText("My mission is to boldly push boundaries and embrace uncertainty,", Vector2{140, 180}, 20, false);
    DrawNormalText("daring to take risks in pursuit of creativity, knowledge and growth. I thrive on", Vector2{140, 180 + 18}, 20, false);
    DrawNormalText("challenges and embrace failure as an opportunity to learn and evolve. I aim to", Vector2{140, 180 + 18 * 2}, 20, false);
    DrawNormalText("inspire others, disrupt existing norms and make impact through my effort.", Vector2{140, 180 + 18 * 3}, 20, false);

    DrawNormalText("I have been passionate about programming since I was 12. Starting ", Vector2{140, 180 + 18 * 5}, 20, false);
    DrawNormalText("out together with my cousin in a local technology class, I fell in love with the", Vector2{140, 180 + 18 * 6}, 20, false);
    DrawNormalText("aspect of creating whatever we wish digitally through the keyboard and mouse.", Vector2{140, 180 + 18 * 7}, 20, false);

    DrawNormalText("And then, I came across Unity Game Engine, which I proceeded to spend", Vector2{140, 180 + 18 * 9}, 20, false);
    DrawNormalText("more than 5-6 years creating prototypes after prototypes just for fun without any", Vector2{140, 180 + 18 * 10}, 20, false);
    DrawNormalText("external motivation. I realized I found my ikigai.", Vector2{140, 180 + 18 * 11}, 20, false);

    DrawNormalText("This was further enhanced by the fact that I was invited to collaborate", Vector2{140, 180 + 18 * 13}, 20, false);
    DrawNormalText("within an organization to develop games that made a hit on the market", Vector2{140, 180 + 18 * 14}, 20, false);
    DrawNormalText("Using that previous experience, I was able to hop onto", Vector2{140, 180 + 18 * 15}, 20, false);
    DrawNormalText("freelance projects relatively easier", Vector2{140, 180 + 18 * 16}, 20, false);

    DrawNormalText("Right now, I am an active student/freelancer hoping to expand my knowledge", Vector2{140, 180 + 18 * 18}, 20, false);
    DrawNormalText("further while specializing in AI, C++ and Rapid Application Development.", Vector2{140, 180 + 18 * 19}, 20, false);

    DrawNormalText("Looking forward to collaborate with ya <3", Vector2{140, 180 + 18 * 21}, 20, false);

    DrawHeader("EXPERIENCES", Vector2{800, 134}, 48);
    DrawNormalText("Research Assistant @ Centre of Research and Development of IOT (APU) - Present", Vector2{703, 180}, 20, false);
    DrawNormalText("Research Head @ Competitive Programming Club (APU) - Present", Vector2{703, 180 + 18}, 20, false);
    DrawNormalText("Freelance Software Developer @ Gnosis Labs - 2023", Vector2{703, 180 + 18 * 2}, 20, false);
    DrawNormalText("Project Manager/ Game Developer @ UNDISCLOSED - 2022", Vector2{703, 180 + 18 * 3}, 20, false);

    DrawHeader("TECHNOLOGIES AND TOOLS", Vector2{910, 180 + 18 * 6}, 48);
    DrawNormalText("- Docker", Vector2{703, 180 + 18 * 8}, 20, false);
    DrawNormalText("- Emscripten", Vector2{703, 180 + 18 * 9}, 20, false);
    DrawNormalText("- C++", Vector2{703, 180 + 18 * 10}, 20, false);
    DrawNormalText("- C#", Vector2{703, 180 + 18 * 11}, 20, false);
    DrawNormalText("- Firebase", Vector2{703, 180 + 18 * 12}, 20, false);
    DrawNormalText("- Supabase", Vector2{703, 180 + 18 * 13}, 20, false);
    DrawNormalText("- AWS", Vector2{703, 180 + 18 * 14}, 20, false);
    DrawNormalText("- Unity", Vector2{703, 180 + 18 * 15}, 20, false);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portfolio");
    InitAudioDevice();

    #ifdef __EMSCRIPTEN__
        emscripten::val::global("window").call<void>("resizeCanvas");
    #endif

    font = LoadFontEx("resources/font.ttf", 72, 0, 0);

    NavIcons[0] = LoadTexture("resources/sprites/home.png");
    NavIcons[1] = LoadTexture("resources/sprites/about.png");
    NavIcons[2] = LoadTexture("resources/sprites/projects.png");
    NavIcons[3] = LoadTexture("resources/sprites/skills.png");
    NavIcons[4] = LoadTexture("resources/sprites/contact.png");
    
    BackgroundMusic = LoadMusicStream("resources/bg.mp3");
    clickEffect = LoadSound("resources/click.wav");

    PlayMusicStream(BackgroundMusic);
    GenTextureMipmaps(&font.texture);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    Projects projects = Projects();
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };   // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    int camera_mode = CAMERA_ORBITAL;

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        IsMouseHovering = false;
        UpdateCamera(&camera, camera_mode);

        BeginDrawing();

        DrawBackground();
        
        BeginMode3D(camera);
        //DrawGrid(15, 2.0f);
        DrawCubeWires(Vector3{0, 0, 0}, 2, 2, 2, BLACK);
        EndMode3D();
        DrawNavBar();

        switch(currentScreen){
            case HOME:
                DrawHomeScreen();
                break;
            case ABOUT:
                DrawAboutScreen();
                break;
            case PROJECTS:
                projects.DrawProjects();
                break;
            default:
                DrawHomeScreen();
                break;
        }

        // DrawTextEx(font, "HTET AUNG HLAING", Vector2(SCREEN_WIDTH/2 + 10, SCREEN_HEIGHT/2 + 10), 96, 0, BACKGROUND_TERTIARY);
        // DrawTextEx(font, "HTET AUNG HLAING", Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 96, 0, FOREGROUND_MAIN);
        EndDrawing();

        UpdateTransparency();
        UpdateMusicStream(BackgroundMusic);
        if(IsMouseHovering && ShouldPlayMouseHover){
            PlaySound(clickEffect);
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