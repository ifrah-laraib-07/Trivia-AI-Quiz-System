#include "../include/Question.h"
#include <cctype>// toupper means convert to uppercase

//default constructor initializes all strings to empty and correct answer to 'A'
Question::Question() : questionText(""), optionA(""), optionB(""), optionC(""), optionD(""), correctAnswer('A') {}
//parameterized constructor initializes all members with provided values, ensuring correct answer is uppercase
Question::Question(string q, string a, string b, string c, string d, char correct)
    : questionText(q), optionA(a), optionB(b), optionC(c), optionD(d), correctAnswer(toupper(correct)) {}

void Question::displayQuestion() const {
    cout << questionText << endl;
    cout << "A. " << optionA << endl;
    cout << "B. " << optionB << endl;
    cout << "C. " << optionC << endl;
    cout << "D. " << optionD << endl;
}

bool Question::checkAnswer(char answer) const {
    return toupper(answer) == toupper(correctAnswer);
}

char Question::getCorrectAnswer() const { return correctAnswer; }
string Question::getQuestionText() const { return questionText; }
string Question::getOptionA() const { return optionA; }
string Question::getOptionB() const { return optionB; }
string Question::getOptionC() const { return optionC; }
string Question::getOptionD() const { return optionD; }
