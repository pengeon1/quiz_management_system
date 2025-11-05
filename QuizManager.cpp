#include "QuizManager.h"
#include "User.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

QuizSet::QuizSet(const std::string& name) : setName(name), totalPoints(0) {}

QuizSet::~QuizSet() { for (auto q : questions) delete q; }

void QuizSet::addQuestion(Question* q) { 
    questions.push_back(q); 
    totalPoints += q->getPoints(); 
}

int QuizSet::takeQuiz() {
    int score = 0;
    Utilities::printTitle("Starting Quiz: " + setName);
    std::cout << CYAN << "Total Points: " << totalPoints << RESET << std::endl;
    Utilities::showLoading("Preparing questions");
    for (auto q : questions) {
        try {
            std::cout << MAGENTA << "\n───────────────────────────────────────────────\n" << RESET;
            std::cout << *q << std::endl;
            std::string ans;
            std::cout << MAGENTA << "Your answer: " << RESET;
            std::getline(std::cin, ans);
            if (q->checkAnswer(ans)) {
                score += q->getPoints();
                std::cout << GREEN << "Correct! +" << q->getPoints() << " pts" << RESET << std::endl;
            } else std::cout << RED << "Wrong! Correct: " << q->getCorrectAnswer() << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } catch (const InvalidAnswerException& e) {
            std::cout << RED << "Error: " << e.what() << " Score unchanged." << RESET << std::endl;
        }
    }
    std::cout << BLUE << "\nQuiz complete! Score: " << score << "/" << totalPoints << RESET << std::endl;
    return score;
}

std::string QuizSet::getName() const { return setName; }
int QuizSet::getTotalPoints() const { return totalPoints; }
size_t QuizSet::getNumQuestions() const { return questions.size(); }

bool Admin::handleAdminChoice(int choice, QuizManager& qm) {
    switch (choice) {
        case 1: {
            std::cout << YELLOW << "New Quiz Name: " << RESET;
            std::string name; std::getline(std::cin, name);
            qm.getQuizzes().push_back(new QuizSet(name));
            std::cout << GREEN << "Quiz set created!" << RESET << std::endl;
            break;
        }
        case 2: {
            auto* quiz = qm.selectQuiz();
            if (!quiz) break;
            std::cout << YELLOW << "Question Type (1:MCQ, 2:TF, 3:SAQ): " << RESET;
            int type; std::cin >> type; std::cin.ignore();
            std::cout << YELLOW << "Text: " << RESET;
            std::string text; std::getline(std::cin, text);
            std::cout << YELLOW << "Points: " << RESET;
            int pts; std::cin >> pts; std::cin.ignore();
            if (type == 1) {
                std::vector<std::string> opts(4);
                for (int i = 0; i < 4; i++) {
                    std::cout << YELLOW << "Option " << char('A' + i) << ": " << RESET;
                    std::getline(std::cin, opts[i]);
                }
                std::cout << YELLOW << "Correct Answer (A/B/C/D): " << RESET;
                std::string corr; std::getline(std::cin, corr);
                char ch = std::toupper(corr[0]);
                if (ch < 'A' || ch > 'D') {
                    std::cout << RED << "Invalid option!" << RESET << std::endl;
                    break;
                }
                std::string correct = opts[ch - 'A'];
                quiz->addQuestion(new MCQ(text, pts, correct, opts));
            } else if (type == 2) {
                std::cout << YELLOW << "Is it True? (1 for True, 0 for False): " << RESET;
                int isTrueInt; std::cin >> isTrueInt;
                std::cin.ignore();
                bool isTrue = (isTrueInt != 0);
                quiz->addQuestion(new TFQuestion(text, pts, isTrue));
            } else if (type == 3) {
                std::cout << YELLOW << "Correct Answer: " << RESET;
                std::string corr; std::getline(std::cin, corr);
                quiz->addQuestion(new SAQ(text, pts, corr));
            } else {
                std::cout << RED << "Invalid question type!" << RESET << std::endl;
                break;
            }
            std::cout << GREEN << "Question added!" << RESET << std::endl;
            break;
        }
        case 3:
            qm.getLeaderboard().displayGlobal();
            break;
        case 4: {
            std::cout << YELLOW << "Quiz Name: " << RESET;
            std::string qname; std::getline(std::cin, qname);
            qm.getLeaderboard().displayPerQuiz(qname);
            break;
        }
        case 5:
            std::cout << GREEN << "\nAll Users:" << RESET << std::endl;
            for (const auto& u : userMgr.getAllUsernames())
                std::cout << BLUE << u << RESET << std::endl;
            break;
        case 6: {
            std::cout << YELLOW << "Delete Username: " << RESET;
            std::string uname; std::getline(std::cin, uname);
            if (uname == username) {
                std::cout << RED << "Cannot delete yourself!" << RESET << std::endl;
            } else if (userMgr.deleteUser(uname)) {
                std::cout << GREEN << "User deleted!" << RESET << std::endl;
            } else {
                std::cout << RED << "User not found!" << RESET << std::endl;
            }
            break;
        }
        case 7:
            std::cout << GREEN << "\nQuiz Statistics:" << RESET << std::endl;
            for (auto q : qm.getQuizzes())
                std::cout << BLUE << q->getName() << ": " << q->getNumQuestions()
                         << " Qs, " << q->getTotalPoints() << " pts" << RESET << std::endl;
            break;
        case 8:
            std::cout << YELLOW << "Logging out..." << RESET << std::endl;
            return true;
        default:
            std::cout << RED << "Invalid choice!" << RESET << std::endl;
    }
    return false;
}

bool Student::handleStudentChoice(int choice, QuizManager& qm) {
    switch (choice) {
        case 1: {
            auto* quiz = qm.selectQuiz();
            if (quiz) {
                int score = quiz->takeQuiz();
                qm.getLeaderboard().addScore(Score(username, score, quiz->getName()));
            }
            break;
        }
        case 2: 
            qm.getLeaderboard().displayPersonal(username); 
            break;
        case 3: 
            qm.getLeaderboard().displayGlobal(); 
            break;
        case 4: {
            std::cout << YELLOW << "Quiz Name: " << RESET;
            std::string qname; std::getline(std::cin, qname);
            qm.getLeaderboard().displayPerQuiz(qname);
            break;
        }
        case 5:
            std::cout << YELLOW << "Logging out..." << RESET << std::endl;
            return true;
        default:
            std::cout << RED << "Invalid choice!" << RESET << std::endl;
    }
    return false;
}

void QuizManager::initSampleQuizzes() {
    auto basic = new QuizSet("Basic Quiz");
    std::vector<std::string> opts1 = {"Red", "Blue", "Green", "Yellow"};
    basic->addQuestion(new MCQ("What color is the sky?", 10, "Blue", opts1));
    basic->addQuestion(new TFQuestion("Is Python a programming language?", 5, true));
    basic->addQuestion(new SAQ("What does OOP stand for?", 15, "object oriented programming"));
    quizzes.push_back(basic);
}

QuizSet* QuizManager::selectQuiz() {
    if (quizzes.empty()) { std::cout << RED << "No quizzes available!" << RESET << std::endl; return nullptr; }
    std::cout << GREEN << "\nAvailable Quizzes:" << RESET << std::endl;
    for (size_t i = 0; i < quizzes.size(); ++i) {
        auto q = quizzes[i];
        std::cout << BLUE << (i + 1) << ". " << q->getName() << " (" << q->getNumQuestions()
                 << " Qs, " << q->getTotalPoints() << " pts)" << RESET << std::endl;
    }
    int choice;
    std::cout << MAGENTA << "Select quiz: " << RESET;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(quizzes.size())) {
        std::cout << RED << "Invalid quiz selection!" << RESET << std::endl;
        return nullptr;
    }
    return quizzes[choice - 1];
}

QuizManager::QuizManager() {
    initSampleQuizzes();
    try { userMgr.registerUser("admin", "admin123", true); } catch (...) {}
}

QuizManager::~QuizManager() {
    for (auto q : quizzes) delete q;
    delete currentUser;
}

void QuizManager::run() {
    while (true) {
        try {
            if (!currentUser) {
                std::vector<std::string> mainOpts = {"Login", "Register (Student)", "Exit"};
                Utilities::printMenu("Quiz Management System", mainOpts);
                int choice; 
                std::cout << MAGENTA << "Select option: " << RESET;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (choice == 3) break;
                if (choice == 1) {
                    std::cout << YELLOW << "Username: " << RESET;
                    std::string uname; std::getline(std::cin, uname);
                    std::cout << YELLOW << "Password: " << RESET;
                    std::string pwd; std::getline(std::cin, pwd);
                    bool isAdmin = userMgr.authenticate(uname, pwd);
                    currentUser = isAdmin ?
                        static_cast<User*>(new Admin(uname, pwd, userMgr)) :
                        static_cast<User*>(new Student(uname, pwd, userMgr));
                    std::cout << GREEN << "\nLogged in as " << CYAN << *currentUser << RESET << std::endl;
                    Utilities::showLoading("Loading dashboard");
                } else if (choice == 2) {
                    std::cout << YELLOW << "New Username: " << RESET;
                    std::string uname; std::getline(std::cin, uname);
                    std::cout << YELLOW << "New Password: " << RESET;
                    std::string pwd; std::getline(std::cin, pwd);
                    userMgr.registerUser(uname, pwd, false);
                    std::cout << GREEN << "Registered successfully!" << RESET << std::endl;
                } else {
                    std::cout << RED << "Invalid choice!" << RESET << std::endl;
                }
            } else {
                currentUser->showMenu();
                int choice;
                std::cout << MAGENTA << "Select option: " << RESET;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool wantsLogout = false;
                if (currentUser->isAdminUser())
                    wantsLogout = static_cast<Admin*>(currentUser)->handleAdminChoice(choice, *this);
                else
                    wantsLogout = static_cast<Student*>(currentUser)->handleStudentChoice(choice, *this);

                if (wantsLogout) {
                    delete currentUser;
                    currentUser = nullptr;
                }
            }
        } catch (const LoginException& e) {
            std::cout << RED << "Login failed: " << e.what() << RESET << std::endl;
        } catch (const std::exception& e) {
            std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

Leaderboard& QuizManager::getLeaderboard() { return lb; }
std::vector<QuizSet*>& QuizManager::getQuizzes() { return quizzes; }
UserManager& QuizManager::getUserManager() { return userMgr; }