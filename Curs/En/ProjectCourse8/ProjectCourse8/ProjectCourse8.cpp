// ProjectCourse8.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>

using namespace std;


class Student {
private:
	//attributes
	int cod;
	char name[50];
	int * grades;
	int noGrades;
	char* faculty;

public:
	//constructor
	Student() {
		//cout << endl << "Default constructor";
		cod = 0;
		noGrades = 0;
		this->grades = NULL;
		strcpy(this->name, "John Doe");
		// DON'T this->faculty = "CSIE";
		this->faculty = new char[strlen("CSIE") + 1];
		strcpy(this->faculty, "CSIE");
	}

	//constructor with arguments
	Student(char* name, int code, char*faculty) {
		//cout << endl << "Constructor with arguments";
		//shadowing 
		//code = code
		this->cod = code;
		this->noGrades = 0;
		this->grades = NULL;
		strcpy(this->name, name);
		this->faculty =
			new char[strlen(faculty) + 1];
		strcpy(this->faculty, faculty);

	}

	~Student() {
		//cout << endl << "Destructor !!!!!";
		if (this->faculty != NULL)
			delete [] this->faculty;
		if (this->grades != NULL)
			delete [] grades;
	}

	//copy constructor
	Student(const Student& s) {

		//cout << endl << "Copy constructor";
		this->cod = s.cod;
		strcpy(this->name, s.name);

		this->faculty = NULL;
		this->setFaculty(s.faculty);

		//grades
		if (s.noGrades != 0) {
			this->grades = new int[s.noGrades];
			for (int i = 0; i < s.noGrades; i++)
				grades[i] = s.grades[i];
			this->noGrades = s.noGrades;
		}
		else
		{
			this->noGrades = 0;
			this->grades = NULL;
		}
	}

public:
	//accessor methods
	//for reading
	int getCode() {
		return this->cod;
	}

	char* getFaculty() {
		return this->faculty;
	}
	char* getName() {
		return this->name;
	}

	int getNoGrades() {
		return this->noGrades;
	}

	//write access
	void setFaculty(char* newFaculty) {
		//validating the input
		if (strlen(newFaculty) >= 2) {

			//this->faculty = newFaculty; DON'T
			if (this->faculty != NULL)
				delete [] this->faculty;
			this->faculty = new char[strlen(newFaculty) + 1];
			strcpy(this->faculty, newFaculty);
		}
		else {
			throw exception("The name is too short!");
		}

	}


	void operator=(const Student& s2) {

		if (this == &s2)
			return;

		delete [] this->grades;
		delete [] this->faculty;

		cout << endl << "Operator = called";
		this->cod = s2.cod;
		strcpy(this->name, s2.name);

		this->setFaculty(s2.faculty);


		//grades
		if (s2.noGrades != 0) {
			if (this->grades != NULL)
				delete [] this->grades;
			this->grades = new int[s2.noGrades];
			for (int i = 0; i < s2.noGrades; i++)
				grades[i] = s2.grades[i];
			this->noGrades = s2.noGrades;
		}
		else
		{
			this->noGrades = 0;
			this->grades = NULL;
		}
	}


	int& operator[](int index) {
		if (index >= 0 && index < this->noGrades) {
			return this->grades[index];
		}
		else
			throw exception();
	}

	void operator+=(int newGrade) {
		int* newGradesArray = new int[this->noGrades + 1];
		for (int i = 0; i < this->noGrades; i++)
			newGradesArray[i] = this->grades[i];
		newGradesArray[this->noGrades] = newGrade;
		delete [] this->grades;
		this->grades = newGradesArray;
		this->noGrades += 1;
	}

};


ostream& operator<<(ostream& console, Student& s) {
	console << endl << "Numele studentului este "
		<< s.getName() << ", are codul "
		<< s.getCode() << " si este la facultatea "
		<< s.getFaculty();
	console << endl << "Note:";
	for (int i = 0; i < s.getNoGrades(); i++)
		console << " " << s[i];
	return console;
}

void main() {
	Student s1("Gigel", 23, "CSIE");
	Student s2("Ionel", 22, "MK");

	s1 += 10;
	s1 += 9;


	cout << s1 << s2;

	//char buffer1[50];
	//char buffer2[50];

	//cout << endl << "name:";
	//cin >> buffer1;
	//cout << endl << "name 2:";
	//cin >> buffer2;

	//cout << endl << buffer1 << " - " << buffer2;

	Student* list = new Student[2]{ s1,s2 };
	int noStudents = 2;

	//create a text report
	//ofstream report("students.txt");
	unsigned char vb = ios::trunc;
	ofstream report;
	report.open("students.txt", ios::out | ios::trunc);
	if (report.is_open()) {
		report << "The students are ";
		report << s1;
		report << s2;
		report << endl << "The students from the list are ";
		for (int i = 0; i < noStudents; i++) {
			report << endl << list[i].getName();
		}

		report.close();
	}
	else
		cout << endl << "The file is not opened";
	cout << endl << "The end";

	//reading from a file
	Student *list2;
	int noStudents2;
	ifstream inputFile;
	inputFile.open("input.txt", ios::in);
	if (inputFile.is_open()) {
		inputFile >> noStudents2;
		list2 = new Student[noStudents2];
		for (int i = 0; i < noStudents2; i++) {
			char name[50];
			inputFile >> name;
			char faculty[50];
			inputFile >> faculty;
			int noGrades;
			inputFile >> noGrades;
			int * grades = new int[noGrades];
			for (int j = 0; j < noGrades; j++) {
				inputFile >> grades[j];
			}
			Student temp(name, 0, faculty);
			list2[i] = temp;
		}
	}

	inputFile.close();

	cout << list2[0] << list2[1] << list2[2];

}