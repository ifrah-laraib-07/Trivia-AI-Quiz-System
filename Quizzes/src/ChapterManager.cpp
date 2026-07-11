#include <windows.h>// for colors and cursor position
#include "../include/ChapterManager.h"
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

static fs::path chaptersDir() {
    return exeDir() / "Chapters";
}
static void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

void ChapterManager::createChapter() {
    string chapterName;
    setColor(11); cout << "\n  Enter Chapter Name > "; setColor(15);
    getline(cin, chapterName);
    setColor(7);
    if (chapterName.empty()) { setColor(12); cout << "  Chapter name cannot be empty.\n"; setColor(7); return; }

    if (!fs::exists(chaptersDir())) fs::create_directory(chaptersDir());

    string filename = (chaptersDir() / (chapterName + ".txt")).string();
    ofstream file(filename);
    if (!file.is_open()) { setColor(12); cerr << "  Error creating chapter file.\n"; setColor(7); return; }

    setColor(8); cout << "  Enter content (type 'END' on a new line to finish):\n"; setColor(7);
    string line;
    while (getline(cin, line)) {
        if (line == "END") break;
        file << line << "\n";
    }
    file.close();
    setColor(10); cout << "  Chapter '" << chapterName << "' created successfully!\n"; setColor(7);
}

void ChapterManager::deleteChapter() {
    listChapters();
    string chapterName;
    setColor(12); cout << "\n  Enter Chapter Name to Delete > "; setColor(15);
    getline(cin, chapterName);
    setColor(7);

    string filename = (chaptersDir() / (chapterName + ".txt")).string();
    if (fs::exists(filename)) {
        fs::remove(filename);
        setColor(10); cout << "  Chapter '" << chapterName << "' deleted successfully!\n"; setColor(7);
    } else {
        setColor(12); cout << "  Chapter not found.\n"; setColor(7);
    }
}

void ChapterManager::listChapters() const {
    setColor(13);
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  AVAILABLE CHAPTERS                  ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    setColor(7);

    int count = 1;
    if (fs::exists(chaptersDir()) && fs::is_directory(chaptersDir())) {
        for (const auto& entry : fs::directory_iterator(chaptersDir())) {
            if (entry.path().extension() == ".txt") {
                string name = entry.path().stem().string();
                setColor(7); cout << "  ║  ";
                setColor(11); cout << "[" << count++ << "]  ";
                setColor(15); cout << left << setw(47) << name;
                setColor(7); cout << "║\n";
            }
        }
    }
    if (count == 1) {
        setColor(8); cout << "  ║          No chapters available.                      ║\n"; setColor(7);
    }
    setColor(13);
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}

void ChapterManager::readChapter(const string& chapterName) const {
    string filename = (chaptersDir() / (chapterName + ".txt")).string();
    ifstream file(filename);
    if (!file.is_open()) {
        setColor(12); cout << "  Chapter '" << chapterName << "' not found. Use 'list' to see available chapters.\n"; setColor(7);
        return;
    }

    setColor(13);
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║  Chapter: " << left << setw(45) << chapterName << "║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    setColor(7);

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            cout << "  ║  "; setColor(15);
            // Print up to 51 chars per line
            if (line.size() <= 51) {
                cout << left << setw(51) << line;
            } else {
                cout << line.substr(0, 51);
            }
            setColor(7); cout << "║\n";
        }
    }
    setColor(13);
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
    file.close();
}
