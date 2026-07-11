#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <iostream>

using namespace std;
class Question {
private:
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctAnswer;

public:
    Question();
    Question(string q, string a, string b, string c, string d, char correct);
    
    void displayQuestion() const;
    bool checkAnswer(char answer) const;
    char getCorrectAnswer() const;
    string getQuestionText() const;
    string getOptionA() const;
    string getOptionB() const;
    string getOptionC() const;
    string getOptionD() const;
};

#endif
