#include "../include/User.h"

User::User(string n) : name(n) {}
// Getter for the user's name
string User::getName() const {
    return name;
}
