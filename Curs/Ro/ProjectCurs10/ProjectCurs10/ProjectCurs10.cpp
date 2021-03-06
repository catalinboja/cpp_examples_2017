// ProjectCurs10.cpp : Defines the entry point for the console application.
//


#include <fstream>
#include <iostream>


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

	void setCod(int cod) {
		this->cod = cod;
	}

	void setNote(int nrNote, int* note) {
		if (this->grades != NULL)
			delete [] this->grades;
		if (nrNote == 0) {
			this->grades = NULL;
			this->noGrades = 0;
		}
		else {
			this->grades = new int[nrNote];
			for (int i = 0; i < nrNote; i++)
				this->grades[i] = note[i];
			this->noGrades = nrNote;
		}
	}

	void setNume(char* nume) {
		strcpy(this->name, nume);
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

	//metoda pentru serializare obiect
	void serializare(ofstream& fisier) {
		if (fisier.is_open()) {
			//scriem codul
			fisier.write((char*) &this->cod,
				sizeof(int));
			//scriem numele
			fisier.write(this->name,
				sizeof(Student::name));
			//scriem numarul de note
			fisier.write((char*) &this->noGrades,
				sizeof(int));
			//scriem notele
			for (int i = 0; i < this->noGrades; i++) {
				fisier.write((char*) &this->grades[i],
					sizeof(int));
			}
			////scriem facultatea - solutia 1
			//char buffer[1000];
			//strcpy(buffer, this->faculty);
			//fisier.write(buffer, sizeof(buffer));

			//scriem facultatea - solutia 2
			int dim = strlen(this->faculty) + 1;
			fisier.write((char*) &dim, sizeof(int));
			fisier.write(this->faculty,
				dim * sizeof(char));
		}
		else
		{
			cout << endl << "Probleme deschidere fisier";
			throw exception();
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


class StudentMasterat: public Student {
	char programMasterat[100];
	char gen;
};


int main()
{
	StudentMasterat sm1;
	cout << sm1;
}

