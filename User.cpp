#include "User.h"
#include "UserManager.h"
#include "QuizManager.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

User::User(const std::string& uname, const std::string& pwd, bool admin)
    : username(uname), password(pwd), isAdmin(admin) {}

std::string User::getUsername() const { return username; }
bool User::isAdminUser() const { return isAdmin; }

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << " (Admin: " << (user.isAdmin ? "Yes" : "No") << ")";
    return os;
}

Admin::Admin(const std::string& uname, const std::string& pwd, UserManager& mgr)
    : User(uname, pwd, true), userMgr(mgr) {}

void Admin::showMenu() {
    std::vector<std::string> opts = {
        "Add New Quiz Set",
        "Add Question to Quiz",
        "View Global Leaderboard",
        "View Per-Quiz Leaderboard",
        "View All Users",
        "Delete User",
        "Quiz Stats",
        "Logout"
    };
    Utilities::printMenu("Admin Menu", opts);
}

Student::Student(const std::string& uname, const std::string& pwd, UserManager& mgr)
    : User(uname, pwd, false), userMgr(mgr) {}

void Student::showMenu() {
    std::vector<std::string> opts = {
        "Start Quiz",
        "View My Scores",
        "View Global Leaderboard",
        "View Quiz Leaderboard",
        "Logout"
    };
    Utilities::printMenu("Student Menu", opts);
}