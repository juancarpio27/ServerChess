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