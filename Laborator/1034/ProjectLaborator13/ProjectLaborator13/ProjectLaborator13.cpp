// ProjectLaborator13.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

class LipsaDenumireException : public exception {
public:
	LipsaDenumireException(const char* mesaj)
		:exception(mesaj){
	}
};

class PretGresitException : public exception {

};

class GreutateNegativaException : public exception {

};

class Electrocasnic {
	int greutate;
	float pret;
	char denumire[50];
public:
	Electrocasnic(const char* Denumire,
		float Pret,
		int Greutate) {
		if (Denumire == NULL) {
			throw new LipsaDenumireException(
				"Lipsa denumire");
		}
		if (Greutate < 0) {
			throw new GreutateNegativaException();
		}
		if (Pret < 0) {
			throw new PretGresitException();
		}
		strcpy(this->denumire, Denumire);
		this->greutate = Greutate;
		this->pret = Pret;
	}

	char* getDenumire() {
		return this->denumire;
	}
	float getPret() {
		return this->pret;
	}
};

int main()
{
	Electrocasnic e1("Frigider", 670, 16);
	while (true) {
		try {
			char buffer[100];
			cout << endl << "Denumire aparat electrocasnic: ";
			cin >> buffer;
			float pret;
			cout << endl << " Pret aparat: ";
			cin >> pret;
			int greutate;
			cout << endl << " Greutate aparat: ";
			cin >> greutate;
			Electrocasnic e2(buffer, pret, greutate);
			cout << endl << e2.getDenumire() << " are pretul "
				<< e2.getPret();

			break;
		}

		catch (PretGresitException* e) {
			cout << endl << "Pretul este gresit. Trebuie reintrodus";
		}
		catch (GreutateNegativaException* e) {
			cout << endl << "Atentie. Greutate negativa";
		}
		catch (exception* e) {
			cout << endl << "Eroare "
				<< e->what();
		}
		catch (...) {
			cout << endl << "Eroare generica";
		}
	}

	cout << endl << "Program terminat";
}

