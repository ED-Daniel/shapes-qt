#ifndef LEVEL_H
#define LEVEL_H


class Level
{
public:
    Level(double start, double end, double space);

    double getSpace();
    double getStart();
    double getEnd();
    double getUsedSpace();

    bool fits(double height, double width);
    void add(double width);
    double checkFreeSpace(double width);

private:
    double space;
    double usedSpace;
    double start;
    double end;
};

#endif // LEVEL_H
