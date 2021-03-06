// Projectlab11.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

class Employee {
protected:
	char name[100];
	int age;
	float salary;
public:
	//Employee() {
	//	strcpy(this->name, "John Doe");
	//	this->age = 16;
	//	this->salary = 0;
	//}
	Employee(char* Name, int Age, float Salary)
		:age(Age), salary(Salary) {
		strcpy(this->name, Name);
	}
	virtual void display() {
		cout << endl << this->name << ", age "
			<< this->age << " has a base salary of"
			<< this->salary;
	}

	virtual float getSalary() {
		return this->salary;
	}

	char* getName() {
		return this->name;
	}

	float getCost() {
		return this->salary * 1.42;
	}
};


class Manager :public Employee {
	char department[50];
	int bonus;
public:
	Manager(char* Department, int Bonus, char* Name, int Age, float Salary)
		:Employee(Name, Age, Salary) {
		strcpy(this->department, Department);
		this->bonus = Bonus;
	}

	//overriding display()
	void display() {
		this->Employee::display();
		cout << endl << "It's managing " << this->department
			<< " department";
	}
};


class Programmer :public Employee {
	bool taxFree;
	Manager *pManger;
public:
	Programmer(char* Name, int Age, float Salary, Manager *pointerManager)
		:Employee(Name, Age, Salary) {
		if (pointerManager == NULL) {
			throw exception("I need a manager");
		}
		pManger = pointerManager;
		taxFree = true;
	}

	//overriding display()
	void display() {
		this->Employee::display();
		cout << endl << "It's a programmer";
		cout << endl << "It's manager is " <<
			this->pManger->getName();
	}

	//override getCost
	float getCost() {
		return this->salary*1.32;
	}



};

int main()
{
	//Employee emp1;
	Employee emp2("Alice", 22, 1600);
	Employee *pEmp1;
	pEmp1 = &emp2;
	pEmp1 = new Employee("George",23,1600);

	//arrays of objects
	//Employee employees[10]; - works only if you have default constructor
	Employee knownEmployees [] = { *pEmp1, emp2 };
	//Employee* employees;
	//employees = new Employee[10]; - works only if you have default constructor

	//arrays of pointers to objects
	//Employee* employees[10];
	Employee** employees;
	employees = new Employee*[10];

	//initialize them
	employees[0] = &emp2;
	employees[1] = pEmp1;
	//read the data from console
	//Employee temp;
	char name[100];
	cout << endl << "The employee name:";
	cin >> name;
	int age;
	cout << endl << "The age ";
	cin >> age;
	float salary;
	cout << endl << "The salary ";
	cin >> salary;
	employees[2] = new Employee(name, age, salary);

	//print the data
	for (int i = 0; i < 3; i++) {
		employees[i]->display();
	}

	Manager m1("Automotive", 5, "Alex", 32, 2000);
	Manager m2("Financial", 6, "Bianca", 32, 2000);

	Programmer p1("John", 23, 1500, &m1);
	Programmer p2("Vlad", 23, 1000, &m1);
	Programmer p3("Alina", 23, 1000, &m2);

	employees[3] = &m1;
	employees[4] = &m2;
	employees[5] = &p1;
	employees[6] = &p2;
	employees[7] = &p3;


	cout << endl << "___________________";
	//print the data
	for (int i = 0; i < 8; i++) {
		employees[i]->display();
	}
}

