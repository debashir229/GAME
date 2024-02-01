#pragma once

#include "Point.h"
#include "SuperObject.h"
#include <vector>
using namespace std;

class Entity : public SuperObject
{
public:
    int life = 1;
    //vector <SuperObject> inventory{ };
    Entity() : SuperObject() {}
    Entity(Point* placeP, char iconP, int lifeP) :
        SuperObject(placeP, iconP), life{ lifeP } {}
    virtual int collision_hanlder(SuperObject* obj)
    {
        if (typeid(obj) == typeid(Entity)) //EXAMPLE
        {
            obj = dynamic_cast<Entity*>(obj);
            life = 0;
        }
        //else if (typeid(obj) == typeid(Item))
        //{
        //    inventory.push_back(&Item);
        //    
        //}
        return 1;
    }
