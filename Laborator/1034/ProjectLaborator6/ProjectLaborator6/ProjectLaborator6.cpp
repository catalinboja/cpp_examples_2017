// ProjectLaborator6.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

class CardFidelitate {
	char nume[50];
	int* puncte;
	int nrPlati;
public:
	CardFidelitate(char* proprietar) {
		strcpy(this->nume, proprietar);
		this->puncte = NULL;
		this->nrPlati = 0;
	}

	void afisare() {
		cout << endl << "Nume " << this->nume;
		if (this->puncte != NULL)
		{
			cout << endl << "Puncte ";
			int suma = 0;
			for (int i = 0; i < this->nrPlati; i++) {
				suma += this->puncte[i];
			}
			cout << suma;
		}
		else
			cout << endl << "Nu are puncte";
	}

	void setNume(const char* numeNou) {
		if (strlen(numeNou) < 50)
			strcpy(this->nume, numeNou);
		else
			throw exception();
	}

	void setPuncte(int* valori, int n) {
		if (this->puncte != NULL)
			delete [] this->puncte;
		this->puncte = new int[n];
		for (int i = 0; i < n; i++)
			this->puncte[i] = valori[i];
		this->nrPlati = n;
	}

	CardFidelitate(const CardFidelitate& card) {
		//card.nrPlati = 1000;
		this->setNume(card.nume);
		this->puncte = NULL;
		this->setPuncte(card.puncte, card.nrPlati);
	}

	void operator=(CardFidelitate card) {
		this->setNume(card.nume);
		this->setPuncte(card.puncte, card.nrPlati);
	}
};

void main()
{
	CardFidelitate card1("Gigel");
	card1.afisare();

	int valori[] = { 10,20,30 };
	int n = 3;

	card1.setPuncte(valori, n);
	card1.afisare();
	
	CardFidelitate card2 = card1;

	card2.setNume("Ana");
	int valori2[] = { 1,2,3,4 };
	int n2 = 4;
	card2.setPuncte(valori2, n2);

	card1.afisare();
	card2.afisare();

	CardFidelitate card3("Nimic");
	card3 = card2;

	card3.afisare();

}

