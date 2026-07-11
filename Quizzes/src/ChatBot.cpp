#include <windows.h>// for colors , cursor position, and file paths
#include "../include/ChatBot.h"// for the main ChatBot class
#include "../include/Quiz.h"// for Quiz class used in trivia mode
#include <iostream>
#include <thread>// for sleep in typing animation
#include <chrono>// for sleep durations
#include <algorithm>// for trim and toLower functions
#include <iomanip>// for setw in result display
#include <filesystem>// for file and directory management

using namespace std;
namespace fs = std::filesystem;

// Returns the directory containing TriviaBot.exe
static fs::path exeDir() {
    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return fs::path(buf).parent_path();
}

// ─── Helpers ─────────────────────────────────────────────────────────────────
static inline void trim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch){ return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !isspace(ch); }).base(), s.end());
}
static inline void toLower(string &s) { for (char &c : s) c = tolower(c); }

// ─── Color Helper ─────────────────────────────────────────────────────────────
static void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// Colors: 7=White 10=Green 11=Cyan 12=Red 13=Magenta 14=Yellow 9=Blue 15=Bright White

// ─── Dividers ─────────────────────────────────────────────────────────────────
static void divider(char ch = '-', int len = 56) {
    setColor(8); // Dark gray
    cout << string(len, ch) << "\n";
    setColor(7);
}

// ─── Partial Clear Helper ────────────────────────────────────────────────────
static COORD getCursorPos() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}
static void clearFromRow(COORD pos) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);
    DWORD written;
    DWORD cells = (DWORD)csbi.dwSize.X * (csbi.dwSize.Y - pos.Y);
    FillConsoleOutputCharacter(h, ' ', cells, pos, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cells, pos, &written);
    SetConsoleCursorPosition(h, pos);
}

// ─────────────────────────────────────────────────────────────────────────────
ChatBot::ChatBot() : currentUser(nullptr) {
    // Force UTF-8 output so all Unicode box-drawing characters render correctly
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void ChatBot::clearConsole() const { system("cls"); }

void ChatBot::typingAnimation(const string &text) const {
    for (char c : text) {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(12));
    }
    cout << "\n";
}

void ChatBot::respond(const string &text) const {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << "\n  >> ";
    SetConsoleTextAttribute(h, 15);
    typingAnimation(text);
    setColor(7);
}

void ChatBot::respond() const {
    respond("Unknown command. Type 'help' to see available commands.");
}

// ─── WELCOME SCREEN ──────────────────────────────────────────────────────────
void ChatBot::printWelcomeScreen() const {
    clearConsole();
    setColor(10); // Green
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║    ████████╗██████╗ ██╗██╗   ██╗██╗ █████╗          ║\n";
    cout << "  ║       ██╔══╝██╔══██╗██║██║   ██║██║██╔══██╗         ║\n";
    cout << "  ║       ██║   ██████╔╝██║██║   ██║██║███████║         ║\n";
    cout << "  ║       ██║   ██╔══██╗██║╚██╗ ██╔╝██║██╔══██║         ║\n";
    cout << "  ║       ██║   ██║  ██║██║ ╚████╔╝ ██║██║  ██║         ║\n";
    cout << "  ║       ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝  ╚═╝╚═╝  ╚═╝         ║\n";
    cout << "  ║                                                      ║\n";
    setColor(14); // Yellow
    cout << "  ║         AI Learning & Trivia Assistant               ║\n";
    setColor(8);
    cout << "  ║                  v2.0 Enhanced                       ║\n";
    setColor(10);
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}

// ─── MODE HEADERS ────────────────────────────────────────────────────────────
void ChatBot::printLearningHeader() const {
    setColor(13); // Magenta
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  📚  LEARNING MODE                  ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}

void ChatBot::printTriviaHeader() const {
    setColor(11); // Cyan
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  🎯  TRIVIA MODE                    ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}

void ChatBot::printAdminHeader() const {
    setColor(12); // Red
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  🔐  ADMIN PANEL                    ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
    setColor(7);
}

// ─── LOGIN ───────────────────────────────────────────────────────────────────
void ChatBot::login() {
    printWelcomeScreen();
    setColor(14);
    cout << "  ┌──────────────────────────────────────────────────────┐\n";
    cout << "  │                    LOGIN PORTAL                      │\n";
    cout << "  └──────────────────────────────────────────────────────┘\n\n";
    setColor(7);
    respond("Please select your role: type  'student'  or  'admin'");

    while (true) {
        setColor(14);
        cout << "\n  Login > ";
        setColor(15);
        string role;
        getline(cin, role);
        trim(role);
        toLower(role);
        setColor(7);

        if (role == "admin") {
            setColor(12);
            cout << "\n  Password > ";
            setColor(15);
            string pass;
            getline(cin, pass);
            setColor(7);
            if (pass == "admin123") {
                currentUser = make_unique<Admin>("System Admin");
                respond("Admin access granted. Welcome back!");
                break;
            } else {
                respond("Incorrect password. Please try again.");
            }
        } else if (role == "student") {
            setColor(11);
            cout << "\n  Enter your Name > ";
            setColor(15);
            string name;
            getline(cin, name);
            trim(name);
            setColor(7);
            if (name.empty()) name = "Student";
            currentUser = make_unique<Student>(name);
            respond("Welcome, " + name + "! Let's start learning!");
            break;
        } else if (role == "exit") {
            respond("Goodbye!");
            exit(0);
        } else {
            respond("Invalid input. Please type 'student' or 'admin'.");
        }
    }
    this_thread::sleep_for(chrono::milliseconds(700));
}

void ChatBot::start() {
    login();
    mainMenu();
}

// ─── MAIN MENU ───────────────────────────────────────────────────────────────
void ChatBot::mainMenu() {
    while (true) {
        clearConsole();
        setColor(14);
        cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
        cout << "  ║                     MAIN MENU                       ║\n";
        setColor(8);
        cout << "  ║            Logged in as: ";
        setColor(15);
        cout << left << setw(30) << currentUser->getName();
        setColor(8);
        cout << "║\n";
        setColor(14);
        cout << "  ╠══════════════════════════════════════════════════════╣\n";
        setColor(7);

        if (currentUser->isAdmin()) {
            cout << "  ║   [1]  Admin Panel  (Manage & View Content)         ║\n";
            cout << "  ║   [2]  Logout                                        ║\n";
            cout << "  ║   [3]  Exit System                                   ║\n";
        } else {
            cout << "  ║   [1]  Learning Section  (Read Chapters)             ║\n";
            cout << "  ║   [2]  Trivia Section    (Take Quizzes)              ║\n";
            cout << "  ║   [3]  My Scores                                     ║\n";
            cout << "  ║   [4]  Logout                                        ║\n";
            cout << "  ║   [5]  Exit System                                   ║\n";
        }
        setColor(14);
        cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
        setColor(7);

        string choice;
        while (true) {
            setColor(14);
            cout << "  Choose > ";
            setColor(15);
            getline(cin, choice);
            trim(choice);
            setColor(7);

            bool valid = false;
            if (currentUser->isAdmin()) {
                if (choice == "1" || choice == "2" || choice == "3") valid = true;
            } else {
                if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") valid = true;
            }

            if (valid) break;
            respond("Invalid choice. Please enter a number from the menu above.");
        }

        if (currentUser->isAdmin()) {
            if      (choice == "1") adminMode();
            else if (choice == "2") { login(); return; }
            else if (choice == "3") { respond("Goodbye!"); break; }
        } else {
            if      (choice == "1") learningMode();
            else if (choice == "2") triviaMode();
            else if (choice == "3") {
                clearConsole();
                scoreManager.showScores();
                setColor(8); cout << "\n  Press Enter to return to menu..."; setColor(7);
                string tmp; getline(cin, tmp);
            }
            else if (choice == "4") { login(); return; }
            else if (choice == "5") { respond("Goodbye!"); break; }
        }
    }
}

// ─── LEARNING MODE ───────────────────────────────────────────────────────────
void ChatBot::learningMode() {
    clearConsole();
    printLearningHeader();
    setColor(7);
    cout << "  Commands:\n";
    setColor(11);
    cout << "  list               ";
    setColor(7); cout << "- Show all available chapters\n";
    setColor(11);
    cout << "  read [ChapterName] ";
    setColor(7); cout << "- Read a specific chapter\n";
    setColor(11);
    cout << "  clear              ";
    setColor(7); cout << "- Clear the screen\n";
    setColor(11);
    cout << "  back               ";
    setColor(7); cout << "- Return to Main Menu\n\n";

    COORD contentStart = getCursorPos(); // snapshot: clear will restore to here
    while (true) {
        divider();
        setColor(13);
        cout << "  Learning > ";
        setColor(15);
        string cmd;
        getline(cin, cmd);
        trim(cmd);
        string lowerCmd = cmd;
        toLower(lowerCmd);
        setColor(7);

        if (lowerCmd == "back" || lowerCmd == "menu") {
            break;
        } else if (lowerCmd == "clear") {
            clearFromRow(contentStart);
        } else if (lowerCmd == "list") {
            chapterManager.listChapters();
        } else if (lowerCmd.find("read ") == 0) {
            string chapter = cmd.substr(5);
            trim(chapter);
            if (chapter.empty()) {
                respond("Usage: read [ChapterName]  e.g.  read OOP");
            } else {
                chapterManager.readChapter(chapter);
            }
        } else if (lowerCmd == "help") {
            respond("Commands: 'list', 'read [name]', 'clear', 'back'");
        } else {
            respond("Unknown command. Try 'list', 'read [name]', 'clear', or 'back'.");
        }
    }
}

// ─── TRIVIA MODE ─────────────────────────────────────────────────────────────
void ChatBot::triviaMode() {
    clearConsole();
    printTriviaHeader();
    setColor(7);
    cout << "  Commands:\n";
    setColor(11);
    cout << "  list               ";
    setColor(7); cout << "- Show all available quizzes\n";
    setColor(11);
    cout << "  start [QuizName]   ";
    setColor(7); cout << "- Start a quiz\n";
    setColor(11);
    cout << "  clear              ";
    setColor(7); cout << "- Clear the screen\n";
    setColor(11);
    cout << "  back               ";
    setColor(7); cout << "- Return to Main Menu\n\n";

    COORD contentStart = getCursorPos(); // snapshot: clear will restore to here
    while (true) {
        divider();
        setColor(11);
        cout << "  Trivia > ";
        setColor(15);
        string cmd;
        getline(cin, cmd);
        trim(cmd);
        string lowerCmd = cmd;
        toLower(lowerCmd);
        setColor(7);

        if (lowerCmd == "back" || lowerCmd == "menu") {
            break;
        } else if (lowerCmd == "clear") {
            clearFromRow(contentStart);
        } else if (lowerCmd == "list") {
            quizManager.listQuizzes();
        } else if (lowerCmd.find("start ") == 0) {
            string course = cmd.substr(6);
            trim(course);
            if (course.empty()) {
                respond("Usage: start [QuizName]  e.g.  start OOP");
                continue;
            }

            string filename = (exeDir() / "Quizzes" / (course + ".txt")).string();
            Quiz q(course);
            q.loadQuestions(filename);

            if (q.getTotalQuestions() > 0) {
                clearConsole();
                printTriviaHeader();
                setColor(14);
                cout << "  Loading quiz: " << course << "  (" << q.getTotalQuestions() << " questions)\n\n";
                setColor(7);
                this_thread::sleep_for(chrono::milliseconds(500));

                int s = q.startQuiz();

                if (Student* student = dynamic_cast<Student*>(currentUser.get())) {
                    student->addScore(s);
                    scoreManager.saveScore(student->getName(), course, s, q.getTotalQuestions());
                }

                double percent = ((double)s / q.getTotalQuestions()) * 100;
                string perf = (percent >= 80 ? "Excellent!" : (percent >= 50 ? "Good Job!" : "Keep Practicing!"));
                int perfColor = (percent >= 80 ? 10 : (percent >= 50 ? 14 : 12));

                clearConsole();
                setColor(14);
                cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
                cout << "  ║                    QUIZ RESULTS                      ║\n";
                cout << "  ╠══════════════════════════════════════════════════════╣\n";
                setColor(7);
                cout << "  ║  Player  : " << left << setw(42) << currentUser->getName() << "║\n";
                cout << "  ║  Quiz    : " << left << setw(42) << course << "║\n";
                cout << "  ║  Score   : " << left << setw(42) << (to_string(s) + " / " + to_string(q.getTotalQuestions())) << "║\n";
                cout << "  ║  Percent : " << left << setw(42) << (to_string((int)percent) + "%") << "║\n";
                setColor(perfColor);
                cout << "  ║  Result  : " << left << setw(42) << perf << "║\n";
                setColor(14);
                cout << "  ╚══════════════════════════════════════════════════════╝\n\n";
                setColor(8);
                cout << "  Press Enter to continue...";
                setColor(7);
                string tmp; getline(cin, tmp);
                clearConsole();
                printTriviaHeader();
            } else {
                respond("Quiz '" + course + "' not found. Use 'list' to see available quizzes.");
            }
        } else if (lowerCmd == "help") {
            respond("Commands: 'list', 'start [name]', 'clear', 'back'");
        } else {
            respond("Unknown command. Try 'list', 'start [name]', 'clear', or 'back'.");
        }
    }
}

// ─── ADMIN MODE ──────────────────────────────────────────────────────────────
void ChatBot::adminMode() {
    clearConsole();
    printAdminHeader();
    setColor(7);
    cout << "  Commands:\n";
    setColor(12);
    cout << "  list chapters      ";  setColor(7); cout << "- List all chapters\n";
    setColor(12);
    cout << "  read [chapter]     ";  setColor(7); cout << "- Read a chapter\n";
    setColor(12);
    cout << "  add chapter        ";  setColor(7); cout << "- Create a new chapter\n";
    setColor(12);
    cout << "  delete chapter     ";  setColor(7); cout << "- Delete a chapter\n";
    setColor(12);
    cout << "  list quizzes       ";  setColor(7); cout << "- List all quizzes\n";
    setColor(12);
    cout << "  add quiz           ";  setColor(7); cout << "- Create a new quiz\n";
    setColor(12);
    cout << "  delete quiz        ";  setColor(7); cout << "- Delete a quiz\n";
    setColor(12);
    cout << "  scores             ";  setColor(7); cout << "- View all student scores\n";
    setColor(12);
    cout << "  clear              ";  setColor(7); cout << "- Clear the screen\n";
    setColor(12);
    cout << "  back               ";  setColor(7); cout << "- Return to Main Menu\n\n";

    COORD contentStart = getCursorPos(); // snapshot: clear will restore to here
    while (true) {
        divider();
        setColor(12);
        cout << "  Admin > ";
        setColor(15);
        string cmd;
        getline(cin, cmd);
        trim(cmd);
        string lowerCmd = cmd;
        toLower(lowerCmd);
        setColor(7);

        if (lowerCmd == "back" || lowerCmd == "menu") {
            break;
        } else if (lowerCmd == "clear") {
            clearFromRow(contentStart);
        } else if (lowerCmd == "list chapters") {
            chapterManager.listChapters();
        } else if (lowerCmd == "list quizzes") {
            quizManager.listQuizzes();
        } else if (lowerCmd.find("read ") == 0) {
            string chapter = cmd.substr(5);
            trim(chapter);
            chapterManager.readChapter(chapter);
        } else if (lowerCmd == "add chapter") {
            chapterManager.createChapter();
        } else if (lowerCmd == "delete chapter") {
            chapterManager.deleteChapter();
        } else if (lowerCmd == "add quiz") {
            quizManager.createQuiz();
        } else if (lowerCmd == "delete quiz") {
            quizManager.deleteQuiz();
        } else if (lowerCmd == "scores") {
            scoreManager.showScores();
        } else if (lowerCmd == "help") {
            respond("Commands: 'list chapters', 'list quizzes', 'read [chapter]', 'add chapter', 'delete chapter', 'add quiz', 'delete quiz', 'scores', 'clear', 'back'");
        } else {
            respond("Unknown command. Type 'help' to see available commands.");
        }
    }
}
