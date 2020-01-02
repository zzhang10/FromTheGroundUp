#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "../observer.h"

class Cell;

class TextDisplay final : public Observer {
    //2D vector of character representing the map visually
    std::vector<std::vector<char>> theDisplay;

    //Stats about the map
    const int width;
    const int height;

    void doNotify(Subject &whoNotified) override;
    void doPrint(bool hasSmartPointer, std::ostream&,
	std::vector<std::string>elines) override;
 public:
    TextDisplay(int width, int height);
};

#endif


