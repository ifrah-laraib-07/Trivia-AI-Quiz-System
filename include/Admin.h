#ifndef ADMIN_H// for Admin class definition
#define ADMIN_H// for defining the Admin class, which inherits from User

#include "User.h"// for the base User class
#include <string>

using namespace std;
//inherited from user class
class Admin : public User {
public:
    Admin(string n = "Admin");
    void display() const override;
    bool isAdmin() const override;
};

#endif
