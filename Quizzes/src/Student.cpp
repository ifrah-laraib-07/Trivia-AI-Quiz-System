#include "../include/Student.h"
#include <iostream>
// Constructor initializes the student's name using the User constructor and sets initial score to 0
Student::Student(string n) : User(n), score(0) {}

void Student::setScore(int s) {
    score = s;
}

void Student::addScore(int s) {
    score += s;
}

int Student::getScore() const {
    return score;
}

void Student::display() const {
    cout << "Student: " << name << " | Score: " << score << endl;
}

bool Student::isAdmin() const {
    return false;
}
