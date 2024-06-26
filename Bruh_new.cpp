#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>

#include "Coord.h"
#include "Point.h"
#include "SuperObject.h"
#include "Entity.h"
#include "Item.h"
#include "Helper.cpp"


using namespace std;


Point display[HIGH][WIDTH]{};
list<SuperObject*> objects;
int Moved[4] = { 1, 2, 3, 4 };

void display_init()
{
    for (int i = 0; i < HIGH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            display[i][j].coord(j, i);
        }
    }
}
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
            if (display[i][j].into == nullptr ) { display[i][j].icon = emptyChar; }
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

int main()
{
    srand(time(NULL));
    display_init();
    int counter = 0;
    Entity player(&display[5][5], '@', 20, 15, 1);
    Entity enemy(&display[5][7], '$', 15);
    Entity enemy1(&display[9][9], '%', 15);
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
                player.is_move = true;
                player.direct = 1;
                break;
            case 'a':
                player.is_move = true;
                player.direct = 2;
                break;
            case 's':
                player.is_move = true;
                player.direct = 3;
                break;
            case 'd':
                player.is_move = true;
                player.direct = 4;
                break;
            case ' ':
                break;
            case 27:
                main_flag = false;  // exit
                break;
            }
        // environment motor
        // здесь будет логика всех объектов: 
        // исполнение каких то паттернов движения, появление, применение свойств итд
        // в общем все, что должно произойти за этот такт
            

            enemy.is_move = true;
            enemy.direct = ++counter;
            (counter > 3) ? counter = 0 : counter;
            enemy1.steps(&display[player.getCoord()->y][player.getCoord()->x]);

        // ---------STEP 2: processing---------
        // здесь же примененные действия обрабатываются, в частности - в блоке коллизии

        for (SuperObject* curObj : objects)
        {
            if (curObj->speed != 0)
            {
                tempCoord = curObj->move();
                if (tempCoord.y >= HIGH || tempCoord.y <= 0 || tempCoord.x >= WIDTH || tempCoord.x <= 0)
                {
                    curObj->is_move = false;
                    continue;
                }
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
                curObj->is_move = false;
            }
        }

        // -----------STEP 3: output-----------
        // вывод сцены на экран
        // очистка сцены и наполнение ее
        system("cls");
        displayFill();
        // добавление всех объектов на сцену
        // вывод сцены на экран
        cout << "|  " << player.life << "\t|  " << player.damage << "\t|  " << player.balance << "  |" << endl;
        displayOut();
        player.show_invenoty();
        Sleep(latency);
    }
}
