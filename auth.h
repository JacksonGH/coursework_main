#pragma once
#include "common.h"
#include "work_with_users.h"

using namespace std;

const string ACCESS_DENIED = "You get access to the resource as soon as the administrator confirms your account\n";

const int LOGIN = 1;
const int REGISTER = 2;

const string SALT = "kasd83mfds";

int auth(int &choice, User *user);
int loginUser(User *);
int registerUser(User *);

int getCredentials(User *);
void getLoginAndPass(User *);

void insertUser(User *);

bool isValidLogin(char *);
bool isValidPass(char *);
int checkLoginUnique(char *);