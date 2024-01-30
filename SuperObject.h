#pragma once
#include "Point.h"
class SuperObject
{
    Point* place;
public:
    char icon;
    int speed;
    int direct;
    // direct
    //    1
    // 2     3
    //    4
    SuperObject() : place{ nullptr }, speed{ 0 }, direct{ 0 }, icon{ emptyChar } {}
    SuperObject(Point* placeP, int speedP = 0, int directP = 0, char iconP = emptyChar) : speed{ speedP }, direct{ directP }, icon{ iconP } { link(placeP); }

    virtual Coord& getCoord()
    {
        return place->coord;
    }
    virtual void link(Point* p)
    {
        p->into = nullptr;
        place = p;
        p->into = this;
    }
    virtual int collision_hanlder(SuperObject* obj)
    {
        return 0;
    };
    virtual Coord move()
    {
        Coord tcoord(place->coord);
        switch (direct)
        {
        case 1:
            tcoord.y -= speed;
            break;
        case 2:
            tcoord.x -= speed;
            break;
        case 3:
            tcoord.x += speed;
            break;
        case 4:
            tcoord.y += speed;
            break;
        }
        return tcoord;
    }
};