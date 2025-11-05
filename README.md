# Quiz Management System

A comprehensive C++ quiz management system with role-based access control, multiple question types, and leaderboard functionality.

## Features

### ➢ Core Features
- **Role-based Access**: Admin and Student roles with different privileges
- **Multiple Question Types**: MCQ, True/False, and Short Answer questions
- **Quiz Management**: Create, manage, and take quizzes
- **Leaderboard System**: Global and per-quiz rankings
- **User Management**: Register, login, and user administration
- **Persistent Storage**: Saves users, scores, and quizzes to files

### ➢ Admin Features
- Create new quiz sets
- Add questions to quizzes
- View all users and delete users
- View quiz statistics
- Access global and per-quiz leaderboards

### ➢ Student Features
- Take available quizzes
- View personal scores
- Compete on leaderboards
- Track progress across multiple quizzes

## Project Structure

**quiz-management-system/** <br>
**├── main.cpp**                   # Main program entry point <br>
**├── Exceptions.h**               # Custom exception classes <br>
**├── Utilities.h/.cpp**           # UI utilities and formatting <br>
**├── UserManager.h/.cpp**         # User authentication and management <br>
**├── User.h/.cpp**                # User base class and derived classes <br>
**├── Question.h/.cpp**            # Question hierarchy and types <br>
**├── Leaderboard.h/.cpp**         # Score tracking and ranking <br>
**├── QuizManager.h/.cpp**         # Main application logic <br>
**├── compile.sh**                 # Compilation script <br>
**└── README.md**                  # This file <br>

## Installation & Compilation
```
# Make the script executable
chmod +x compile.sh

# Compile the project
./compile.sh

./quiz_system
```

## Default Login Credentials

**Admin:**

    Username: admin
    Password: admin123

**Students:** Register new accounts through the login screen

## File Storage

The system automatically creates and manages these data files:

 - users.txt - User accounts and credentials

 - scores.txt - Quiz scores and leaderboard data

## Usage Guide
**For Students:**

● Register a new account or login

● Select "Start Quiz" to take available quizzes

● View your scores and leaderboard positions

● Track progress across multiple attempts

**For Admins:**

● Login with admin credentials

● Create new quiz sets and add questions

● Manage user accounts

● Monitor quiz statistics and leaderboards

● View system-wide performance metrics

## Question Types Supported

*MCQ (Multiple Choice)*

- 4 options (A, B, C, D)

- Single correct answer

*True/False Questions*

- Binary answer selection

- Case-insensitive input

*Short Answer Questions*

- Flexible text matching

- Case-insensitive comparison

- Partial answer acceptance
