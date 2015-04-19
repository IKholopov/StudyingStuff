#ifndef __PhoneNumber_H__
#define __PhoneNumber_H__

struct Position
{
    int XL;
    int YL;
    int XR;
    int YR;
    double price;
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
