#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <string>

using namespace std;
// inherited from user class
class Student : public User {
private:
    int score;
public:
    Student(string n = "Student");
    void setScore(int s);
    void addScore(int s);
    int getScore() const;
    void display() const override;
    bool isAdmin() const override;
};

#endif
