#include "Utilities.h"

void Utilities::printBorder(int width, const std::string& left, const std::string& right, const std::string& fill) {
    std::cout << MAGENTA << left;
    for (int i = 0; i < width - 2; ++i) std::cout << fill;
    std::cout << right << RESET << std::endl;
}

void Utilities::printTitle(const std::string& title, int width) {
    printBorder(width, "╔", "╗", "═");
    std::cout << MAGENTA << "║     " << RESET << CYAN << title << std::string(std::max(0, width - 7 - (int)title.size()), ' ') << MAGENTA << "║" << RESET << std::endl;
    printBorder(width, "╚", "╝", "═");
}

void Utilities::printMenu(const std::string& title, const std::vector<std::string>& options, int width) {
    std::cout << "\n";
    printTitle(title, width);
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << MAGENTA << "║ " << RESET << YELLOW << std::setw(2) << (i + 1) << ". " << options[i] << std::string(std::max(0, width - 7 - (int)options[i].size()), ' ') << MAGENTA << "║" << RESET << std::endl;
    }
    printBorder(width, "╚", "╝", "═");
}

void Utilities::showLoading(const std::string& msg) {
    std::cout << CYAN << msg << " " << RESET;
    for (int i = 0; i < 3; ++i) {
        std::cout << BOLD << CYAN << "." << std::flush;
        usleep(400000);
    }
    std::cout << RESET << std::endl;
}