
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct employee {
	string name;
	vector<employee *> workers;
};

class Company {
private:
	employee * boss = nullptr;
public:
	struct employee* createEmployee(string _name);

	employee* getBoss();
	void addWorkers(employee* boss, vector<employee *> _workers);
	void getWorkers(vector<employee *> &vec, employee * e);

	int getWorkersCount(employee *e);

	void getEmployeeWithNoWorkers(vector<employee *> &vec, employee *e);


	void getEmployeeWithThreeWorkers(vector<employee *> &vec, employee *e);

	void createWorkers(employee * e, int wokerSize);


};