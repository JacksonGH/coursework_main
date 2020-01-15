#pragma once
#include "common.h"
#include "auth.h"

const string USERS = "users.bin";

void viewAllUsers();
bool readAllUsers(User *, int &);
void coutUsers(User *, int);
void coutUser(User);

int addUser(int);
void searchUsers(int &);
void sortUsers(int &);
int editUser(User *);
int deleteUser(User *);

void logicSearchUsers(User *, int, int);
void logicSortUsers(User *, int, int &);

User searchByLogin(User *, int &);
User *searchByAccess(User *, int &);
User *searchByRole(User *, int&);

void sortByLogin(User *, int, int);
void sortByAccess(User *, int, int);
void sortByRole(User *, int, int);

int checkUserLogin(User *, int &, User &);
User editEnterUser(User, User *);
void updateUserInfo(User, int);
void rewriteUsersFile(User *, int);
void deleteUserInArray(User *, int &, int);
int enableUser(User *);

char *getLogin();
int getPass();
int getAccess();
int getRole();

int getRoleValueFromName(string);

string getAccessNameFromValue(int);
string getRoleNameFromValue(int);