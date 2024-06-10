#include "Resources.h"
#include "Shape.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

Resources::Resources(){};

Resources *Resources::instance = NULL;
bool Resources::instanceFlag = false;

Resources *Resources::getInstance() {
    if(!instanceFlag){
        instance = new Resources();
        instanceFlag = true;
        return instance;
    }
    else{
        return instance;
    }
}

Shape *Resources::getShape(std::string label) {
    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getLabel() == label) {
            return shapes[i];
        }
    }
    return nullptr;
}
bool Resources::start() {
    shapeCount = 0;
    shapes = std::vector<Shape *>();
    return true;
}

void Resources::end() {
    for (int i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
    shapes.clear();
}

bool Resources::loadShape(std::string filename, std::string label) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; //cannot open
    }

    std::string line;
    int length = 0, width = 0, delay = 0, frameCount = 0;
    bool inInfo = false, inFrames = false;

    Shape* newShape = nullptr;

    while (getline(file, line)) {
        if (line == "infobegin") {
            inInfo = true;
        } else if (line == "infoend") {
            inInfo = false;
            newShape = new Shape(frameCount);
            newShape->setFrameDelay(delay);
        } else if (line == "framesbegin") {
            inFrames = true;
        } else if (line == "framesend") {
            inFrames = false;
        } else if (inInfo) {
            std::istringstream iss(line);
            std::string key;
            int value;
            iss >> key >> value;
            if (key == "length:") {
                length = value;
            } else if (key == "width:") {
                width = value;
            } else if (key == "delay:") {
                delay = value;
            } else if (key == "frames:") {
                frameCount = value;
            }
        } else if (inFrames && newShape) {
            if (line == "begin") {
                std::string frameData;
                for (int i = 0; i < width; ++i) {
                    std::string frameLine;
                    if (!getline(file, frameLine) || frameLine.size() != length){
                        delete newShape;
                        return false;
                    }
                    frameData += frameLine;
                }

                Frame frame(width, length, frameData);
                newShape->addFrame(frame);
                getline(file, line); 
                if (line != "end") {
                    delete newShape;
                    return false;
                }
            }
        }
    }

    newShape->setLength(width);
    newShape->setWidth(length);

    if (newShape && newShape->getFrameCount() != frameCount) {
        delete newShape;
        return false;
    }

    if (newShape) {
        newShape->setLabel(label);
        shapes.push_back(newShape);
    }

    file.close();

    if (!newShape) return false;
    return true;
}

bool Resources::unloadShape(std::string label) {
    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getLabel() == label) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            return true;
        }
    }
    return false;
}

void Resources::createRectangle(char c, int length, int width, std::string label){
    Shape* newShape = new Shape(1);
    newShape->setFrameDelay(0);
    newShape->setLength(length);
    newShape->setWidth(width);
    std::string frameData;
    for (int i = 0; i < width; ++i) {
        std::string frameLine;
        for (int j = 0; j < length; ++j) {
            frameLine += c;
        }
        frameData += frameLine;
    }
    Frame frame(length, width, frameData);
    newShape->addFrame(frame);
    newShape->setLabel(label);
    shapes.push_back(newShape);

}

