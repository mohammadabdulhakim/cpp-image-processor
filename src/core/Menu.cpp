#include "../../include/core/Menu.h"
#include "../../include/utils/Colors.h"


    Menu::Menu(vector<pair<string, shared_ptr<Filter>>>& filters) : filters(filters) {};

    void Menu::welcomeMsg()
    {
        // string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
        // cout << welcomeMsg << "\n";
        // cout << string(welcomeMsg.length() / 5, ' ') << string(welcomeMsg.length() * 3 / 5, '=') << string(welcomeMsg.length() / 5, ' ') << "\n \n";
        std::cout << CYAN << "====================\n";
        std::cout << RESET << BOLD << "    Image Filters    \n";
        std::cout << RESET << CYAN << "=====================\n";
    }

    void Menu::showMenuOptions(bool fileLoaded)
    {

        std::cout << RESET << GREEN << "[l] Load Image\n";
        if (fileLoaded)
        {

            std::cout << CYAN << "=====================\n";
            std::cout << RESET << BOLD << "    Choose Filters    \n";
            std::cout << RESET << CYAN << "======================\n" << RESET;

            auto it = filters.begin();
            while (it != filters.end()) {
                cout << "\t [" << it->first << "] " << it->second->getName() << " Filter.\n";
                ++it;
            }

            cout << "\t[s] Save the Image.\n" ;
            cout << "\t[u] Undo \t [r] Redo\n";
        }
        // cout << "0. Exit.\n";
        std::cout << RESET << RED << "[0] Exit\n" << RESET;
        cout << "-------------------------------\n";
    }

    void Menu::invalidOptionMsg() {
        cout << RED << "Invalid option \n" << RESET;
        cout << YELLOW << "Plz Enter Valid option";
        cout << "\n\n";
    }
    bool Menu::getIsActive()
    {
        return isActive;
    }
    void Menu::setIsActive(bool newIsActive)
    {
        isActive = newIsActive;
    }

    void Menu::setResponse()
    {
        // cout << "Enter Your Response:\t";
        std::cout << BOLD << GREEN << "# " << RESET;
        cin >> res;
        cout << '\n';
    }

    string Menu::getResponse()
    {
        return res;
    }