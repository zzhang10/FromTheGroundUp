#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class Observer;

class Subject {
    //vector of observers
    std::vector<std::shared_ptr<Observer>> observers;

    //position in the world
    int x, y;

    //Display character
    char displayChar;

    //Can it move?
    bool movable;

    //Can a player step on it?
    bool steppable;


  public:
    //add an observer
    void attach(std::shared_ptr<Observer> ob);

    //notify the observers of a change
    void notifyObservers();

    //getters and setters
    void setPos(int x, int y);
    void getPos(int &x, int &y);
    char getDisplay();
    void setDisplay(char display);
    void setSteppable(bool step);
    bool isMovable();
    bool isSteppable();


    Subject(int y, int x, bool canStepOn, bool canMove, char defaultChar);

    //Making destructor pure virtual to avoid instantiating subject base class
    virtual ~Subject() = 0;
};
#endif



