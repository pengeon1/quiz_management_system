#include "Utilities.h"
#include <thread>
#include <chrono>

void Utilities::printBorder(int width, const std::string& left, const std::string& right, const std::string& fill) {
    std::cout << left;
    for (int i = 0; i < width - 2; ++i) std::cout << fill;
    std::cout << right << std::endl;
}

void Utilities::printTitle(const std::string& title, int width) {
    printBorder(width, BORDER_TOP_LEFT, BORDER_TOP_RIGHT, BORDER_HORIZONTAL);
    
    int padding = (width - 2 - title.length()) / 2;
    if (padding < 0) padding = 0;
    
    std::cout << BORDER_VERTICAL;
    std::cout << std::string(padding, ' ') << title << std::string(padding, ' ');
    if ((width - 2 - title.length()) % 2 != 0) std::cout << " ";
    std::cout << BORDER_VERTICAL << std::endl;
    
    printBorder(width, BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT, BORDER_HORIZONTAL);
}

void Utilities::printMenu(const std::string& title, const std::vector<std::string>& options, int width) {
    std::cout << "\n";
    printTitle(title, width);
    
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << BORDER_VERTICAL << " ";
        std::cout << (i + 1) << ". " << options[i];

        int textWidth = 3 + options[i].length();
        int spaces = width - 3 - textWidth;
        if (spaces > 0) {
            std::cout << std::string(spaces, ' ');
        }
        
        std::cout << BORDER_VERTICAL << std::endl;
    }
    
    printBorder(width, BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT, BORDER_HORIZONTAL);
}

void Utilities::showLoading(const std::string& msg) {
    std::cout << msg << " ";
    for (int i = 0; i < 3; ++i) {
        std::cout << "." << std::flush;
        Sleep(400);
    }
    std::cout << std::endl;
}
