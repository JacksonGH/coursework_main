#include "work_with_users.h"

void viewAllUsers() {
	User *users = new User[MAX_ARRAY_SIZE];
	int num = 0;
	readAllUsers(users, num);
	coutUsers(users, num);
}
bool readAllUsers(User *users, int &num) {
	ifstream fin(USERS, ios::binary | ios::in);

	int m = 0;
	if (!fin.is_open()) {
		return 1;
	}
	else {
		while (!fin.eof()) {
			fin.read((char*)&users[m], sizeof users[m]);
			m++;
		}
		fin.close();
		m--;
	}
	num = m;

	return 0;
}
void coutUsers(User *users, int num) {
	if (num <= 0) {
		cout << "No data.\n";
		return;
	}

	cout << left << setw(20) << "Login"
		<< setw(10) << "Role"
		<< setw(10) << "Access"
		<< '\n';
	cout << setfill('-') << setw(40) << "" << setfill(' ') << '\n';

	for (int i = 0; i < num; i++) {
		cout << setw(20) << users[i].login
			<< setw(10) << (
			(users[i].role == ROLE_ADMIN_VALUE || users[i].role == ROLE_SUPER_ADMIN_VALUE) ? ROLE_ADMIN_NAME : ROLE_USER_NAME
				)
			<< setw(10) << (
			(users[i].access == AVAILABLE) ? HAS_ACCESS : HAS_NOT_ACCESS
				)
			<< '\n';
	}
}
void coutUser(User user) {
	cout << setw(20) << left << user.login
		<< setw(10) << (
		(user.role == ROLE_ADMIN_VALUE) ? ROLE_ADMIN_NAME : ROLE_USER_NAME
			)
		<< setw(10) << (
		(user.access == AVAILABLE) ? HAS_ACCESS : HAS_NOT_ACCESS
			)
		<< '\n' << setfill('-') << setw(80) << "" << setfill(' ') << '\n';
}
int addUser(int access) {
	User *user = new User;
	if (0 != getCredentials(user)) {
		return 1;
	}

	if (access == ROLE_SUPER_ADMIN_VALUE) {
		cout << "Enter user role(available options: user or admin).\n";
		user->role = getRole();
	}
	else {
		user->role = ROLE_USER_VALUE;
	}

	user->access = AVAILABLE;

	insertUser(user);
	cout << "Successful added new " << (user->role == ROLE_ADMIN_VALUE ? ROLE_ADMIN_NAME : ROLE_USER_NAME) << ".\n";

	return 0;
}
void searchUsers(int &choice) {
	do {
		cout << "Choose parameter for search:\n"
			" 1.login\n"
			" 2.access\n"
			" 3.role\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");
	} while (choice < 0 || choice > 3);

	if (choice != 0) {
		int num;
		User *users = new User[MAX_ARRAY_SIZE];
		readAllUsers(users, num);

		logicSearchUsers(users, num, choice);
	}
}
void logicSearchUsers(User *users, int num, int choice) {
	switch (choice) {
	case 1:
	{
		User foundUser = searchByLogin(users, num);
		if (num == 0) {
			cout << "No data.\n";
			return;
		}
		coutUser(foundUser);

		return;
	}
	case 2:
	{
		User *foundUsers = searchByAccess(users, num);
		coutUsers(foundUsers, num);

		return;
	}
	case 3:
	{
		User *foundUsers = searchByRole(users, num);
		coutUsers(foundUsers, num);

		return;
	}
	default:
		throw exception();
	}
}
User searchByLogin(User *users, int &num) {
	char *login = new char[MAX_STR_SIZE];
	cout << "Enter login:\n";
	cin.getline(login, MAX_STR_SIZE);

	int foundNum = 0;

	User foundUser;
	for (int i = 0; i < num; i++) {
		if (!strcmp(users[i].login, login)) {
			foundUser = users[i];
			foundNum++;
			break;
		}
	}

	num = foundNum;
	return foundUser;
}
User *searchByAccess(User *users, int &num) {
	cout << "Enter access(available options: 1(has access) or 0(no access)).\n";
	int access = getAccess();
	
	User *foundUsers = new User[MAX_ARRAY_SIZE];
	int foundNum = 0;

	for (int i = 0; i < num; i++) {
		if (access == users[i].access) {
			foundUsers[foundNum++] = users[i];
		}
	}

	num = foundNum;
	return foundUsers;
}
User *searchByRole(User *users, int &num) {
	cout << "Enter user role(available options: user or admin).\n";
	int role = getRole();

	User *foundUsers = new User[MAX_ARRAY_SIZE];
	int foundNum = 0;

	for (int i = 0; i < num; i++) {
		if (role == users[i].role) {
			foundUsers[foundNum++] = users[i];
		}
	}

	num = foundNum;
	return foundUsers;
}
void sortUsers(int &choice) {
	do {
		cout << "Choose parameter for sort:\n"
			" 1.login\n"
			" 2.access\n"
			" 3.role\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");
	} while (choice < 0 || choice > 3);

	if (choice == EXIT_OPTION)
		return;

	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	readAllUsers(users, num);

	logicSortUsers(users, num, choice);
}
void logicSortUsers(User *users, int num, int &sortFrom) {
	int sortBy = sortFrom;
	do {
		cout << "Enter from sort:\n"
			" 1.[1-9][a-z]\n"
			" 2.[9-1][z-a]\n"
			" 0.back\n";
		sortFrom = readIntNum();
	} while (sortFrom < 0 || sortFrom > 2);
	system("clear");

	if (sortFrom == EXIT_OPTION)
		return;

	switch (sortBy) {
	case 1:
	{
		sortByLogin(users, num, sortFrom);

		break;
	}
	case 2:
	{
		sortByAccess(users, num, sortFrom);

		break;
	}
	case 3: {
		sortByRole(users, num, sortFrom);

		break;
	}
	default:
		throw exception();
	}

	coutUsers(users, num);
}
void sortByLogin(User *users, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (strcmp(users[i].login, users[i + 1].login) > 0) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (strcmp(users[i].login, users[i + 1].login) < 0) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
void sortByAccess(User *users, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (getAccessNameFromValue(users[i].access) > getAccessNameFromValue(users[i + 1].access)) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (getAccessNameFromValue(users[i].access) < getAccessNameFromValue(users[i + 1].access)) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
void sortByRole(User *users, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (getRoleNameFromValue(users[i].role) > getRoleNameFromValue(users[i + 1].role)) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (getRoleNameFromValue(users[i].role) < getRoleNameFromValue(users[i + 1].role)) {
					swap(users[i], users[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
string getAccessNameFromValue(int access) {
	return access == AVAILABLE ? HAS_ACCESS : HAS_NOT_ACCESS;
}
string getRoleNameFromValue(int role) {
	switch (role) {
	case ROLE_USER_VALUE:
		return ROLE_USER_NAME;
	case ROLE_ADMIN_VALUE:
		return ROLE_ADMIN_NAME;
	case ROLE_SUPER_ADMIN_VALUE:
		return ROLE_SUPER_ADMIN_NAME;
	default:
		throw exception();
	}
}
int editUser(User *authUser) {
	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	readAllUsers(users, num);

	User user;

	cout << "Enter login:\n";
	strcpy(user.login, getLogin());

	int findAt = checkUserLogin(users, num, user);
	if (findAt < 0) {
		cout << "User with this login not found.\n";
		return 1;
	}

	if (!checkCan(authUser->role, user.role)) {
		cout << "You can't change info of this user.\n";
		return 1;
	}

	system("clear");

	int choice;
	bool changed = false;
	while (1) {
		coutUser(user);
		cout << "Choose what you want:\n"
			" 1.confirm\n"
			" 2.edit\n"
			" 3.cancel\n";
		choice = readIntNum();
		system("clear");

		if (choice == EDIT) {
			changed = true;
			user = editEnterUser(user, authUser);
		}
		else if (choice == CONFIRM) {
			break;
		}
		else if (choice == CANCEL) {
			cout << "Edit user canceled.\n";
			return 0;
		}
	}

	if (!changed) {
		cout << "Nothing changed.\n";
		return 1;
	}

	for (int i = 0; i < num; i++) {
		if (i == findAt)
			continue;
		if (!strcmp(users[i].login, user.login)) {
			cout << "This is login of another user.\n";
			return 1;
		}
	}

	updateUserInfo(user, findAt);
	cout << "User info changed successfully.\n";

	return 0;
}
int checkUserLogin(User *users, int &num, User &user) {
	int findAt = -1;
	for (int i = 0; i < num; i++) {
		if (!strcmp(users[i].login, user.login)) {
			findAt = i;
			user = users[i];
			break;
		}
	}
	return findAt;
}
User editEnterUser(User user, User *authUser) {
	int choice;
	while (1) {
		coutUser(user);
		cout << "Choose what you want edit:\n"
			" 1.Login\n"
			" 2.Pass\n"
			" 3.Access\n"
			" 4.Role\n"
			" 0.exit\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return user;
		case 1:
		{
			cout << "Enter login:\n";

			char *login = getLogin();
			if (0 != checkLoginUnique(login)) {
				doPauseAndCls();
			} else {
				strcpy(user.login, login);
			}

			system("clear");
			break;
		}
		case 2:
			cout << "Enter pass:\n";
			user.pass = getPass();
			system("clear");
			break;
		case 3:
			cout << "Enter access(1 if has ot 0 if hasn't):\n";
			user.access = getAccess();
			system("clear");
			break;
		case 4:
		{
			cout << "Enter role(admin or user):\n";
			int role = getRole();

			if (!checkCan(authUser->role, role)) {
				cout << "You can't change user role to this role.\n";
				doPauseAndCls();
				break;
			}

			user.role = role;
			system("clear");
			break;
		}
		default:
			cout << "Unknown option: " << choice << '\n';
		}
	}
}
void updateUserInfo(User user, int findAt) {
	fstream in(USERS, ios::binary | ios::in | ios::out);
	in.seekp(sizeof user * findAt);
	in.write((char*)&user, sizeof user);
	in.close();
}
char *getLogin() {
	char *login = new char[MAX_STR_SIZE];
	do {
		cin.getline(login, MAX_STR_SIZE);
	} while (!isValidLogin(login));

	return login;
}
int getPass() {
	char t, *pass = new char[MAX_STR_SIZE];

	do {
		for (int i = 0;;) {
			t = custom_getch();
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t >= '0' && t <= '9' || t == '_') {
				pass[i++] = t;
				cout << "*";
			}
			if (127 == t &&  i >= 1) {
				cout << "\b \b";
				i--;
			}
			if (t == '\n') {
				pass[i] = '\0';
				break;
			}
		}
		cout << '\n';
	} while (!isValidPass(pass));

	hash <string> hash;
	return hash(SALT + pass);
}
int getAccess() {
	int access;
	do {
		access = readPosIntNum();
	} while (access != AVAILABLE && access != NOT_AVAILABLE);

	return access;
}
int getRole() {
	string role;
	do {
		getline(cin, role);
	} while (find(begin(AVAILABLE_ROLES), end(AVAILABLE_ROLES), role) == end(AVAILABLE_ROLES));

	return getRoleValueFromName(role);
}
int getRoleValueFromName(string role) {
	if (role == ROLE_USER_NAME)
		return ROLE_USER_VALUE;
	else if (role == ROLE_ADMIN_NAME)
		return ROLE_ADMIN_VALUE;
	else if (role == ROLE_SUPER_ADMIN_NAME)
		return ROLE_SUPER_ADMIN_VALUE;

	throw exception();
}
int deleteUser(User *authUser) {
	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	readAllUsers(users, num);

	User user;

	cout << "Enter login:\n";
	strcpy(user.login, getLogin());

	int findAt = checkUserLogin(users, num, user);
	if (findAt < 0) {
		cout << "User with this login not found.\n";
		return 1;
	}

	if (!checkCan(authUser->role, user.role)) {
		cout << "You can't delete user with this role.\n";
		return 1;
	}

	system("clear");

	coutUser(user);
	if (!confirmDelete()) {
		cout << "Deleted of user canceled.\n";
		return 0;
	}

	deleteUserInArray(users, num, findAt);
	rewriteUsersFile(users, num);
	cout << "User successfully deleted.\n";

	return 0;
}
void rewriteUsersFile(User *users, int num) {
	ofstream fout(USERS, ios::binary | ios::out);
	fout.write((char*)&users[0], sizeof users[0] * num);
	fout.close();
}
int enableUser(User *authUser) {
	User user;
	cout << "Enter login:\n";
	strcpy(user.login, getLogin());

	int num;
	User *users = new User[MAX_ARRAY_SIZE];
	readAllUsers(users, num);

	int findAt = checkUserLogin(users, num, user);
	if (findAt < 0) {
		cout << "User with this login not found.\n";
		return 1;
	}

	if (!checkCan(authUser->role, user.role)) {
		cout << "You can't enable this user\n";
		return 1;
	}

	system("clear");

	if (user.access == AVAILABLE) {
		cout << "User " << HAS_ACCESS << " to the resource.\n";
		return 1;
	}

	user.access = AVAILABLE;
	updateUserInfo(user, findAt);
	cout << "Successfully changed user access.\n";

	return 0;
}
void deleteUserInArray(User *users, int &num, int findAt) {
	for (int i = findAt; i + 1 < num; i++) {
		users[i] = users[i + 1];
	}
	num--;
}