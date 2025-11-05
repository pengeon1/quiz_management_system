#include "UserManager.h"

void UserManager::loadUsers() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string uname, pwd;
        bool admin;
        if (ss >> uname >> pwd >> admin) users[uname] = {pwd, admin};
    }
    file.close();
}

void UserManager::saveUsers() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& u : users)
        file << u.first << " " << u.second.first << " " << u.second.second << std::endl;
    file.close();
}

UserManager::UserManager() { loadUsers(); }
UserManager::~UserManager() { saveUsers(); }

bool UserManager::registerUser(const std::string& uname, const std::string& pwd, bool admin) {
    if (users.find(uname) != users.end()) throw LoginException("Username already exists!");
    users[uname] = {pwd, admin};
    saveUsers();
    return true;
}

bool UserManager::authenticate(const std::string& uname, const std::string& pwd) {
    auto it = users.find(uname);
    if (it == users.end()) throw LoginException("Invalid username or password!");
    if (it->second.first != pwd) throw LoginException("Invalid username or password!");
    return it->second.second;
}

std::vector<std::string> UserManager::getAllUsernames() const {
    std::vector<std::string> names;
    for (const auto& u : users)
        names.push_back(u.first + (u.second.second ? " (Admin)" : ""));
    return names;
}

bool UserManager::deleteUser(const std::string& uname) { return users.erase(uname) > 0; }