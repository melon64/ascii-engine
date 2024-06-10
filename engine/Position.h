#ifndef POSITION_H
#define POSITION_H

class Position{
    int x, y;
  public:
    Position();
    Position(int, int);
    bool operator==(const Position&);
    int getX();
    int getY();
    void setX(int);
    void setY(int);
};

#endif
