#ifndef GAMEINFO_H
#define GAMEINFO_H
#include<vector>
#include"Portal.h"
#include"Box.h"
using std::vector;
class Portal;
class Destination;
class GameInfo
{
public:
    int x, y;

    int x_person, y_person;

    int n_boxes;
    vector<std::pair<int, int> > boxes;

    int n_pair_portal;
    vector<std::pair<std::pair<int, int> , std::pair<int, int > > > portals;

    vector<vector<int>> down_layer;

    vector<std::pair<int, int> > goals;
    int n_goal;
    GameInfo(int _x,int _y,int _x_person,int _y_person,int _n_boxes,vector<std::pair<int, int> > _boxes,int _n_pair_portal,vector<std::pair<std::pair<int, int>
             , std::pair<int, int > > > _portals,vector<vector<int>> _down_layer,vector<std::pair<int, int> > _goals,int _n_goal):
       x(_x),y(_y),x_person(_x_person),y_person(_y_person),n_boxes(_n_boxes),boxes(_boxes),n_pair_portal(_n_pair_portal),portals(_portals),down_layer(_down_layer)
     ,goals(_goals),n_goal(_n_goal){}
};
#endif // !GAMEINFO_H


