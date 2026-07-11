#ifndef CHATBOT_H
#define CHATBOT_H

#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "QuizManager.h"
#include "ScoreManager.h"
#include "ChapterManager.h"
#include <string>
#include <memory>// for unique_ptr

using namespace std;
//Polymorphism used here: meaning different forms of the user class (student or admin) 
class ChatBot {
private:
	unique_ptr<User> currentUser;// used to store either a Student or Admin object, leveraging polymorphism
    QuizManager quizManager;
    ScoreManager scoreManager;
    ChapterManager chapterManager;
    
    void typingAnimation(const string& text) const;
    void printWelcomeScreen() const;
    void printLearningHeader() const;
    void printTriviaHeader() const;
    void printAdminHeader() const;
    void clearConsole() const;
    
    void login();
    void mainMenu();
    void learningMode();
    void triviaMode();
    void adminMode();

public:
    ChatBot();
    void start();
    void respond(const string& text) const;
    void respond() const; 
};

#endif
