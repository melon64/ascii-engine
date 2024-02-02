#ifndef RESOURCES_H
#define RESOURCES_H

#include "Shape.h"
#include <vector>

class Resources {
    std::vector<Shape *> shapes;
    int shapeCount;
    Resources();
    Resources(Resources const&) = delete;
    void operator=(Resources const&) = delete;
    static bool instanceFlag;
    static Resources *instance;

  public:
    static Resources *getInstance();
    bool start();
    void end();
    void createRectangle(char c, int length, int width, std::string label);
    bool loadShape(std::string filename, std::string label);
    bool unloadShape(std::string label);
    Shape *getShape(std::string label);
};

#endif
