#include"cell.h"
#include <iostream>

using namespace std;

Cell :: Cell(int y, int x, int chamberNumber, bool canStepon, char defaultChar)
  : Subject(y,x,canStepon, false, defaultChar), chamberNumber{chamberNumber} {}



  
