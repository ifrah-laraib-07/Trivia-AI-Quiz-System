#include "../include/Admin.h"
#include <iostream>

Admin::Admin(string n) : User(n) {}

void Admin::display() const {
    cout << "Administrator: " << name << endl;
}

bool Admin::isAdmin() const {
    return true;
}
