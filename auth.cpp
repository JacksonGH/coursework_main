#include "auth.h"

int auth(int &choice, User *user) {
	while (1) {
		cout << "Choose what you want:\n"
			" 1.login\n"
			" 2.register\n"
			" 0.exit\n";
		choice = readIntNum();
		system("clear");

		int resultCode;
		switch (choice)
		{
		case LOGIN:
			resultCode = loginUser(user);
			break;
		case REGISTER: 
			resultCode = registerUser(user);
			break;
		case EXIT_OPTION:
			resultCode = EXIT_OPTION;
		}
		doPauseAndCls();

		return resultCode;
	}
}
int loginUser(User *user) {
	getLoginAndPass(user);

	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	if (readAllUsers(users, num)) {
		cout << "File with users doesn't exist.\n";
		return 1;
	}

	for (int i = 0; i < num; i++) {
		if (strcmp(users[i].login, user->login)) continue;

		if (users[i].pass == user->pass) {
			if (users[i].access == NOT_AVAILABLE) {
				cout << ACCESS_DENIED;
				return 1;
			}

			cout << "Login successful.\n";
			user->role = users[i].role;
			user->access = users[i].access;
			return 0;
		}
		
		cout << "Wrong password.\n";
		return 1;
	}

	cout << "Unknown login.\n";
	return 1;
}
int getCredentials(User *user) {
	getLoginAndPass(user);

	return checkLoginUnique(user->login);
}
int registerUser(User *user) {
	if (getCredentials(user) != 0) {
		return 1;
	}

	insertUser(user);
	cout << "Successful registration.\n"
		<< ACCESS_DENIED;

	return 0;
}
void getLoginAndPass(User *user) {
	cout << "Enter login:\n";
	strcpy(user->login, getLogin());

	cout << "Enter password:\n";
	user->pass = getPass();
}
void insertUser(User *user) {
	ofstream fadd(USERS, ios::binary | ios::app);
	fadd.write((char*) user, sizeof *user);
	fadd.close();
}
bool isValidLogin(char *str) {
	cmatch result;
	regex regular("^[a-zA-Z][a-zA-Z0-9-_\\.]{1,19}$");
	bool valid = std::regex_match(str, result, regular);
	if (!valid)
		cout << "Login must be a string(2-20 characters long), which can contain letters or numbers, the first character must be a letter.\n";
	return valid;
}
bool isValidPass(char *str) {
	cmatch result;
	regex regular("(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])[0-9a-zA-Z_]{6,20}");
	bool valid = std::regex_match(str, result, regular);
	if (!valid)
		cout << "Password must be a string, 6-20 characters long, which can contain letters, numbers or an underscore(! must contain at least uppercase letter, lowercase letter and number).\n";
	return valid;
}
int checkLoginUnique(char *login) {
	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	readAllUsers(users, num);

	for (int i = 0; i < num; i++) {
		if (!strcmp(users[i].login, login)) {
			cout << "Login already taken.\n";

			return 1;
		}
	}

	return 0;
}