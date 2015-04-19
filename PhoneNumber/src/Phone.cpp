#include "Phone.h"

#include <math.h>
#include <vector>
#include <iostream>

double Phone::GetPathToFrom(int xdest, int ydest,
                         int xsrc, int ysrc)
{
    return sqrt(pow(xdest - xsrc, 2) + pow(ydest - ysrc, 2));
}
double Phone::GetShortPathTo(int x, int y, Position p)
{
    double l = GetPathToFrom(x, y, p.XL, p.YL);
    double r = GetPathToFrom(x, y, p.XR, p.YR);
    if(l < r)
        return l;
    else
        return r;
}
void Phone::Solve(int M, int N, int L)
{
    std::vector<Position>* options = new std::vector<Position>();
    std::vector<Position>* newOptions = new std::vector<Position>();
    Position start = {0, 0, N - 1, 0, 0};
    options->push_back(start);
    for(int i = 0; i < L; ++i)
    {
        int numX, numY;
        std::cin >> numX;
        std::cin >> numY;
        unsigned long size = options->size();
        for(unsigned long j = 0; j < size; ++j)
        {
            Position pl = {numX, numY, options->at(j).XR, options->at(j).YR,
                           options->at(j).price + Phone::GetPathToFrom(options->at(j).XL, options->at(j).YL, numX, numY)};
            newOptions->push_back(pl);
            Position pr = {options->at(j).XL, options->at(j).YL, numX, numY,
                           options->at(j).price + Phone::GetPathToFrom(options->at(j).XR, options->at(j).YR, numX, numY)};
            newOptions->push_back(pr);
        }
        options->clear();
        std::vector<Position>* temp = options;
        options = newOptions;
        newOptions = temp;
    }
    unsigned long size = options->size();
    double min = options->at(0).price;
    unsigned long index = 0;
    /*for(unsigned long i = 0; i < size; ++i)
        if(min > index)*/

}
