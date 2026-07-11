#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string name;
public:
    User(string n = "Unknown");
    virtual ~User() = default;
    virtual void display() const = 0; // Pure virtual function for abstraction
    virtual bool isAdmin() const = 0;
    string getName() const;
};

#endif
