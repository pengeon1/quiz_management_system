#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#define RED     ""
#define GREEN   ""
#define YELLOW  ""
#define BLUE    ""
#define MAGENTA ""
#define CYAN    ""
#define WHITE   ""
#define RESET   ""
#define BOLD    ""
#define UNDER   ""
#define BORDER_TOP_LEFT     "+"
#define BORDER_TOP_RIGHT    "+"
#define BORDER_BOTTOM_LEFT  "+"
#define BORDER_BOTTOM_RIGHT "+"
#define BORDER_HORIZONTAL   "-"
#define BORDER_VERTICAL     "|"
#else
#include <unistd.h>
#define RED     "\033[38;5;196m"
#define GREEN   "\033[38;5;46m"
#define YELLOW  "\033[38;5;226m"
#define BLUE    "\033[38;5;45m"
#define MAGENTA "\033[38;5;201m"
#define CYAN    "\033[38;5;51m"
#define WHITE   "\033[38;5;15m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define UNDER   "\033[4m"
#define BORDER_TOP_LEFT     "╔"
#define BORDER_TOP_RIGHT    "╗"
#define BORDER_BOTTOM_LEFT  "╚"
#define BORDER_BOTTOM_RIGHT "╝"
#define BORDER_HORIZONTAL   "═"
#define BORDER_VERTICAL     "║"
#endif

namespace Utilities {
    void printBorder(int width = 40, const std::string& left = "╔", const std::string& right = "╗", const std::string& fill = "═");
    void printTitle(const std::string& title, int width = 40);
    void printMenu(const std::string& title, const std::vector<std::string>& options, int width = 40);
    void showLoading(const std::string& msg = "Loading");
}

#endif
