#ifndef QUIZSET_TPP
#define QUIZSET_TPP

template <typename T>
QuizSet<T>::QuizSet(const std::string& name) : setName(name), totalPoints(0) {}

template <typename T>
QuizSet<T>::~QuizSet() { for (auto q : questions) delete q; }

template <typename T>
void QuizSet<T>::addQuestion(T* q) { 
    questions.push_back(q); 
    totalPoints += q->getPoints(); 
}

template <typename T>
int QuizSet<T>::takeQuiz() {
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

template <typename T>
std::string QuizSet<T>::getName() const { return setName; }

template <typename T>
int QuizSet<T>::getTotalPoints() const { return totalPoints; }

template <typename T>
size_t QuizSet<T>::getNumQuestions() const { return questions.size(); }

#endif