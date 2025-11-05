#ifndef QUIZSET_H
#define QUIZSET_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "Question.h"
#include "Utilities.h"

template <typename T>
class QuizSet {
private:
    std::vector<T*> questions;
    std::string setName;
    int totalPoints;
public:
    QuizSet(const std::string& name);
    ~QuizSet();
    void addQuestion(T* q);
    int takeQuiz();
    std::string getName() const;
    int getTotalPoints() const;
    size_t getNumQuestions() const;
};

#include "QuizSet.tpp"

#endif