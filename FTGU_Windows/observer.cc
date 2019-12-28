#include "observer.h"
#include <vector>
using namespace std;

void Observer :: notify(Subject &whoNotified) {
    this->doNotify(whoNotified);
}

void Observer::print(bool gotSmartPointer, std::ostream &out, vector<string>elines) {
    this->doPrint(gotSmartPointer, out, elines);

}

Observer :: ~Observer() {

}


