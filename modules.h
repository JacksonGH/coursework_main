#pragma once
#include "work_with_workers.h"
#include "work_with_users.h"
#include "auth.h"

using namespace std;

int mainApp(User *);
int userApp(User *);
int adminApp(User *);
int adminAppWorkers(User *user, int &);
int adminAppUsers(User *user, int &);

void initUsersFile();
void init();