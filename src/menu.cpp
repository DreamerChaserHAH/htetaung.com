#include <menu.hpp>
#include <iostream>

ListMenu::ListMenu(int numberOfMenus, MenuItem* menuItems): numberOfMenus(numberOfMenus), menuItems(menuItems){
    menuButtons = new Button[numberOfMenus];
    for(int i = 0; i < numberOfMenus; i++){
        menuButtons[i] = Button(menuItems[i].itemName.c_str(), 
                                i,
                                [&](int index){
                                this->currentSelection = index;
                                },menuItems[0].func);
    }
}

void ListMenu::DrawMenu(int X){

    int itemheight = numberOfMenus * (BUTTON_HEIGHT + 10);

    DrawLine(X, SCREEN_HEIGHT/2 - itemheight/2, X, SCREEN_HEIGHT/2 - itemheight/2, FOREGROUND_MAIN);
    DrawLine(X + 1, SCREEN_HEIGHT/2 - itemheight/2, X + 1, SCREEN_HEIGHT/2 - itemheight/2 + itemheight, FOREGROUND_MAIN);
    DrawLine(X + 2, SCREEN_HEIGHT/2 - itemheight/2, X + 2, SCREEN_HEIGHT/2 - itemheight/2 + itemheight, FOREGROUND_MAIN);

    float middlePoint = numberOfMenus/2;
    DrawRectangle(X + 125.0f - 190/2, SCREEN_HEIGHT/2 - static_cast<float>(BUTTON_HEIGHT + 5) * (numberOfMenus - middlePoint), 220, itemheight, BACKGROUND_FOURTH);
    for(int i = 0; i < numberOfMenus; i++){
        int BUTTON_Y = SCREEN_HEIGHT/2 - static_cast<float>(BUTTON_HEIGHT + 5) * (i - middlePoint);
        menuButtons[i].DrawButton(Vector2{X + 125.0f, SCREEN_HEIGHT/2 - static_cast<float>(BUTTON_HEIGHT + 5) * (i - middlePoint)}, i == currentSelection);
        DrawLine(X + 125.0f - 190/2, BUTTON_Y - 17.5f, X + 125.0f + 190 - 190/2, BUTTON_Y - 17.5f, FOREGROUND_MAIN);
        DrawLine(X + 125.0f - 190/2, BUTTON_Y + 17.5f, X + 125.0f + 190 - 190/2, BUTTON_Y + 17.5f, FOREGROUND_MAIN);
        menuButtons[i].Update();
    }
    DrawLine(X + 125.0f + 190/2 + 10, SCREEN_HEIGHT/2 - 100, X + 125.0f + 190/2 + 10, SCREEN_HEIGHT/2 + 100, FOREGROUND_MAIN);
}

void ListMenu::UpdateMenu(){
    if(isActive){
        if(IsKeyPressed(KEY_UP)){
            currentSelection++;
            std::cout << currentSelection << std::endl;
        }
        if(IsKeyPressed(KEY_DOWN)){
            std::cout << currentSelection << std::endl;
            if(!(currentSelection <= 0)){
                currentSelection--;
            }
        }
    }
}

SimpleWindow::SimpleWindow(WindowItem item, Vector2 position, Vector2 size): item(item), position(position), size(size){

}

void SimpleWindow::DrawHeaderBar(){
    DrawRectangle(position.x - size.x / 2, position.y - size.y/2, size.x, headerBarHeight, FOREGROUND_MAIN);
}

void SimpleWindow::DrawWindowBackground(){
    DrawRectangle(position.x - size.x / 2, position.y - size.y/2 + headerBarHeight, size.x, size.y - headerBarHeight, BACKGROUND_FOURTH);
    DrawRectangleLines(position.x - size.x / 2, position.y - size.y/2 + headerBarHeight, size.x, size.y - headerBarHeight, FOREGROUND_MAIN);
}

void SimpleWindow::DrawContent(){
    DrawTexturePro(item.coverImage, Rectangle{0, 0, item.coverImage.width + 0.0f, item.coverImage.height + 0.0f}, 
                                    Rectangle{
                                        position.x - size.x / 2 + 5, 
                                        position.y + headerBarHeight + 10 - size.y / 2, 
                                        static_cast<float>(size.x - 10), 
                                        static_cast<float>(size.x * item.coverImage.height/item.coverImage.width)}, 
                                        Vector2{}, 
                                        0, 
                                        WHITE
                                    );
    
    DrawHeader(item.title.c_str(), Vector2{position.x + 5, position.y + 190}, 36);
    DrawNormalText(item.description.c_str(), Vector2{position.x, position.y + 220}, 16, true);
    //DrawTexture(item.coverImage, position.x - size.x / 2, position.y - size.y/2 + headerBarHeight, WHITE);
}

void SimpleWindow::DrawSimpleWindow(){
    if(isActive){
        DrawHeaderBar();
        DrawWindowBackground();
        DrawContent();
    }
}