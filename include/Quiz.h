#ifndef QUIZ_H
#define QUIZ_H

#include "Question.h"
#include <vector>
#include <string>

using namespace std;

class Quiz {
private:
    string courseName;
    vector<Question> questions; // Composition
public:
    Quiz(string name = "");
    void loadQuestions(const string& filename);
    int startQuiz();
    string getCourseName() const;
    int getTotalQuestions() const;
};

#endif
