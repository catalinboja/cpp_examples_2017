// Project19Ianuarie2018.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include <string>
using namespace std;

template<typename T,typename R>
class Cutie {
	int greutate;
	T culoare;
	R continut;
public:
	Cutie(R Continut, T Culoare, int Greutate) {
		this->continut = Continut;
		this->culoare = Culoare;
		this->greutate = Greutate;
	}

	T getCuloare() {
		return this->culoare;
	}

	void modificaCuloare(T nouaCuloare) {
		cout << endl << "Apel varianta generica";
		this->culoare += nouaCuloare;
	}

	void afisare() {
		cout << endl << "Continut: " << this->continut;
		cout << endl << "Culoare: " << this->culoare;
		cout << endl << "Greutate: " << this->greutate;
	}
};

//specializare metoda modificaCuloare pentru T = char*

template<>
void Cutie<const char*, string>::modificaCuloare(const char* nouaCuloare) {
	cout << endl << "Apel varianta specializata";
}


class Electrocasnic {
public:
	virtual void afisare() {
		cout << endl << "Este un aparat electrocasnic";
	}
};

class MasinaSpalatVase: public Electrocasnic {
public:
	void afisare() {
		cout << endl << "Este o masina de spalat vase";
	}
};

class Microunde: public Electrocasnic {
public:
	void afisare() {
		cout << endl << "Este un aparat cu microunde";
	}
};

class ListaProduse {
public:
	virtual void getDescriereProduse() = 0;
};

class StocMagazin : public ListaProduse {
	//vector de obiecte
	//Electrocasnic *lista;
	//Electrocasnic lista[100];

	//vector de pointeri
	Electrocasnic* *lista;
	//Electrocasnic* lista[100];
	int nrEchipamente;

public:
	StocMagazin() {
		this->nrEchipamente = 0;
		lista = NULL;
	}

	//supradefinire metoda virtuala pura
	void getDescriereProduse() {
		for (int i = 0; i < nrEchipamente; i++)
			this->lista[i]->afisare();
	}

	void operator+=(Electrocasnic* aparat) {
		Electrocasnic** listaNoua = 
			new Electrocasnic*[this->nrEchipamente + 1];
		for (int i = 0; i < this->nrEchipamente; i++)
			listaNoua[i] = this->lista[i];
		listaNoua[this->nrEchipamente] = aparat;
		delete[] this->lista;
		this->lista = listaNoua;
		this->nrEchipamente += 1;
	}

	~StocMagazin() {
		//for (int i = 0; i < this->nrEchipamente; i++)
		//	delete this->lista[i];
		delete[] lista;
	}

	StocMagazin(StocMagazin& magazin) {

		//partajare adrese
		//this->lista = new Electrocasnic*[magazin.nrEchipamente];
		//for (int i = 0; i < magazin.nrEchipamente; i++)
		//	this->lista[i] = magazin.lista[i];

		//creare obiecte noi
		this->lista = new Electrocasnic*[magazin.nrEchipamente];
		for (int i = 0; i < magazin.nrEchipamente; i++) {
			//NU 
			//Electrocasnic e = *magazin.lista[i]
			//verific ce am la adresa respectiva
			if (dynamic_cast<Microunde*>(magazin.lista[i])) {
				Microunde* ref = (Microunde*)magazin.lista[i];
				this->lista[i] = new Microunde(*ref);
			}
			else
				if (dynamic_cast<MasinaSpalatVase*>(magazin.lista[i])) {
					MasinaSpalatVase* ref = (MasinaSpalatVase*)magazin.lista[i];
					this->lista[i] = new MasinaSpalatVase(*ref);
				}
				else
					this->lista[i] = new Electrocasnic(*magazin.lista[i]);
		}

		this->nrEchipamente = magazin.nrEchipamente;
	}
};


int main()
{
	Cutie<int,int> cIntregi(10,2,35);
	cIntregi.modificaCuloare(50);
	cIntregi.afisare();

	Cutie<int, string> cScrisori("O scrisoare", 1, 0);
	cScrisori.modificaCuloare(50);
	cScrisori.afisare();

	Cutie<const char*, string> cScrisori2(
		"O scrisoare", "Albastru", 0);
	cScrisori2.modificaCuloare("Rosu");
	cScrisori2.afisare();

	//ListaProduse lista;
	//utilizare ca pointer type
	ListaProduse* lista;

	Electrocasnic e1;
	MasinaSpalatVase mv1;
	Microunde mu1;

	//utilizare stoc magazin
	StocMagazin magazin;
	magazin += &e1;
	magazin += &mv1;
	magazin += &mu1;

	magazin += new Microunde();

	magazin.getDescriereProduse();


	StocMagazin magazin2 = magazin;
	magazin2.getDescriereProduse();
}

