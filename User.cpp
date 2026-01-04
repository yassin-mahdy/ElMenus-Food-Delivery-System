/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#include "User.h"

// Static variable initiation
int User::totalUsers = 0;

User::User() : UserId(""), name(""), PhoneNumber("")
{
    totalUsers++;
}
User::User(string Id, string n, string phonen) : UserId(Id), name(n), PhoneNumber(phonen)
{
    totalUsers++;
}