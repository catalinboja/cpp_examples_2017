// ProjectLab4.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

class Student {

	char* name;
	char faculty[50];
	int* grades;
	int noGrades;
	int age;
public:
	//default constructor
	Student() {
		this->name =
			new char[strlen("John Doe") + 1];
		strcpy(this->name, "John Doe");
		strcpy(this->faculty, "None");
		this->grades = NULL;
		this->noGrades = 0;
		this->age = 18;
	}

	//constructor - receives the name
	Student(char* Name) {
		this->name = 
			new char[strlen(Name) + 1];
		strcpy_s(this->name,
			strlen(Name) + 1, Name);
		//strcpy(this->name, Name);
		strcpy(this->faculty, "None");
		this->grades = NULL;
		this->noGrades = 0;
		this->age = 18;
	}

	Student(char* Name, char* faculty,
		int* grades, int noGrades,
		int age) {
		this->name =
			new char[strlen(Name) + 1];
		strcpy(this->name, Name);
		strcpy(this->faculty, faculty);
		this->age = age;
		this->noGrades = noGrades;
		this->grades = new int[noGrades];
		for (int i = 0; i < noGrades; i++)
			this->grades[i] = grades[i];
	}

	void display() {
		cout << endl << this->name
			<< " is " << this->age
			<< " years old";
		cout << endl << "The faculty is "
			<< this->faculty;
		if (this->grades != NULL) {
			cout << endl << "The grades:";
			for (int i = 0; i < this->noGrades; i++)
				cout << " " << this->grades[i];
		}
	}


	//add a new grade to the student
	void addGrade(int grade) {
		int* newGrades = new int[this->noGrades + 1];
		for (int i = 0; i < this->noGrades; i++)
			newGrades[i] = this->grades[i];
		newGrades[this->noGrades] = grade;
		this->noGrades += 1;
		delete [] this->grades;
		this->grades = newGrades;
	}

	void setFaculty(char* faculty) {
		strcpy(this->faculty, faculty);
	}

	void setName(char* Name) {
		delete [] this->name;
		this->name = new char[strlen(Name) + 1];
		strcpy(this->name, Name);

	}

};


int main()
{
	//default constructor
	Student student;
	Student student2("Alice");
	int grades[] = { 9,9,8 };

	Student student3(
		"Bob", "MAN", grades, 3, 19);

	student.addGrade(10);
	student2.addGrade(8);
	student3.addGrade(9);
	student3.addGrade(10);

	student.display();
	student2.display();
	student3.display();

	student2.setName("Yoyoooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	student2.display();
}

