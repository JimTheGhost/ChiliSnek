#include "Board.h"

Board::Board(Graphics& gfx)
    :
gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
    assert( loc.x >= 0 );
    assert( loc.x < width );
    assert( loc.y >= 0 );
    assert( loc.y < height );
   // int x =(loc.x * cWidth)+padding;
  //  int y = (loc.y * cHeight)+padding;
   // gfx.DrawRectDim(x, y, cWidth-padding,cHeight-padding,c);
    const int x_off = x + (borderPadding + borderWidth);
    const int y_off = y + (borderPadding + borderWidth);
    //gfx.DrawRectDim((loc.x * dim)+ x_off + padding, (loc.y * dim)+ y_off + padding, dim-(padding * 2),dim-(padding * 2),c);
    gfx.DrawRectDim((loc.x * cWidth)+ x_off + padding, (loc.y * cHeight)+ y_off + padding, cWidth-(padding * 2),cHeight-(padding * 2),c);
}

bool Board::isOnBoard(const Location& loc) const
{
    return loc.x >= 0 && loc.x < width && loc.y >=0 && loc.y < height;
}

void Board::DrawBorder()
{
    const int top = y;
    const int left = x;
    const int bottom = (cHeight*height) + (y + (borderWidth + borderPadding) * 2);
    const int right = (cWidth*width) + (x + (borderWidth + borderPadding) * 2);

    gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
    gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);
    gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);
    gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);
}