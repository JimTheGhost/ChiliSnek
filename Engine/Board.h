#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include <cmath>

class Board
{
public:
    Board(Graphics& gfx);
    void DrawCell( const Location& loc, Color c);
    int GetGridHeight() const {return height;}
    int GetGridWidth() const {return width;}
    bool isOnBoard(const Location& loc) const;
    void DrawBorder();

private:
    Graphics& gfx;

    static constexpr int dim = 20;
    static constexpr int arX = Graphics::ScreenWidth/20;
    static constexpr int arY = Graphics::ScreenHeight/20;
    
    static constexpr int width = 40;
    static constexpr int height = 30;
    static constexpr int padding = 1;

    static constexpr int borderWidth = 4;
    static constexpr int borderPadding = 2;
    static constexpr Color borderColor = Colors::Green;
    static constexpr int borderInsetLevel = 1;
    static constexpr int x = ((arX - borderWidth+borderPadding)) * borderInsetLevel;
    static constexpr int y = ((arY - borderWidth+borderPadding)) * borderInsetLevel;

    static constexpr int cWidth = (Graphics::ScreenWidth - ((borderInsetLevel*arX)*2))/width;
    static constexpr int cHeight = (Graphics::ScreenHeight - ((borderInsetLevel*arY)*2))/height;

};
