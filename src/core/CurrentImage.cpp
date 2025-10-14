#include "iostream"
#include <filesystem>
#include<cmath>

#include "../../include/core/CurrentImage.h"
#include "../../include/utils/Colors.h"
#include "../../include/utils/Utils.h"

namespace fs = std::filesystem;
using namespace std;

    void CurrentImage::filterApplied() {
        Undo.push(img);
    }

    void CurrentImage::load()
    {
        if (isLoaded && !Undo.empty())
        {
            char OP;
            cout << CYAN <<"Do you want keep your changing ?  (y)es or (n)o: " << RESET << endl;
            cin >> OP;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (OP == 'y')
            {
                save();
                cout << GREEN << "Image changed successfully \n" << RESET;
            }
        }
        string imgName;
        cout << CYAN << "Please enter image name you want to apply filter on: " << RESET << GREEN << BOLD;
        cin >> ws ;
        getline(cin, imgName);
        cout << "\n\n" << RESET;
        img.loadNewImage(Utils::getImagePath(imgName));
        setIsLoaded(true);

        Undo = stack<Image>();
        Redo = stack<Image>();
    }

    void CurrentImage::save()
    {
        cout << YELLOW << "Enter the name of the new image : " << RESET;
        string imgName;
        cin >> imgName;

        if (!fs::exists("output"))
            fs::create_directory("output");

        img.saveImage("output/" + imgName);
        cout << GREEN << "Your image has been saved successfully!\n" << RESET;
    }

    void CurrentImage::undo()
    {
        if (!Undo.empty())
        {
            Redo.push(img);
            img = Undo.top();
            Undo.pop();
        }
        else
        {
            cout << RED << "No more steps to undo.\n" << RESET;
        }
    }

    void CurrentImage::redo()
    {
        if (!Redo.empty())
        {
            Undo.push(img);
            img = Redo.top();
            Redo.pop();
        }
        else
        {
            cout << RED << "No more steps to redo.\n" << RESET;
        }
    }

    bool CurrentImage::getIsLoaded() const
    {
        return isLoaded;
    }

    void CurrentImage::setIsLoaded(bool newIsLoaded)
    {
        isLoaded = newIsLoaded;
    }