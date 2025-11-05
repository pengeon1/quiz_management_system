#ifndef QUIZMANAGER_H
#define QUIZMANAGER_H

#include "UserManager.h"
#include "Leaderboard.h"
#include "Question.h"
#include "Utilities.h"
#include <vector>

class User;

class QuizSet {
private:
    std::vector<Question*> questions;
    std::string setName;
    int totalPoints;
public:
    QuizSet(const std::string& name);
    ~QuizSet();
    void addQuestion(Question* q);
    int takeQuiz();
    std::string getName() const;
    int getTotalPoints() const;
    size_t getNumQuestions() const;
};

class QuizManager {
private:
    User* currentUser = nullptr;
    UserManager userMgr;
    Leaderboard lb;
    std::vector<QuizSet*> quizzes;
    void initSampleQuizzes();
public:
    QuizSet* selectQuiz();
    QuizManager();
    ~QuizManager();
    void run();
    Leaderboard& getLeaderboard();
    std::vector<QuizSet*>& getQuizzes();
    UserManager& getUserManager();
};

#endif