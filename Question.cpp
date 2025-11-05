#include "Question.h"
#include "Utilities.h"

Question::Question(const std::string& qtext, int pts, const std::string& corr)
    : text(qtext), points(pts), correctAnswer(corr) {}

std::string Question::getText() const { return text; }
int Question::getPoints() const { return points; }
std::string Question::getCorrectAnswer() const { return correctAnswer; }

std::ostream& operator<<(std::ostream& os, const Question& q) { 
    q.display(); 
    return os; 
}

MCQ::MCQ(const std::string& qtext, int pts, const std::string& corr, const std::vector<std::string>& opts)
    : Question(qtext, pts, corr), options(opts) {
    if (options.size() < 2) throw std::invalid_argument("MCQ needs at least 2 options");
}

void MCQ::display() const {
    std::cout << CYAN << text << RESET << std::endl;
    for (size_t i = 0; i < options.size(); ++i)
        std::cout << YELLOW << (char)('A' + i) << ". " << options[i] << RESET << std::endl;
}

bool MCQ::checkAnswer(const std::string& userAnswer) const {
    if (userAnswer.empty()) throw InvalidAnswerException("No answer provided!");
    char ch = std::toupper(userAnswer[0]);
    size_t idx = ch - 'A';
    if (idx >= options.size()) throw InvalidAnswerException("Invalid option selected!");
    return options[idx] == correctAnswer;
}

std::string MCQ::getType() const { return "MCQ"; }

TFQuestion::TFQuestion(const std::string& qtext, int pts, bool corr)
    : Question(qtext, pts, corr ? "TRUE" : "FALSE") {}

void TFQuestion::display() const {
    std::cout << CYAN << text << RESET << std::endl;
    std::cout << YELLOW << "True/False?" << RESET << std::endl;
}

bool TFQuestion::checkAnswer(const std::string& userAnswer) const {
    if (userAnswer.empty()) throw InvalidAnswerException("No answer provided!");
    std::string normalized = userAnswer;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::toupper);
    if (normalized != "TRUE" && normalized != "FALSE")
        throw InvalidAnswerException("Answer must be True or False!");
    return normalized == correctAnswer;
}

std::string TFQuestion::getType() const { return "TF"; }

SAQ::SAQ(const std::string& qtext, int pts, const std::string& corr)
    : Question(qtext, pts, corr) {}

void SAQ::display() const {
    std::cout << CYAN << text << RESET << std::endl;
    std::cout << YELLOW << "Short answer:" << RESET << std::endl;
}

bool SAQ::checkAnswer(const std::string& userAnswer) const {
    if (userAnswer.empty()) throw InvalidAnswerException("No answer provided!");
    std::string userNorm = userAnswer, corrNorm = correctAnswer;
    std::transform(userNorm.begin(), userNorm.end(), userNorm.begin(), ::tolower);
    std::transform(corrNorm.begin(), corrNorm.end(), corrNorm.begin(), ::tolower);
    return corrNorm.find(userNorm) != std::string::npos || userNorm.find(corrNorm) != std::string::npos;
}

std::string SAQ::getType() const { return "SAQ"; }