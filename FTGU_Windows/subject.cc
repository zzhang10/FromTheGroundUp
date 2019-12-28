#include "subject.h"
#include "observer.h"
#include <iostream>
using namespace std;

Subject::Subject(int y, int x, bool canStepOn, bool canMove, char defaultChar)
  : x{x}, y{y},  displayChar{defaultChar}, movable{canMove},
  steppable{canStepOn} {}

void Subject::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Subject::getPos(int &x, int &y) {
    y = this->y;
    x = this->x;
}

void Subject::attach(std::shared_ptr<Observer> ob) {
    observers.emplace_back(ob);
}

void Subject::notifyObservers() {
    for (size_t i = 0; i < observers.size(); i++) {
        observers[i]->notify(*this);
    }
}

void Subject:: setSteppable(bool step) {
    steppable = step;
}

char Subject::getDisplay() {
    return displayChar;
}

void Subject::setDisplay(char display) {
    this->displayChar = display;
}

bool Subject::isMovable() {
    return movable;
}

bool Subject::isSteppable() {
    return steppable;
}

Subject::~Subject() {
    observers.clear();
}



