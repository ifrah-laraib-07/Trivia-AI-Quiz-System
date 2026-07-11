#include <windows.h>
#include "../include/QuizManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Returns the directory that contains TriviaBot.exe
static fs::path exeDir() {
    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return fs::path(buf).parent_path();
}

static fs::path quizzesDir() {
    return exeDir() / "Quizzes";
}
static void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

void QuizManager::createQuiz() {
    string courseName;
    setColor(11); cout << "\n  Enter Quiz Name (e.g. OOP, Genetics) > "; setColor(15);
    getline(cin, courseName);
    setColor(7);
    if (courseName.empty()) { setColor(12); cout << "  Quiz name cannot be empty.\n"; setColor(7); return; }

    int numQuestions = 0;
    while (numQuestions <= 0) {
        setColor(11); cout << "  How many questions? > "; setColor(15);
        string input; getline(cin, input); setColor(7);
        try { numQuestions = stoi(input); } catch (...) {}
        if (numQuestions <= 0) { setColor(12); cout << "  Please enter a valid number > 0.\n"; setColor(7); }
    }

    if (!fs::exists(quizzesDir())) fs::create_directory(quizzesDir());

    string filename = (quizzesDir() / (courseName + ".txt")).string();
    ofstream file(filename);
    if (!file.is_open()) { setColor(12); cerr << "  Error creating quiz file.\n"; setColor(7); return; }

    for (int i = 0; i < numQuestions; ++i) {
        setColor(14); cout << "\n  --- Question " << (i + 1) << " ---\n"; setColor(7);

        string q, a, b, c, d;
        setColor(11); cout << "  Question text > "; setColor(15); getline(cin, q);
        setColor(11); cout << "  Option A      > "; setColor(15); getline(cin, a);
        setColor(11); cout << "  Option B      > "; setColor(15); getline(cin, b);
        setColor(11); cout << "  Option C      > "; setColor(15); getline(cin, c);
        setColor(11); cout << "  Option D      > "; setColor(15); getline(cin, d);
        setColor(7);

        char correct = 0;
        while (correct == 0) {
            setColor(11); cout << "  Correct (A/B/C/D) > "; setColor(15);
            string ans; getline(cin, ans); setColor(7);
            if (!ans.empty()) {
                char ch = toupper(ans[0]);
                if (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D') correct = ch;
            }
            if (correct == 0) { setColor(12); cout << "  Please enter A, B, C, or D.\n"; setColor(7); }
        }

        file << q << "\n" << a << "\n" << b << "\n" << c << "\n" << d << "\n" << correct << "\n";
    }
    file.close();
    setColor(10); cout << "\n  Quiz '" << courseName << "' created successfully with " << numQuestions << " questions!\n"; setColor(7);
}

void QuizManager::deleteQuiz() {
    listQuizzes();
    string courseName;
    setColor(12); cout << "\n  Enter Quiz Name to Delete > "; setColor(15);
    getline(cin, courseName);
    setColor(7);

    string filename = (quizzesDir() / (courseName + ".txt")).string();
    if (fs::exists(filename)) {
        fs::remove(filename);
        setColor(10); cout << "  Quiz '" << courseName << "' deleted successfully!\n"; setColor(7);
    } else {
        setColor(12); cout << "  Quiz not found.\n"; setColor(7);
    }
}

bool QuizManager::saveQuiz(const string& filename, const string& quizContent) { return true; }

void QuizManager::listQuizzes() const {
    setColor(11);
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  AVAILABLE QUIZZES                   ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    setColor(7);

    int count = 1;
    if (fs::exists(quizzesDir()) && fs::is_directory(quizzesDir())) {
        for (const auto& entry : fs::directory_iterator(quizzesDir())) {
            if (entry.path().extension() == ".txt") {
                string name = entry.path().stem().string();
                setColor(7); cout << "  ║  ";
                setColor(14); cout << "[" << count++ << "]  ";
                setColor(15); cout << left << setw(47) << name;
                setColor(7); cout << "║\n";
            }
        }
    }
    if (count == 1) {
        setColor(8); cout << "  ║          No quizzes available.                       ║\n"; setColor(7);
    }
    setColor(11);
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}
