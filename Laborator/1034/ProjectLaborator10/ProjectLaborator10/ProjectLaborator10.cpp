// ProjectLaborator10.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

class Persoana {
	char nume[50];
	int varsta;
	const int cod;

public:
	Persoana():cod(0),varsta(0) {
		cout << endl << "Apel constructor default Persoana";
		strcpy(this->nume, "Anonim");
		//this->varsta = 0;
	}

	Persoana(int Varsta, int Cod, const char* Nume):cod(Cod)
	{
		strcpy(this->nume, Nume);
		this->varsta = Varsta;
	}

	void afisare() {
		cout << endl << this->nume << " are varsta " << this->varsta
			<< " si are codul " << this->cod;
	}

};

class Student :public Persoana {
	char facultate[50];
public:
	Student():Persoana(23,1,"Student necunoscut") {
		cout << endl << "Apel constructor default Student";
		strcpy(this->facultate, "");
	}

	Student(const char* Nume, int Varsta, int Cod, const char* Facultate)
		:Persoana(Varsta, Cod, Nume) {
		strcpy(this->facultate, Facultate);
	}

	//supradefinire
	void afisare() {
		//cout << endl << this->nume << " are varsta " << this->varsta
		//	<< " si are codul " << this->cod;
		this->Persoana::afisare();
		cout << endl << " este la facultatea " << this->facultate;
	}
};

class Masterand : public Student {
	char masterat[50];
public: 
	Masterand():Student() {
		cout << endl << "Apel constructor default Masterand";
	}

	Masterand(const char* Nume, int Varsta, int Cod, const char* Facultate, const char* Masterat)
		:Student(Nume, Varsta, Cod, Facultate) {
		strcpy(this->masterat, Masterat);
	}

};

int main()
{
	//Persoana p1;

	Masterand m1;
	Masterand m2("Gigel", 22, 1, "CSIE", "Cibernetica");

	m1.afisare();
	m2.afisare();
}

