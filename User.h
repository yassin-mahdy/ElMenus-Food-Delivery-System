/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User
{
protected:
    string UserId;
    string name;
    string PhoneNumber;
    static int totalUsers;

public:
    User();                                   // default constructor
    User(string Id, string n, string phonen); // paramatarized constructor

    // pure virtual functions
    virtual void displayInfo() const = 0;
    virtual double calculateEarnings() const = 0;

    // static function that return the number of total users
    static int getTotalUsers() { return totalUsers; }

    // getters
    string getUserID() const { return UserId; }

    string getName() const { return name; }

    string getPhoneNumber() const { return PhoneNumber; }

    // virtual destructor (needed to for the dervide class destructor to run)
    virtual ~User() { cout << "User is destroyed" << endl; }
};

#endif
