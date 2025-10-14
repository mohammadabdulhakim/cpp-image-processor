#include <memory>
#include <vector>

#include "../filters/Filter.h"

#ifndef MENU_H
#define MENU_H



class Menu
{
    bool isActive = true;
    string res;
    vector<pair<string, shared_ptr<Filter>>>& filters;

public:
    Menu(vector<pair<string, shared_ptr<Filter>>>& filters);

    void welcomeMsg();

    void showMenuOptions(bool fileLoaded);

    void invalidOptionMsg();
    bool getIsActive();
    void setIsActive(bool newIsActive);

    void setResponse();

    string getResponse();
};



#endif //MENU_H
