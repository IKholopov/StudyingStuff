#ifndef __PhoneNumber_H__
#define __PhoneNumber_H__


enum Finger
{
    Right = 1, Left = 0
};

struct Position
{
    Finger freeFinger;
    Position* prev;
    double price;
    short seqLink;
};

class Phone
{
    public:
        static double GetPathToFrom(int xdest, int ydest,
                                 int xsrc, int ysrc);
        static double GetShortPathTo(int x, int y, Position p);
        static void Solve(int M, int N, int L);

};

#endif
