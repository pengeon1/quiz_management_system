#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Exceptions.h"

class Question {
protected:
    std::string text;
    int points;
    std::string correctAnswer;
public:
    Question(const std::string& qtext, int pts, const std::string& corr);
    virtual ~Question() = default;
    virtual void display() const = 0;
    virtual bool checkAnswer(const std::string& userAnswer) const = 0;
    virtual std::string getType() const = 0;
    std::string getText() const;
    int getPoints() const;
    std::string getCorrectAnswer() const;
    friend std::ostream& operator<<(std::ostream& os, const Question& q);
};

class MCQ : public Question {
private:
    std::vector<std::string> options;
public:
    MCQ(const std::string& qtext, int pts, const std::string& corr, const std::vector<std::string>& opts);
    void display() const override;
    bool checkAnswer(const std::string& userAnswer) const override;
    std::string getType() const override;
};

class TFQuestion : public Question {
public:
    TFQuestion(const std::string& qtext, int pts, bool corr);
    void display() const override;
    bool checkAnswer(const std::string& userAnswer) const override;
    std::string getType() const override;
};

class SAQ : public Question {
public:
    SAQ(const std::string& qtext, int pts, const std::string& corr);
    void display() const override;
    bool checkAnswer(const std::string& userAnswer) const override;
    std::string getType() const override;
};

#endif