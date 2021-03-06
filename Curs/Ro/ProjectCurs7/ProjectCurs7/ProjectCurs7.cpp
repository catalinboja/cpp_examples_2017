#include<iostream>
using namespace std;

//fara variabile globale
//int contor = 0;

class Student {
private:
	char* nume;
	int varsta;
	const int cod;
	static int contor;
	static int VARSTA_MINIMA;

	//const int cod2;
	//Student() :cod(0),cod2(0)

	Student() :cod(0) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 18;
	}

public:
	Student(char* nume, int varsta, int Cod) :cod(Cod) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->varsta = varsta;
	}

	//copy constructor
	Student(const Student& existent) :cod(Student::contor) {
		Student::contor += 1;
		//if (existent.varsta > VARSTA_MINIMA)
		//	this->varsta = existent.varsta;
		//else
		//	throw exception("Valoare gresita");

		//existent.varsta = 34;

		this->setVarsta(existent.varsta);

		this->nume = NULL;
		this->setNume(existent.nume);

		/*this->nume = new char[strlen(existent.nume) + 1];
		strcpy(this->nume, existent.nume);*/
	}


	void afisare() {
		cout << endl << this->nume << " - " << this->varsta <<
			" cod " << this->cod;

	}

	//interfata clasei
	//pentru citire
	int getVarsta() {
		return this->varsta;
	}

	//pentru modificari
	void setVarsta(int valoare) {
		if (valoare > VARSTA_MINIMA)
			this->varsta = valoare;
		else
			throw exception("Valoare gresita");
	}

	char* getNume() {
		return this->nume;
	}

	int getCod() {
		return this->cod;
	}

	void setNume(char* Nume) {
		if (strlen(Nume) < 3)
			throw exception("Numele este prea scurt");
		if (this->nume != NULL)
			delete [] this->nume;
		this->nume = new char[strlen(Nume) + 1];
		strcpy(this->nume, Nume);
	}

	Student& operator=(Student& s2) {
		this->setVarsta(s2.varsta);
		this->setNume(s2.nume);
		return s2;
	}

	//destructor
	~Student() {
		if (this->nume != NULL)
			delete [] this->nume;
	}

	Student operator+(int valoare) {
		Student rezultat = *this;
		rezultat.varsta += valoare;
		return rezultat;
	}

	Student operator+=(int valoare) {
		this->varsta += valoare;
		return *this;
	}


	explicit operator int() {
		//return this->varsta;
		return strlen(this->nume);
	}


	friend void operator>>(istream& consola, Student& s);

};

int Student::contor = 1000;
int Student::VARSTA_MINIMA = 10;

//supraincarcare de functii
int suma(int a, int b) {
	return a + b;
}

int suma(int a, int b, int c) {
	return a + b + c;
}

int suma(int a, Student s) {
	return 0;
}


ostream& operator<<(ostream& consola, Student& s) {
	consola << endl << s.getNume() << " - " << s.getVarsta() <<
		" cod " << s.getCod();
	return consola;
}

void operator>>(istream& consola, Student& s) {
	cout << endl << "Numele studentului: ";
	char buffer[1000];
	consola >> buffer;
	s.setNume(buffer);
	cout << endl << "Varsta studentului: ";
	consola>>s.varsta;

}

Student operator+(int valoare, Student s) {
	return s + valoare;
}



void main() {

	suma(2, 3);
	suma(1, 2, 3);

	Student student1("Gigel", 21, 1);
	Student student2("Ana", 21, 2);
	Student* pStudent1 = new Student("Ioana", 22, 2);

	suma(2, student1);


	student1.afisare();
	student2.afisare();
	pStudent1->afisare();


	Student student3("test", 1, 1);

	//student3 = student2;
	//student3 = student2 = student1;

	//for (;;) {
	//	Student* pStudent2 = new Student("Ioana", 22, 2);
	//	delete pStudent2;
	//}

	cout << endl << "****************************";

	cout << student3; //void operator<<(ostream,Student)
	//operator<<(cout, student3);

	cout << student1 << student2; //ostream operator<<(ostream, Student)
	//operator<<(operator<<(cout,student1),student2)


	cin >> student3; //operator>>(istream, Student)
	cout << student3;

	student3 = student3 + 3;//modificare varsta operator+(Student,int)
	///student3.operator+(3)
	cout << student3;
	student2 = 3+student3; //Student operator+(int, Student)
	//3.operator+(student3);

	cout << student2;

	student3 += 1;		//operator+=(Student, int)	//modificare varsta
	//student3++;
	//student2 = student3++;
	//student1 = ++student3;


	//int numarCaractereNume = student3;	//operator cast implicit
	int numarCaractereNume = (int) student3;	//operator cast explicit
	int suma = 23 + (int) student3;

	//char initialaStudent = student3[0];
	//student3[0] = 'I';

	//if (!student3)
	//	cout << endl << "Studentul are varsta mai mica decat varsta minima";
	//else
	//	cout << endl << "Este ok";

	//if (student3 > student2)
	//	cout << endl << "Student3 are varsta mai mare";
	//else
	//	cout << endl << "Studentul2 are aceeasi varsta sau este mai tanar";

}

