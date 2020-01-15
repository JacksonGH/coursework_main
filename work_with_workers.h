#pragma once
#include "common.h"

using namespace std;

const string WORKERS = "workers.bin";

const double TAX = 12;
const int OVERTIME_RANGE = 144;

struct Date {
	int year;
	int month;
};

struct Worker {
	char fio[MAX_STR_SIZE];
	int pers_num;
	char date[DATE_SIZE];
	int work_hours;
	double rate;
};

struct Salary {
	char fio[MAX_STR_SIZE];
	char date[DATE_SIZE];
	int pers_num;
	double salary_per_month;//current salary for normal time
	double salary_per_range = 0;
};

struct FIO {
	char surname[MAX_STR_SIZE];
	char name[MAX_STR_SIZE];
	char patronymic[MAX_STR_SIZE];
};

void updateWorkerInfo(Worker, int);
void rewriteWorkersFile(Worker *, int);
void deleteWorkerInArray(Worker *, int &, int);
int addWorker();
Worker editEnterWorker(Worker);
void viewAllWorkers();
void calcAndCoutSalariesForRange();
void logicCalcAndCoutSalariesForRange(Worker *, int, char *);
void searchWorkers(int &);
void sortWorkers(int &);

void logicSearchWorkers(Worker *, int, int);
void logicSortWorkers(Worker *, int, int &);

Worker *searchByPersNum(Worker *, int &);
Worker *searchByDate(Worker *, int &);
Worker *searchByFio(Worker *, int &);

void sortByPersNum(Worker *, int, int);
void sortByDate(Worker *, int, int);
void sortByFio(Worker *, int, int);

int editWorker();
int deleteWorker();
void insertWorker(Worker);
bool readAllWorkers(Worker *, int &);

void coutWorkersSalaries(Salary *, int);
void coutWorkers(Worker *, int);
void coutWorker(Worker);

Worker getWorkerInfo();
char *getWorkerFIO();
char *getWorkerDate();
char *getRange();
Worker getWorkerFK();

int checkWorkerFK(Worker *, int &, Worker &);
bool isValidFIO(char *);
bool isValidDate(char *);
bool isValidRange(char *);

int workersFixture();
double getWorkerSalary(Worker);
Date nowDate();

FIO getFioStructForSearch();
bool isValidPartOfFIO(char *str);
bool likeFio(FIO fio, FIO likeFio);
FIO getStructFromStr(char *fioStr);