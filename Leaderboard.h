#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

class Score {
private:
    std::string studentName;
    int points;
    std::string quizName;
public:
    Score(const std::string& name, int pts, const std::string& qname);
    std::string getStudentName() const;
    int getPoints() const;
    std::string getQuizName() const;
    Score operator+(const Score& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Score& s);
};

class Leaderboard {
private:
    std::map<std::string, std::map<std::string, Score>> scores;
    const std::string filename = "scores.txt";
    void loadScores();
    void saveScores();
public:
    Leaderboard();
    ~Leaderboard();
    void addScore(const Score& score);
    void displayGlobal() const;
    void displayPerQuiz(const std::string& qname) const;
    void displayPersonal(const std::string& name) const;
};

#endif