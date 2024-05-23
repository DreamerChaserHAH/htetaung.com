/// Author : Htet Aung Hlaing
/// Created Date: 22nd May, 2024
/// <summary>
/// Creating for myself
/// </summary>

#include "projects.hpp"
#include <iostream>

void Projects::ShowProjects(int index){
    simpleWindow.item = windowItems[index];
}

Projects::Projects(){
    MenuItem* parentMenusLocal = new MenuItem[7];
    parentMenusLocal[0] = MenuItem{0, "Portfolio", [&](int index){
        this->ShowProjects(index);
    }};
    parentMenusLocal[1] = {1, "Multi-Chess", nullptr};
    parentMenusLocal[2] = {2, "Snake", nullptr};
    parentMenusLocal[3] = {3, "Gnosis", nullptr};
    parentMenusLocal[4] = {4, "RPG", nullptr};
    parentMenusLocal[5] = {5, "Tank Crews", nullptr};
    parentMenusLocal[6] = {6, "Fly High", nullptr};

    windowItems = new WindowItem[7];
    windowItems[0] = WindowItem{"Portfolio (2024)", "Personal Portfolio Website for showcasing my skills, experiences and aspirations", LoadTexture("resources/sprites/PortfolioProject.png")};
    windowItems[1] = WindowItem{"Multi-Chess (2024)", "A C++ Multiplayer Chess Game running inside the browser\nthrough WebRTC and WASM technologies", LoadTexture("resources/sprites/MultiChessProject.png")};
    windowItems[2] = WindowItem{"Snake (2024)", "A C++ WASM based retro snake game", LoadTexture("resources/sprites/SnakeProject.png")};
    windowItems[3] = WindowItem{"Gnosis (2023)", "A Rust + Tauri Desktop Application for a freelance client", LoadTexture("resources/sprites/GnosisProject.png")};
    windowItems[4] = WindowItem{"Palknect (2022)", "A RAD request to quickly generate a prototype by an Upwork client", LoadTexture("resources/sprites/RPGProject.png")};
    windowItems[5] = WindowItem{"Tank Crews (2020)", "A Unity Multiplayer Tank Game using Photon SDK with a huge emphasis\non collaboration over voice chat", LoadTexture("resources/sprites/TankCrewsProject.png")};
    windowItems[6] = WindowItem{"Fly High (2019)", "A Unity Multiplayer Jet Airplane Combat Prototype", LoadTexture("resources/sprites/FlyHighProject.png")};

    simpleWindow = SimpleWindow();
    simpleWindow = SimpleWindow(windowItems[0], Vector2{800, SCREEN_HEIGHT/2}, Vector2{700, 500});
    simpleWindow.isActive = true;

    parentMenu = new ListMenu(7, parentMenusLocal);
}

void Projects::DrawProjects(){
    DrawHeader("PROJECTS", Vector2{HORIZONTAL_DRAW_START_DISTANCE, 75}, HEADER_1_FONT_SIZE, false);
    parentMenu->DrawMenu(HORIZONTAL_DRAW_START_DISTANCE);
    parentMenu->UpdateMenu();
    simpleWindow.DrawSimpleWindow(Vector2{SCREEN_WIDTH/2 + HORIZONTAL_CLAMP_DIFFERENCE/2, SCREEN_HEIGHT/2}, Vector2{HORIZONTAL_CLAMP_DIFFERENCE + HORIZONTAL_CLAMP_DIFFERENCE/2, SCREEN_HEIGHT * 0.6f});
}