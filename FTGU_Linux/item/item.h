#ifndef ITEM_H
#define ITEM_H
#include "../subject.h"
#include <iostream>

class Item: public Subject {
  protected:
    //Note that all gold has displaychar 'G' but their itemType can be
    //"Normal", "SmallStash", "MercenaryStash" or "DefendedStash"
	std::string itemType;
  public:
    //Sets whether item is protected by a defender, or send error message if
    //item does not support defender protection
    virtual void setProtect(bool isProtected);

    //Gets the protector's position. Send error message if it has no protector
    virtual void getDefPos(int &px, int &py);


	Item(int y, int x, std::string itemType, bool canStepon, char c);
	virtual std::tuple<std::string, double, bool> getInfo();
    virtual void setDefPos(int px, int py);
    ~Item() = 0;
};

class Gold: public Item {
	bool defenderProtect;
	std::pair<int, int> defenderat;
  public:
	Gold(int y, int x, std::string goldType, std::pair<int, int> defenderat);
    std::tuple<std::string, double, bool>getInfo() override;
    void setProtect(bool isProtected) override;
    void getDefPos(int &px, int &py) override;
    void setDefPos(int px, int py)override;
};

class ForceShield: public Item {
    bool defenderProtect;
    std::pair<int, int> defenderat;
public:
    ForceShield(int y, int x, std::pair<int, int> defenderat);
    std::tuple<std::string, double, bool>getInfo() override;
    void setProtect(bool isProtected) override;
    void getDefPos(int &px, int &py) override;
    void setDefPos(int px, int py)override;
};

class Potion: public Item {
    std::string type;
  public:
	Potion(int y, int x, std::string type = "RANDOM");
    std::tuple<std::string, double, bool>getInfo() override;
};

class SmartPointer: public Item {
  public:
	SmartPointer(int y, int x);

};


#endif


