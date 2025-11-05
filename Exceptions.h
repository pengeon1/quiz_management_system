#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class LoginException : public std::exception {
private:
    std::string message;
public:
    LoginException(const std::string& msg) : message(msg) {}
    const char* what() const throw() override { return message.c_str(); }
};

class InvalidAnswerException : public std::exception {
private:
    std::string message;
public:
    InvalidAnswerException(const std::string& msg) : message(msg) {}
    const char* what() const throw() override { return message.c_str(); }
};

#endif