#pragma once

#include <game-config.h>
#include <raylib.h>
#include "menu.hpp"
#include "text.hpp"

class Projects{

    ListMenu* parentMenu;
    WindowItem* windowItems;

    SimpleWindow simpleWindow;

    void ShowProjects(int index);

    public:
        Projects();
        void DrawProjects();
};
//void DrawProjects();

