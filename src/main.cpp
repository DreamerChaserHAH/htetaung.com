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

    EM_JS(int, canvas_get_width, (), {
        return window.screen.width * window.devicePixelRatio;
    });

    EM_JS(int, canvas_get_height, (), {
        return window.screen.height * window.devicePixelRatio;
    });

#endif

using std::cout, std::endl;

enum Screen: uint8_t{
    HOME,
    ABOUT,
    PROJECTS,
    SKILLS,
    CONTACT
};

float SCREEN_WIDTH = INITIAL_SCREEN_WIDTH;
float SCREEN_HEIGHT = INITIAL_SCREEN_HEIGHT;
float TITLE_FONT_SIZE = INITIAL_MAIN_TITLE_FONT_SIZE;
float SUBHEADER_FONT_SIZE = INITIAL_SUBHEADER_FONT_SIZE;
float HEADER_1_FONT_SIZE = INITIAL_HEADER_1_FONT_SIZE;
float HEADER_2_FONT_SIZE = INITIAL_HEADER_2_FONT_SIZE;
float HEADER_3_FONT_SIZE = INITIAL_HEADER_3_FONT_SIZE;
float TEXT_FONT_SIZE = INITIAL_TEXT_FONT_SIZE;
float HORIZONTAL_CLAMP_DIFFERENCE = INITIAL_HORIZONTAL_CLAMP_DIFFERENCE;
float HORIZONTAL_DRAW_START_DISTANCE = 0;
float BUTTON_WIDTH = INITIAL_BUTTON_WIDTH;
float BUTTON_HEIGHT = INITIAL_BUTTON_HEIGHT;

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

float BasedOnScreenHeight(float Original){
    return SCREEN_HEIGHT * Original/INITIAL_SCREEN_HEIGHT;
}

float BasedOnScreenWidth(float Original){
    return SCREEN_WIDTH * Original/INITIAL_SCREEN_WIDTH;
}

float BasedOnScreenHeightCapped(float Original, float min, float max){
    return std::clamp(BasedOnScreenHeight(Original), min, max);
}

float BasedOnScreenWidthCapped(float Original, float min, float max){
    return std::clamp(BasedOnScreenWidth(Original), min, max);
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
        DrawRectangle(positionX, positionY, BUTTON_WIDTH, 50, BackgroundColor);
    }

    DrawRectangle(positionX, positionY, BUTTON_WIDTH, 35, BackgroundColor);
    DrawTextEx(font, text, Vector2{positionX + 25, positionY + 1}, 34, 0, ForegroundColor);
    DrawTexture(GetNavIcon(iconType), positionX + 3, positionY + 7, ForegroundColor);
}

void DrawNavBar()
{
    DrawNavButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2 - HORIZONTAL_CLAMP_DIFFERENCE, 10, 185, "HOME", HOME);
    DrawNavButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2 - HORIZONTAL_CLAMP_DIFFERENCE/2, 10, 186, "ABOUT", ABOUT);
    DrawNavButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, 10, 178, "PROJECTS", PROJECTS);
    DrawNavButton(SCREEN_WIDTH/2 + BUTTON_WIDTH/2 + 10, 10, 149, "SKILLS", SKILLS);
    DrawNavButton(SCREEN_WIDTH/2 + BUTTON_WIDTH/2 + HORIZONTAL_CLAMP_DIFFERENCE/2 + 10, 10, 191, "CONTACT", CONTACT);
    DrawNavLines();
    DrawNormalText("Copyrighted 2024 by HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40}, 15, true);
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
    DrawFlickingText("I am looking to fill an backend internship role in 2025 June", Vector2{SCREEN_WIDTH / 2, 100}, INITIAL_TEXT_FONT_SIZE);
    DrawNormalText("ASPIRING ENTREPRENEUR/DEVELOPER", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - BasedOnScreenHeight(50)}, SUBHEADER_FONT_SIZE, true);
    DrawHeader("HTET AUNG HLAING", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, TITLE_FONT_SIZE);
    DrawNormalText("DARE TO MAKE A NEW WAY", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + BasedOnScreenHeight(50)}, SUBHEADER_FONT_SIZE, true);
    DrawFlickingText("Use your arrows keys or mouse button switch between menus", Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, INITIAL_TEXT_FONT_SIZE);
}

void DrawAboutScreen(){
    DrawHeader("HTET AUNG HLAING", Vector2{HORIZONTAL_DRAW_START_DISTANCE, 75}, HEADER_1_FONT_SIZE, false);
    DrawNormalText("Age : 21; MBTI : ENTP; TimeZone: GMT+8;", Vector2{HORIZONTAL_DRAW_START_DISTANCE, 75 + BasedOnScreenHeight(50)}, SUBHEADER_FONT_SIZE, false);

    DrawNormalText("My mission is to boldly push boundaries and embrace uncertainty,\ndaring to take risks in pursuit of creativity, knowledge and growth. I thrive on\nchallenges and embrace failure as an opportunity to learn and evolve. I aim to\ninspire others, disrupt existing norms and make impact through my effort.\n\nI have been passionate about programming since I was 12. Starting\nout together with my cousin in a local technology class, I fell in love with the\naspect of creating whatever we wish digitally through the keyboard and mouse.\nAnd then, I came across Unity Game Engine, which I proceeded to spend\nmore than 5-6 years creating prototypes after prototypes just for fun without any\nexternal motivation. I realized I found my ikigai.\nThis was further enhanced by the fact that I was invited to collaborate\nwithin an organization to develop games that made a hit on the market\nUsing that previous experience, I was able to hop onto\nfreelance projects relatively easier\n\nRight now, I am an active student/freelancer hoping to expand my knowledge\nfurther while specializing in AI, C++ and Rapid Application Development.\nLooking forward to collaborate with ya <3", Vector2{HORIZONTAL_DRAW_START_DISTANCE, 75 + BasedOnScreenHeight(80)}, TEXT_FONT_SIZE, false);

    DrawHeader("EXPERIENCES", Vector2{SCREEN_WIDTH/2, 75}, HEADER_2_FONT_SIZE, false);
    DrawNormalText("Research Assistant @ Centre of Research and Development of IOT (APU) - Present\nResearch Head @ Competitive Programming Club (APU) - Present\nFreelance Software Developer @ Gnosis Labs - 2023\nProject Manager/ Game Developer @ UNDISCLOSED - 2022", Vector2{SCREEN_WIDTH/2, 75 + BasedOnScreenHeight(40)}, TEXT_FONT_SIZE, false);
    
    DrawHeader("TECHNOLOGIES AND TOOLS", Vector2{SCREEN_WIDTH/2, 75 + BasedOnScreenHeight(140)}, HEADER_2_FONT_SIZE, false);
    DrawNormalText("- Docker\n- Emscripten\n- C++\n- C#\n- Firebase\n- Supabase\n- AWS\n- Unity", Vector2{SCREEN_WIDTH/2, 75 + BasedOnScreenHeight(180)}, TEXT_FONT_SIZE, false);
}

void Update(){
    SCREEN_WIDTH = GetScreenWidth();
    SCREEN_HEIGHT = GetScreenHeight();
    TITLE_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_MAIN_TITLE_FONT_SIZE, 0, INITIAL_MAIN_TITLE_FONT_SIZE);
    SUBHEADER_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_SUBHEADER_FONT_SIZE, 0, INITIAL_SUBHEADER_FONT_SIZE);
    HEADER_1_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_HEADER_1_FONT_SIZE, 0, INITIAL_HEADER_1_FONT_SIZE);
    HEADER_2_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_HEADER_2_FONT_SIZE, 0, INITIAL_HEADER_2_FONT_SIZE);
    HEADER_3_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_HEADER_3_FONT_SIZE, 0, INITIAL_HEADER_3_FONT_SIZE);
    TEXT_FONT_SIZE = BasedOnScreenHeightCapped(INITIAL_TEXT_FONT_SIZE, 0, INITIAL_TEXT_FONT_SIZE);
    HORIZONTAL_CLAMP_DIFFERENCE = BasedOnScreenWidthCapped(INITIAL_HORIZONTAL_CLAMP_DIFFERENCE, 0, INITIAL_HORIZONTAL_CLAMP_DIFFERENCE);
    BUTTON_WIDTH = BasedOnScreenWidthCapped(INITIAL_BUTTON_WIDTH, 0, INITIAL_BUTTON_WIDTH);
    BUTTON_HEIGHT = BasedOnScreenHeightCapped(INITIAL_BUTTON_HEIGHT, 0, INITIAL_BUTTON_HEIGHT);
    HORIZONTAL_DRAW_START_DISTANCE = SCREEN_WIDTH/2 - BUTTON_WIDTH/2 - HORIZONTAL_CLAMP_DIFFERENCE;
}

int main()
{   
    #ifdef __EMSCRIPTEN__
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    float resolutionX = static_cast<float>(canvas_get_width());
    float resolutionY = static_cast<float>(canvas_get_height());
    
    float X = resolutionX > resolutionY? resolutionX : resolutionY;
    float Y = resolutionX > resolutionY? resolutionY : resolutionX;
    
    float factor = std::clamp(X/Y, static_cast<float>(INITIAL_SCREEN_WIDTH)/INITIAL_SCREEN_HEIGHT, 100.0f);

    SCREEN_HEIGHT = INITIAL_SCREEN_HEIGHT;
    SCREEN_WIDTH = INITIAL_SCREEN_HEIGHT * factor;
    cout << SCREEN_WIDTH << " " << SCREEN_HEIGHT << " \n";
    #endif

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
        DrawCubeWires(Vector3{0, 0, 0}, 2, 2, 2, Color{0, 0, 0, 100});
        EndMode3D();

        if(SCREEN_HEIGHT > SCREEN_WIDTH){
            DrawNormalText("Please turn your device to landscape\nfor better experience", Vector2{SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, HEADER_1_FONT_SIZE, true);
        }else{
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
        Update();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}