#pragma once

#include "Point.h"
#include "SuperObject.h"
using namespace std;

class Item : public SuperObject
{
public:
    int damage{ 50 };
    Item() : SuperObject() {}
    Item(Point* placeP, char iconP, int damageP = 50) :
        SuperObject(placeP, iconP), damage{ damageP } {}
    virtual int collision_hanlder(SuperObject* obj)
    {
        //your code here
        return 1;
    }
};
