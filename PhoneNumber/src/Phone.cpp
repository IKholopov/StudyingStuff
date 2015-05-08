#include "Phone.h"

#include <math.h>
#include <vector>
#include <iostream>
#include <utility>

typedef std::pair<int, int> Point;


double Phone::GetPathToFrom(int xdest, int ydest,
                         int xsrc, int ysrc)
{
    return sqrt(pow(xdest - xsrc, 2) + pow(ydest - ysrc, 2));
}
void UpdateCell(Position*** d, int step, int coord, Finger finger, double dist, Position* prev)
{
    if(d[step][coord][finger].prev == NULL || prev->price + dist < d[step][coord][finger].price)
    {
        d[step][coord][finger].prev = prev;
        d[step][coord][finger].price = prev->price + dist ;
        d[step][coord][finger].freeFinger = finger;
    }
}

void Phone::Solve(int M, int N, int L)
{
    Position** d0 = new Position*[N*M];
        for(int j = 0; j < N * M; ++j)
            d0[j] = new Position[2];
    Position** d1 = new Position*[N*M];
            for(int j = 0; j < N * M; ++j)
                d1[j] = new Position[2];
    for(int j = 0; j < N * M; ++j)
    {
        d0[j][0].prev = NULL;
        d0[j][1].prev = NULL;
        d1[j][0].prev = NULL;
        d1[j][1].prev = NULL;
    }
    d0[N - 1][1].price = 0;
    std::vector<int>* prevIds = new std::vector<int>();
    std::vector<std::pair<char, unsigned long> > sequence;
    prevIds->push_back(N - 1);
    Position EndP;
    EndP.prev = NULL;
    d0[N - 1][1].prev = &EndP;
    d0[N - 1][1].freeFinger = Finger::Right;
    d0[N - 1][1].seqLink = 0;
    sequence.push_back(std::pair<char, unsigned long>(0, 0));
    std::vector<Point> number;
    Point p(0, 0);
    number.push_back(p);
    int step;
    int coord;
    Finger finger;
    double dist;
    Position* prev;
    for(int i = 0; i < L; ++i)
    {
        for(int j = 0; j < N * M; ++j)
        {
            d1[j][0].prev = NULL;
            d1[j][1].prev = NULL;
        }
        std::cin >> p.first;
        std::cin >> p.second;
        number.push_back(p);
        prevIds->clear();
        for(int j = 0; j < N * M; ++j)
        {
            if(d0[j][0].prev != NULL || d0[j][1].prev != NULL)
            {
                prevIds->push_back(j);
            }
        }
        for(int j  = 0; j < prevIds->size(); ++j)
        {
            if(d0[prevIds->at(j)][0].prev != NULL)
            {
                step = i + 1;
                coord = prevIds->at(j);//number[i].first + N * number[i].second;
                finger = Finger::Left;
                dist = GetPathToFrom(number[i + 1].first,
                        number[i + 1].second, number[i].first, number[i].second);
                prev = &(d0[prevIds->at(j)][0]);                                           //Left is where he is
                if(d1[coord][finger].prev == NULL || prev->price + dist < d1[coord][finger].price)
                {
                    d1[coord][finger].prev = prev;
                    d1[coord][finger].price = prev->price + dist ;
                    d1[coord][finger].freeFinger = finger;
                    sequence.push_back(std::pair<char, unsigned long>('R', prev->seqLink));
                    d1[coord][finger].seqLink = sequence.size() - 1;
                }
                coord = number[i].first + N * number[i].second;
                finger = Finger::Right;
                dist = GetPathToFrom(number[i + 1].first,
                        number[i + 1].second, prevIds->at(j) % N, prevIds->at(j) / N);
                prev = &(d0[prevIds->at(j)][0]);                                           //Right is where he is
                if(d1[coord][finger].prev == NULL || prev->price + dist < d1[coord][finger].price)
                {
                    d1[coord][finger].prev = prev;
                    d1[coord][finger].price = prev->price + dist ;
                    d1[coord][finger].freeFinger = finger;
                    sequence.push_back(std::pair<char, unsigned long>('L', prev->seqLink));
                    d1[coord][finger].seqLink = sequence.size() - 1;
                }
            }
            if(d0[prevIds->at(j)][1].prev != NULL)
            {
                step = i + 1;
                coord = prevIds->at(j);//number[i].first + N * number[i].second;
                finger = Finger::Right;
                dist = GetPathToFrom(number[i + 1].first,
                        number[i + 1].second, number[i].first, number[i].second);
                prev = &(d0[prevIds->at(j)][1]);                                           //Right is where he is
                if(d1[coord][finger].prev == NULL || prev->price + dist < d1[coord][finger].price)
                {
                    d1[coord][finger].prev = prev;
                    d1[coord][finger].price = prev->price + dist ;
                    d1[coord][finger].freeFinger = finger;
                    sequence.push_back(std::pair<char, unsigned long>('L', prev->seqLink));
                    d1[coord][finger].seqLink = sequence.size() - 1;
                }
                coord = number[i].first + N * number[i].second;
                finger = Finger::Left;
                dist = GetPathToFrom(number[i + 1].first,
                        number[i + 1].second, prevIds->at(j) % N, prevIds->at(j) / N);
                prev = &(d0[prevIds->at(j)][1]);                                           //Left is where he is
                if(d1[coord][finger].prev == NULL || prev->price + dist < d1[coord][finger].price)
                {
                    d1[coord][finger].prev = prev;
                    d1[coord][finger].price = prev->price + dist ;
                    d1[coord][finger].freeFinger = finger;
                    sequence.push_back(std::pair<char, unsigned long>('R', prev->seqLink));
                    d1[coord][finger].seqLink = sequence.size() - 1;
                }
            }
        }
        Position** temp = d0;
        d0 = d1;
        d1  = temp;
    }
    for(int i = 0; i < N * M; ++i)
    {
        if(d0[i][0].prev != NULL)
            std::cout << i << " " << d0[i][0].freeFinger << " " << d0[i][0].price << std::endl;
        if(d0[i][1].prev != NULL)
            std::cout << i << " " << d0[i][1].freeFinger << " " << d0[i][1].price << std::endl;
    }
    double cost = -1;
    Position* id;
    for(int i = 0; i < N * M; ++i)
    {
        if(d0[i][0].prev != NULL)
        {
            if(cost < 0)
            {
                cost = d0[i][0].price;
                id =  &(d0[i][0]);
            }
            else if(d0[i][0].price - cost < 0.0)
            {
                cost = d0[i][0].price;
                id = &(d0[i][0]);
            }
        }
        if(d0[i][1].prev != NULL)
        {
            if(cost < 0)
            {
                cost = d0[i][1].price;
                id = &(d0[i][1]);
            }
            else if(d0[i][0].price - cost < 0.0)
            {
                cost = d0[i][1].price;
                id = &(d0[i][1]);
            }
        }
    }
    char c = sequence[id->seqLink].first;
    unsigned long link = id->seqLink;
    while(link != 0)
    {
        std::cout << c;
        c = sequence[link].first;
        link = sequence[link].second;
    }
    std::cout << std::endl;
    //std::cout << id->sequence << std::endl;
    return;
}
