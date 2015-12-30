#include"company.h"


	struct employee* Company::createEmployee(string _name) {
		employee* e = new employee;
		e->name = _name;
		if (this->boss == nullptr) {
			this->boss = e;
		}
		return e;
	}

	employee* Company::getBoss() {
		return this->boss;
	}

	void Company::addWorkers(employee* boss, vector<employee *> _workers) {
		boss->workers = _workers;
	}
	void Company::getWorkers(vector<employee *> &vec, employee * e) {
		auto workers = e->workers;
		if (workers.size() != 0) {
			for (int i = 0; i < workers.size(); i++) {
				vec.push_back(workers[i]);
				getWorkers(vec, workers[i]);
			}
		}
	}

	int Company::getWorkersCount(employee *e) {
		vector<employee *> vec;
		getWorkers(vec, e);
		return static_cast<int>(vec.size());
	}

	void Company::getEmployeeWithNoWorkers(vector<employee *> &vec, employee *e) {
		auto workers = e->workers;
		if (workers.size() != 0) {
			for (int i = 0; i < workers.size(); i++) {

				auto count = getWorkersCount(workers[i]);
				if (count == 0) {
					vec.push_back(workers[i]);
				}
				getEmployeeWithNoWorkers(vec, workers[i]);
			}
		}
	}


	void Company::getEmployeeWithThreeWorkers(vector<employee *> &vec, employee *e) {
		auto workers = e->workers;
		auto count = getWorkersCount(e);
		if (count >= 3 && e == boss) {
			vec.push_back(e);
		}
		if (workers.size() != 0) {
			for (int i = 0; i < workers.size(); i++) {

				auto count = getWorkersCount(workers[i]);
				if (count >= 3) {
					vec.push_back(workers[i]);
				}
				getEmployeeWithThreeWorkers(vec, workers[i]);
			}
		}
	}

	void Company::createWorkers(employee * e, int wokerSize) {
		for (int i = 0; i< wokerSize; i++) {
			cout << "add a new employee his/her name is:" ;
			string name;
			cin >> name;
			auto em = this->createEmployee(name);
			e->workers.push_back(em);
		}


		if (wokerSize == 0) {
			return;
		}
		for (int i = 0; i<wokerSize; i++) {
			cout << "how many workers does " << e->workers[i]->name << " have?" << endl;
			int workerCnt;
			cin >> workerCnt;
			this->createWorkers(e->workers[i], workerCnt);
		}



	}

int main() {
	Company c;
	string name;
	int workerSize;
	employee* boss;
	cout << "enter the name of a employee:" << endl;
	cin >> name;
	cout << "how many workers does " << name << " have?" << endl;
	cin >> workerSize;

	boss = c.createEmployee(name);
	c.createWorkers(boss, workerSize);




	vector<employee *> employeeWithNoWorkers;
	c.getEmployeeWithNoWorkers(employeeWithNoWorkers, c.getBoss());

	cout << " =======================output===========================" << endl;
	cout << "employee with no workers:" ;
	for (int i = 0; i<employeeWithNoWorkers.size(); i++) {
		cout << employeeWithNoWorkers[i]->name<<", ";
	}
	cout << endl;
	cout << endl;

	cout <<" =======================employee has 3+ workers=======================" << endl;
	vector<employee *> employeeWithThreeWorkers;
	c.getEmployeeWithThreeWorkers(employeeWithThreeWorkers, c.getBoss());
	for (int i = 0; i< employeeWithThreeWorkers.size(); i++) {
		vector<employee *> vec;
		c.getWorkers(vec, employeeWithThreeWorkers[i]);
		cout << employeeWithThreeWorkers[i]->name << " has " << vec.size() << " workers, ";
		cout << "the workers are: ";
		for (int j = 0; j<vec.size(); j++) {
			cout << vec[j]->name << ", ";
		}
		cout << endl;
	}


	return 0;
}