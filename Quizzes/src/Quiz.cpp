#include <windows.h>
#include "../include/Quiz.h"
#include <fstream>
#include <iostream>
#include <cctype>

static void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

Quiz::Quiz(string name) : courseName(name) {}

void Quiz::loadQuestions(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string q, a, b, c, d;
    char correct;

    while (getline(file, q)) {
        if (q.empty()) continue;
        if (!getline(file, a)) break;
        if (!getline(file, b)) break;
        if (!getline(file, c)) break;
        if (!getline(file, d)) break;
        string correctStr;
        if (!getline(file, correctStr)) break;
        if (!correctStr.empty()) {
            correct = toupper(correctStr[0]);
            questions.push_back(Question(q, a, b, c, d, correct));
        }
    }
    file.close();
}

int Quiz::startQuiz() {
    int score = 0;
    if (questions.empty()) {
        setColor(12);
        cout << "\n  No questions found in this quiz.\n";
        setColor(7);
        return score;
    }

    for (size_t i = 0; i < questions.size(); ++i) {
        setColor(14);
        cout << "\n  ┌──────────────────────────────────────────────────────┐\n";
        cout << "  │  Question " << (i + 1) << " of " << questions.size();
        int pad = 42 - to_string(i+1).size() - to_string(questions.size()).size();
        cout << string(pad, ' ') << "│\n";
        cout << "  └──────────────────────────────────────────────────────┘\n";
        setColor(15);

        // Display question with word wrap at 52 chars
        string qt = questions[i].getQuestionText();
        cout << "\n  " << qt << "\n\n";

        setColor(10);  cout << "  [A] "; setColor(7); cout << questions[i].getOptionA() << "\n";
        setColor(10);  cout << "  [B] "; setColor(7); cout << questions[i].getOptionB() << "\n";
        setColor(10);  cout << "  [C] "; setColor(7); cout << questions[i].getOptionC() << "\n";
        setColor(10);  cout << "  [D] "; setColor(7); cout << questions[i].getOptionD() << "\n";

        char answer = 0;
        while (true) {
            setColor(11);
            cout << "\n  Your answer (A/B/C/D) > ";
            setColor(15);
            string input;
            getline(cin, input);
            setColor(7);
            if (!input.empty()) {
                char ch = toupper(input[0]);
                if (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D') {
                    answer = ch;
                    break;
                }
            }
            setColor(12);
            cout << "  Invalid input. Please enter A, B, C, or D.\n";
            setColor(7);
        }

        if (questions[i].checkAnswer(answer)) {
            setColor(10);
            cout << "  ✔  Correct!\n";
            setColor(7);
            score++;
        } else {
            setColor(12);
            cout << "  ✘  Wrong!  Correct answer: " << questions[i].getCorrectAnswer() << "\n";
            setColor(7);
        }
    }
    return score;
}

string Quiz::getCourseName() const { return courseName; }
int Quiz::getTotalQuestions() const { return questions.size(); }
