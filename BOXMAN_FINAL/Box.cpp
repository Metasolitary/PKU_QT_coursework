#include "Box.h"
#include"Floor.h"
#include"Wall.h"

//bool Box::check_collision(GameObject obj) {
//    if (dynamic_cast<Floor*>(&obj)) {
//        return false;
//    }
//    else if (dynamic_cast<Wall*>(&obj)) {
//        return true;
//    }
//}
int Box::get_num() { return num; }
void  Box::set_num(int n) { num = n; }