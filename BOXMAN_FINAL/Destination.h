#ifndef DESTINATION_H
#define DESTINATION_H
#include"Floor.h"


class Destination :
    public Floor
{
public:
    Destination(int x, int y) :Floor(x, y) {};
};

#endif // !DESTINATION_H

