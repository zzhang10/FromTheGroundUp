#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <vector>

class Subject;

class Observer {
    //subclasses must implement how they want to get notified and print
    virtual void doNotify(Subject &whoNotified) = 0;
    virtual void doPrint(bool hasSmartPointer, std::ostream&, std::vector<std::string>elines) = 0;

  public:

    //abstract template pattern
    void notify (Subject &whoNotified);

    void print (bool, std::ostream&, std::vector<std::string>elines);
    virtual ~Observer();
};
#endif


