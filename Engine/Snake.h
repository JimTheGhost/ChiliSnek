#pragma once
#include "Board.h"
class Snake
{
private:
    class Segment
    {
    public:
        Segment()
            : loc(0,0),
              c(Snake::headColor)
        {
        }

        void Follow( const Segment& next);
        void InitHead ( const Location& inLoc);
        void InitBody( Color inCol);
        void MoveBy(const Location& deltaLoc);
        void Draw( Board& brd ) const;
        const Location& GetLocation() const;
    private:
        Location loc;
        Color c;
    };
public:
    Snake(const Location& inLoc );
    void Respawn(const Location& inLoc);
    void MoveBy(const Location& deltaLoc);
    Location GetNextHeadLocation(const Location& deltaLoc) const;
    void Grow();
    void Draw( Board& brd ) const;
    bool IsInTileExceptEnd( const Location& target) const;
    bool IsInTile( const Location& target) const;
    int GetLength()
    {
        return currentSegments;
    }
    const Location& GetTravelDir()
    {
        return travelDir;
    }
private:
    static constexpr Color headColor = {255, 166, 158};
    static constexpr Color bodyColor[3] = { {250, 243, 221}, {184, 242, 230}, {174, 217, 224}} ;
    static constexpr int maxSegments = 100;
    Segment segments[maxSegments];
    int currentSegments = 1;
    Location travelDir;
    
};
