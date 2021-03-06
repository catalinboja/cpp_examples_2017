// ProjectLaborator7.cpp : Defines the entry point for the console application.
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

	char* getNume() {
		return this->nume;
	}

	int* getPuncte() {
		return this->puncte;
	}

	int getNrPlati() {
		return this->nrPlati;
	}

	//postincrementare
	CardFidelitate operator++(int) {
		CardFidelitate copie = *this;
		for (int i = 0; i < this->nrPlati; i++)
			this->puncte[i] += 5;
		return copie;
	}

	//preincrementare
	CardFidelitate operator++() {
		for (int i = 0; i < this->nrPlati; i++)
			this->puncte[i] += 5;
		return *this;
	}

	int& operator[](int index) {
		if (index >= 0 && index < this->nrPlati)
			return this->puncte[index];
		else
			throw exception();
	}

	bool operator!() {
		int suma = 0;
		for (int i = 0; i < this->nrPlati; i++) {
			suma += this->puncte[i];
			if (suma >= 100)
				return true;
			else
				return false;
		}
	}

};


ostream& operator<<(ostream& consola, CardFidelitate& card) {
	consola << endl << "Nume " << card.getNume();

	int* puncte = card.getPuncte();
	if (card.getPuncte() != NULL)
	{
		consola << endl << "Puncte ";
		int suma = 0;
		for (int i = 0; i < card.getNrPlati(); i++) {
			//suma += card.getPuncte()[i];
			suma += puncte[i];
		}
		consola << suma;
	}
	else
		consola << endl << "Nu are puncte";

	return consola;
}

void operator>>(istream& consola, CardFidelitate& card) {
	cout << endl << "Nume nou proprietar card:";
	char buffer[100];
	consola >> buffer;
	card.setNume(buffer);
	int nrPuncte;
	cout << endl << "Numarul de plati: ";
	consola >> nrPuncte;
	int* puncte = new int[nrPuncte];
	for (int i = 0; i < nrPuncte; i++) {
		cout << endl << "Puncte pentru plata " << i + 1 << ": ";
		consola >> puncte[i];
	}
	card.setPuncte(puncte, nrPuncte);
	delete [] puncte;
}

void main()
{
	CardFidelitate card1("Gigel");
	card1.afisare();

	int valori [] = { 10,20,30 };
	int n = 3;

	card1.setPuncte(valori, n);
	card1.afisare();

	CardFidelitate card2 = card1;

	card2.setNume("Ana");
	int valori2 [] = { 1,2,3,4 };
	int n2 = 4;
	card2.setPuncte(valori2, n2);

	card1.afisare();
	card2.afisare();

	CardFidelitate card3("Nimic");
	card3 = card2;
	card3.afisare();

	cout << endl << "********** Test operatori";

	cout << card1 << card2;  //ostream operator<<(ostream,CardFidelitate)
	CardFidelitate card4("Nimic");
	cin >> card4;
	cout << card4;

	cout << endl << "********** Test operator ++";
	card1 = card4++; // CardFidelitate operator++(CardFidelitate)
	card2 = ++card4; // CardFidelitate operator++(CardFidelitate)
	cout << card1 << card2 << card4;


	//int operator[](CardFidelitate, int)
	int nrPunctePlata = card4[0]; //operator indexare
	card4[0] = 100;
	cout << card4;



	if (!card4) //numar puncte >=100
		cout << endl << "Nu este client premium";
	else
		cout << endl << "Este client premium";

	//if (card4 > card1)  //bool operator>(CardFidelitate,CardFidelitate)
	//	cout << endl << "Card4 are mai multe puncte";
	//else
	//	cout << endl << "Card1 are mai multe puncte sau la fel";

	//operatorul ()
}