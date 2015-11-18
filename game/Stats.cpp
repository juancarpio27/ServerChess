//
// Created by César Millán on 11/8/15.
//

#include "Stats.h"

bool Stats::instanceFlag = false;
Stats* Stats::single = nullptr;
Stats* Stats::getInstance()
{
    if(! instanceFlag)
    {
        single = new Stats();
        single->boards_json = json_object();
        json_t *array_json = json_array();
        json_object_set(single->boards_json, "boards", array_json);
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void Stats::printStats(){

}