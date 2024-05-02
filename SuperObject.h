#pragma once
#include "Point.h"
class Point;
class SuperObject
{
    Point* place;
public:
    char icon;
    int speed{ 1 }; // квантификатор скорости
    bool is_move{ false }; // движется объект или нет
    int direct{ 0 };

    // direct
    //    1
    // 4  0  2
    //    3

    SuperObject() :
        place{ nullptr }, icon{ emptyChar } {}
    SuperObject(Point* placeP, char iconP = emptyChar, int speedP = 1, bool ismovP = false, int directP = 0) :
        speed{ speedP }, direct{ directP }, is_move{ ismovP }, icon{ iconP } 
    {
        link(placeP);
    }

    virtual Coord* getCoord()
    {
        return &place->coord;
    }
    virtual void link(Point* p)
    {
        if(p->into)
        {   p->into = nullptr;
            p->into = this;
            place = p;
        }
    }
    virtual int collision_hanlder(SuperObject* obj)
    {
        return 0;
    };
    virtual Coord move()
    {
        Coord tcoord( place->coord );
        switch (direct)
        {
        case 1:
            tcoord.y -= speed;
            break;
        case 2:
            tcoord.x += speed;
            break;
        case 3:
            tcoord.y += speed;
            break;
        case 4:
            tcoord.x -= speed;
            break;
        }
        return tcoord;
    }
};
