#include "modules.h"

int mainApp(User *user) {
	return (user->role == ROLE_ADMIN_VALUE || user->role == ROLE_SUPER_ADMIN_VALUE)
		? adminApp(user)
		: userApp(user);
}
int userApp(User *user) {
	int choice;
	while (1) {
		cout << "Login: " << user->login << '\n' <<
			"Choose what you want:\n"
			" 1.view all data about workers\n"
			" 2.calculate the wages of all employees for a certain period of time\n"
			" 3.search data about workers\n"
			" 4.sort data about workers\n"
			" 5.logout(back to auth)\n"
			" 0.exit\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return EXIT_OPTION;
		case 1:
			viewAllWorkers();
			break;
		case 2:
			calcAndCoutSalariesForRange();
			break;
		case 3:
			searchWorkers(choice);
			break;
		case 4:
			sortWorkers(choice);
			break;
		case 5:
		{
			int choice;
			User *user = new User;
			while (auth(choice, user));
			return EXIT_OPTION;
		}
		default:
			cout << "Unknown option: " << choice << '\n';
		}

		if (choice != EXIT_OPTION)
			doPauseAndCls();
	}
}
int adminApp(User *user) {
	int choice;
	while (1) {
		cout << "Login: " << user->login << '\n' <<
			"Choose what you want:\n"
			" 1.work with workers\n"
			" 2.work with users\n"
			" 3.logout(back to auth)\n"
			" 0.exit\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return EXIT_OPTION;
		case 1:
			while(adminAppWorkers(user, choice));
			break;
		case 2:
		{
			while(adminAppUsers(user, choice));
			break;
		}
		case 3:
		{
			User *user = new User;
			while (auth(choice, user));
			return EXIT_OPTION;
		}
		default:
			cout << "Unknown option: " << choice << '\n';
		}

		if (choice != EXIT_OPTION)
			doPauseAndCls();
	}
}
int adminAppWorkers(User *user, int &choice) {
	while (1) {
		cout << "Login: " << user->login << '\n' <<
			"Choose what you want:\n"
			" 1.add worker\n"
			" 2.view all data about workers\n"
			" 3.edit worker info\n"
			" 4.remove worker info\n"
			" 5.calculate the wages of all workers for a certain period of time\n"
			" 6.search data about workers\n"
			" 7.sort data about workers\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return EXIT_OPTION;
		case 1:
			addWorker();
			break;
		case 2:
			viewAllWorkers();
			break;
		case 3:
			editWorker();
			break;
		case 4:
			deleteWorker();
			break;
		case 5:
			calcAndCoutSalariesForRange();
			break;
		case 6:
			searchWorkers(choice);
			break;
		case 7:
		{
			sortWorkers(choice);
			break;
		}
		default:
			cout << "Unknown option: " << choice << '\n';
		}

		if (choice != EXIT_OPTION)
			doPauseAndCls();
	}
}
int adminAppUsers(User *user, int &choice) {
	while (1) {
		cout << "Login: " << user->login << '\n' <<
			"Choose what you want:\n"
			" 1.add user\n"
			" 2.view all data about users\n"
			" 3.edit user\n"
			" 4.remove user\n"
			" 5.get user access to resource\n"
			" 6.search data about workers\n"
			" 7.sort data about workers\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return EXIT_OPTION;
		case 1:
			addUser(user->role);
			break;
		case 2:
			viewAllUsers();
			break;
		case 3:
			editUser(user);
			break;
		case 4:
			deleteUser(user);
			break;
		case 5:
			enableUser(user);
			break;
		case 6:
			searchUsers(choice);
			break;
		case 7:
			sortUsers(choice);
			break;
		default:
			cout << "Unknown option: " << choice << '\n';
		}

		if (choice != EXIT_OPTION)
			doPauseAndCls();
	}
}
void initUsersFile() {
	User *user = new User;

	strcpy(user->login, "admin");

	hash <string> hash;
    unsigned int pass = hash(SALT + "Qwerty1");
	user->pass = pass;

	user->role = ROLE_SUPER_ADMIN_VALUE;
	user->access = AVAILABLE;

	insertUser(user);
}
void init() {
	ifstream finUsers(USERS, ios::binary | ios::in);

	if (!finUsers.is_open()) {
	   initUsersFile();
	}
	finUsers.close();
}