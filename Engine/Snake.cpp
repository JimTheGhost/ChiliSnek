#include "Snake.h"
#include <assert.h>
#include <d3d9.h>


void Snake::Segment::Follow(const Segment& next)
{
    loc = next.loc;
}

void Snake::Segment::InitHead(const Location& inLoc)
{
    loc = inLoc;
    c = Snake::headColor;
}

void Snake::Segment::InitBody(Color inCol)
{
    c = inCol;
}

void Snake::Segment::MoveBy(const Location& deltaLoc)
{
    assert( abs(deltaLoc.x) + abs(deltaLoc.y) == 1);
    loc.addLocation(deltaLoc);
}

void Snake::Segment::Draw(Board& brd) const
{
    brd.DrawCell( loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
    return loc;
}

Snake::Snake(const Location& inLoc)
{
    segments[0].InitHead(inLoc);
    for (int i = 1; i < maxSegments; i++)
    {
        segments[i].InitBody(bodyColor[i%3]);
    }
}

void Snake::Respawn(const Location& inLoc)
{
    segments[0].InitHead(inLoc);
    currentSegments = 1;
}

void Snake::MoveBy(const Location& deltaLoc)
{
    travelDir = deltaLoc;
    for( int i = currentSegments - 1; i > 0; i--)
    {
        segments[i].Follow( segments[i-1] );
    }
    segments[0].MoveBy(deltaLoc);
}

Location Snake::GetNextHeadLocation(const Location& deltaLoc) const
{
    Location tempLoc = segments[0].GetLocation();
    return {tempLoc.x + deltaLoc.x, tempLoc.y + deltaLoc.y};
}

void Snake::Grow()
{
    if (currentSegments < maxSegments)
    {
        currentSegments++;
    }
}

void Snake::Draw(Board& brd) const
{
    for(int i = 0; i < currentSegments; i++ )
    {
        segments[i].Draw(brd);
    }
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
    for( int i = 0; i < currentSegments-1; i++)
    {
        if(segments[i].GetLocation() == target)
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsInTile(const Location& target) const
{
    for( int i = 0; i < currentSegments; i++)
    {
        if(segments[i].GetLocation() == target)
        {
            return true;
        }
    }
    return false;
}