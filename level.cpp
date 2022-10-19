#include "level.h"

Level::Level(double start, double end, double space)
{
    this->space = space;
    this->start = start;
    this->end = end;
    usedSpace = 0;
}

double Level::getSpace()
{
    return space;
}

double Level::getStart()
{
    return start;
}

double Level::getEnd()
{
    return end;
}

double Level::getUsedSpace()
{
 return usedSpace;
}

bool Level::fits(double height, double width)
{
    return (height <= end - start && width < space);
}

void Level::add(double width)
{
    space -= width;
    usedSpace += width;
}

double Level::checkFreeSpace(double width)
{
    return space - width;
}
