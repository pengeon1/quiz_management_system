#include "Leaderboard.h"
#include "Utilities.h"

Score::Score(const std::string& name, int pts, const std::string& qname)
    : studentName(name), points(pts), quizName(qname) {}

std::string Score::getStudentName() const { return studentName; }
int Score::getPoints() const { return points; }
std::string Score::getQuizName() const { return quizName; }

Score Score::operator+(const Score& other) const {
    if (studentName != other.studentName || quizName != other.quizName)
        throw std::invalid_argument("Cannot add scores from different students/quizzes");
    return Score(studentName, points + other.points, quizName);
}

std::ostream& operator<<(std::ostream& os, const Score& s) {
    os << s.studentName << ": " << s.points << " (Quiz: " << s.quizName << ")";
    return os;
}

void Leaderboard::loadScores() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string uname, qname;
        int pts;
        if (ss >> uname >> qname >> pts)
            addScore(Score(uname, pts, qname));
    }
    file.close();
}

void Leaderboard::saveScores() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& stu : scores)
        for (const auto& q : stu.second)
            file << q.second.getStudentName() << " "
                 << q.second.getQuizName() << " "
                 << q.second.getPoints() << std::endl;
    file.close();
}

Leaderboard::Leaderboard() { loadScores(); }
Leaderboard::~Leaderboard() { saveScores(); }

void Leaderboard::addScore(const Score& score) {
    std::string name = score.getStudentName(), qname = score.getQuizName();
    auto& stuScores = scores[name];
    auto it = stuScores.find(qname);
    if (it != stuScores.end()) {
        if (score.getPoints() > it->second.getPoints()) {
            it->second = score;
        }
    } else {
        stuScores.emplace(qname, score);
    }
}

void Leaderboard::displayGlobal() const {
    std::cout << GREEN << "\n--- Global Leaderboard ---" << RESET << std::endl;
    std::vector<std::pair<std::string, int>> sorted;
    for (const auto& stu : scores) {
        int total = 0;
        for (const auto& q : stu.second) total += q.second.getPoints();
        sorted.emplace_back(stu.first, total);
    }
    std::sort(sorted.begin(), sorted.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { 
            return a.second > b.second; 
        });
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::cout << BLUE << (i + 1) << ". " << sorted[i].first << ": " << sorted[i].second << RESET << std::endl;
    }
}

void Leaderboard::displayPerQuiz(const std::string& qname) const {
    std::cout << GREEN << "\n--- " << qname << " Leaderboard ---" << RESET << std::endl;
    std::vector<std::pair<std::string, int>> sorted;
    for (const auto& stu : scores) {
        auto it = stu.second.find(qname);
        if (it != stu.second.end()) sorted.emplace_back(stu.first, it->second.getPoints());
    }
    std::sort(sorted.begin(), sorted.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { 
            return a.second > b.second; 
        });
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::cout << BLUE << (i + 1) << ". " << sorted[i].first << ": " << sorted[i].second << RESET << std::endl;
    }
}

void Leaderboard::displayPersonal(const std::string& name) const {
    auto it = scores.find(name);
    if (it != scores.end() && !it->second.empty()) {
        std::cout << GREEN << "\nYour Scores:" << RESET << std::endl;
        for (const auto& q : it->second)
            std::cout << BLUE << q.second << RESET << std::endl;
    } else std::cout << YELLOW << "No scores yet." << RESET << std::endl;
}