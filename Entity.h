#pragma once

#include "Point.h"
#include "SuperObject.h"
#include <vector>
using namespace std;

class Entity : public SuperObject
{
public:
    int life = 10;
    int damage{ 0 };
    int balance{ 10 };
    vector <Item*> inventory;
    Entity() : SuperObject() {}
    Entity(Point* placeP, char iconP, int lifeP) :
        SuperObject(placeP, iconP), life{ lifeP } {}
    virtual int collision_hanlder(SuperObject* obj)
{
    if (typeid(obj) == typeid(Entity))
    {
        Entity* temp = dynamic_cast<Entity*>(obj);
        if (temp->inventory.size() == 15)
        {
            life -= temp->inventory[0].
        }
        else if
        {
            life -= temp->damage;
            temp->loot();
        }
    }
    else if (typeid(obj) == typeid(Coin))
    {
        Coin* temp = dynamic_cast<Coin*>(obj);
        balance += temp->money;
    }
    else if (typeid(obj) == typeid(Item))
    {
        Item* temp = dynamic_cast<Item*>(obj);
        obj->link(nullptr);
        inventory.push_back(temp);
    }
    return 1;
}
void show_invenoty()
{
    for (int i = 0; i < inventory.size(); i++)
        cout << inventory[i]->icon << " |   " << inventory[i]->damage << endl;
    if (inventory.empty())
        cout << "Empty! " << endl;
}
void steps(Point* placeP)
{
    this->is_move = true;
    if (abs(this->place->getCoord().y - placeP->place->getCoord().y) < abs(this->place->getCoord().x - placeP->place->getCoord().x))
    {
        if (this->place->getCoord().y - placeP->place->getCoord().y >= 0)
            this->direct = 3;
        else
            this->direct = 1;
    }
    else
    {
        if (this->place->getCoord().x - placeP->place->getCoord().x >= 0)
            this->direct = 4;
        else
            this->direct = 2;
    }
}
