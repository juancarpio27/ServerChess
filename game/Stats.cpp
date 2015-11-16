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

    long int total = draw + whiteWins + blackWins;

    printf("Draws %f\n",(draw/(float)total)*100);
    printf("Whites %f\n",(whiteWins/(float)total)*100);
    printf("Blacks %f\n",(blackWins/(float)total)*100);


}