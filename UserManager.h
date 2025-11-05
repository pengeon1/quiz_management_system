#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Exceptions.h"

class UserManager {
private:
    std::map<std::string, std::pair<std::string, bool>> users;
    const std::string filename = "users.txt";

    void loadUsers();
    void saveUsers();

public:
    UserManager();
    ~UserManager();
    bool registerUser(const std::string& uname, const std::string& pwd, bool admin = false);
    bool authenticate(const std::string& uname, const std::string& pwd);
    std::vector<std::string> getAllUsernames() const;
    bool deleteUser(const std::string& uname);
};

#endif