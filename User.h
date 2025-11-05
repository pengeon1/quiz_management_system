#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class UserManager;
class QuizManager;

class User {
protected:
    std::string username;
    std::string password;
    bool isAdmin;
public:
    User(const std::string& uname, const std::string& pwd, bool admin = false);
    virtual ~User() = default;
    virtual void showMenu() = 0;
    std::string getUsername() const;
    bool isAdminUser() const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

class Admin : public User {
private:
    UserManager& userMgr;
public:
    Admin(const std::string& uname, const std::string& pwd, UserManager& mgr);
    void showMenu() override;
    bool handleAdminChoice(int choice, QuizManager& qm);
};

class Student : public User {
private:
    UserManager& userMgr;
public:
    Student(const std::string& uname, const std::string& pwd, UserManager& mgr);
    void showMenu() override;
    bool handleStudentChoice(int choice, QuizManager& qm);
};

#endif