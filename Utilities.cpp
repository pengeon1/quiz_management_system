#include "Utilities.h"
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

void Utilities::printBorder(int width, const std::string& left, const std::string& right, const std::string& fill) {
    std::cout << MAGENTA << left;
    for (int i = 0; i < width - 2; ++i) std::cout << fill;
    std::cout << right << RESET << std::endl;
}

void Utilities::printTitle(const std::string& title, int width) {
    printBorder(width, BORDER_TOP_LEFT, BORDER_TOP_RIGHT, BORDER_HORIZONTAL);
    
#ifdef _WIN32
    int padding = (width - 2 - title.length()) / 2;
    if (padding < 0) padding = 0;
    std::cout << BORDER_VERTICAL;
    std::cout << std::string(padding, ' ') << title << std::string(padding, ' ');
    if ((width - 2 - title.length()) % 2 != 0) std::cout << " ";
    std::cout << BORDER_VERTICAL << std::endl;
#else
    std::cout << MAGENTA << BORDER_VERTICAL << "     " << RESET << CYAN << title 
              << std::string(std::max(0, width - 7 - (int)title.size()), ' ') 
              << MAGENTA << BORDER_VERTICAL << RESET << std::endl;
#endif
    
    printBorder(width, BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT, BORDER_HORIZONTAL);
}

void Utilities::printMenu(const std::string& title, const std::vector<std::string>& options, int width) {
    std::cout << "\n";
    printTitle(title, width);
    
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << MAGENTA << BORDER_VERTICAL << RESET << " ";
        std::cout << YELLOW << (i + 1) << ". " << RESET << options[i];
        
        int textWidth = 3 + options[i].length();
        int spaces = width - 3 - textWidth;
        if (spaces > 0) {
            std::cout << std::string(spaces, ' ');
        }
        
        std::cout << MAGENTA << BORDER_VERTICAL << RESET << std::endl;
    }
    
    printBorder(width, BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT, BORDER_HORIZONTAL);
}

void Utilities::showLoading(const std::string& msg) {
    std::cout << CYAN << msg << " " << RESET;
    for (int i = 0; i < 3; ++i) {
        std::cout << BOLD << CYAN << "." << std::flush;
#ifdef _WIN32
        Sleep(400);
#else
        usleep(400000);
#endif
    }
    std::cout << RESET << std::endl;
}
