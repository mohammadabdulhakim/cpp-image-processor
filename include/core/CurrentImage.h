#include "../../third_party/Image_Class.h"
#include <stack>
using namespace std;

#ifndef CURRENTIMAGE_H
#define CURRENTIMAGE_H



class CurrentImage
{
    bool isLoaded = false;
    stack<Image> Undo;
    stack<Image> Redo;

public:
    Image img;

    void filterApplied();

    void load();

    void save();

    void undo();

    void redo();

    bool getIsLoaded() const;

    void setIsLoaded(bool newIsLoaded);
};



#endif //CURRENTIMAGE_H
