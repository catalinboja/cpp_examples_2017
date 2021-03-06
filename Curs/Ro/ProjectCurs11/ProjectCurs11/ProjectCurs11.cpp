// ProjectCurs11.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

class Jucarie {
protected:
	char denumire[50];
	int varstaMinima;
	float pret;
public:
	Jucarie() {
		cout << endl << "Apel constructor Jucarie";
		strcpy(this->denumire, "");
		this->varstaMinima = 3;
		this->pret = 0;
	}
	Jucarie(const char* Denumire, int Varsta, float Pret) {
		cout << endl << "Apel constructor cu argumente Jucarie";
		strcpy(this->denumire, Denumire);
		this->varstaMinima = Varsta;
		this->pret = Pret;
	}
	float getPret() {
		return this->pret;
	}

	void afisare(){
		cout << endl << "Jucaria " << this->denumire <<
			" are varsta minima recomandata " << this->varstaMinima
			<< " si are pretul " << this->pret;
	}
};


class JucarieDiscount:public Jucarie {
	float discount;

public:
	JucarieDiscount():Jucarie("",2,0) {
		cout << endl << "Apel constructor JucarieDiscount";
		//strcpy(this->denumire, "");
		//this->varstaMinima = 3;
		//this->pret = 0;
		this->discount = 0;
	}

	JucarieDiscount(const char* Denumire,
		int Varsta, float Pret, float Discount) 
		:Jucarie(Denumire,Varsta,Pret){
		this->discount = Discount;
	}

	//supradefinire metode din baza
	void afisare() {
		cout << endl << "Jucaria " << this->denumire <<
			" are varsta minima recomandata " << this->varstaMinima
			<< " si are pretul " << this->pret;
		cout << endl << " si are discount de "
			<< this->discount << "%";
	}

	void afisare2() {
		cout << endl << "Jucaria " << this->denumire <<
			" are varsta minima recomandata " << this->varstaMinima
			<< " si are pretul " << this->pret;
		cout << endl << " si are discount de "
			<< this->discount << "%";
	}
};

class Robot :public Jucarie {
	char sistemOperare[50];
};


int main()
{
	//Jucarie j1;
	Jucarie j2("Masina teleghidata", 10, 150);

	//j1.afisare();
	j2.afisare();

	JucarieDiscount jd1;
	jd1.afisare();
	JucarieDiscount jd2("Papusa Maria", 3, 180, 15);
	jd2.afisare();
	jd2.afisare2();

	//j2 = jd2;	//up casting
	//j2.afisare();

	Jucarie catalogJucarii[3];
	catalogJucarii[0] = j2;
	catalogJucarii[1] = jd2;
	catalogJucarii[2] = Robot();

	cout << endl << "******* vector obiecte";
	for (int i = 0; i < 3; i++)
		catalogJucarii[i].afisare();

	Jucarie* catalogJucarii2[3];
	catalogJucarii2[0] = &j2;
	catalogJucarii2[1] = &jd2;
	catalogJucarii2[2] = new Robot();

	cout << endl << "******* vector pointeri";
	for (int i = 0; i < 3; i++)
		catalogJucarii2[i]->afisare();
}

