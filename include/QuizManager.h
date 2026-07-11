#ifndef QUIZMANAGER_H
#define QUIZMANAGER_H

#include <string>
#include <vector>

using namespace std;

class QuizManager {
public:
    void createQuiz();
    void deleteQuiz();
    bool saveQuiz(const string& filename, const string& quizContent);
    void listQuizzes() const;
};

#endif
