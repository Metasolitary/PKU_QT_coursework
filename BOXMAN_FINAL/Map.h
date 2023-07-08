#ifndef MAP_H
#define MAP_H
#include"BasicLand.h"
#include"GameObject.h"
#include"GameInfo.h"
using std::vector;

class BasicLand;
class GameObject;
class GameInfo;
class Destination;
class Map
{
private:
    std::pair<int, int> to[5] = { {-1,0},{0,1},{1,0},{0,-1} };
public:
    // Size of the map
    int x_length, y_length;


    // Two-dimensional scene, where the third dimension's 0th layer is basic land, and the 1st layer is person or box
    BasicLand*** Lower_map;
    GameObject*** Upper_map;
    // Person's location
    int x_person;
    int y_person;

    // Box's destination
    vector<std::pair<int, int> > goals;

    // Total number of goal locations
    int n_goal;

public:
    Map(const GameInfo& info);

    void print_map();

    void reset_map(const GameInfo& info);
    void save_gameinfo(GameInfo& info);


    // Check whether the point is out of the map boundary, return true if out of boundary
    bool check_out(int x, int y);

    // Function for person's movement
    void person_move(int direction);

    // Move the location to the next destination
    void next_position(int& x_next, int& y_next, int x, int y, int direction);

    // Function for moving the box
    int move_box(int x, int y, int direction);

    // Return the pointer reference to the upper layer on the map that has walked n steps from a certain direction
    GameObject*& in_front_of(int x, int y, int n, int direction);

    // Judge if player wins
    bool win_judge();

};


#endif // !MAP_H
