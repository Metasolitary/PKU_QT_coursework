#include "Map.h"
#include<typeinfo>
#include"Box.h"
#include"Floor.h"
#include"Person.h"
#include"Wall.h"
#include<iostream>
#include "Vacuum.h"
#include"Destination.h"
#include"FakeWall.h"
void print_red(char s) {
    printf("\033[1;31m%c\033[0m", s);
}

void print_yellow(char s) {
    printf("\033[1;33m%c\033[0m", s);
}

void print_brown(char s) {
    printf("\033[0;33m%c\033[0m", s);
}

void print_blue(char s) {
    printf("\033[1;34m%c\033[0m", s);
}
void Map::print_map() {
    for (auto i = 0; i != x_length; ++i) {
        for (auto j = 0; j != y_length; ++j)
        {
            //upper layer first
            if
                (dynamic_cast<Box*>(Upper_map[i][j])) {
                print_red('B');
                continue;
            }
            else if
                (dynamic_cast<Person*>(Upper_map[i][j]))
            {
                print_blue('O');
                continue;
            }
            else if
                (dynamic_cast<Destination*>(Lower_map[i][j])) {
                print_red('X');
            }
            else if
                (dynamic_cast<FakeWall*>(Lower_map[i][j])) {
                FakeWall* temp = (FakeWall*)Lower_map[i][j];
                if (temp->found) {
                    printf("#");
                }
                else {
                    print_brown('W');
                }
            }
            else if
                (dynamic_cast<Floor*>(Lower_map[i][j])) {
                printf("#");
                continue;
            }
            else if
                (dynamic_cast<Portal*>(Lower_map[i][j])) {
                print_blue('T');
            }
            else if
                (dynamic_cast<Wall*> (Lower_map[i][j])) {
                print_brown('W');
            }
            else if
                (dynamic_cast<Vacuum*>(Lower_map[i][j])) {
                std::cout << ' ';
            }

        }
        std::cout << std::endl;
    }
}
Map::Map(const GameInfo& info) {
    x_length = info.x;
    y_length = info.y;
    Upper_map = new GameObject * *[x_length + 1];
    Lower_map = new BasicLand * *[x_length + 1];
    for (int i = 0; i < x_length; ++i) {
        Upper_map[i] = new GameObject * [y_length + 1];
        Lower_map[i] = new BasicLand * [y_length + 1];
        for (int j = 0; j < y_length; ++j) {
            Upper_map[i][j] = nullptr;
            Lower_map[i][j] = nullptr;
        }
    }
    //innitialize lower map
    for (int i = 0; i < x_length; ++i)
        for (int j = 0; j < y_length; ++j)
        {
            switch (info.down_layer[i][j]) {
            case 0:
                Lower_map[i][j] = new Floor(i, j);
                break;
            case 1:
                Lower_map[i][j] = new Wall(i, j);
                break;
            case 2:
                Lower_map[i][j] = new Vacuum(i, j);
                break;
            case 3:
                Lower_map[i][j] = new FakeWall(i, j);
                break;
            default:
                Lower_map[i][j] = nullptr;
                break;
            }
        }
    //initialize box
    for (int i = 0; i < info.n_boxes; ++i) {
        Upper_map[info.boxes[i].first][info.boxes[i].second] = new Box(info.boxes[i].first, info.boxes[i].second);
    }
    //initialize person
    Upper_map[info.x_person][info.y_person] = new Person(info.x_person, info.y_person);
    x_person = Upper_map[info.x_person][info.y_person]->x;
    y_person = Upper_map[info.x_person][info.y_person]->y;

    //initialize portal
    for (int i = 0; i < info.n_pair_portal; ++i) {
        Lower_map[info.portals[i].first.first][info.portals[i].first.second]
            = new Portal(info.portals[i].first.first, info.portals[i].first.second);
        Lower_map[info.portals[i].second.first][info.portals[i].second.second]
            = new Portal(info.portals[i].second.first, info.portals[i].second.second);
        Portal* temp1 = (Portal*)Lower_map[info.portals[i].first.first][info.portals[i].first.second];
        Portal* temp2 = (Portal*)Lower_map[info.portals[i].second.first][info.portals[i].second.second];
        temp1->cor_portal = Lower_map[info.portals[i].second.first][info.portals[i].second.second];
        temp2->cor_portal = Lower_map[info.portals[i].first.first][info.portals[i].first.second];
    }

    n_goal = info.n_goal;
    for (int i = 0; i < n_goal; ++i) {
        goals.push_back({ info.goals[i].first, info.goals[i].second });
    }
    for (int i = 0; i < n_goal; ++i) {
        if (Lower_map[goals[i].first][goals[i].second] != nullptr) {
            delete Lower_map[goals[i].first][goals[i].second];
            Lower_map[goals[i].first][goals[i].second] = new Destination(goals[i].first, goals[i].second);
            continue;
        }
        Lower_map[goals[i].first][goals[i].second] = new Destination(goals[i].first, goals[i].second);
    }
}
void Map::reset_map(const GameInfo& info)
{
    for (int i = 0; i < x_length; ++i) {

        for (int j = 0; j < y_length; ++j) {
            if(Upper_map[i][j]!=nullptr)
            {
                delete Upper_map[i][j];
            }
            Upper_map[i][j]=nullptr;
        }
    }
    for (int i = 0; i < info.n_boxes; ++i) {
        Upper_map[info.boxes[i].first][info.boxes[i].second] = new Box(info.boxes[i].first, info.boxes[i].second);
    }
    //initialize person
    Upper_map[info.x_person][info.y_person] = new Person(info.x_person, info.y_person);
    x_person = Upper_map[info.x_person][info.y_person]->x;
    y_person = Upper_map[info.x_person][info.y_person]->y;

    //initialize portal
    for (int i = 0; i < info.n_pair_portal; ++i) {
        Lower_map[info.portals[i].first.first][info.portals[i].first.second]
            = new Portal(info.portals[i].first.first, info.portals[i].first.second);
        Lower_map[info.portals[i].second.first][info.portals[i].second.second]
            = new Portal(info.portals[i].second.first, info.portals[i].second.second);
        Portal* temp1 = (Portal*)Lower_map[info.portals[i].first.first][info.portals[i].first.second];
        Portal* temp2 = (Portal*)Lower_map[info.portals[i].second.first][info.portals[i].second.second];
        temp1->cor_portal = Lower_map[info.portals[i].second.first][info.portals[i].second.second];
        temp2->cor_portal = Lower_map[info.portals[i].first.first][info.portals[i].first.second];
    }
}
void Map::save_gameinfo(GameInfo& info)
{
    vector<std::pair<int,int>> temp;
    for (auto i = 0; i != x_length; ++i) {
        for (auto j = 0; j != y_length; ++j)
        {
            //upper layer first
            if
                (dynamic_cast<Box*>(Upper_map[i][j])) {
                temp.push_back({i,j});
            }
            else if
                (dynamic_cast<Person*>(Upper_map[i][j]))
            {

                info.x_person=i;
                info.y_person=j;
            }
        }
    }
    info.boxes=temp;
}
bool Map::check_out(int x, int y) {
    return (x < 0 || x >= x_length || y < 0 || y >= y_length) ? true : false;
}
void Map::next_position(int& x_next, int& y_next, int x, int y, int direction) {
    switch (direction)
    {
        // 0 up 1 right 2 down 3 left
    case 0:
        x_next = x - 1;
        y_next = y;
        break;
    case 1:
        x_next = x;
        y_next = y + 1;
        break;
    case 2:
        x_next = x + 1;
        y_next = y;
        break;
    case 3:
        x_next = x;
        y_next = y - 1;

    default:
        break;
    }
}
GameObject*& Map::in_front_of(int x, int y, int n, int direction) {
    int x_next, y_next;
    for (int i = 0; i < n; ++i) {
        next_position(x_next, y_next, x, y, direction);
        x = x_next;
        y = y_next;
    }
    return Upper_map[x][y];
}
int Map::move_box(int x, int y, int direction) {//return how many boxes do you move
    //to prevent (x,y) is not box
    if (!(dynamic_cast<Box*>(Upper_map[x][y]))) return 999;
    int x_next; int y_next;
    next_position(x_next, y_next, x, y, direction);
    //box shouldn't get out of the map
    if (check_out(x_next, y_next)) return 999;
    //the lower layer doesn't accpet any upper layer
    if (!Lower_map[x_next][y_next]->acceptable())
        return 999;
    int box_cnt = 1;
    //box can push box
    if (dynamic_cast<Box*>(Upper_map[x_next][y_next])) {
        box_cnt += move_box(x_next, y_next, direction);
    }
    return box_cnt;
}
void Map::person_move(int direction) {
    if (dynamic_cast<Person*> (Upper_map[x_person][y_person]));
    else {
        std::cout << "Person are not here " << std::endl;
    }
    int x_next, y_next;
    next_position(x_next, y_next, x_person, y_person, direction);
    if (check_out(x_next, y_next)) 
        return;
    //Upper layer has nothing
    if (Upper_map[x_next][y_next] == nullptr)
    {
        Person* temp = (Person*)Upper_map[x_person][y_person];
        Lower_map[x_next][y_next]->accept(Upper_map[x_person][y_person], this);
        x_person = temp->x;
        y_person = temp->y;
        return;
    }
    //Upper layer has something(most probably boxes)
    if (dynamic_cast<Box*> (Upper_map[x_next][y_next])) {
        int boxes_ahead = move_box(x_next, y_next, direction);
        if (boxes_ahead > 2) return;
        else {
            Person* temp = (Person*)Upper_map[x_person][y_person];
            for (int i = boxes_ahead + 1; i >= 1; --i)
            {
                Lower_map[x_person + to[direction].first * i]
                    [y_person + to[direction].second * i]
                ->accept(
                    Upper_map[x_person + to[direction].first * (i - 1)]
                    [y_person + to[direction].second * (i - 1)],
                    this);
            }
            
            x_person = temp->x;
            y_person = temp->y;
        }
    }
}
bool Map::win_judge() {
    if (n_goal == 0)
        return false;
    bool temp = true;
    for (int i = 0; i < n_goal; ++i) {
        if (dynamic_cast<Box*>(Upper_map[goals[i].first][goals[i].second]));
        else
            temp = false;
    }
    return temp;
}
