// ProjectLaborator8.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;

class Meteo;

class StatieMeteo {
	char localitate[50];
	float temperaturi[24];
	int oraCurenta;
public:
	StatieMeteo() {
		strcpy(this->localitate, "Nicaieri");
		this->oraCurenta = 0;
		for (int i = 0; i < 24; i++) {
			this->temperaturi[i] = INT32_MAX;
		}
	}

	StatieMeteo(char* localitate) {
		strcpy(this->localitate, localitate);
		this->oraCurenta = 0;
		for (int i = 0; i < 24; i++) {
			this->temperaturi[i] = INT32_MAX;
		}
	}

	float operator[](int ora) {
		if (ora >= 0 && ora < this->oraCurenta) {
			return this->temperaturi[ora];
		}
		else
			throw exception();
	}

	void setTemperatura(int ora, float temp) {
		if (ora >= 0 && ora < 24) {
			if (temp > -200 && temp < 1000) {
				this->temperaturi[ora] = temp;
				if (ora > this->oraCurenta)
					this->oraCurenta = ora;
			}
			else
				throw exception();
		}
		else
			throw exception();
	}

	char* getLocalitate() {
		return this->localitate;
	}

	void setLocalitate(char* localitate) {
		strcpy(this->localitate, localitate);
	}

	//metoda pentru serializare Statie
	void salvareDate(ofstream& fisier) {
		if (fisier.is_open()) {
			//salvare localitate
			fisier.write(this->localitate, 
				sizeof(StatieMeteo::localitate));
			//salvare ora curenta
			fisier.write((char*) &this->oraCurenta, sizeof(int));
			//salvare temperaturi
			for (int i = 0; i < 24; i++) {
				fisier.write((char*) &this->temperaturi[i],
					sizeof(float));
			}
		}
	}


	friend void generareRaport(Meteo meteo, char* numeRaport);
	friend ostream& operator<<(ostream& consola, StatieMeteo& statie);
};

ostream& operator<<(ostream& consola, StatieMeteo& statie) {
	consola << endl << "Locatie: " << statie.localitate;
	consola << endl << "Temperaturi:";
	for (int i = 0; i <= statie.oraCurenta; i++)
		if (statie.temperaturi[i] == INT32_MAX)
			consola << " - ";
		else
			consola << " " << statie.temperaturi[i];
	return consola;
}

class Meteo {
public:
	StatieMeteo statii[100];
	int nrStatii;
	char *tara;

	Meteo() {
		this->tara = NULL;
		this->nrStatii = 0;
	}

	void setTara(char* Tara) {
		if (this->tara != NULL)
			delete [] this->tara;
		this->tara = new char[strlen(Tara) + 1];
		strcpy(this->tara, Tara);
	}

	void incarcaFisierText(char* fisier) {
		ifstream file;
		file.open(fisier, ios::in);
		if (file.is_open()) {
			//citim nume tara
			char tara[100];
			file >> tara;
			int nrStatii;
			file >> nrStatii;

			this->setTara(tara);
			this->nrStatii = nrStatii;
			for (int i = 0; i < nrStatii; i++) {
				//citim in variabile locale
				char Locatie[100];
				file >> Locatie;
				int nrInregistrari;
				file >> nrInregistrari;
				//definire statie meteo
				StatieMeteo statie;
				statie.setLocalitate(Locatie);
				//citim temperaturile
				for (int j = 0; j < nrInregistrari; j++) {
					float temperatura;
					file >> temperatura;
					int ora;
					file >> ora;
					statie.setTemperatura(ora, temperatura);
				}
				this->statii[i] = statie;
			}
			file.close();
		}
		else
		{
			cout <<endl << "Fisierul nu s-a deschis";
			throw exception();
		}
	}

	//metoda pentru serializare - salvare date in fisier binar
	void salvareDate(char* numeFisier) {
		ofstream backup;
		backup.open(numeFisier, ios::out | ios::binary);
		if (backup.is_open()) {
			//serializare locatie
			//NU MERGE backup.write(this->tara, sizeof(Meteo::tara));
			
			//solutia 1
			char buffer[100];
			strcpy(buffer, this->tara);
			backup.write(buffer, sizeof(buffer));

			////solutia 2
			//int nrCaractere = strlen(this->tara)+1;
			//backup.write((char*) &nrCaractere, sizeof(int));
			//backup.write(this->tara, sizeof(char)*nrCaractere);

			//numarul de statii
			backup.write((char*)&this->nrStatii, 
				sizeof(int));
			//statiile
			for (int i = 0; i < this->nrStatii; i++) {
				this->statii[i].salvareDate(backup);
			}
			backup.close();
		}
	}
};

void generareRaport(Meteo meteo, char* numeRaport) {
	ofstream raport;
	raport.open(numeRaport, ios::out | ios::trunc);
	if (raport.is_open()) {
		raport << "\t\t Raport meteo";
		raport << endl << "Lista orase";
		for (int i = 0; i < meteo.nrStatii; i++) {
			raport << endl << meteo.statii[i].getLocalitate();
		}
		raport << endl << "Info";
		for (int i = 0; i < meteo.nrStatii; i++) {
			raport << meteo.statii[i];
		}
	}
	raport.close();
}

int main()
{
	StatieMeteo statie1("Bucuresti");
	StatieMeteo statie2("Ploiesti");

	statie1.setTemperatura(7, 10.56);
	statie1.setTemperatura(10, 14.2);

	statie2.setTemperatura(9, 12.9);
	statie1.setTemperatura(3, 6.2);

	cout << statie1 << statie2;

	Meteo meteo;
	meteo.nrStatii = 2;
	meteo.statii[0] = statie1;
	meteo.statii[1] = statie2;
	
	meteo.setTara("Romania");

	generareRaport(meteo, "Temperaturi Romania.txt");

	meteo.incarcaFisierText("DateIntrare.txt");
	generareRaport(meteo, "RaportNou.txt");
	cout << endl << "*********** Date noi ******";
	for (int i = 0; i < meteo.nrStatii; i++)
		cout << endl << meteo.statii[i];


	meteo.salvareDate("backup.dat");

}