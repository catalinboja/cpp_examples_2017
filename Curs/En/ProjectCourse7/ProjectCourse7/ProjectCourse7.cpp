// ProjectCourse7.cpp 
//

#include <iostream>
using namespace std;

class Student {

	char* name;
	char faculty[50];
	int* grades;
	int noGrades;
	int age;

	static int MIN_AGE;
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

	Student(const Student& stud) {
		this->setFaculty(stud.faculty);
		this->name = NULL;
		this->setName(stud.name);
		this->grades = NULL;
		this->setGrades(stud.grades, stud.noGrades);
		this->age = stud.age;
	}

	void operator =(Student& stud) {
		this->setFaculty(stud.faculty);
		this->setName(stud.name);
		this->setGrades(stud.grades, stud.noGrades);
		this->age = stud.age;
	}

	~Student() {
		delete [] this->name;
		delete [] this->grades;
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


	void setFaculty(const char* faculty) {
		strcpy(this->faculty, faculty);
	}

	void setName(const char* Name) {
		delete [] this->name;
		this->name = new char[strlen(Name) + 1];
		strcpy(this->name, Name);
	}

	void setGrades(const int* Grades, int NoGrades) {
		delete [] this->grades;
		this->grades = new int[NoGrades];
		for (int i = 0; i < NoGrades; i++)
			this->grades[i] = Grades[i];
		this->noGrades = NoGrades;
	}

	void setAge(int value) {
		if (value > MIN_AGE)
			this->age = value;
		else
			throw exception();
	}

	int getMIN_AGE() {
		return Student::MIN_AGE;
	}

	//static methods
	static int get_MIN_AGE() {
		return Student::MIN_AGE;
	}

	int getNoGrades() {
		return this->noGrades;
	}
	
	int* getGrades() {
		return this->grades;
	}

	Student operator+(int grade) {

		Student clone = *this;

		int* newGrades = new int[clone.getNoGrades() + 1];
		int* existingGrades = clone.getGrades();
		for (int i = 0; i < clone.getNoGrades(); i++)
			//newGrades[i] = student.getGrades()[i];
			newGrades[i] = existingGrades[i];
		newGrades[clone.getNoGrades()] = grade;
		clone.setGrades(newGrades, clone.getNoGrades() + 1);

		return clone;
	}

	//cast to float
	explicit operator float() {
		float average = 0;
		for (int i = 0; i < this->noGrades; i++)
			average += this->grades[i];
		return average / (float)this->noGrades;
	}


	friend void operator<<(ostream& console, const Student& stud);
};

int Student::MIN_AGE = 10;


int sum(int a, int b) {
	return a + b;
}

int sum(int a, int b, int c) {
	return a + b + c;
}

void sum(int a, Student stud) {

}

//add a new grade
void operator+=(Student& student, int grade) {
	int* newGrades = new int[student.getNoGrades()+1];
	int* existingGrades = student.getGrades();
	for(int i = 0; i < student.getNoGrades(); i++)
		//newGrades[i] = student.getGrades()[i];
		newGrades[i] = existingGrades[i];
	newGrades[student.getNoGrades()] = grade;
	student.setGrades(newGrades, student.getNoGrades() + 1);

}

void operator<<(ostream& console, const Student& stud) {
	console << endl << stud.name
		<< " is " << stud.age
		<< " years old";
	console << endl << "The faculty is "
		<< stud.faculty;
	if (stud.grades != NULL) {
		console << endl << "The grades:";
		for (int i = 0; i < stud.noGrades; i++)
			console << " " << stud.grades[i];
	}
}

Student operator+(int grade, Student stud) {
	return stud + grade;
}

//Student operator+(Student& stud, int grade) {
//
//}

int main()
{

	cout << endl << "Class minimum age is " << Student::get_MIN_AGE();

	Student student("John");
	int value = 6;
	if(value > student.getMIN_AGE())
		student.setAge(6);

	//overloading operator
	sum(1, 2);
	sum(1, 2, 3);

	student += 9; //operator+=(Student, int)
	student += 10;
	//student.display();


	cout << student; //operator<<(ostream,Student) function
	//cin >> student;
	student = student + 10; //student.operator+(10) //operator+(Student, int)
	cout << student;

	student = 10 + student; //operator+(int, Student)

							//
	float average = (float)student; //cast operator float(Student)

	cout << endl << "The grades average is " << (float) student;
	//if (!student)
	//	cout << endl << "Has 0 grades";
	//else
	//	cout << endl << "The grades average is " << (float) student;
	//int secondGrade = student[1];
	//if(student1>student2)
	//	//do something

	//read the function operator

}

