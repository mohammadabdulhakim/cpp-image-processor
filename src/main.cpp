/*
    This is an image processing app.
    When you start the program it asks you to load an image from the assets folder you write the name and the extension of the image (image.jpg).
    Then a punch of filters appears, you can apply any filter you want, and you can apply filters one by one.
    At any point you can save the image with any extension and in any folder even it does not exist.

    The App is colorful and eyes friendly. it's not only about the look.
    The app follows Object-Oriented Programming paradigm.
    It is scalable, and you can implement any filter smoothly without changing other classes.


    20242110 - Hamza Mohammad Zaki - Filters that have been assigned to Hamza by our beloved doctor (GreyScale, Merge, Darken and Lighten, Edge Detection)
    20242295 - Mohammad Abdulhakim Ramadan - Filters that have been assigned to Mohammad by our beloved doctor (White and Black, Flip, Crop, Resizing, Oil Painting, Infrared, Painting, Bloody, Sky, Grass )
    20240588 - Mostafa Ahmed Ali - Filters that have been assigned to Mostafa by our beloved doctor (Invert, Rotate, Frame, Blur, Sunlight, Night, Old TV, Skew)

    Repo: https://github.com/mohammadabdulhakim/cpp-image-processor
    Video:https://drive.google.com/file/d/1JwfZ4EaOa0lDDdudM1ykVUVurc86tPN4/view?usp=drive_link
    Doc: https://docs.google.com/document/d/1qCHJ92_c90hBn0wo34rJ349e9NXzKGfr/edit?usp=sharing&ouid=104606776738113898703&rtpof=true&sd=true

    Competition Drive: https://drive.google.com/drive/folders/1YQpSNy2T5i5xhCbJqXt8GEbWl3ScDerE

*/
#include<stack>
#include <memory>
#include <vector>
#include<algorithm>

#include "../include/core/Menu.h"
#include "../include/core/CurrentImage.h"

#include "../include/filters/Filter.h"
#include "../include/filters/GreyScale.h"
#include "../include/filters/WhiteAndBlack.h"
#include "../include/filters/Invert.h"
#include "../include/filters/Merge.h"
#include "../include/filters/Flip.h"
#include "../include/filters/Rotate.h"
#include "../include/filters/Brightness.h"
#include "../include/filters/Crop.h"
#include "../include/filters/Frame.h"
#include "../include/filters/EdgeDetection.h"
#include "../include/filters/Resize.h"
#include "../include/filters/Blur.h"
#include "../include/filters/Sunlight.h"
#include "../include/filters/OilPainting.h"
#include "../include/filters/OldTV.h"
#include "../include/filters/Night.h"
#include "../include/filters/Infrared.h"
#include "../include/filters/Skewing.h"
#include "../include/filters/Bloody.h"
#include "../include/filters/Grass.h"
#include "../include/filters/Sky.h"
#include "../include/filters/ArtisticBrush.h"


using namespace std;



int main()
{
    CurrentImage currentImage;

    vector<pair<string, shared_ptr<Filter>>> filters = {
        {GreyScale::getId(), make_shared<GreyScale>(currentImage.img)},
        {WhiteAndBlack::getId(), make_shared<WhiteAndBlack>(currentImage.img)},
        {Invert::getId(), make_shared<Invert>(currentImage.img)},
        {Merge::getId(), make_shared<Merge>(currentImage.img)},
        {Flip::getId(), make_shared<Flip>(currentImage.img)},
        {Rotate::getId(), make_shared<Rotate>(currentImage.img)},
        {Brightness::getId(), make_shared<Brightness>(currentImage.img)},
        {Crop::getId(), make_shared<Crop>(currentImage.img)},
        {Frame::getId(), make_shared<Frame>(currentImage.img)},
        {EdgeDetection::getId(),make_shared<EdgeDetection>(currentImage.img)},
        {Resize::getId(), make_shared<Resize>(currentImage.img)},
        {Blur::getId(), make_shared<Blur>(currentImage.img)},
        {Sunlight::getId(), make_shared<Sunlight>(currentImage.img)},
        {OilPainting::getId(), make_shared<OilPainting>(currentImage.img)},
        {OldTV::getId(), make_shared<OldTV>(currentImage.img)},
        {Night::getId(), make_shared<Night>(currentImage.img)},
        {Infrared::getId(), make_shared<Infrared>(currentImage.img)},
        {Skewing::getId(), make_shared<Skewing>(currentImage.img)},
        {Bloody::getId(), make_shared<Bloody>(currentImage.img)},
        {Grass::getId(),make_shared<Grass>(currentImage.img)},
        {Sky::getId(),make_shared<Sky>(currentImage.img)},
        {ArtisticBrush::getId(), make_shared<ArtisticBrush>(currentImage.img)},
    };

    Menu menu(filters);
    menu.welcomeMsg();

    while (menu.getIsActive())
    {
        menu.showMenuOptions(currentImage.getIsLoaded());
        menu.setResponse();

        string res = menu.getResponse();

        if (res == "l")
        {
            currentImage.load();
        }
        else if (res == "s" && currentImage.getIsLoaded())
        {
            currentImage.save();
        }
        else if (res == "u" && currentImage.getIsLoaded())
        {
            currentImage.undo();
        }
        else if (res == "r" && currentImage.getIsLoaded())
        {
            currentImage.redo();
        }
        else if (res == "0")
        {
            menu.setIsActive(false);
        }
        else if (currentImage.getIsLoaded())
        {
            bool noFilterWithRes = true;
            for(auto &filter: filters) {
                if (filter.first == res) {
                    currentImage.filterApplied();
                    filter.second->getNeeds();
                    filter.second->apply();
                    noFilterWithRes = false;
                }
            }

            if (noFilterWithRes) menu.invalidOptionMsg();
        }
        else
        {
            menu.invalidOptionMsg();
        }
    }
    return 0;
}