#include <windows.h>
#include "../include/ScoreManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

static void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

// Returns the directory containing TriviaBot.exe
static fs::path exeDir() {
    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return fs::path(buf).parent_path();
}

static std::string scoresFile() {
    return (exeDir() / "scores.txt").string();
}

void ScoreManager::saveScore(const string& playerName, const string& courseName, int score, int total) {
    ofstream file(scoresFile(), ios::app);
    if (file.is_open()) {
        file << playerName << " | " << courseName << " | " << score << "/" << total << "\n";
        file.close();
    }
}

void ScoreManager::showScores() const {
    ifstream file(scoresFile());

    setColor(14);
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                    SCORE HISTORY                     ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    setColor(7);

    if (!file.is_open()) {
        setColor(8);
        cout << "  ║          No scores recorded yet.                     ║\n";
        setColor(14);
        cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
        setColor(7);
        return;
    }

    string line;
    bool hasData = false;
    while (getline(file, line)) {
        if (!line.empty()) {
            hasData = true;
            setColor(7);  cout << "  ║  ";
            setColor(15); cout << left << setw(51) << line;
            setColor(7);  cout << "║\n";
        }
    }
    if (!hasData) {
        setColor(8);
        cout << "  ║          No scores recorded yet.                     ║\n";
        setColor(7);
    }
    setColor(14);
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
    file.close();
}
