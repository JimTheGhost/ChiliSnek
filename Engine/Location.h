#pragma once

struct Location
{
    Location(){ x=0; y=0; }
    Location(int xx, int yy){ x=xx; y=yy; }
    bool operator == (const Location& r) const
    {
        return x == r.x && y == r.y;
    }
    bool operator != (const Location& r) const
    {
        return x != r.x || y != r.y;
    }
    const Location& Negate () const
    {
        Location negatedLoc = {-x, -y};
        return negatedLoc;
    }
    void addLocation(const Location delta)
    {
        x += delta.x;
        y += delta.y;
    }
    int x;
    int y;
};
