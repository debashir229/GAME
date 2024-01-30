#include <iostream>
#include <windows.h>
#include <list>
#include <conio.h>
using namespace std;
char emptyChar = '.';

class SuperObject;
class Coord
{
public:
    int x = 0;
    int y = 0;
    Coord(int xP, int yP) :
        x{ xP }, y{ yP } {};
    Coord& operator()(int xP, int yP)
    {
        x = xP; y = yP;
        return *this;
    };
};
class Point
{
public:
    char icon = emptyChar;
    Coord coord;
    SuperObject* into;
    Point() : icon{ emptyChar }, coord(0, 0), into{ nullptr } {};
    Point(Coord coordP) : coord{ coordP } {};
    Point(Coord coordP, SuperObject* intoP, char iconP = emptyChar) :
        icon{ iconP }, coord(coordP), into{ intoP } {};

    Point* operator()(char iconP)
    {
        icon = iconP;
        return this;
    }

    void clear(int xP = 0, int yP = 0)
    {
        coord(0, 0);
        icon = emptyChar;
        into = nullptr;

    }
};
ostream& operator<<(ostream& out, Point& obj)
{
    return out << obj.icon;
}

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

//----- env var -----
const int HIGH = 10;
const int WIDTH = 10;

int fps = 4;
int latency = 1000 / fps;

Point display[HIGH][WIDTH]{};
list<SuperObject*> objects;

char keyboardPress;
bool main_flag = true;
//===== env var =====

void displayClearField()
{
    for (int i = 0; i < HIGH; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            display[i][j].clear(j, i);
        };
    }
}
void displayFill()
{
    for (int i = 0; i < HIGH; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (!display[i][j].into) display[i][j].icon = emptyChar;
            else { display[i][j].icon = display[i][j].into->icon; }
        };
    }
}
void displayOut()
{
    for (int i = 0; i < HIGH; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cout << display[i][j];
        };
        cout << "\n";
    }
}


class Entity : public SuperObject
{
public:
    int life = 1;

    Entity() : SuperObject() {}
    Entity(Point* placeP, char iconP, int lifeP, int speedP = 0, int directP = 0) :
        SuperObject(placeP, speedP, directP, iconP), life{ lifeP } {}
    virtual int collision_hanlder(SuperObject* obj)
    {
        if (typeid(obj) == typeid(Entity)) //EXAMPLE
        {
            obj = dynamic_cast<Entity*>(obj);
            life = 0;
        }
        return 1;
    }
};

class Item : public SuperObject
{
public:
    int temp = 2;

    Item() : SuperObject() {}
    Item(Point* placeP, char iconP, int tempP, int speedP = 0, int directP = 0) :
        SuperObject(placeP, speedP, directP, iconP), temp{ tempP } {}

    virtual int collision_hanlder(SuperObject* obj)
    {
        //code here
        return 1;
    }
};

int main()
{
    Entity player;
    player.link(&display[5][5]);
    player.icon = '@';
    player.life = 10;
    Entity enemy(&display[5][7], '$', 15);
    Item sword(&display[3][3], '!', 2);

    //добавление объектов в список
    objects.push_back(&player);
    objects.push_back(&enemy);
    objects.push_back(&sword);

    Coord tempCoord(0, 0);

    while (main_flag)
    {
        // -----------STEP 1: input-----------
        // keyboard reciver
        keyboardPress = _getch();
        switch (keyboardPress)
        {
        case 'w':
            player.getCoord().y -= 1;
            break;
        case 'd':
            player.getCoord().x += 1;
            break;
        case 's':
            player.getCoord().y += 1;
            break;
        case 'a':
            player.getCoord().x -= 1;
            break;
        case ' ':
            break;
        case 27:
            main_flag = false;  //exit
            break;
        }

        // environment motor
        // здесь будет логика всех объектов: 
        // исполнение каких то паттернов движения, появление, применение свойств и т.д.
        // в общем все, что должно произойти за этот такт



        // ---------STEP 2: processing---------
        // здесь же примененные действия обрабатываются, в частности - в блоке коллизии

        for (SuperObject* curObj : objects)
        {
            if (curObj->speed != 0)
            {
                tempCoord = curObj->move();
                //проверка на то, есть ли что-то в этой точке (into=nulptr - false - пустота)
                if (display[tempCoord.y][tempCoord.x].into)
                {
                    display[tempCoord.y][tempCoord.x].into->collision_hanlder(curObj);
                    curObj->collision_hanlder(display[tempCoord.y][tempCoord.x].into);
                }
                else
                {
                    curObj->link(&display[tempCoord.y][tempCoord.x]);
                }
            }
        }

        // -----------STEP 3: output-----------
        // вывод сцены на экран
        // очистка сцены и наполнение ее
        system("cls");
        displayFill();
        // добавление всех объектов на сцену
        // вывод сцены на экран
        displayOut();
        cout << keyboardPress << endl;
        Sleep(latency);
    }
}
