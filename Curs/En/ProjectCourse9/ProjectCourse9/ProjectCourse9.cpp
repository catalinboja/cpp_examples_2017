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

	void setGrades(int* grades, int n) {
		if (this->grades != NULL)
			delete [] this->grades;
		//this->grades = grades; DON'T
		this->grades = new int[n];
		for (int i = 0; i < n; i++)
			this->grades[i] = grades[i];
		this->noGrades = n;

	}


	void operator=(const Student& s2) {

		if (this == &s2)
			return;

		delete [] this->grades;
		delete [] this->faculty;

		cout << endl << "Operator = called";
		this->cod = s2.cod;
		strcpy(this->name, s2.name);

		this->faculty = NULL;
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

	//a method for serializing the object
	void write2File(ofstream& file) {
		if (file.is_open()) {
			//write the code
			file.write((char*) &this->cod, sizeof(int));
			//write the name
			file.write(this->name, sizeof(Student::name));
			//write the number of grades
			file.write((char*) &this->noGrades, sizeof(int));
			//write the grades
			for (int i = 0; i < this->noGrades; i++) {
				file.write((char*) &this->grades[i], sizeof(int));
			}
			//write the faculty - option 1
			char buffer[100];
			strcpy(buffer, this->faculty);
			file.write(buffer, sizeof(buffer));

			//write the faculty - option 2
			//write the faculty value size
			int facultySize = strlen(this->faculty) + 1;
			file.write((char*)&facultySize, sizeof(int));
			file.write(this->faculty, facultySize*sizeof(char));


		}
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
	Student s1("John", 23, "CSIE");
	Student s2("Ionel", 22, "MK");

	s1 += 10;
	s1 += 9;


	//cout << s1 << s2;

	////char buffer1[50];
	////char buffer2[50];

	////cout << endl << "name:";
	////cin >> buffer1;
	////cout << endl << "name 2:";
	////cin >> buffer2;

	////cout << endl << buffer1 << " - " << buffer2;

	//Student* list = new Student[2]{ s1,s2 };
	//int noStudents = 2;

	////create a text report
	////ofstream report("students.txt");
	//unsigned char vb = ios::trunc;
	//ofstream report;
	//report.open("students.txt",ios::out|ios::trunc);
	//if (report.is_open()) {
	//	report << "The students are ";
	//	report << s1;
	//	report << s2;
	//	report << endl<<"The students from the list are ";
	//	for (int i = 0; i < noStudents; i++) {
	//		report << endl << list[i].getName();
	//	}

	//	report.close();
	//}
	//else
	//	cout << endl << "The file is not opened";
	//cout << endl << "The end";

	////reading from a file
	//Student *list2;
	//int noStudents2;
	//ifstream inputFile;
	//inputFile.open("input.txt", ios::in);
	//if (inputFile.is_open()) {
	//	inputFile >> noStudents2;
	//	list2 = new Student[noStudents2+1];
	//	for (int i = 0; i < noStudents2; i++) {
	//		char name[50];
	//		inputFile >> name;
	//		char faculty[50];
	//		inputFile >> faculty;
	//		int noGrades;
	//		inputFile >> noGrades;
	//		int * grades = new int[noGrades];
	//		for (int j = 0; j < noGrades; j++) {
	//			inputFile >> grades[j];
	//		}
	//		Student temp(name, 0, faculty);
	//		temp.setGrades(grades, noGrades);
	//		list2[i] = temp;
	//	}
	//}

	//inputFile.close();

	////cout << list2[0] << list2[1] << list2[2];

	//list2[3] = s1;


	//for (int i = 0; i < 4; i++) {
	//	cout << list2[i];
	//}

	////binary files
	//noStudents2 = 4;
	//ofstream myData;
	//myData.open("Backup.dat", ios::out | ios::binary | ios::trunc);
	//if (myData.is_open()) {
	//	//write the number of students
	//	//myData << noStudents2; WON'T WORK
	//	myData.write((char*) &noStudents2, sizeof(int));
	//	for (int i = 0; i < noStudents2; i++)
	//		myData.write((char*) &list2[i], sizeof(Student));
	//}

	//myData.close();

	Student *list2 = new Student[2]{ s1,s1 };
	int noStudents2 = 2;
	ofstream myData;
	myData.open("Backup.dat", ios::out | ios::binary | ios::trunc);
	if (myData.is_open()) {
		//write the number of students
		//myData << noStudents2; WON'T WORK
		myData.write((char*) &noStudents2, sizeof(int));
		for (int i = 0; i < noStudents2; i++)
			//write the code
			list2[i].write2File(myData);
	}

	myData.close();



	//ifstream myInputData;
	//myInputData.open("Backup.dat", ios::in | ios::binary);
	//int noStudents3;
	//Student* list3;
	//if (myInputData.is_open()) {
	//	myInputData.read((char*) &noStudents3, sizeof(int));
	//	list3 = new Student[noStudents3];
	//	for (int i = 0; i < noStudents3; i++) {
	//		myInputData.read((char*) &list3[i], sizeof(Student));
	//	}
	//}
	//myInputData.close();

	//cout << endl << "*********** After lunch *****";

	//for (int i = 0; i < noStudents3; i++) {
	//	cout << list3[i];
	//}


	cout << endl << "THE END";

}