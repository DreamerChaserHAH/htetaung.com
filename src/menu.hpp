#pragma once

#include <game-config.h>
#include <button.hpp>
#include <text.hpp>

#include <raylib.h>

#include <string>
#include <functional>

using std::string;


struct MenuItem{
    int index;
    string itemName;
    std::function<void(int)> func;
};

struct WindowItem{
    string title;
    string description;
    Texture coverImage;
};

class ListMenu{

    int numberOfMenus;
    Button* menuButtons;
    int currentSelection = 0;
    bool isActive = true;

    public:
        MenuItem* menuItems;

        ListMenu(int numberOfMenus, MenuItem* menuItems);
        void DrawMenu(int X);
        void UpdateMenu();
};

class SimpleWindow{

    Vector2 position;
    Vector2 size;

    int headerBarHeight = 20;

    void DrawHeaderBar();
    void DrawWindowBackground();
    void DrawContent();

    public:
        WindowItem item;
        bool isActive = false;

        SimpleWindow(){

        }
        SimpleWindow(WindowItem item, Vector2 position, Vector2 size);
        void DrawSimpleWindow();
};