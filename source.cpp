#define _CRT_SECURE_NO_WARNINGS
#include "modules.h"

int main()
{
    init();

	//auth
	int choice;
	User *user = new User;
	while (auth(choice, user));

	if (choice == EXIT_OPTION || !hasAccess(user))
		return 0;

	//modules
	while (mainApp(user));

	return 0;
}