#!/bin/bash
echo "Compiling Quiz System..."
g++ -std=c++14 -Wall -Wextra -pedantic -o quiz_system main.cpp User.cpp UserManager.cpp Question.cpp Leaderboard.cpp QuizManager.cpp Utilities.cpp

if [ $? -eq 0 ]; then
    echo "Compilation successful! Run with: ./quiz_system"
else
    echo "Compilation failed!"
fi