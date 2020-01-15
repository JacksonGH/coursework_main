#include "work_with_workers.h"

void calcAndCoutSalariesForRange() {
	cout << "Input date range(valid ranges: 1.2, 0.18, 2.0)\n";
	char range[DATE_SIZE];
	strcpy(range, getRange());

	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	logicCalcAndCoutSalariesForRange(workers, num, range);
}
double getWorkerSalary(Worker worker) {
	int overtime = 0;
	if (worker.work_hours > OVERTIME_RANGE) {
		overtime = worker.work_hours - OVERTIME_RANGE;
		worker.work_hours = OVERTIME_RANGE;
	}

	return worker.rate * (1 - TAX / 100) * (worker.work_hours + overtime * 2);
}
void logicCalcAndCoutSalariesForRange(Worker *workers, int num_workers, char *range) {
	Salary *salaries = new Salary[MAX_STR_SIZE];
	int num_salaries = 0;

	bool flag;
	for (int i = 0; i < num_workers; i++) {
		if (atof(workers[i].date) <= atof(range))
			continue;

		flag = false;
		for (int j = 0; j < num_salaries; j++) {
			if (salaries[j].pers_num == workers[i].pers_num) {
				flag = true;
				salaries[j].salary_per_range += getWorkerSalary(workers[i]);
				if (atof(workers[i].date) > atof(salaries[j].date)) {
					salaries[num_salaries].salary_per_month = getWorkerSalary(workers[i]);
				}

				break;
			}
		}

		if (!flag) {
			strcpy(salaries[num_salaries].fio, workers[i].fio);
			strcpy(salaries[num_salaries].date, workers[i].date);
			salaries[num_salaries].pers_num = workers[i].pers_num;
			salaries[num_salaries].salary_per_month = getWorkerSalary(workers[i]);
			salaries[num_salaries].salary_per_range += getWorkerSalary(workers[i]);
			num_salaries++;
		}
	}

	coutWorkersSalaries(salaries, num_salaries);
}
void coutWorkersSalaries(Salary *salaries, int num) {
	if (num == 0) {
		cout << "No data.\n";
		return;
	}

	cout << left << setw(18) << "Personal number"
		<< setw(32) << "For month: salary per month"
		<< setw(18) << "Salary per range" << '\n'
		<< setfill('-') << setw(80) << "" << setfill(' ') << '\n';
	for (int i = 0; i < num; i++) {
		cout << setw(80) << left << salaries[i].fio << '\n'
			<< setw(18) << salaries[i].pers_num
			<< salaries[i].date << ": " << setw(23) << salaries[i].salary_per_month
			<< setw(28) << salaries[i].salary_per_range << '\n'
			<< setfill('-') << setw(80) << "" << setfill(' ') << '\n';
	}
}
void searchWorkers(int &choice) {
	do {
		cout << "Choose parameter for search:\n"
			" 1.personal number\n"
			" 2.date\n"
			" 3.fio\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");
	} while (choice < 0 || choice > 3);

	if (choice == 0)
		return;

	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	logicSearchWorkers(workers, num, choice);
}
void logicSearchWorkers(Worker *workers, int num, int choice) {
	Worker *foundWorkers;

	switch (choice) {
	case 1:
		foundWorkers = searchByPersNum(workers, num);

		break;
	case 2:
		foundWorkers = searchByDate(workers, num);

		break;
	case 3:
		foundWorkers = searchByFio(workers, num);

		break;
	default:
		throw exception();
	}

	coutWorkers(foundWorkers, num);
}
Worker *searchByPersNum(Worker *workers, int &num) {
	cout << "Enter personal number:\n";
	int pers_num = readPosIntNum();

	Worker *foundWorkers = new Worker[MAX_ARRAY_SIZE];
	int foundNum = 0;

	for (int i = 0; i < num; i++) {
		if (workers[i].pers_num == pers_num) {
			foundWorkers[foundNum++] = workers[i];
		}
	}

	num = foundNum;
	return foundWorkers;
}
Worker *searchByDate(Worker *workers, int &num) {
	char date[DATE_SIZE];

	cout << "Enter date:\n";
	strcpy(date, getWorkerDate());

	Worker *foundWorkers = new Worker[MAX_ARRAY_SIZE];
	int foundNum = 0;

	for (int i = 0; i < num; i++) {
		if (!strcmp(workers[i].date, date)) {
			foundWorkers[foundNum++] = workers[i];
		}
	}

	num = foundNum;
	return foundWorkers;
}
Worker *searchByFio(Worker *workers, int &num) {
	FIO fio = getFioStructForSearch();

	Worker *foundWorkers = new Worker[MAX_ARRAY_SIZE];
	int foundNum = 0;

	for (int i = 0; i < num; i++) {
		if (likeFio(fio, getStructFromStr(workers[i].fio))) {
			foundWorkers[foundNum++] = workers[i];
		}
	}

	num = foundNum;
	return foundWorkers;
}
void sortWorkers(int &choice) {
	do {
		cout << "Choose parameter for sort:\n"
			" 1.personal number\n"
			" 2.date\n"
			" 3.fio\n"
			" 0.back\n";
		choice = readIntNum();
		system("clear");
	} while (choice < 0 || choice > 3);

	if (choice == EXIT_OPTION)
		return;

	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	logicSortWorkers(workers, num, choice);
}
void logicSortWorkers(Worker *workers, int num, int &sortFrom) {
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
		sortByPersNum(workers, num, sortFrom);

		break;
	}
	case 2:
	{
		sortByDate(workers, num, sortFrom);

		break;
	}
	case 3: {
		sortByFio(workers, num, sortFrom);

		break;
	}
	default:
		throw exception();
	}

	coutWorkers(workers, num);
}
void sortByPersNum(Worker *workers, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (workers[i].pers_num > workers[i + 1].pers_num) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (workers[i].pers_num < workers[i + 1].pers_num) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
void sortByDate(Worker *workers, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (atof(workers[i].date) > atof(workers[i + 1].date)) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (atof(workers[i].date) < atof(workers[i + 1].date)) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
void sortByFio(Worker *workers, int num, int sortFrom) {
	bool flag;

	if (sortFrom == 1) {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (strcmp(workers[i].fio, workers[i + 1].fio) > 0) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
	else {
		do {
			flag = false;
			for (int i = 0; i < num - 1; i++) {
				if (strcmp(workers[i].fio, workers[i + 1].fio) < 0) {
					swap(workers[i], workers[i + 1]);
					flag = true;
				}
			}
		} while (flag);
	}
}
void viewAllWorkers() {
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	int num = 0;
	readAllWorkers(workers, num);
	coutWorkers(workers, num);
}
void coutWorkers(Worker *workers, int num) {
	if (num <= 0) {
		cout << "No data.\n";
		return;
	}

	cout << left << setw(18) << "Personal Number"
		<< setw(10) << "Date"
		<< setw(13) << "Work hours"
		<< setw(10) << "Rate"
		<< '\n' << setfill('-') << setw(80) << "" << setfill(' ') << '\n';

	for (int i = 0; i < num; i++)
		cout << setw(80) << workers[i].fio << '\n'
		<< setw(18) << workers[i].pers_num
		<< setw(10) << workers[i].date
		<< setw(13) << workers[i].work_hours
		<< setw(10) << workers[i].rate << '\n'
		<< setfill('-') << setw(80) << "" << setfill(' ') << '\n';
}
void coutWorker(Worker worker) {
	cout << setw(80) << left << worker.fio << '\n'
		<< setw(18) << worker.pers_num
		<< setw(10) << worker.date
		<< setw(13) << worker.work_hours
		<< setw(10) << worker.rate
		<< '\n' << setfill('-') << setw(80) << "" << setfill(' ') << '\n';
}
char *getRange() {
	char *date = new char[MAX_STR_SIZE];
	do {
		cin >> date;
	} while (!isValidRange(date));

	Date range, from, now = nowDate();
	range.year = atoi(strtok(date, "."));
	range.month = atoi(strtok(NULL, "."));

	if (range.month > 12) {
		range.year += range.month / 12;
		range.month = range.month % 12;
	}

	from.year = now.year - range.year;
	int diff_month = now.month - range.month;
	if (diff_month < 0) {
		from.year--;
		from.month = 12 - fabs(diff_month);
	}
	else
		from.month = diff_month;

	char *from_str = new char[DATE_SIZE];
	(from.month >= 10)
		? sprintf(from_str, "%d.%d", from.year, from.month)
		: sprintf(from_str, "%d.0%d", from.year, from.month);

	return from_str;
}
bool isValidRange(char *str) {
	cmatch result;
	regex regular("^[0-9]\\.[0-9][0-9]?$");
	bool valid = regex_match(str, result, regular);
	if (!valid)
		cout << "Wrong date format.\n";
	return valid;
}
int workersFixture() {
	int num = 6;
	Worker *workers = new Worker[num];

	string arr_fio[] = {
		"Andrew Brown",
		"Pavel Petrov",
		"Ivan I P",
		"Ivan Ivanovich Ivanov",
		"New Try"
	};
	int num_dates = 9;
	string arr_date[] = {
		"2019.05", "2019.04", "2019.03", "2019.02", "2019.01",
		"2018.12", "2018.11", "2018.10", "2018.09"
	};

	int numFromFile;
	Worker *workersFromFile = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workersFromFile, numFromFile);

	int rate = 10, work_hours = 140, pers_num = 2143;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num_dates; j++) {
			strcpy(workers[i].fio, arr_fio[i].c_str());
			strcpy(workers[i].date, arr_date[j].c_str());
			workers[i].pers_num = pers_num;
			workers[i].work_hours = work_hours;
			workers[i].rate = rate;

			insertWorker(workers[i]);

			work_hours += (j % 3 ? 7 : -10);
		}

		pers_num++;
		rate++;
	}

	return 0;
}
int addWorker() {
	Worker worker = getWorkerInfo();

	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	for (int i = 0; i < num; i++) {
		if (workers[i].pers_num == worker.pers_num && strcmp(workers[i].fio, worker.fio)) {
			cout << "You cannot create records with the same personal number and differents FIO.\n";
			doPauseAndCls();
			return 1;
		}
		if (workers[i].pers_num == worker.pers_num && !strcmp(workers[i].date, worker.date)) {
			cout << "You cannot create records with the same date for one worker.\n";
			doPauseAndCls();
			return 1;
		}
	}
	system("clear");

	int choice;
	while (1) {
		coutWorker(worker);
		cout << "Choose what you want:\n"
			" 1.confirm\n"
			" 2.edit\n"
			" 3.cancel\n";
		choice = readIntNum();
		system("clear");

		if (choice == EDIT)
			worker = editEnterWorker(worker);
		else if (choice == CONFIRM) {
			insertWorker(worker);
			cout << "Successful added worker info.\n";
			return 0;
		}
		else if (choice == CANCEL) {
			cout << "Added worker canceled.\n";
			return 0;
		}
	}
}
Worker editEnterWorker(Worker worker) {
	int choice;
	while (1) {
		coutWorker(worker);
		cout << "Choose what you want edit:\n"
			" 1.FIO\n"
			" 2.personal number\n"
			" 3.date\n"
			" 4.work hours\n"
			" 5.rate\n"
			" 0.exit\n";
		choice = readIntNum();
		system("clear");

		switch (choice) {
		case EXIT_OPTION:
			return worker;
		case 1:
			cout << "Enter FIO:\n";
			strcpy(worker.fio, getWorkerFIO());
			system("clear");
			break;
		case 2:
			cout << "Enter personal number:\n";
			worker.pers_num = readPosIntNum();
			system("clear");
			break;
		case 3:
			cout << "Enter year and month(! in format year.month):\n";
			strcpy(worker.date, getWorkerDate());
			system("clear");
			break;
		case 4:
			cout << "Enter work hours(! int number):\n";
			worker.work_hours = readPosIntNum();
			system("clear");
			break;
		case 5:
			cout << "Enter rate(! can be double number):\n";
			worker.rate = readPosDoubleNum();
			system("clear");
			break;
		default:
			cout << "Unknown option: " << choice << '\n';
		}
	}
}
Date nowDate() {
	struct tm localtime;
	time_t now = time(NULL);
	localtime_r(&now, &localtime);
	Date date;
	date.year = localtime.tm_year + 1900;
	date.month = localtime.tm_mon + 1;
	return date;
}
bool isValidDate(char *date) {
	cmatch result;
	regex regular("^([0-9]{4})\\.([0-9][0-9]?)$");
	if (!regex_match(date, result, regular)) {
		cout << "Wrong format.\n";
		return false;
	}

	Date now = nowDate();
	int year = atoi(result[1].str().c_str()),
		month = atoi(result[2].str().c_str()),
		rangeY = fabs(now.year - year),
		rangeM = fabs(now.month - month);

	if (rangeY >= 2 && rangeM > 0) {
		cout << "Wrong year(year must be a number not larger than the current year by 2 and not less than the current year by 2).\n";
		return false;
	}

	if (month < 1 || month > 12) {
		cout << "Wrong month(month must be a number from 1 to 12).\n";
		return false;
	}

	return true;
}
bool isValidFIO(char *str) {
	cmatch result;
	regex regular("^[A-Z][a-z]{0,18}(-[A-Z][a-z]{0,18})? {1}[A-Z][a-z]{0,18}( {1}[A-Z][a-z]{0,18})?$");
	bool valid = regex_match(str, result, regular);
	if (!valid)
		cout << "FIO must be a string, which can contain minimum surname and name(word cannot be more than 19, if the surname is compound then 38 excluding hyphens).\n";
	return valid;
}
char *getWorkerFIO() {
	char *fio = new char[MAX_STR_SIZE];
	do {
		cin.getline(fio, MAX_ARRAY_SIZE);
	} while (!isValidFIO(fio));
	return fio;
}
char *getWorkerDate() {
	char *date = new char[MAX_STR_SIZE];
	do {
		cin.getline(date, MAX_STR_SIZE);
	} while (!isValidDate(date));
	if (strlen(date) != DATE_SIZE - 1) {
		date[DATE_SIZE - 1] = '\0';
		date[DATE_SIZE - 2] = date[DATE_SIZE - 3];
		date[DATE_SIZE - 3] = '0';
	}
	return date;
}
Worker getWorkerInfo() {
	Worker worker;

	cout << "Enter FIO:\n";
	strcpy(worker.fio, getWorkerFIO());

	cout << "Enter personal number:\n";
	worker.pers_num = readPosIntNum();

	cout << "Enter year and month(! in format year.month):\n";
	strcpy(worker.date, getWorkerDate());

	cout << "Enter work hours(! int number):\n";
	worker.work_hours = readPosIntNum();

	cout << "Enter rate(! can be double number):\n";
	worker.rate = readPosDoubleNum();

	return worker;
}
void insertWorker(Worker worker) {
	ofstream fadd(WORKERS, ios::binary | ios::app);
	fadd.write((char*)&worker, sizeof worker);
	fadd.close();
}
bool readAllWorkers(Worker *workers, int &num) {
	ifstream fin(WORKERS, ios::binary | ios::in);

	int m = 0;
	if (!fin.is_open()) {
		return 1;
	}
	else {
		while (!fin.eof()) {
			fin.read((char*)&workers[m], sizeof workers[m]);
			m++;
		}
		fin.close();
		m--;
	}
	num = m;

	return 0;
}
Worker getWorkerFK() {
	Worker worker;

	cout << "Enter personal number:\n";
	worker.pers_num = readPosIntNum();

	cout << "Enter year and month(! in format year.month):\n";
	strcpy(worker.date, getWorkerDate());

	return worker;
}
int checkWorkerFK(Worker *workers, int &num, Worker &worker) {
	int findAt = -1;
	for (int i = 0; i < num; i++) {
		if (workers[i].pers_num == worker.pers_num && !strcmp(workers[i].date, worker.date)) {
			findAt = i;
			worker = workers[i];
			break;
		}
	}
	return findAt;
}
int editWorker() {
	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	Worker worker = getWorkerFK();

	int findAt = checkWorkerFK(workers, num, worker);
	if (findAt < 0) {
		cout << "Worker with this credentials not found.\n";
		return 1;
	}
	system("clear");

	int choice;
	bool changed = false;
	while (1) {
		coutWorker(worker);
		cout << "Choose what you want:\n"
			" 1.confirm\n"
			" 2.edit\n"
			" 3.cancel\n";
		choice = readIntNum();
		system("clear");

		if (choice == EDIT) {
			changed = true;
			worker = editEnterWorker(worker);
		}
		else if (choice == CONFIRM) {
			break;
		}
		else if (choice == CANCEL) {
			cout << "Edit worker canceled.\n";
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
		if (workers[i].pers_num == worker.pers_num && strcmp(workers[i].fio, worker.fio)) {
			cout << "This is personal number of another worker.\n";
			return 1;
		}
		if (workers[i].pers_num == worker.pers_num && !strcmp(workers[i].date, worker.date)) {
			cout << "Worker info for this date already exist.\n";
			return 1;
		}
	}

	updateWorkerInfo(worker, findAt);
	cout << "Worker info changed successfully.\n";

	return 0;
}
void updateWorkerInfo(Worker worker, int findAt) {
	fstream in(WORKERS, ios::binary | ios::in | ios::out);
	in.seekp(sizeof worker * findAt);
	in.write((char*)&worker, sizeof worker);
	in.close();
}
int deleteWorker() {
	int num;
	Worker *workers = new Worker[MAX_ARRAY_SIZE];
	readAllWorkers(workers, num);

	Worker worker = getWorkerFK();

	int findAt = checkWorkerFK(workers, num, worker);
	if (findAt < 0) {
		cout << "Worker with this credentials not found.\n";
		return 1;
	}

	system("clear");
	coutWorker(worker);
	if (!confirmDelete()) {
		cout << "Deleted of worker canceled.\n";
		return 0;
	}

	deleteWorkerInArray(workers, num, findAt);
	rewriteWorkersFile(workers, num);
	cout << "Worker info successfully deleted.\n";

	return 0;
}
void rewriteWorkersFile(Worker *workers, int num) {
	ofstream fout(WORKERS, ios::binary | ios::out);
	fout.write((char*)&workers[0], sizeof workers[0] * num);
	fout.close();
}
FIO getFioStructForSearch() {
	FIO fio;

	do {
		cout << "Surname: ";
		do {
			cin.getline(fio.surname, sizeof fio.surname);
		} while (!isValidPartOfFIO(fio.surname));

		cout << "Name: ";
		do {
			cin.getline(fio.name, sizeof fio.name);
		} while (!isValidPartOfFIO(fio.name));

		cout << "Patronymic: ";
		do {
			cin.getline(fio.patronymic, sizeof fio.patronymic);
		} while (!isValidPartOfFIO(fio.patronymic));

		system("clear");
	} while (!strcmp(fio.surname, "") && !strcmp(fio.name, "") && !strcmp(fio.patronymic, ""));

	return fio;
}
bool isValidPartOfFIO(char *str) {
	if (!strcmp(str, "")) return true;
	cmatch result;
	regex regular("^[A-Z][a-z]{0,18}$");
	bool valid = regex_match(str, result, regular);
	if (!valid)
		cout << "FIO part must be a string, starting with a capital letter and then all small letters, not more than 19 letters.\n";
	return valid;
}
bool likeFio(FIO fio, FIO likeFio) {
	bool flag = false;

	if (strcmp(fio.surname, "")) {
		flag = strcmp(fio.surname, likeFio.surname)
			? false
			: true;
	}

	if (strcmp(fio.name, "")) {
		flag = strcmp(fio.name, likeFio.name)
			? false
			: true;
	}

	if (strcmp(fio.patronymic, "")) {
		flag = strcmp(fio.patronymic, likeFio.patronymic)
			? false
			: true;
	}

	return flag;
}
FIO getStructFromStr(char *fioStr) {
	FIO fio;
	char *str = new char[MAX_STR_SIZE], *buff;
	strcpy(str, fioStr);

	strcpy(fio.surname, strtok(str, " "));
	strcpy(fio.name, strtok(NULL, " "));;
	strcpy(
		fio.patronymic,
		(buff = strtok(NULL, " ")) == NULL ? "" : buff
	);
	if (strcmp(fio.patronymic, ""))
		strtok(NULL, " ");

	return fio;
}
void deleteWorkerInArray(Worker *workers, int &num, int findAt) {
	for (int i = findAt; i + 1 < num; i++) {
		workers[i] = workers[i + 1];
	}
	num--;
}